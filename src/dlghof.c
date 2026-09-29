
#include <stdio.h>
#include <string.h>
#include "mine2.h"

extern HAB    hAnchorBlock;
extern INIDATA IniData;

MRESULT EXPENTRY DlgFktHOF( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 );
static VOID ShowHofData( HWND hwnd );

static INT  iHofIndex;
static HWND hwndNewName = NULLHANDLE;

/* Return pointer to the string, skipping any leading '~' */
static const char *NoTilde( const char *psz ) {
    return ( psz && psz[0] == '~' ) ? psz + 1 : psz;
}

VOID DlgHallOfFame( HWND hwnd, INT iIndex ) {
    iHofIndex = iIndex;
    if ( ! WinDlgBox( HWND_DESKTOP, hwnd, DlgFktHOF,
                      NULLHANDLE, ID_DLG_HOF, NULL )) {
        Error( __FILE__, __LINE__,
               "WinDlgBox failed. rc(0x%X)", WinRC( hAnchorBlock ));
    }
}

MRESULT EXPENTRY DlgFktHOF( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 ) {

    MRESULT mReturn;

    switch ( ulMsg ) {

        case WM_INITDLG : {
            HWND  hwndTemp;
            RECTL rectl;
            LONG  cy;

            /* Set translated dialog title and labels */
            WinSetWindowText( hwnd, (PSZ)NoTilde( LS( STR_HALL_OF_FAME )));
            WinSetDlgItemText( hwnd, ID_HOF_LBL_NOV,  (PSZ)NoTilde( LS( STR_NOVICE )));
            WinSetDlgItemText( hwnd, ID_HOF_LBL_ADV,  (PSZ)NoTilde( LS( STR_ADVANCED )));
            WinSetDlgItemText( hwnd, ID_HOF_LBL_PRO,  (PSZ)NoTilde( LS( STR_PROFESSIONAL )));
            WinSetDlgItemText( hwnd, ID_HOF_LBL_SEC1, (PSZ)LS( STR_HOF_SEC ));
            WinSetDlgItemText( hwnd, ID_HOF_LBL_SEC2, (PSZ)LS( STR_HOF_SEC ));
            WinSetDlgItemText( hwnd, ID_HOF_LBL_SEC3, (PSZ)LS( STR_HOF_SEC ));

            WinQueryWindowRect( hwnd, &rectl );
            cy = rectl.yTop - WinQuerySysValue( HWND_DESKTOP, SV_CYTITLEBAR );
            hwndTemp = WinWindowFromID( hwnd, ID_BMP_FAME );
            WinQueryWindowRect( hwndTemp, &rectl );
            cy = cy - rectl.yTop;
            WinMapWindowPoints( hwndTemp, hwnd, (PVOID)&rectl, 2L );
            WinSetWindowPos( hwndTemp, NULLHANDLE,
                             rectl.xLeft, cy / 2,
                             0L, 0L, SWP_MOVE );

            ShowHofData( hwnd );

            if ( iHofIndex >= 0 ) {
                hwndTemp = WinWindowFromID( hwnd, ID_TXT_NOV_NAME + (ULONG)iHofIndex );
                WinQueryWindowRect( hwndTemp, &rectl );
                WinMapWindowPoints( hwndTemp, hwnd, (PVOID)&rectl, 2L );
                WinDestroyWindow( hwndTemp );
                hwndNewName = WinCreateWindow(
                                  hwnd, WC_ENTRYFIELD, "",
                                  WS_VISIBLE | WS_TABSTOP | ES_LEFT | ES_MARGIN,
                                  rectl.xLeft, rectl.yBottom,
                                  rectl.xRight - rectl.xLeft,
                                  rectl.yTop   - rectl.yBottom,
                                  hwnd, HWND_TOP, 0L, NULL, NULL );
                WinSendMsg( hwndNewName, EM_CLEAR, 0, 0 );
                WinSendMsg( hwndNewName, EM_SETTEXTLIMIT,
                            MPFROMSHORT( MAX_HOFNAME ), 0 );
                WinSetDlgItemText( hwnd, ID_TXT_CLEAR, (PSZ)LS( STR_HOF_CONGRATS ));
                WinPostMsg( hwnd, WM_USER_SET_FOCUS, 0, 0 );
            } else {
                WinShowWindow( WinWindowFromID( hwnd, ID_BUT_CLEAR_1 ), TRUE );
                WinSetDlgItemText( hwnd, ID_TXT_CLEAR, (PSZ)LS( STR_HOF_CLEAR_1 ));
            }

            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        case WM_USER_SET_FOCUS : {
            WinSetFocus( HWND_DESKTOP, hwndNewName );
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_COMMAND : {
            USHORT usCommand = SHORT1FROMMP( mp1 );

            switch ( usCommand ) {

                case ID_BUT_CLEAR_1 : {
                    ULONG ulStyles;
                    HWND hwndText = WinWindowFromID( hwnd, ID_TXT_CLEAR );
                    ulStyles = WinQueryWindowULong( hwndText, QWL_STYLE );
                    ulStyles = ( ulStyles & ~(ULONG)( DT_RIGHT | DT_CENTER )) | DT_LEFT;
                    WinSetWindowULong( hwndText, QWL_STYLE, ulStyles );
                    WinSetDlgItemText( hwnd, ID_TXT_CLEAR, (PSZ)LS( STR_HOF_CLEAR_2 ));
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
                    WinSetDlgItemText( hwnd, ID_TXT_CLEAR, (PSZ)LS( STR_HOF_CLEARED ));
                    WinShowWindow( WinWindowFromID( hwnd, ID_BUT_CLEAR_2 ), FALSE );
                    for ( iLoop = 0; iLoop < 3; iLoop++ ) {
                        IniData.HofTime[ iLoop ] = 999;
                        strcpy( IniData.HofName[ iLoop ], PSZ_HOF_NOBODY );
                    }
                    ShowHofData( hwnd );
                    break;
                }

                default : {
                    if ( iHofIndex >= 0 ) {
                        WinQueryWindowText( hwndNewName, MAX_HOFNAME,
                                            IniData.HofName[ iHofIndex ] );
                        WinDestroyWindow( hwndNewName );
                    }
                    WinDismissDlg( hwnd, TRUE );
                    break;
                }
            }

            mReturn = MRFROMLONG( 0L );
            break;
        }

        default :
            mReturn = WinDefDlgProc( hwnd, ulMsg, mp1, mp2 );
            break;
    }

    return mReturn;
}

static VOID ShowHofData( HWND hwnd ) {
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

/* EOF */
