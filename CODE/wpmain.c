#pragma strings( readonly )

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mine2.h"
#include "7segment.h"

extern HAB  hAnchorBlock;
extern HWND hwndFrame;
extern HWND hwndClient;
extern HWND hwndCount;
extern HWND hwndTime;
extern HWND hwndButton;
extern HWND hwndField;
extern HWND hwndMenu;
extern HWND hwndHelp;
extern HPOINTER hPointer;
extern INIDATA IniData;
extern SIZEL   sizelCell;

#define DB_RAISED       0x0400
#define DB_DEPRESSED    0x0800

INT iAktiveGameIndex = -1;

// ===========================================================================================================
MRESULT EXPENTRY wpMain( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
// ===========================================================================================================

    MRESULT mReturn;

    switch ( msg ) {

        //----------------------------------------------------------------------------------------------------
        case WM_CREATE : {
        //----------------------------------------------------------------------------------------------------

            CHAR  pszID[ 8 ];
            HINI  hIni;
            ULONG ulBufferMax = sizeof( IniData );

            IniData.Big = (USHORT)(( WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN ) > 1000 ) ? -1 : 0 );

            if (( hIni = PrfOpenProfile( hAnchorBlock                       // Anchorblock handle
                                       , INI_FILENAME )) == NULLHANDLE ) {  // Userprofile file name
                ;
            } else {
                PrfQueryProfileData( hIni               // Initializationfile handle
                                   , INI_APPLNAME       // Application name
                                   , INI_KEYNAME        // Key name
                                   , &IniData           // Value data
                                   , &ulBufferMax );    // Size of value data
                PrfCloseProfile( hIni );                // Initializationfile handle
            } /* endif */
            if ( IniData.Big ) {
                sizelCell.cx = CELL_CX_BIG;
                sizelCell.cy = CELL_CY_BIG;
            } else {
                sizelCell.cx = CELL_CX;
                sizelCell.cy = CELL_CY;
            } /* endif */

            hwndCount = WinCreateWindow( hwnd           // Parentwindow handle 
                           , CLASS7SEG      // Registered class name 
                           , NULL           // Window text 
                           , WS_VISIBLE     // Window style 
                           , 0L             // x-coordinate of window position 
                           , 0L             // y-coordinate of window position 
                           , SIZE_BMP_CX * AKTIV_DIGITS  // Width of window, in window coordinates 
                           , SIZE_BMP_CY                 // Height of window, in window coordinates 
                           , hwnd           // Ownerwindow handle 
                           , HWND_TOP       // Sibling-window handle 
                           , ID_WIN_COUNT   // Window identifier 
                           , NULL           // Pointer to control data 
                           , NULL );        // Presentation parameters 
            hwndTime = WinCreateWindow( hwnd           // Parentwindow handle 
                           , CLASS7SEG      // Registered class name 
                           , NULL           // Window text 
                           , WS_VISIBLE     // Window style 
                           , 0L             // x-coordinate of window position 
                           , 0L             // y-coordinate of window position 
                           , SIZE_BMP_CX * AKTIV_DIGITS  // Width of window, in window coordinates 
                           , SIZE_BMP_CY                 // Height of window, in window coordinates 
                           , hwnd           // Ownerwindow handle 
                           , HWND_TOP       // Sibling-window handle 
                           , ID_WIN_TIME    // Window identifier 
                           , NULL           // Pointer to control data 
                           , NULL );        // Presentation parameters 
            sprintf( pszID, "#%d", ID_BMP_BUTTON_NORMAL );
            hwndButton = WinCreateWindow( hwnd           // Parentwindow handle 
                           , WC_BUTTON     // Registered class name 
                           , pszID         // Window text 
                           , WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP | BS_NOPOINTERFOCUS  // Window style 
                           , 0L             // x-coordinate of window position 
                           , 0L             // y-coordinate of window position 
                           , SIZE_BMP_CY + 4   // Width of window, in window coordinates 
                           , SIZE_BMP_CY + 4   // Height of window, in window coordinates 
                           , hwnd           // Ownerwindow handle 
                           , HWND_TOP       // Sibling-window handle 
                           , ID_WIN_BUTTON  // Window identifier 
                           , NULL           // Pointer to control data 
                           , NULL );        // Presentation parameters 
            hwndField = WinCreateWindow( hwnd           // Parentwindow handle 
                           , WC_MINEFIELD   // Registered class name 
                           , NULL           // Window text 
                           , WS_VISIBLE | WS_DISABLED // Window style 
                           , 0L             // x-coordinate of window position 
                           , 0L             // y-coordinate of window position 
                           , 0L             // Width of window, in window coordinates 
                           , 0L             // Height of window, in window coordinates 
                           , hwnd           // Ownerwindow handle 
                           , HWND_TOP       // Sibling-window handle 
                           , ID_WIN_FIELD   // Window identifier 
                           , NULL           // Pointer to control data 
                           , NULL );        // Presentation parameters 
            hPointer = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, IniData.Pointer );
            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        //----------------------------------------------------------------------------------------------------
        case WM_DESTROY : {
        //----------------------------------------------------------------------------------------------------

            HINI  hIni;
            ULONG ulBufferMax = sizeof( IniData );
            RECTL rectl;

            if ( ! ( WinQueryWindowULong( hwndFrame, QWL_STYLE ) & WS_MINIMIZED )) {
                if (( hIni = PrfOpenProfile( hAnchorBlock                       // Anchorblock handle
                                           , INI_FILENAME )) != NULLHANDLE ) {  // Userprofile file name
                    WinQueryWindowRect( hwndFrame, &rectl );
                    WinMapWindowPoints( hwndFrame, HWND_DESKTOP, (PVOID)&rectl, 2L );
                    IniData.x = (USHORT)rectl.xLeft;
                    IniData.y = (USHORT)rectl.yTop;
                    PrfWriteProfileData( hIni               // Initializationfile handle
                                       , INI_APPLNAME       // Application name
                                       , INI_KEYNAME        // Key name
                                       , &IniData           // Value data
                                       , ulBufferMax );     // Size of value data
                    PrfCloseProfile( hIni );                // Initializationfile handle
                } /* endif */
            } /* endif */

            WinDestroyPointer( hPointer );
            WinDestroyWindow( hwndField );
            WinDestroyWindow( hwndButton );
            WinDestroyWindow( hwndTime );
            WinDestroyWindow( hwndCount );

            mReturn = MRFROMLONG( 0L );
            break;
        }


        //----------------------------------------------------------------------------------------------------
        case WM_PAINT : {
        //----------------------------------------------------------------------------------------------------

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
            rectl.yBottom = rectl.yTop + 8;
            rectl.yTop    += 51L;
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );
            WinQueryWindowRect( hwndCount, &rectl );
            rectl.xLeft   -= 1L;
            rectl.xRight  += 1L;
            rectl.yBottom -= 1L;
            rectl.yTop    += 1L;
            WinMapWindowPoints( hwndCount, hwnd, (PVOID)&rectl, 2L );
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );          
            WinQueryWindowRect( hwndTime, &rectl );
            rectl.xLeft   -= 1L;
            rectl.xRight  += 1L;
            rectl.yBottom -= 1L;
            rectl.yTop    += 1L;
            WinMapWindowPoints( hwndTime, hwnd, (PVOID)&rectl, 2L );
            WinDrawBorder( hps, &rectl, 1L, 1L, CLR_WHITE, CLR_DARKGRAY, DB_DEPRESSED );          
            WinEndPaint( hps );

            mReturn = MRFROMLONG( 0L );
            break;
        }

        //----------------------------------------------------------------------------------------------------
        case WM_COMMAND : {
        //----------------------------------------------------------------------------------------------------

            USHORT usCommand = SHORT1FROMMP( mp1 );

            switch ( usCommand ) {

                case ID_KEY_ESCAPE : {
                    WinSetWindowPos( hwndFrame   // Window handle
                                   , NULLHANDLE  // Relative window placement order
                                   , 0L          // Window position, x-coordinate
                                   , 0L          // Window position, y-coordinate
                                   , 0L          // Window size x
                                   , 0L          // Window size y
                                   , (ULONG)( WinQueryWindowULong( hwndFrame, QWL_STYLE ) & WS_MINIMIZED ? SWP_RESTORE : SWP_MINIMIZE )); // Window positioning options
                    break;
                }

                case ID_POINTER_1 :
                case ID_POINTER_2 :
                case ID_POINTER_3 :
                case ID_POINTER_4 : {
                    IniData.Pointer = usCommand;
                    WinDestroyPointer( hPointer );
                    hPointer = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, usCommand );
                    break;
                }

                case ID_MENU_ABOUT : {
                    DlgAbout( hwnd );
                    break;
                }

                case ID_MENU_HALL_OF_FAME : {
                    DlgHallOfFame( hwnd, -1 );
                    break;
                }

                case ID_MENU_USERDLG : {
                    if ( DlgUserDef( hwnd )) {
                        WinPostMsg( hwnd, WM_COMMAND, MPFROM2SHORT( ID_MENU_USERDEF, TRUE ), MPFROMLONG( 0L ));
                    } /* endif */
                    break;
                }

                case ID_MENU_STATISTIC :
                case ID_KEY_STATISTIC : {
                    DlgStatistic( hwnd );
                    break;
                }

                case ID_MENU_EXIT :
                case ID_KEY_EXIT : {
                    WinPostMsg( hwnd, WM_CLOSE, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_NEWGAME :
                case ID_KEY_NEW      : 
                case ID_WIN_BUTTON   : {
                    WinPostMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IniData.GameType, 0 ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_NOVICE :
                case ID_MENU_ADVANCED :
                case ID_MENU_PROFESSIONAL : {

                    WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                    WinSetWindowULong( hwndTime,  QWL_VALUE,  0L );
                    WinEnableWindow( hwndField, FALSE );
                    if ( IniData.GameType != usCommand ) {
                        WinSendMsg( hwndMenu
                                  , MM_SETITEMATTR
                                  , MPFROM2SHORT( IniData.GameType == ID_MENU_USERDEF ? ID_MENU_USERDLG : IniData.GameType, TRUE )
                                  , MPFROM2SHORT( MIA_CHECKED, FALSE ));
                        IniData.GameType = usCommand;
                        if ( IniData.GameType == ID_MENU_NOVICE ) {
                            iAktiveGameIndex =  0;
                            IniData.cx       =  8;
                            IniData.cy       =  8;
                            IniData.Mines    = 10;
                        } else if ( IniData.GameType == ID_MENU_ADVANCED ) {
                            iAktiveGameIndex =  1;
                            IniData.cx       = 16;
                            IniData.cy       = 16;
                            IniData.Mines    = 40;
                        } else if ( IniData.GameType == ID_MENU_PROFESSIONAL ) {
                            iAktiveGameIndex =  2;
                            IniData.cx       = 30;
                            IniData.cy       = 16;
                            IniData.Mines    = 99;
                        } else {
                            ;
                        } /* endif */
                        WinSendMsg( hwndMenu
                                  , MM_SETITEMATTR
                                  , MPFROM2SHORT( IniData.GameType, TRUE )
                                  , MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ));
                        Resize( IniData.cx, IniData.cy );
                        WinInvalidateRect( hwndClient, NULL, TRUE );
                    } else {
                        WinInvalidateRect( hwndField, NULL, TRUE );
                        WinInvalidateRect( hwndTime, NULL, TRUE );
                    } /* endif */
                    WinPostMsg( hwndField, WM_USER_INIT, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_USERDEF : {

                    WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
                    WinSetWindowULong( hwndTime,  QWL_VALUE,  0L );
                    WinEnableWindow( hwndField, FALSE );
                    WinSendMsg( hwndMenu
                              , MM_SETITEMATTR
                              , MPFROM2SHORT( IniData.GameType, TRUE )
                              , MPFROM2SHORT( MIA_CHECKED, FALSE ));
                    IniData.GameType = ID_MENU_USERDEF;
                    iAktiveGameIndex = 3;
                    WinSendMsg( hwndMenu
                              , MM_SETITEMATTR
                              , MPFROM2SHORT( ID_MENU_USERDLG, TRUE )
                              , MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ));
                    if ( SHORT2FROMMP( mp1 )) {
                        Resize( IniData.cx, IniData.cy );
                        WinInvalidateRect( hwndClient, NULL, TRUE );
                    } else {
                        WinInvalidateRect( hwndField, NULL, TRUE );
                        WinInvalidateRect( hwndTime, NULL, TRUE );
                    } /* endif */
                    WinPostMsg( hwndField, WM_USER_INIT, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_HELPINDEX : {
                    WinSendMsg( hwndHelp, HM_HELP_INDEX, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_HELPGENERAL : {
                    WinSendMsg( hwndHelp, HM_EXT_HELP, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_HELPKEYS : {
                    WinSendMsg( hwndHelp, HM_KEYS_HELP, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_HELPUSING : {
                    WinSendMsg( hwndHelp, HM_DISPLAY_HELP, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
                    break;
                }

                case ID_MENU_SPECIAL_BIG : {
                    IniData.Big = (USHORT)~IniData.Big;
                    WinSendMsg( hwndMenu
                              , MM_SETITEMATTR
                              , MPFROM2SHORT( usCommand, TRUE )
                              , MPFROM2SHORT( MIA_CHECKED, IniData.Big ));
                    if ( IniData.Big ) {
                        sizelCell.cx = CELL_CX_BIG;
                        sizelCell.cy = CELL_CY_BIG;
                    } else {
                        sizelCell.cx = CELL_CX;
                        sizelCell.cy = CELL_CY;
                    } /* endif */
                    WinSendMsg( hwndField, WM_USER_SET_BITMAP, MPFROMSHORT( IniData.Big ), MPFROMLONG( 0L ));
                    Resize( IniData.cx, IniData.cy );
                    WinInvalidateRect( hwndClient, NULL, TRUE );
                    break;
                }
                case ID_MENU_SPECIAL_SAV : {
                    IniData.Safety = (USHORT)~IniData.Safety;
                    WinSendMsg( hwndMenu
                              , MM_SETITEMATTR
                              , MPFROM2SHORT( usCommand, TRUE )
                              , MPFROM2SHORT( MIA_CHECKED, IniData.Safety ));
                    break;
                }
                case ID_MENU_SPECIAL_QUE : {
                    IniData.Questionmark = (USHORT)~IniData.Questionmark;
                    WinSendMsg( hwndMenu
                              , MM_SETITEMATTR
                              , MPFROM2SHORT( usCommand, TRUE )
                              , MPFROM2SHORT( MIA_CHECKED, IniData.Questionmark ));
                    break;
                }
                default : {
                    break;
                }
            }

            mReturn = MRFROMLONG( 0L );
            break;
        }

        //----------------------------------------------------------------------------------------------------
        case HM_QUERY_KEYS_HELP : {
        //----------------------------------------------------------------------------------------------------

            mReturn = MRFROMSHORT( HELP_PAGE_KEYS );

            break;
        }

        //----------------------------------------------------------------------------------------------------
        case WM_USER_START : {
        //----------------------------------------------------------------------------------------------------

            WinStartTimer( hAnchorBlock, hwnd, ID_TIMER_GAME, 1000L );
            IniData.GamesStarted[ iAktiveGameIndex ]++;
            if ( IniData.FirstGame.year == 0 ) {
                DATETIME DateTime;
                DosGetDateTime( &DateTime );
                IniData.FirstGame.day   = DateTime.day;
                IniData.FirstGame.month = DateTime.month;
                IniData.FirstGame.year  = DateTime.year - 1966;
            } /* endif */
            mReturn = MRFROMLONG( 0L );
            break;
        }

        //----------------------------------------------------------------------------------------------------
        case WM_USER_END : {
        //----------------------------------------------------------------------------------------------------

            USHORT usTime;
            WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_GAME );
            usTime = (USHORT)WinQueryWindowULong( hwndTime, QWL_VALUE );
            
            if ( SHORT1FROMMP( mp1 )) {                     // won
                IniData.GamesWon[ iAktiveGameIndex ]++;
                if (( iAktiveGameIndex < 3 ) && ( IniData.HofTime[ iAktiveGameIndex ] > usTime )) {
                    IniData.HofTime[ iAktiveGameIndex ] = usTime;
                    strcpy( IniData.HofName[ iAktiveGameIndex ], PSZ_HOF_UNKNOWN );
                    DlgHallOfFame( hwnd, iAktiveGameIndex );
                } /* endif */
            } else {                                        // lost
                IniData.GamesLost[ iAktiveGameIndex ]++;
            } /* endif */

            mReturn = MRFROMLONG( 0L );
            break;
        }

        //----------------------------------------------------------------------------------------------------
        case WM_TIMER : {
        //----------------------------------------------------------------------------------------------------

            
            if ( ! ( WinQueryWindowULong( hwndFrame, QWL_STYLE ) & WS_MINIMIZED )) {
                LONG lValue = (LONG)WinQueryWindowULong( hwndTime, QWL_VALUE );
                WinSetWindowULong( hwndTime, QWL_VALUE, (ULONG)min( lValue + 1L, 999L ));
                WinInvalidateRect( hwndTime, NULL, FALSE );
                IniData.PlayTime[ iAktiveGameIndex ]++;
                if ( IniData.GamesStarted[ iAktiveGameIndex ] == 0 ) {
                    DATETIME DateTime;
                    DosGetDateTime( &DateTime );
                    IniData.FirstGame.day   = DateTime.day;
                    IniData.FirstGame.month = DateTime.month;
                    IniData.FirstGame.year  = DateTime.year - 1966;
                    IniData.GamesStarted[ iAktiveGameIndex ] = 1;
                } /* endif */
            } /* endif */
            mReturn = MRFROMLONG( 0L );
            break;
        }

        //----------------------------------------------------------------------------------------------------
        default : {
        //----------------------------------------------------------------------------------------------------

            mReturn = WinDefWindowProc( hwnd, msg, mp1, mp2 );
            break;
        }

    } /* endswitch */

    return mReturn;
}

// ===========================================================================================================
VOID Resize( INT CellX, INT CellY ) {
// ===========================================================================================================

    RECTL  rectl;
    SIZEL  sizel, screen;
    POINTL pointl;
    SWP    swp[ 4 ];

    screen.cx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
    screen.cy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

    // --- calculate new client size -------------------------------------------------------------------------

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

    // --- calculate new frame size --------------------------------------------------------------------------

    WinCalcFrameRect( hwndFrame, &rectl, FALSE );
    sizel.cx = rectl.xRight - rectl.xLeft;
    sizel.cy = rectl.yTop - rectl.yBottom;

    // --- query old frame pos -------------------------------------------------------------------------------

    WinQueryWindowRect( hwndFrame, &rectl );
    WinMapWindowPoints( hwndFrame, HWND_DESKTOP, (PVOID)&rectl, 2L );

    // --- new position (preserve upper-left corner) ---------------------------------------------------------

    pointl.x = rectl.xLeft;
    pointl.y = rectl.yTop - sizel.cy;

    // --- limit to screen -----------------------------------------------------------------------------------

    pointl.y = max( 0, pointl.y );
    pointl.x = min( pointl.x, screen.cx - sizel.cx );
    pointl.y = min( pointl.y, screen.cy - sizel.cy );
    pointl.x = max( 0, pointl.x );

    WinSetWindowPos( hwndFrame            // Window handle
                   , NULLHANDLE           // Relative window placement order
                   , pointl.x             // Window position, x-coordinate
                   , pointl.y             // Window position, y-coordinate
                   , sizel.cx             // Window size x
                   , sizel.cy             // Window size y
                   ,   SWP_SIZE           // Window positioning options
                     | SWP_MOVE );
 
    WinSetMultWindowPos( hAnchorBlock     // Anchor-block handle
                       , swp              // An array of set window position (SWP) structures
                       , 4L );            // Window count
}

// --- EOF ---------------------------------------------------------------------------------------------------
