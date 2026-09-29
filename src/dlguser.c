
#include <stdlib.h>
#include <stdio.h>
#include "mine2.h"

extern HAB    hAnchorBlock;
extern INIDATA IniData;

static HWND hwndCirc = NULLHANDLE;
static HWND hwndVScr = NULLHANDLE;
static HWND hwndHScr = NULLHANDLE;
static HWND hwndRecX = NULLHANDLE;
static HWND hwndRecY = NULLHANDLE;
static HWND hwndText = NULLHANDLE;
static SIZEL  sizelCurtain  = { 0L, 0L };
static POINTL pointlCurtain = { 0L, 0L };

MRESULT EXPENTRY DlgFktUserDef( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 );
static VOID UpdateRect( BOOL fCurtain );

BOOL DlgUserDef( HWND hwnd ) {
    return (BOOL)(( WinDlgBox( HWND_DESKTOP, hwnd, DlgFktUserDef,
                               NULLHANDLE, ID_DLG_USERDEF, NULL ) == DID_OK )
                  ? TRUE : FALSE );
}

MRESULT EXPENTRY DlgFktUserDef( HWND hwnd, ULONG ulMsg, MPARAM mp1, MPARAM mp2 ) {

    MRESULT mReturn;

    switch ( ulMsg ) {

        case WM_INITDLG : {
            RECTL rectl, rectlV, rectlH;
            HWND  hwndBmp;

            hwndRecX = WinWindowFromID( hwnd, ID_BGR_RECTL_X );
            hwndRecY = WinWindowFromID( hwnd, ID_BGR_RECTL_Y );
            hwndCirc = WinWindowFromID( hwnd, ID_CSL_MINES );
            hwndVScr = WinWindowFromID( hwnd, ID_VSL_CY );
            hwndHScr = WinWindowFromID( hwnd, ID_HSL_CX );
            hwndText = WinWindowFromID( hwnd, FID_TITLEBAR );
            hwndBmp  = WinWindowFromID( hwnd, ID_BMP_GRID );

            WinQueryWindowRect( hwndHScr, &rectlH );
            WinMapWindowPoints( hwndHScr, hwnd, (PVOID)&rectlH, 2L );
            WinQueryWindowRect( hwndVScr, &rectlV );
            WinMapWindowPoints( hwndVScr, hwnd, (PVOID)&rectlV, 2L );
            WinQueryWindowRect( hwndBmp, &rectl );
            pointlCurtain.x = rectlH.xLeft + (( rectlH.xRight - rectlH.xLeft ) - rectl.xRight ) / 2L;
            pointlCurtain.y = rectlV.yBottom + (( rectlV.yTop - rectlV.yBottom ) - rectl.yTop ) / 2L;
            WinSetWindowPos( hwndBmp, NULLHANDLE,
                             pointlCurtain.x, pointlCurtain.y,
                             0L, 0L, SWP_MOVE );
            sizelCurtain.cx = rectl.xRight;
            sizelCurtain.cy = rectl.yTop;

            WinSendMsg( hwndHScr, SBM_SETSCROLLBAR,
                        MPFROMSHORT( IniData.cx ),
                        MPFROM2SHORT( 8, 40 ));
            WinSendMsg( hwndVScr, SBM_SETSCROLLBAR,
                        MPFROMSHORT( IniData.cy ),
                        MPFROM2SHORT( 8, 40 ));
            UpdateRect( TRUE );
            WinSendMsg( hwndCirc, CSM_SETVALUE,
                        MPFROMLONG( IniData.Mines ), 0 );
            UpdateRect( FALSE );
            WinSendMsg( hwndCirc, CSM_SETINCREMENT,
                        MPFROMSHORT( 1L ), MPFROMSHORT( 1L ));

            mReturn = WinDefDlgProc( hwnd, ulMsg, mp1, mp2 );
            break;
        }

        case WM_HSCROLL : {
            if ( SHORT1FROMMP( mp1 ) == ID_HSL_CX ) {
                SHORT sValue = 0;
                switch ( SHORT2FROMMP( mp2 )) {
                    case SB_LINELEFT  : sValue = -1; break;
                    case SB_LINERIGHT : sValue =  1; break;
                    case SB_PAGELEFT  : sValue = -8; break;
                    case SB_PAGERIGHT : sValue =  8; break;
                    case SB_SLIDERPOSITION :
                    case SB_ENDSCROLL : UpdateRect( TRUE ); break;
                    default : break;
                }
                if ( sValue != 0 ) {
                    sValue = (SHORT)( sValue + SHORT1FROMMR( WinSendMsg(
                                hwndHScr, SBM_QUERYPOS, 0, 0 )));
                    WinSendMsg( hwndHScr, SBM_SETPOS, MPFROMSHORT( sValue ), 0 );
                }
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_VSCROLL : {
            if ( SHORT1FROMMP( mp1 ) == ID_VSL_CY ) {
                SHORT sValue = 0;
                switch ( SHORT2FROMMP( mp2 )) {
                    case SB_LINEUP    : sValue = -1; break;
                    case SB_LINEDOWN  : sValue =  1; break;
                    case SB_PAGEUP    : sValue = -8; break;
                    case SB_PAGEDOWN  : sValue =  8; break;
                    case SB_SLIDERPOSITION :
                    case SB_ENDSCROLL : UpdateRect( TRUE ); break;
                    default : break;
                }
                if ( sValue != 0 ) {
                    sValue = (SHORT)( sValue + SHORT1FROMMR( WinSendMsg(
                                hwndVScr, SBM_QUERYPOS, 0, 0 )));
                    WinSendMsg( hwndVScr, SBM_SETPOS, MPFROMSHORT( sValue ), 0 );
                }
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_CONTROL : {
            if ( mp1 == MPFROM2SHORT( ID_CSL_MINES, CSN_CHANGED ))
                UpdateRect( FALSE );
            mReturn = WinDefDlgProc( hwnd, ulMsg, mp1, mp2 );
            break;
        }

        case WM_COMMAND : {
            USHORT usCommand = SHORT1FROMMP( mp1 );
            if ( usCommand == DID_OK ) {
                IniData.cx = SHORT1FROMMR( WinSendMsg( hwndHScr, SBM_QUERYPOS, 0, 0 ));
                IniData.cy = SHORT1FROMMR( WinSendMsg( hwndVScr, SBM_QUERYPOS, 0, 0 ));
                WinSendMsg( hwndCirc, CSM_QUERYVALUE,
                            MPFROMP( &IniData.Mines ), 0 );
                IniData.Mines = (USHORT)min(( IniData.cx * IniData.cy ) / 2,
                                            IniData.Mines );
            }
            WinDismissDlg( hwnd, usCommand );
            mReturn = 0;
            break;
        }

        default :
            mReturn = WinDefDlgProc( hwnd, ulMsg, mp1, mp2 );
            break;
    }

    return mReturn;
}

static VOID UpdateRect( BOOL fCurtain ) {

    LONG  NewCX, NewCY;
    CHAR  pszText[ 32 ];
    SHORT Mines = 0;

    NewCX = SHORT1FROMMR( WinSendMsg( hwndHScr, SBM_QUERYPOS, 0, 0 ));
    NewCY = SHORT1FROMMR( WinSendMsg( hwndVScr, SBM_QUERYPOS, 0, 0 ));

    if ( fCurtain ) {
        WinSendMsg( hwndCirc, CSM_SETRANGE,
                    MPFROMSHORT( 0L ),
                    MPFROMSHORT(( NewCX * NewCY ) / 2 ));
    }
    WinSendMsg( hwndCirc, CSM_QUERYVALUE, MPFROMP( &Mines ), 0 );

    sprintf( pszText, "%d x %d, %d Mines",
             NewCX, NewCY,
             min( Mines, ( NewCX * NewCY ) / 2 ));
    WinSetWindowText( hwndText, pszText );

    if ( fCurtain ) {
        WinSetWindowPos( hwndRecX, NULLHANDLE,
                         pointlCurtain.x, pointlCurtain.y,
                         sizelCurtain.cx, ( 40 - NewCY ) * 4L,
                         SWP_MOVE | SWP_SIZE );
        WinSetWindowPos( hwndRecY, NULLHANDLE,
                         pointlCurtain.x + NewCX * 4L, pointlCurtain.y,
                         sizelCurtain.cx - NewCX * 4L, sizelCurtain.cy,
                         SWP_MOVE | SWP_SIZE );
    }
}

/* EOF */
