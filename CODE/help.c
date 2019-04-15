#pragma strings( readonly )

#include <string.h>
#include <stdlib.h>

#include "mine2.h"

extern HAB  hAnchorBlock;
extern HWND hwndFrame;
extern HWND hwndHelp;
extern HWND hwndMenu;

// ===============================================================================================
BOOL HelpConstructor( PSZ pszExeFileName ) {
// ===============================================================================================

    BOOL     fReturn = TRUE;
    HELPINIT helpinit;
    CHAR     pszHelpFileName[ CCHMAXPATH ];

    strcpy( pszHelpFileName, pszExeFileName );
    strcpy( strrchr( pszHelpFileName, '\\' ) + 1, PSZ_HELP_FILE_NAME );

    // --- initialize help init structure ----------------------------------------------------

    helpinit.cb                       = sizeof( HELPINIT );
    helpinit.ulReturnCode             = 0L;
    helpinit.pszTutorialName          = NULL;
    helpinit.phtHelpTable             = (PHELPTABLE)( ID_HELP_TABLE | 0xFFFF0000 );
    helpinit.hmodHelpTableModule      = NULLHANDLE;
    helpinit.hmodAccelActionBarModule = NULLHANDLE;
    helpinit.idAccelTable             = 0;
    helpinit.idActionBar              = 0;
    helpinit.pszHelpWindowTitle       = PSZ_TITLE_HELP;
    helpinit.fShowPanelId             = CMIC_HIDE_PANEL_ID; // CMIC_SHOW_PANEL_ID;
    helpinit.pszHelpLibraryName       = pszHelpFileName;

    // --- Creating help instance ------------------------------------------------------------

    hwndHelp = WinCreateHelpInstance( hAnchorBlock  // Anchorblock handle
                                    , &helpinit );  // Helpmanager initialization structure

    if (( hwndHelp == NULLHANDLE ) || helpinit.ulReturnCode ) {
        fReturn = FALSE;
    } else if ( ! WinAssociateHelpInstance( hwndHelp        // Handle of an instance of the Helpmanager
                                          , hwndFrame )) {  // Handle of an Applicationwindow
        fReturn = FALSE;
    } /* endif */

    return fReturn;
}

// ===============================================================================================
VOID HelpMenuUpdate( VOID ) {
// ===============================================================================================

    if (( hwndHelp != NULLHANDLE ) && ( hwndMenu != NULLHANDLE )) {

        // --- enable all four menuentries -------------------------------------------------------

        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_HELPINDEX, TRUE )
                  , MPFROM2SHORT( MIA_DISABLED, FALSE ));
        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_HELPGENERAL, TRUE )
                  , MPFROM2SHORT( MIA_DISABLED, FALSE ));
        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_HELPUSING, TRUE )
                  , MPFROM2SHORT( MIA_DISABLED, FALSE ));
        WinSendMsg( hwndMenu
                  , MM_SETITEMATTR
                  , MPFROM2SHORT( ID_MENU_HELPKEYS, TRUE )
                  , MPFROM2SHORT( MIA_DISABLED, FALSE ));

    } /* endif */
}

// ===============================================================================================
VOID HelpDestructor( VOID ) {
// ===============================================================================================

    if ( hwndHelp != NULLHANDLE ) {

        // --- cleanup ---------------------------------------------------------------------------

        WinAssociateHelpInstance( NULLHANDLE, hwndFrame );
        WinDestroyHelpInstance( hwndHelp );

    } /* endif */
}

