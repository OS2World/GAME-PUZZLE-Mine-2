#pragma strings( readonly )

#include <stdlib.h>
#include <string.h>
#include "mine2.h"
#include "7segment.h"

HAB hAnchorBlock = NULLHANDLE;
HWND hwndFrame   = NULLHANDLE;
HWND hwndClient  = NULLHANDLE;
HWND hwndCount   = NULLHANDLE;
HWND hwndTime    = NULLHANDLE;
HWND hwndButton  = NULLHANDLE;
HWND hwndField   = NULLHANDLE;
HWND hwndMenu    = NULLHANDLE;
HWND hwndHelp    = NULLHANDLE;
HPOINTER hPointer = NULLHANDLE;
INIDATA  IniData = INITVALUES;
SIZEL    sizelCell = { 0L, 0L };

// ===========================================================================================================
INT main( INT argc, PSZ argv[] ) {
// ===========================================================================================================

    INT    iReturnValue = 1;
    HMQ    hMsgQueue = NULLHANDLE;
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

    if (( hAnchorBlock = WinInitialize( 0L )) == NULLHANDLE ) {             // Initialization options

        Error( __FILE__, __LINE__
             , "WinInitialize failed." );

        // --- create messge queue for the thread ------------------------------------------------------------

    } else if (( hMsgQueue = WinCreateMsgQueue( hAnchorBlock                // Anchor Block handle
                                              , 0L )) == NULLHANDLE ) {     // Queue size, use default

        Error( __FILE__, __LINE__
             , "WinCreateMsgQueue failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if ( ! WinRegisterClass( hAnchorBlock            // Anchor-block handle
                                  , WC_MINE2                // Window-class name
                                  , (PFNWP)wpMain           // Window-procedure identifier
                                  , 0L                      // Default-window style
                                  , 0L )) {                 // Reserved storage

        Error( __FILE__, __LINE__
             , "WinRegisterClass failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if ( ! WinRegisterClass( hAnchorBlock            // Anchor-block handle
                                  , WC_MINEFIELD            // Window-class name
                                  , (PFNWP)wpField          // Window-procedure identifier
                                  , 0L                      // Default-window style
                                  , 0L )) {                 // Reserved storage

        Error( __FILE__, __LINE__
             , "WinRegisterClass failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if ( ! Register7SegClass( hAnchorBlock )) {      // Anchor-block handle

        Error( __FILE__, __LINE__
             , "Register7SegClass failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else if (( hwndFrame = WinCreateStdWindow( HWND_DESKTOP       // Parentwindow handle
                                               , 0L                 // Framewindow style
                                               , &ulFrameFlags      // Framecreation flags
                                               , WC_MINE2           // Clientwindow class name
                                               , PSZ_TITLE          // Titlebar text
                                               , WS_VISIBLE         // Clientwindow style
                                               , NULLHANDLE         // Resource identifier
                                               , ID_RESOURCE        // Framewindow identifier
                                               , &hwndClient ))     // Clientwindow handle
                                       == NULLHANDLE ) {

        Error( __FILE__, __LINE__
             , "WinCreateStdWindow failed. rc(0x%X)", WinRC( hAnchorBlock ));

    } else {

        hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );

        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_SPECIAL_BIG, TRUE )
                  , MPFROM2SHORT( MIA_CHECKED, IniData.Big ));
        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_SPECIAL_SAV, TRUE )
                  , MPFROM2SHORT( MIA_CHECKED, IniData.Safety ));
        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_SPECIAL_QUE, TRUE )
                  , MPFROM2SHORT( MIA_CHECKED, IniData.Questionmark ));

        WinSetWindowPos( hwndFrame            // Window handle
                       , HWND_TOP             // Relative window placement order
                       , IniData.x            // Window position, x-coordinate
                       , IniData.y            // Window position, y-coordinate
                       , 0L                   // Window size x
                       , 0L                   // Window size y
                       ,    SWP_ZORDER        // Window positioning options
                          | SWP_MOVE
                          | SWP_SHOW
                          | SWP_ACTIVATE );

        WinPostMsg( hwndClient, WM_COMMAND, MPFROM2SHORT( IniData.GameType, TRUE ), MPFROMLONG( 0L ));
        IniData.GameType = 0; // force resize

        if ( HelpConstructor( argv[ 0 ] )) {
            HelpMenuUpdate();
        } /* endif */

        while ( WinGetMsg( hAnchorBlock    // Anchor block handle
                         , &QueueMsg       // Pointer to queue message structure
                         , 0               // No window message filter
                         , 0               // Retrieve all messages
                         , 0 )) {          // Retrieve all messages

            WinDispatchMsg( hAnchorBlock   // Anchor block handle
                          , &QueueMsg );   // structure holding message
        } /* endwhile */

        // --- the WM_QUIT message has been received.  Destroy all and ---------------------------------------
        //     try to remove the second thread

        HelpDestructor();

        iReturnValue = 0;                   // success

    } /* endif */

    // --- free all you have ---------------------------------------------------------------------------------

    if ( hwndClient != NULLHANDLE ) {
        WinDestroyWindow( hwndClient );
        hwndClient = NULLHANDLE;
    } /* endif */

    if ( hwndFrame != NULLHANDLE ) {
        WinDestroyWindow( hwndFrame );
        hwndFrame = NULLHANDLE;
    } /* endif */

    if ( hMsgQueue != NULLHANDLE ) {
        WinDestroyMsgQueue( hMsgQueue );    // Tidy up...
        hMsgQueue = NULLHANDLE;
    } /* endif */

    if ( hAnchorBlock != NULLHANDLE ) {
        WinTerminate( hAnchorBlock );       // Terminate the application
        hAnchorBlock = NULLHANDLE;
    } /* endif */

    // --- bye bye -------------------------------------------------------------------------------------------

    return iReturnValue;
}

// --- EOF ---------------------------------------------------------------------------------------------------
