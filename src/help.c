
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mine2.h"

extern HAB  hAnchorBlock;
extern HWND hwndFrame;
extern HWND hwndHelp;
extern HWND hwndMenu;
extern int  current_lang;

static const char * const szLangSuffix[ LANG_COUNT ] = {
    "en", "es", "nl", "de", "fr", "it"
};

static CHAR szExeDir[ CCHMAXPATH ] = { 0 };

static VOID BuildHelpPath( CHAR *pszOut, int lang ) {
    int l = ( lang >= 0 && lang < LANG_COUNT ) ? lang : LANG_EN;
    sprintf( pszOut, "%s\\help\\mine2_%s.hlp", szExeDir, szLangSuffix[ l ] );
}

BOOL HelpConstructor( PSZ pszExeFileName ) {

    BOOL     fReturn = TRUE;
    HELPINIT helpinit;
    CHAR     pszHelpFileName[ CCHMAXPATH ];
    CHAR    *pszSlash;

    /* Store exe directory for later reloads */
    strcpy( szExeDir, pszExeFileName );
    pszSlash = strrchr( szExeDir, '\\' );
    if ( pszSlash ) *pszSlash = '\0';
    else            szExeDir[0] = '\0';

    BuildHelpPath( pszHelpFileName, current_lang );

    helpinit.cb                       = sizeof( HELPINIT );
    helpinit.ulReturnCode             = 0L;
    helpinit.pszTutorialName          = NULL;
    helpinit.phtHelpTable             = (PHELPTABLE)( ID_HELP_TABLE | 0xFFFF0000 );
    helpinit.hmodHelpTableModule      = NULLHANDLE;
    helpinit.hmodAccelActionBarModule = NULLHANDLE;
    helpinit.idAccelTable             = 0;
    helpinit.idActionBar              = 0;
    helpinit.pszHelpWindowTitle       = PSZ_TITLE_HELP;
    helpinit.fShowPanelId             = CMIC_HIDE_PANEL_ID;
    helpinit.pszHelpLibraryName       = pszHelpFileName;

    hwndHelp = WinCreateHelpInstance( hAnchorBlock, &helpinit );

    if (( hwndHelp == NULLHANDLE ) || helpinit.ulReturnCode ) {
        fReturn = FALSE;
    } else if ( ! WinAssociateHelpInstance( hwndHelp, hwndFrame )) {
        fReturn = FALSE;
    }

    return fReturn;
}

VOID HelpMenuUpdate( VOID ) {

    if (( hwndHelp != NULLHANDLE ) && ( hwndMenu != NULLHANDLE )) {
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_HELPINDEX,   TRUE ),
                    MPFROM2SHORT( MIA_DISABLED, FALSE ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_HELPGENERAL, TRUE ),
                    MPFROM2SHORT( MIA_DISABLED, FALSE ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_HELPUSING,   TRUE ),
                    MPFROM2SHORT( MIA_DISABLED, FALSE ));
        WinSendMsg( hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( IDM_HELPKEYS,    TRUE ),
                    MPFROM2SHORT( MIA_DISABLED, FALSE ));
    }
}

VOID HelpDestructor( VOID ) {

    if ( hwndHelp != NULLHANDLE ) {
        WinAssociateHelpInstance( NULLHANDLE, hwndFrame );
        WinDestroyHelpInstance( hwndHelp );
        hwndHelp = NULLHANDLE;
    }
}

VOID HelpReload( VOID ) {

    BOOL     fReturn;
    HELPINIT helpinit;
    CHAR     pszHelpFileName[ CCHMAXPATH ];

    HelpDestructor();

    BuildHelpPath( pszHelpFileName, current_lang );

    helpinit.cb                       = sizeof( HELPINIT );
    helpinit.ulReturnCode             = 0L;
    helpinit.pszTutorialName          = NULL;
    helpinit.phtHelpTable             = (PHELPTABLE)( ID_HELP_TABLE | 0xFFFF0000 );
    helpinit.hmodHelpTableModule      = NULLHANDLE;
    helpinit.hmodAccelActionBarModule = NULLHANDLE;
    helpinit.idAccelTable             = 0;
    helpinit.idActionBar              = 0;
    helpinit.pszHelpWindowTitle       = PSZ_TITLE_HELP;
    helpinit.fShowPanelId             = CMIC_HIDE_PANEL_ID;
    helpinit.pszHelpLibraryName       = pszHelpFileName;

    hwndHelp = WinCreateHelpInstance( hAnchorBlock, &helpinit );

    if (( hwndHelp != NULLHANDLE ) && !helpinit.ulReturnCode ) {
        WinAssociateHelpInstance( hwndHelp, hwndFrame );
    }
    (VOID)fReturn;
}

/* EOF */
