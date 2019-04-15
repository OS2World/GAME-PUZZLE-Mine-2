#pragma strings( readonly )

#include <stdio.h>
#include <string.h>
#include "mine2.h"

extern HAB hAnchorBlock;
extern INIDATA IniData;

MRESULT EXPENTRY DlgFktHOF( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 );
VOID ShowHofData( HWND hwnd );

 
INT  iHofIndex;
HWND hwndNewName = NULLHANDLE;

// ===========================================================================================================
VOID DlgHallOfFame( HWND hwnd, INT iIndex ) {
// ===========================================================================================================

    iHofIndex = iIndex;
    if ( ! WinDlgBox( HWND_DESKTOP     // parent
                    , hwnd             // owner
                    , DlgFktHOF        // function
                    , NULLHANDLE       // .dll as resource
                    , ID_DLG_HOF       // ID in resource
                    , NULL )) {        // inidata
        Error( __FILE__, __LINE__
             , "WinDlgBox failed. rc(0x%X)", WinRC( hAnchorBlock ));
    } /* endif */
}

// ===========================================================================================================
MRESULT EXPENTRY DlgFktHOF( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 ) {
// ===========================================================================================================

    MRESULT  mReturn;

    switch ( ulMsg ) {

        case WM_INITDLG : {

            HWND  hwndTemp;
            RECTL rectl;
            LONG  cy;

            WinQueryWindowRect( hwnd, &rectl );
            cy = rectl.yTop - WinQuerySysValue( HWND_DESKTOP, SV_CYTITLEBAR );
            hwndTemp = WinWindowFromID( hwnd, ID_BMP_FAME );
            WinQueryWindowRect( hwndTemp, &rectl );
            cy = cy - rectl.yTop;
            WinMapWindowPoints( hwndTemp, hwnd, (PVOID)&rectl, 2L );
            WinSetWindowPos( hwndTemp       // Window handle
                           , NULLHANDLE     // Relative window placement order
                           , rectl.xLeft    // Window position, x-coordinate
                           , cy / 2         // Window position, y-coordinate
                           , 0L             // Window size x
                           , 0L             // Window size y
                           , SWP_MOVE );    // Window positioning options

            ShowHofData( hwnd );

            if ( iHofIndex >= 0 ) {
                hwndTemp = WinWindowFromID( hwnd, ID_TXT_NOV_NAME + (ULONG)iHofIndex );
                WinQueryWindowRect( hwndTemp, &rectl );
                WinMapWindowPoints( hwndTemp, hwnd, (PVOID)&rectl, 2L );
                WinDestroyWindow( hwndTemp );
                hwndNewName = WinCreateWindow( hwnd           // Parentwindow handle 
                           , WC_ENTRYFIELD    // Registered class name 
                           , ""         // Window text 
                           , WS_VISIBLE | WS_TABSTOP | ES_LEFT | ES_MARGIN  // Window style 
                           , rectl.xLeft            // x-coordinate of window position 
                           , rectl.yBottom     // y-coordinate of window position 
                           , rectl.xRight - rectl.xLeft    // Width of window, in window coordinates 
                           , rectl.yTop - rectl.yBottom   // Height of window, in window coordinates 
                           , hwnd           // Ownerwindow handle 
                           , HWND_TOP       // Sibling-window handle 
                           , 0L             // Window identifier 
                           , NULL           // Pointer to control data 
                           , NULL );        // Presentation parameters 
                WinSendMsg( hwndNewName
                          , EM_CLEAR
                          , MPFROMLONG( 0L )
                          , MPFROMLONG( 0L ));
                WinSendMsg( hwndNewName
                          , EM_SETTEXTLIMIT
                          , MPFROMSHORT( MAX_HOFNAME )
                          , MPFROMLONG( 0L ));
                WinSetDlgItemText( hwnd, ID_TXT_CLEAR, "Congratulation" );
                WinPostMsg( hwnd, WM_USER_SET_FOCUS, MPFROMLONG( 0L ), MPFROMLONG( 0L ));
            } else {
                WinShowWindow( WinWindowFromID( hwnd, ID_BUT_CLEAR_1 ), TRUE );
                WinSetDlgItemText( hwnd, ID_TXT_CLEAR, "press here to clear ->" );
            } /* endif */

            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        case WM_USER_SET_FOCUS : {

            WinSetFocus( HWND_DESKTOP, hwndNewName );
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_COMMAND : {

            // --- termination -------------------------------------------------------------------------------

            USHORT usCommand = SHORT1FROMMP( mp1 );

            switch ( usCommand ) {

                case ID_BUT_CLEAR_1 : {
                    ULONG ulStyles;
                    HWND hwndText = WinWindowFromID( hwnd, ID_TXT_CLEAR );
                    ulStyles = WinQueryWindowULong( hwndText, QWL_STYLE );
                    ulStyles = ( ulStyles & ~(ULONG)( DT_RIGHT | DT_CENTER )) | DT_LEFT;
                    WinSetWindowULong( hwndText, QWL_STYLE, ulStyles );
                    WinSetDlgItemText( hwnd, ID_TXT_CLEAR, "<- confirm clearing" );
                    WinShowWindow( WinWindowFromID( hwnd, ID_BUT_CLEAR_2 ), TRUE );
                    WinShowWindow( WinWindowFromID( hwnd, ID_BUT_CLEAR_1 ), FALSE );
                    break;
                }

                case ID_BUT_CLEAR_2 : {
                    ULONG ulStyles;
                    INT   iLoop;
                    HWND hwndText = WinWindowFromID( hwnd, ID_TXT_CLEAR );
                    ulStyles = WinQueryWindowULong( hwndText, QWL_STYLE );
                    ulStyles = ( ulStyles & ~(ULONG)( DT_LEFT | DT_RIGHT )) | DT_CENTER;
                    WinSetWindowULong( hwndText, QWL_STYLE, ulStyles );
                    WinSetDlgItemText( hwnd, ID_TXT_CLEAR, "cleared!" );
                    WinShowWindow( WinWindowFromID( hwnd, ID_BUT_CLEAR_2 ), FALSE );
                    for ( iLoop = 0; iLoop < 3; iLoop++ ) {
                        IniData.HofTime[ iLoop ] = 999;
                        strcpy( IniData.HofName[ iLoop ], PSZ_HOF_NOBODY );
                    } /* endfor */
                    ShowHofData( hwnd );
                    break;
                }

                default : {
                    if ( iHofIndex >= 0 ) {
                        WinQueryWindowText( hwndNewName
                                          , MAX_HOFNAME
                                          , IniData.HofName[ iHofIndex ] );
                        WinDestroyWindow( hwndNewName );
                    } /* endif */
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

VOID ShowHofData( HWND hwnd ) {

    CHAR pszTime[ 6 ];
    WinSetDlgItemText( hwnd, ID_TXT_NOV_NAME, IniData.HofName[ 0 ] );
    WinSetDlgItemText( hwnd, ID_TXT_ADV_NAME, IniData.HofName[ 1 ] );
    WinSetDlgItemText( hwnd, ID_TXT_PRO_NAME, IniData.HofName[ 2 ] );
    sprintf( pszTime, "%3d", IniData.HofTime[ 0 ] );
    WinSetDlgItemText( hwnd, ID_TXT_NOV_TIME, pszTime );
    sprintf( pszTime, "%3d", IniData.HofTime[ 1 ] );
    WinSetDlgItemText( hwnd, ID_TXT_ADV_TIME, pszTime );
    sprintf( pszTime, "%3d", IniData.HofTime[ 2 ] );
    WinSetDlgItemText( hwnd, ID_TXT_PRO_TIME, pszTime );
}

// --- EOF ---------------------------------------------------------------------------------------------------
