
#include <stdlib.h>
#include <string.h>
#include "mine2.h"
#include "7segment.h"
#include "lang.h"

/* Build-level string embedded in the EXE */
const char bldlevel[] =
    "@#OS2World:1.1#@ Mine/2 - Minesweeper Clone for ArcaOS/eComStation/OS/2";

/* Global state */
HAB      hAnchorBlock  = NULLHANDLE;
HWND     hwndFrame     = NULLHANDLE;
HWND     hwndClient    = NULLHANDLE;
HWND     hwndCount     = NULLHANDLE;
HWND     hwndTime      = NULLHANDLE;
HWND     hwndButton    = NULLHANDLE;
HWND     hwndField     = NULLHANDLE;
HWND     hwndMenu      = NULLHANDLE;
HWND     hwndHelp      = NULLHANDLE;
HPOINTER hPointer      = NULLHANDLE;
INIDATA  IniData       = INITVALUES;
SIZEL    sizelCell     = { 0L, 0L };
SIZEL    sizelBmpCell  = { BMP_CELL_CX, BMP_CELL_CY };

/* App settings */
int  save_on_exit  = 1;
int  current_lang  = LANG_EN;
int  bBackgrndRun  = 0;

/* Frame subclass: forward WM_ACTIVATE to the client */
static PFNWP pfnOldFrameProc = NULL;

static MRESULT EXPENTRY wpFrameSub( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
    MRESULT mr = pfnOldFrameProc( hwnd, msg, mp1, mp2 );
    if ( msg == WM_ACTIVATE )
        WinPostMsg( hwndClient, WM_ACTIVATE, mp1, mp2 );
    return mr;
}

/* ------------------------------------------------------------------ */
/* set_language: update menu item text for current_lang               */
/* ------------------------------------------------------------------ */
VOID set_language( int lang ) {

    if ( lang < 0 || lang >= LANG_COUNT ) lang = LANG_EN;
    current_lang = lang;

    if ( hwndMenu == NULLHANDLE ) return;

    /* Update language radio check */
    {
        int l;
        for ( l = LANG_EN; l < LANG_COUNT; l++ ) {
            WinSendMsg( hwndMenu, MM_SETITEMATTR,
                        MPFROM2SHORT( IDM_LANG_EN + l, TRUE ),
                        MPFROM2SHORT( MIA_CHECKED,
                                      ( l == lang ) ? MIA_CHECKED : 0 ));
        }
    }

    /* Macro: set text of a menu item by ID */
    #define SETMT(id, idx) \
        WinSendMsg( hwndMenu, MM_SETITEMTEXT, \
                    MPFROMSHORT( id ), \
                    MPFROMP( (PSZ)LS( idx ) ))

    SETMT( IDM_SUBMENU_GAME,    STR_GAME );
    SETMT( IDM_NEW,             STR_NEW_GAME );
    SETMT( IDM_PAUSE,           STR_PAUSE_GAME );
    SETMT( IDM_QUIT,            STR_QUIT_GAME );
    SETMT( IDM_EXIT,            STR_EXIT );
    SETMT( IDM_SUBMENU_OPTIONS, STR_OPTIONS );
    SETMT( IDM_SUBMENU_LEVEL,   STR_LEVEL );
    SETMT( IDM_NOVICE,          STR_NOVICE );
    SETMT( IDM_ADVANCED,        STR_ADVANCED );
    SETMT( IDM_PROFESSIONAL,    STR_PROFESSIONAL );
    SETMT( IDM_USERDLG,         STR_USER_DEFINED );
    SETMT( IDM_SUBMENU_POINTER, STR_POINTER );
    SETMT( IDM_SUBMENU_SPECIAL, STR_SPECIAL );
    SETMT( IDM_STATISTIC,       STR_STATISTICS );
    SETMT( IDM_HOF,             STR_HALL_OF_FAME );
    SETMT( IDM_SPECIAL_QUE,     STR_USE_QUESTION );
    SETMT( IDM_SPECIAL_SAV,     STR_SAFETY );
    SETMT( IDM_SPECIAL_BIG,     STR_BIG_BLOCKS );
    SETMT( IDM_SUBMENU_LANG,    STR_LANGUAGE );
    SETMT( IDM_BACKGRND,        STR_BACKGROUND_RUN );
    SETMT( IDM_SAVEONEXIT,      STR_SAVE_ON_EXIT );
    SETMT( IDM_SUBMENU_HELP,    STR_HELP_MENU );
    SETMT( IDM_HELPINDEX,       STR_HELP_INDEX );
    SETMT( IDM_HELPGENERAL,     STR_GENERAL_HELP );
    SETMT( IDM_HELPUSING,       STR_USING_HELP );
    SETMT( IDM_HELPKEYS,        STR_KEYS_HELP );
    SETMT( IDM_ABOUT,           STR_ABOUT );

    #undef SETMT

    /* Update title bar */
    WinSetWindowText( hwndFrame, (PSZ)LS( STR_TITLE ));
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */
INT main( INT argc, PSZ argv[] ) {

    INT    iReturnValue = 1;
    HMQ    hMsgQueue    = NULLHANDLE;
    QMSG   QueueMsg;
    ULONG  ulFrameFlags = FCF_TITLEBAR
                        | FCF_SYSMENU
                        | FCF_MINBUTTON
                        | FCF_TASKLIST
                        | FCF_NOBYTEALIGN
                        | FCF_DLGBORDER
                        | FCF_ACCELTABLE
                        | FCF_MENU
                        | FCF_AUTOICON
                        | FCF_ICON;

    (VOID)argc;

    if (( hAnchorBlock = WinInitialize( 0L )) == NULLHANDLE ) {

        Error( __FILE__, __LINE__, "WinInitialize failed." );

    } else if (( hMsgQueue = WinCreateMsgQueue( hAnchorBlock, 0L )) == NULLHANDLE ) {

        Error( __FILE__, __LINE__,
               "WinCreateMsgQueue failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if ( ! WinRegisterClass( hAnchorBlock, WC_MINE2,
                                    (PFNWP)wpMain, 0L, 0L )) {

        Error( __FILE__, __LINE__,
               "WinRegisterClass(WC_MINE2) failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if ( ! WinRegisterClass( hAnchorBlock, WC_MINEFIELD,
                                    (PFNWP)wpField, 0L, 0L )) {

        Error( __FILE__, __LINE__,
               "WinRegisterClass(WC_MINEFIELD) failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if ( ! Register7SegClass( hAnchorBlock )) {

        Error( __FILE__, __LINE__,
               "Register7SegClass failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if (( hwndFrame = WinCreateStdWindow(
                                 HWND_DESKTOP,
                                 0L,
                                 &ulFrameFlags,
                                 WC_MINE2,
                                 PSZ_TITLE,
                                 0L,           /* client invisible initially */
                                 NULLHANDLE,
                                 ID_RESOURCE,
                                 &hwndClient ))
               == NULLHANDLE ) {

        Error( __FILE__, __LINE__,
               "WinCreateStdWindow failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else {

        /* Get frame control handles */
        hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );

        /* Subclass frame to forward WM_ACTIVATE to client */
        pfnOldFrameProc = WinSubclassWindow( hwndFrame, wpFrameSub );

        /* Apply language (sets checkmark on current_lang item) */
        set_language( current_lang );

        /* Set initial checkmarks for game options */
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_SPECIAL_BIG, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, IniData.Big ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_SPECIAL_SAV, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, IniData.Safety ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_SPECIAL_QUE, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, IniData.Questionmark ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_SAVEONEXIT, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED,
                                  save_on_exit ? MIA_CHECKED : 0 ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_BACKGRND, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED,
                                  bBackgrndRun ? MIA_CHECKED : 0 ));

        /* Position and show the window */
        WinSetWindowPos( hwndFrame, HWND_TOP,
                         IniData.x, IniData.y,
                         0L, 0L,
                         SWP_ZORDER | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE );

        /* Post initial game type to trigger first resize */
        WinPostMsg( hwndClient, WM_COMMAND,
                    MPFROM2SHORT( IniData.GameType, TRUE ), 0 );
        IniData.GameType = 0;   /* force resize on first WM_COMMAND */

        /* Initialize help if available */
        if ( HelpConstructor( argv[ 0 ] ))
            HelpMenuUpdate();

        /* Message loop */
        while ( WinGetMsg( hAnchorBlock, &QueueMsg, 0, 0, 0 ))
            WinDispatchMsg( hAnchorBlock, &QueueMsg );

        HelpDestructor();
        iReturnValue = 0;
    }

    /* Save settings if requested */
    if ( save_on_exit && hwndClient != NULLHANDLE ) {
        HINI  hIni;
        RECTL rectl;

        if (( hIni = PrfOpenProfile( hAnchorBlock, INI_FILENAME ))
            != NULLHANDLE ) {
            if ( !( WinQueryWindowULong( hwndFrame, QWL_STYLE ) & WS_MINIMIZED )) {
                WinQueryWindowRect( hwndFrame, &rectl );
                WinMapWindowPoints( hwndFrame, HWND_DESKTOP, (PVOID)&rectl, 2L );
                IniData.x = (USHORT)rectl.xLeft;
                IniData.y = (USHORT)rectl.yTop;
            }
            PrfWriteProfileData( hIni, INI_APPLNAME, INI_KEYNAME,
                                 &IniData, sizeof( IniData ));
            PrfWriteProfileData( hIni, INI_APPLNAME, INI_KEY_SAVEONEXIT,
                                 &save_on_exit, sizeof( int ));
            PrfWriteProfileData( hIni, INI_APPLNAME, INI_KEY_LANGUAGE,
                                 &current_lang, sizeof( int ));
            PrfWriteProfileData( hIni, INI_APPLNAME, INI_KEY_BACKGRND,
                                 &bBackgrndRun, sizeof( int ));
            PrfCloseProfile( hIni );
        }
    }

    /* Cleanup */
    if ( hwndClient != NULLHANDLE ) {
        WinDestroyWindow( hwndClient );
        hwndClient = NULLHANDLE;
    }
    if ( hwndFrame != NULLHANDLE ) {
        WinDestroyWindow( hwndFrame );
        hwndFrame = NULLHANDLE;
    }
    if ( hMsgQueue != NULLHANDLE ) {
        WinDestroyMsgQueue( hMsgQueue );
        hMsgQueue = NULLHANDLE;
    }
    if ( hAnchorBlock != NULLHANDLE ) {
        WinTerminate( hAnchorBlock );
        hAnchorBlock = NULLHANDLE;
    }

    return iReturnValue;
}

/* EOF */
