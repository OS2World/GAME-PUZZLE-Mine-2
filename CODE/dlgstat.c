#pragma strings( readonly )

#include <stdio.h>
#include <string.h>
#include "mine2.h"

extern HAB hAnchorBlock;
extern INIDATA IniData;

MRESULT EXPENTRY DlgFktStat( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 );
VOID ShowStatData( HWND hwnd );

COUNTRYINFO  CtryInfo = { 0 };   // Buffer for country-specific information

// ===========================================================================================================
VOID DlgStatistic( HWND hwnd ) {
// ===========================================================================================================

    if ( ! WinDlgBox( HWND_DESKTOP     // parent
                    , hwnd             // owner
                    , DlgFktStat       // function
                    , NULLHANDLE       // .dll as resource
                    , ID_DLG_STAT      // ID in resource
                    , NULL )) {        // inidata
        Error( __FILE__, __LINE__
             , "WinDlgBox failed. rc(0x%X)", WinRC( hAnchorBlock ));
    } /* endif */
}

// ===========================================================================================================
MRESULT EXPENTRY DlgFktStat( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 ) {
// ===========================================================================================================

    MRESULT  mReturn;

    switch ( ulMsg ) {

        case WM_INITDLG : {

            COUNTRYCODE  Country = { 0 };   // Country code info (0 = current country)
            ULONG        ulInfoLen = 0;

            if ( DosQueryCtryInfo( sizeof( CtryInfo )
                                 , &Country
                                 , &CtryInfo
                                 , &ulInfoLen ) != NO_ERROR ) {
                CtryInfo.fsDateFmt = 0;
                strcpy( CtryInfo.szDateSeparator, "." );
                strcpy( CtryInfo.szTimeSeparator, ":" );
            } /* endif */

            ShowStatData( hwnd );

            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        case WM_COMMAND : {

            // --- termination -------------------------------------------------------------------------------

            USHORT usCommand = SHORT1FROMMP( mp1 );

            switch ( usCommand ) {

                case ID_BUT_RESET : {
                    INT iLoop;

                    WinShowWindow( WinWindowFromID( hwnd, ID_TXT_RESET ), FALSE );
                    WinShowWindow( WinWindowFromID( hwnd, ID_BUT_RESET ), FALSE );

                    for ( iLoop = 0; iLoop < 4; iLoop++ ) {
                        IniData.PlayTime[ iLoop ]     = 0;
                        IniData.GamesStarted[ iLoop ] = 0;
                        IniData.GamesWon[ iLoop ]     = 0;
                        IniData.GamesLost[ iLoop ]    = 0;
                    } /* endfor */
                    IniData.FirstGame.day   = 1;
                    IniData.FirstGame.month = 10;
                    IniData.FirstGame.year  = 0;  // 1966

                    ShowStatData( hwnd );
                    break;
                }

                default : {
                    WinDismissDlg( hwnd, TRUE );
                    break;
                }
            }

            mReturn = MRFROMLONG( 0L );
            break;
        }

        default : {

            mReturn = WinDefDlgProc( hwnd, ulMsg, mp1, mp2 );
            break;
        }
    }

    return mReturn;
}

VOID ShowStatData( HWND hwnd ) {

    UINT  uiLoop;
    CHAR  pszBuffer[ 12 ];
    ULONG ulTotal[ 5 ] = { 0, 0, 0, 0, 0 };

    for ( uiLoop = 0; uiLoop < 4; uiLoop++ ) {
        ulTotal[ 0 ] += IniData.PlayTime[ uiLoop ];
        sprintf( pszBuffer
               , "%d%s%02d%s%02d"
               , IniData.PlayTime[ uiLoop ] / ( 60 * 60 )
               , CtryInfo.szTimeSeparator
               , ( IniData.PlayTime[ uiLoop ] / 60 ) % 60
               , CtryInfo.szTimeSeparator
               , IniData.PlayTime[ uiLoop ] % 60 );
        WinSetDlgItemText( hwnd, ID_TXT_TIME_BASE    + uiLoop, pszBuffer );
        ulTotal[ 1 ] += IniData.GamesStarted[ uiLoop ];
        sprintf( pszBuffer, "%d", IniData.GamesStarted[ uiLoop ] );
        WinSetDlgItemText( hwnd, ID_TXT_STARTED_BASE + uiLoop, pszBuffer );
        ulTotal[ 2 ] += IniData.GamesWon[ uiLoop ];
        sprintf( pszBuffer, "%d", IniData.GamesWon[ uiLoop ] );
        WinSetDlgItemText( hwnd, ID_TXT_WON_BASE     + uiLoop, pszBuffer );
        ulTotal[ 3 ] += IniData.GamesLost[ uiLoop ];
        sprintf( pszBuffer, "%d", IniData.GamesLost[ uiLoop ] );
        WinSetDlgItemText( hwnd, ID_TXT_LOST_BASE    + uiLoop, pszBuffer );
        ulTotal[ 4 ] += ( IniData.GamesStarted[ uiLoop ] - ( IniData.GamesWon[ uiLoop ] + IniData.GamesLost[ uiLoop ] ));
        sprintf( pszBuffer, "%d", IniData.GamesStarted[ uiLoop ] - ( IniData.GamesWon[ uiLoop ] + IniData.GamesLost[ uiLoop ] ));
        WinSetDlgItemText( hwnd, ID_TXT_ABORT_BASE   + uiLoop, pszBuffer );
    } /* endfor */
    sprintf( pszBuffer
           , "%d%s%02d%s%02d"
           , ulTotal[ 0 ] / ( 60 * 60 )
           , CtryInfo.szTimeSeparator
           , ( ulTotal[ 0 ] / 60 ) % 60
           , CtryInfo.szTimeSeparator
           , ulTotal[ 0 ] % 60 );
    WinSetDlgItemText( hwnd, ID_TXT_TIME_BASE    + 4, pszBuffer );
    sprintf( pszBuffer, "%d", ulTotal[ 1 ] );
    WinSetDlgItemText( hwnd, ID_TXT_STARTED_BASE + 4, pszBuffer );
    sprintf( pszBuffer, "%d", ulTotal[ 2 ] );
    WinSetDlgItemText( hwnd, ID_TXT_WON_BASE     + 4, pszBuffer );
    sprintf( pszBuffer, "%d", ulTotal[ 3 ] );
    WinSetDlgItemText( hwnd, ID_TXT_LOST_BASE    + 4, pszBuffer );
    sprintf( pszBuffer, "%d", ulTotal[ 4 ] );
    WinSetDlgItemText( hwnd, ID_TXT_ABORT_BASE   + 4, pszBuffer );

    switch ( CtryInfo.fsDateFmt ) {
        case 1 /* dd/mm/yyyy */ : {
            sprintf( pszBuffer
                   , "%d%s%d%s%d"
                   , IniData.FirstGame.day
                   , CtryInfo.szDateSeparator
                   , IniData.FirstGame.month
                   , CtryInfo.szDateSeparator
                   , IniData.FirstGame.year + 1966 );
            break;
        }
        case 2 /* yyyy/mm/dd */ : {
            sprintf( pszBuffer
                   , "%d%s%d%s%d"
                   , IniData.FirstGame.year + 1966
                   , CtryInfo.szDateSeparator
                   , IniData.FirstGame.month
                   , CtryInfo.szDateSeparator
                   , IniData.FirstGame.day );
            break;
        }
        default /* mm/dd/yyyy */ : {
            sprintf( pszBuffer
                   , "%d%s%d%s%d"
                   , IniData.FirstGame.month
                   , CtryInfo.szDateSeparator
                   , IniData.FirstGame.day
                   , CtryInfo.szDateSeparator
                   , IniData.FirstGame.year + 1966 );
            break;
        }
 
    } /* endswitch */
    WinSetDlgItemText( hwnd, ID_TXT_FIRST_GAME, pszBuffer );
}

// --- EOF ---------------------------------------------------------------------------------------------------
