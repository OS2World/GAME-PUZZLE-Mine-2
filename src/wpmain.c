
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mine2.h"
#include "7segment.h"

extern HAB      hAnchorBlock;
extern HWND     hwndFrame;
extern HWND     hwndClient;
extern HWND     hwndCount;
extern HWND     hwndTime;
extern HWND     hwndButton;
extern HWND     hwndField;
extern HWND     hwndMenu;
extern HWND     hwndHelp;
extern HPOINTER hPointer;
extern INIDATA  IniData;
extern SIZEL    sizelCell;
extern SIZEL    sizelBmpCell;
extern int      save_on_exit;
extern int      current_lang;
extern int      bBackgrndRun;

#define DB_RAISED    0x0400
#define DB_DEPRESSED 0x0800

static INT  iAktiveGameIndex = -1;
static BOOL bGamePaused      = FALSE;
static BOOL bTimerRunning    = FALSE;
static BOOL bAutopaused      = FALSE;

/* ------------------------------------------------------------------ */
MRESULT EXPENTRY wpMain( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
/* ------------------------------------------------------------------ */

    MRESULT mReturn;

    switch ( msg ) {

        /* ---------------------------------------------------------- */
        case WM_CREATE : {
        /* ---------------------------------------------------------- */

            CHAR  pszID[ 8 ];
            HINI  hIni;
            ULONG ulBufferMax = sizeof( IniData );

            IniData.Big = (USHORT)(( WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN ) > 1000 )
                                   ? (USHORT)-1 : 0 );

            if (( hIni = PrfOpenProfile( hAnchorBlock, INI_FILENAME ))
                != NULLHANDLE ) {
                ULONG ulSz;
                PrfQueryProfileData( hIni, INI_APPLNAME, INI_KEYNAME,
                                     &IniData, &ulBufferMax );

                /* Load extra settings */
                ulSz = sizeof( int );
                PrfQueryProfileData( hIni, INI_APPLNAME, INI_KEY_SAVEONEXIT,
                                     &save_on_exit, &ulSz );
                ulSz = sizeof( int );
                PrfQueryProfileData( hIni, INI_APPLNAME, INI_KEY_LANGUAGE,
                                     &current_lang, &ulSz );
                ulSz = sizeof( int );
                PrfQueryProfileData( hIni, INI_APPLNAME, INI_KEY_BACKGRND,
                                     &bBackgrndRun, &ulSz );

                PrfCloseProfile( hIni );
            }

            /* Migrate/validate GameType from old ICC-built INI if needed */
            if ( IniData.GameType == 2111 ) IniData.GameType = IDM_NOVICE;
            else if ( IniData.GameType == 2112 ) IniData.GameType = IDM_ADVANCED;
            else if ( IniData.GameType == 2113 ) IniData.GameType = IDM_PROFESSIONAL;
            else if ( IniData.GameType == 2114 ) IniData.GameType = ID_MENU_USERDEF;
            else if ( IniData.GameType != IDM_NOVICE &&
                      IniData.GameType != IDM_ADVANCED &&
                      IniData.GameType != IDM_PROFESSIONAL &&
                      IniData.GameType != ID_MENU_USERDEF )
                IniData.GameType = IDM_ADVANCED;

            /* Clamp settings */
            if ( save_on_exit < 0 || save_on_exit > 1 ) save_on_exit = 1;
            if ( current_lang < 0 || current_lang >= LANG_COUNT ) current_lang = LANG_EN;
            if ( bBackgrndRun < 0 || bBackgrndRun > 1 ) bBackgrndRun = 0;

            if ( IniData.Big ) {
                sizelCell.cx    = CELL_CX_BIG;
                sizelCell.cy    = CELL_CY_BIG;
                sizelBmpCell.cx = BMP_CELL_CX_BIG;
                sizelBmpCell.cy = BMP_CELL_CY_BIG;
            } else {
                sizelCell.cx    = CELL_CX;
                sizelCell.cy    = CELL_CY;
                sizelBmpCell.cx = BMP_CELL_CX;
                sizelBmpCell.cy = BMP_CELL_CY;
            }

            /* Create child windows */
            hwndCount = WinCreateWindow( hwnd, CLASS7SEG, NULL, WS_VISIBLE,
                                         0L, 0L,
                                         SIZE_BMP_CX * AKTIV_DIGITS, SIZE_BMP_CY,
                                         hwnd, HWND_TOP, ID_WIN_COUNT, NULL, NULL );
            hwndTime  = WinCreateWindow( hwnd, CLASS7SEG, NULL, WS_VISIBLE,
                                         0L, 0L,
                                         SIZE_BMP_CX * AKTIV_DIGITS, SIZE_BMP_CY,
                                         hwnd, HWND_TOP, ID_WIN_TIME, NULL, NULL );

            sprintf( pszID, "#%d", ID_BMP_BUTTON_NORMAL );
            hwndButton = WinCreateWindow( hwnd, WC_BUTTON, pszID,
                                          WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP | BS_NOPOINTERFOCUS,
                                          0L, 0L,
                                          SIZE_BMP_CY + 4, SIZE_BMP_CY + 4,
                                          hwnd, HWND_TOP, ID_WIN_BUTTON, NULL, NULL );

            hwndField  = WinCreateWindow( hwnd, WC_MINEFIELD, NULL,
                                          WS_VISIBLE | WS_DISABLED,
                                          0L, 0L, 0L, 0L,
                                          hwnd, HWND_TOP, ID_WIN_FIELD, NULL, NULL );

            hPointer = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, IniData.Pointer );

            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_DESTROY : {
        /* ---------------------------------------------------------- */

            WinDestroyPointer( hPointer );
            WinDestroyWindow( hwndField );
            WinDestroyWindow( hwndButton );
            WinDestroyWindow( hwndTime );
            WinDestroyWindow( hwndCount );

            mReturn = MRFROMLONG( 0L );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_PAINT : {
        /* ---------------------------------------------------------- */

            RECTL rectl = { 0L, 0L, 0L, 0L };
            HPS hps = WinBeginPaint( hwnd, NULLHANDLE, &rectl );
            WinFillRect( hps, &rectl, CLR_PALEGRAY );
            WinQueryWindowRect( hwnd, &rectl );
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_RAISED );
            rectl.xLeft   += 12L;
            rectl.xRight  -= 12L;
            rectl.yBottom += 12L;
            rectl.yTop    -= 63L;
            WinDrawBorder( hps, &rectl, 4L, 4L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );
            rectl.yBottom  = rectl.yTop + 8;
            rectl.yTop    += 51L;
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );
            WinQueryWindowRect( hwndCount, &rectl );
            rectl.xLeft--; rectl.xRight++; rectl.yBottom--; rectl.yTop++;
            WinMapWindowPoints( hwndCount, hwnd, (PVOID)&rectl, 2L );
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );
            WinQueryWindowRect( hwndTime, &rectl );
            rectl.xLeft--; rectl.xRight++; rectl.yBottom--; rectl.yTop++;
            WinMapWindowPoints( hwndTime, hwnd, (PVOID)&rectl, 2L );
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );
            WinEndPaint( hps );

            mReturn = MRFROMLONG( 0L );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_COMMAND : {
        /* ---------------------------------------------------------- */

            USHORT usCommand = SHORT1FROMMP( mp1 );

            switch ( usCommand ) {

                /* --- pointer selection --------------------------------- */
                case ID_POINTER_1 :
                case ID_POINTER_2 :
                case ID_POINTER_3 :
                case ID_POINTER_4 : {
                    IniData.Pointer = usCommand;
                    WinDestroyPointer( hPointer );
                    hPointer = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, usCommand );
                    break;
                }

                /* --- dialogs ------------------------------------------- */
                case IDM_ABOUT : {
                    DlgAbout( hwnd );
                    break;
                }

                case IDM_HOF : {
                    DlgHallOfFame( hwnd, -1 );
                    break;
                }

                case IDM_USERDLG : {
                    if ( DlgUserDef( hwnd )) {
                        WinPostMsg( hwnd, WM_COMMAND,
                                    MPFROM2SHORT( ID_MENU_USERDEF, TRUE ), 0 );
                    }
                    break;
                }

                case IDM_STATISTIC : {
                    DlgStatistic( hwnd );
                    break;
                }

                /* --- exit ---------------------------------------------- */
                case IDM_EXIT : {
                    WinPostMsg( hwnd, WM_CLOSE, 0, 0 );
                    break;
                }

                /* --- new / restart game --------------------------------- */
                case IDM_NEW    :
                case ID_WIN_BUTTON : {
                    bGamePaused = FALSE;
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( IDM_PAUSE, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED, 0 ));
                    WinPostMsg( hwnd, WM_COMMAND,
                                MPFROM2SHORT( IniData.GameType, 0 ), 0 );
                    break;
                }

                /* --- quit / give up game ------------------------------- */
                case IDM_QUIT : {
                    if ( iAktiveGameIndex >= 0 ) {
                        WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                        bTimerRunning = FALSE;
                        bAutopaused   = FALSE;
                        WinSetWindowULong( hwndTime, QWL_VALUE, 0L );
                        WinEnableWindow( hwndField, FALSE );
                        bGamePaused = FALSE;
                        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                    MPFROM2SHORT( IDM_PAUSE, TRUE ),
                                    MPFROM2SHORT( MIA_CHECKED, 0 ));
                        WinPostMsg( hwndField, WM_USER_INIT, 0, 0 );
                    }
                    break;
                }

                /* --- pause game ---------------------------------------- */
                case IDM_PAUSE : {
                    bAutopaused = FALSE;   /* user takes over from any auto-pause */
                    bGamePaused ^= 1;
                    if ( bGamePaused ) {
                        WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                        WinEnableWindow( hwndField, FALSE );
                    } else {
                        WinStartTimer( hAnchorBlock, hwnd, ID_TIMER_GAME, 1000L );
                        WinEnableWindow( hwndField, TRUE );
                    }
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( IDM_PAUSE, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED,
                                              bGamePaused ? MIA_CHECKED : 0 ));
                    break;
                }

                /* --- difficulty levels ---------------------------------- */
                case IDM_NOVICE :
                case IDM_ADVANCED :
                case IDM_PROFESSIONAL : {

                    bGamePaused = FALSE;
                    WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                    WinSetWindowULong( hwndTime, QWL_VALUE, 0L );
                    WinEnableWindow( hwndField, FALSE );

                    if ( IniData.GameType != usCommand ) {
                        /* uncheck old level */
                        USHORT usOldCheck = ( IniData.GameType == ID_MENU_USERDEF )
                                            ? IDM_USERDLG : IniData.GameType;
                        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                    MPFROM2SHORT( usOldCheck, TRUE ),
                                    MPFROM2SHORT( MIA_CHECKED, 0 ));
                        IniData.GameType = usCommand;
                        if ( IniData.GameType == IDM_NOVICE ) {
                            iAktiveGameIndex = 0;
                            IniData.cx = 8; IniData.cy = 8; IniData.Mines = 10;
                        } else if ( IniData.GameType == IDM_ADVANCED ) {
                            iAktiveGameIndex = 1;
                            IniData.cx = 16; IniData.cy = 16; IniData.Mines = 40;
                        } else { /* IDM_PROFESSIONAL */
                            iAktiveGameIndex = 2;
                            IniData.cx = 30; IniData.cy = 16; IniData.Mines = 99;
                        }
                        /* check new level */
                        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                    MPFROM2SHORT( IniData.GameType, TRUE ),
                                    MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ));
                        Resize( IniData.cx, IniData.cy );
                        WinInvalidateRect( hwndClient, NULL, TRUE );
                    } else {
                        WinInvalidateRect( hwndField, NULL, TRUE );
                        WinInvalidateRect( hwndTime,  NULL, TRUE );
                    }
                    WinPostMsg( hwndField, WM_USER_INIT, 0, 0 );
                    break;
                }

                /* --- user-defined (posted internally) ------------------- */
                case ID_MENU_USERDEF : {

                    bGamePaused = FALSE;
                    WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                    WinSetWindowULong( hwndTime, QWL_VALUE, 0L );
                    WinEnableWindow( hwndField, FALSE );

                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( IniData.GameType, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED, 0 ));
                    IniData.GameType  = ID_MENU_USERDEF;
                    iAktiveGameIndex  = 3;
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( IDM_USERDLG, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ));

                    if ( SHORT2FROMMP( mp1 )) {
                        Resize( IniData.cx, IniData.cy );
                        WinInvalidateRect( hwndClient, NULL, TRUE );
                    } else {
                        WinInvalidateRect( hwndField, NULL, TRUE );
                        WinInvalidateRect( hwndTime,  NULL, TRUE );
                    }
                    WinPostMsg( hwndField, WM_USER_INIT, 0, 0 );
                    break;
                }

                /* --- special options ------------------------------------ */
                case IDM_SPECIAL_BIG : {
                    IniData.Big = (USHORT)~IniData.Big;
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( usCommand, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED, IniData.Big ));
                    sizelCell.cx    = IniData.Big ? CELL_CX_BIG    : CELL_CX;
                    sizelCell.cy    = IniData.Big ? CELL_CY_BIG    : CELL_CY;
                    sizelBmpCell.cx = IniData.Big ? BMP_CELL_CX_BIG : BMP_CELL_CX;
                    sizelBmpCell.cy = IniData.Big ? BMP_CELL_CY_BIG : BMP_CELL_CY;
                    WinSendMsg( hwndField, WM_USER_SET_BITMAP,
                                MPFROMSHORT( IniData.Big ), 0 );
                    Resize( IniData.cx, IniData.cy );
                    WinInvalidateRect( hwndClient, NULL, TRUE );
                    break;
                }

                case IDM_SPECIAL_SAV : {
                    IniData.Safety = (USHORT)~IniData.Safety;
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( usCommand, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED, IniData.Safety ));
                    break;
                }

                case IDM_SPECIAL_QUE : {
                    IniData.Questionmark = (USHORT)~IniData.Questionmark;
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( usCommand, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED, IniData.Questionmark ));
                    break;
                }

                /* --- options ------------------------------------------- */
                case IDM_BACKGRND : {
                    bBackgrndRun ^= 1;
                    if ( bBackgrndRun && bAutopaused ) {
                        bAutopaused = FALSE;
                        if ( !bGamePaused ) {
                            WinStartTimer( hAnchorBlock, hwnd, ID_TIMER_GAME, 1000L );
                            WinEnableWindow( hwndField, TRUE );
                        }
                    }
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( IDM_BACKGRND, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED,
                                              bBackgrndRun ? MIA_CHECKED : 0 ));
                    break;
                }

                case IDM_SAVEONEXIT : {
                    save_on_exit ^= 1;
                    WinSendMsg( hwndMenu, MM_SETITEMATTR,
                                MPFROM2SHORT( IDM_SAVEONEXIT, TRUE ),
                                MPFROM2SHORT( MIA_CHECKED,
                                              save_on_exit ? MIA_CHECKED : 0 ));
                    break;
                }

                /* --- language ------------------------------------------ */
                case IDM_LANG_EN :
                case IDM_LANG_ES :
                case IDM_LANG_NL :
                case IDM_LANG_DE :
                case IDM_LANG_FR :
                case IDM_LANG_IT : {
                    set_language( usCommand - IDM_LANG_EN );
                    HelpReload();
                    break;
                }

                /* --- help ---------------------------------------------- */
                case IDM_HELPINDEX : {
                    if ( hwndHelp != NULLHANDLE )
                        WinSendMsg( hwndHelp, HM_HELP_INDEX, 0, 0 );
                    break;
                }

                case IDM_HELPGENERAL : {
                    if ( hwndHelp != NULLHANDLE )
                        WinSendMsg( hwndHelp, HM_EXT_HELP, 0, 0 );
                    break;
                }

                case IDM_HELPKEYS : {
                    if ( hwndHelp != NULLHANDLE )
                        WinSendMsg( hwndHelp, HM_KEYS_HELP, 0, 0 );
                    break;
                }

                case IDM_HELPUSING : {
                    if ( hwndHelp != NULLHANDLE )
                        WinSendMsg( hwndHelp, HM_DISPLAY_HELP, 0, 0 );
                    break;
                }

                default : break;
            }

            mReturn = MRFROMLONG( 0L );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_ACTIVATE : {
        /* ---------------------------------------------------------- */
            if ( !bBackgrndRun ) {
                BOOL fActive = (BOOL)SHORT1FROMMP( mp1 );
                if ( !fActive ) {
                    /* deactivated: auto-pause if a timed game is running */
                    if ( bTimerRunning && !bGamePaused ) {
                        WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                        WinEnableWindow( hwndField, FALSE );
                        bAutopaused = TRUE;
                    }
                } else if ( bAutopaused ) {
                    /* reactivated: undo auto-pause */
                    bAutopaused = FALSE;
                    if ( !bGamePaused ) {
                        WinStartTimer( hAnchorBlock, hwnd, ID_TIMER_GAME, 1000L );
                        WinEnableWindow( hwndField, TRUE );
                    }
                }
            }
            mReturn = WinDefWindowProc( hwnd, msg, mp1, mp2 );
            break;
        }

        /* ---------------------------------------------------------- */
        case HM_QUERY_KEYS_HELP : {
        /* ---------------------------------------------------------- */
            mReturn = MRFROMSHORT( HELP_PAGE_KEYS );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_USER_START : {
        /* ---------------------------------------------------------- */
            WinStartTimer( hAnchorBlock, hwnd, ID_TIMER_GAME, 1000L );
            bTimerRunning = TRUE;
            bAutopaused   = FALSE;
            IniData.GamesStarted[ iAktiveGameIndex ]++;
            if ( IniData.FirstGame.year == 0 ) {
                DATETIME dt;
                DosGetDateTime( &dt );
                IniData.FirstGame.day   = dt.day;
                IniData.FirstGame.month = dt.month;
                IniData.FirstGame.year  = (USHORT)( dt.year - 1966 );
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_USER_END : {
        /* ---------------------------------------------------------- */
            {
                USHORT usTime;
                WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                bTimerRunning = FALSE;
                bAutopaused   = FALSE;
                bGamePaused   = FALSE;
                WinSendMsg( hwndMenu, MM_SETITEMATTR,
                            MPFROM2SHORT( IDM_PAUSE, TRUE ),
                            MPFROM2SHORT( MIA_CHECKED, 0 ));
                usTime = (USHORT)WinQueryWindowULong( hwndTime, QWL_VALUE );
                if ( SHORT1FROMMP( mp1 )) {                    /* won */
                    IniData.GamesWon[ iAktiveGameIndex ]++;
                    if (( iAktiveGameIndex < 3 ) &&
                        ( IniData.HofTime[ iAktiveGameIndex ] > usTime )) {
                        IniData.HofTime[ iAktiveGameIndex ] = usTime;
                        strcpy( IniData.HofName[ iAktiveGameIndex ], PSZ_HOF_UNKNOWN );
                        DlgHallOfFame( hwnd, iAktiveGameIndex );
                    }
                } else {                                        /* lost */
                    IniData.GamesLost[ iAktiveGameIndex ]++;
                }
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        /* ---------------------------------------------------------- */
        case WM_TIMER : {
        /* ---------------------------------------------------------- */
            {
                BOOL bMinimized = (BOOL)( WinQueryWindowULong( hwndFrame, QWL_STYLE )
                                          & WS_MINIMIZED );
                if ( !bMinimized || bBackgrndRun ) {
                    LONG lValue = (LONG)WinQueryWindowULong( hwndTime, QWL_VALUE );
                    WinSetWindowULong( hwndTime, QWL_VALUE,
                                       (ULONG)min( lValue + 1L, 999L ));
                    WinInvalidateRect( hwndTime, NULL, FALSE );
                    IniData.PlayTime[ iAktiveGameIndex ]++;
                    if ( IniData.GamesStarted[ iAktiveGameIndex ] == 0 ) {
                        DATETIME dt;
                        DosGetDateTime( &dt );
                        IniData.FirstGame.day   = dt.day;
                        IniData.FirstGame.month = dt.month;
                        IniData.FirstGame.year  = (USHORT)( dt.year - 1966 );
                        IniData.GamesStarted[ iAktiveGameIndex ] = 1;
                    }
                }
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        /* ---------------------------------------------------------- */
        default : {
        /* ---------------------------------------------------------- */
            mReturn = WinDefWindowProc( hwnd, msg, mp1, mp2 );
            break;
        }

    }

    return mReturn;
}

/* ------------------------------------------------------------------ */
VOID Resize( INT CellX, INT CellY ) {
/* ------------------------------------------------------------------ */

    RECTL  rectl;
    SIZEL  sizel, screen;
    POINTL pointl;
    SWP    swp[ 4 ];

    screen.cx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
    screen.cy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

    rectl.xLeft   = 0L;
    rectl.yBottom = 0L;
    rectl.xRight  = CellX * sizelCell.cx + 2 * 16L;
    rectl.yTop    = CellY * sizelCell.cy + 2 * 16L + 51L;

    swp[ 0 ].hwnd = hwndCount;
    swp[ 0 ].fl   = SWP_MOVE;
    swp[ 0 ].x    = rectl.xRight / 4 - SIZE_BMP_CX * AKTIV_DIGITS / 2L;
    swp[ 0 ].y    = rectl.yTop - 35L - SIZE_BMP_CY / 2L;

    swp[ 1 ].hwnd = hwndTime;
    swp[ 1 ].fl   = SWP_MOVE;
    swp[ 1 ].x    = 3 * rectl.xRight / 4 - SIZE_BMP_CX * AKTIV_DIGITS / 2L;
    swp[ 1 ].y    = rectl.yTop - 35L - SIZE_BMP_CY / 2L;

    swp[ 2 ].hwnd = hwndButton;
    swp[ 2 ].fl   = SWP_MOVE;
    swp[ 2 ].x    = rectl.xRight / 2 - ( SIZE_BMP_CY + 4L ) / 2L;
    swp[ 2 ].y    = rectl.yTop - 35L - ( SIZE_BMP_CY + 4L ) / 2L;

    swp[ 3 ].hwnd = hwndField;
    swp[ 3 ].fl   = SWP_MOVE | SWP_SIZE;
    swp[ 3 ].x    = 16L;
    swp[ 3 ].y    = 16L;
    swp[ 3 ].cx   = CellX * sizelCell.cx;
    swp[ 3 ].cy   = CellY * sizelCell.cy;

    WinCalcFrameRect( hwndFrame, &rectl, FALSE );
    sizel.cx = rectl.xRight - rectl.xLeft;
    sizel.cy = rectl.yTop   - rectl.yBottom;

    WinQueryWindowRect( hwndFrame, &rectl );
    WinMapWindowPoints( hwndFrame, HWND_DESKTOP, (PVOID)&rectl, 2L );

    pointl.x = rectl.xLeft;
    pointl.y = rectl.yTop - sizel.cy;

    pointl.y = max( 0, pointl.y );
    pointl.x = min( pointl.x, screen.cx - sizel.cx );
    pointl.y = min( pointl.y, screen.cy - sizel.cy );
    pointl.x = max( 0, pointl.x );

    WinSetWindowPos( hwndFrame, NULLHANDLE,
                     pointl.x, pointl.y,
                     sizel.cx, sizel.cy,
                     SWP_SIZE | SWP_MOVE );

    WinSetMultWindowPos( hAnchorBlock, swp, 4L );
}

/* EOF */
