
#include "mine2.h"
#include <string.h>
#include <math.h>

extern HAB hAnchorBlock;

#define L_UPDATE_PERIOD  50L
#define L_BITMAP_CX      18L
#define L_BITMAP_CY      26L
#define L_LEFT_EYE_X     20L
#define L_LEFT_EYE_Y     26L
#define L_RIGHT_EYE_X    60L
#define L_RIGHT_EYE_Y    26L
#define L_PUPIL_X        3L
#define L_PUPIL_Y        3L
#define D_PUPIL_MOVE_X   ((double) 6L)
#define D_PUPIL_MOVE_Y   ((double)10L)

static HDC      hdcBitmap  = NULLHANDLE;
static HPS      hpsBitmap  = NULLHANDLE;
static HBITMAP  hBitmap    = NULLHANDLE;
static HWND     hwndBitmap = NULLHANDLE;
static HPS      hpsStatic  = NULLHANDLE;
static PFNWP    pfnwpStaticOld = NULL;
static PFNWP    pfnwpTitleOld  = NULL;
static HPOINTER hptrBee[ 2 ] = { NULLHANDLE, NULLHANDLE };
static INT      Index  = 0;
static BOOL     fActiv = FALSE;

MRESULT EXPENTRY DlgFktAbout( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
static MRESULT EXPENTRY wpStatic( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
static MRESULT EXPENTRY wpTitle( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
static VOID DrawEyes( VOID );

VOID DlgAbout( HWND hwnd ) {
    if ( ! WinDlgBox( HWND_DESKTOP, hwnd, DlgFktAbout,
                      NULLHANDLE, ID_DLG_ABOUT, NULL )) {
        Error( __FILE__, __LINE__,
               "WinDlgBox failed. rc(0x%X)", WinRC( hAnchorBlock ));
    }
}

MRESULT EXPENTRY DlgFktAbout( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {

    MRESULT mReturn;

    switch ( msg ) {

        case WM_INITDLG : {
            SIZEL             sizBitmap = { L_BITMAP_CX, L_BITMAP_CY };
            BITMAPINFOHEADER2 bmp2;
            const DEVOPENSTRUC dop = { NULL, "DISPLAY", NULL, NULL,
                                       NULL, NULL, NULL, NULL, NULL };
            ARCPARAMS arcPara;
            RECTL rectlDialog, rectlBitmap;

            hwndBitmap = WinWindowFromID( hwnd, ID_BMP_ABOUT );
            WinQueryWindowRect( hwnd, &rectlDialog );
            WinQueryWindowRect( hwndBitmap, &rectlBitmap );
            WinSetWindowPos( hwndBitmap, HWND_TOP,
                             ( rectlDialog.xRight - rectlBitmap.xRight ) / 2L,
                             rectlDialog.yTop / 2L,
                             0L, 0L, SWP_MOVE | SWP_SHOW );

            pfnwpStaticOld = WinSubclassWindow( hwndBitmap, wpStatic );
            pfnwpTitleOld  = WinSubclassWindow(
                                 WinWindowFromID( hwnd, FID_TITLEBAR ), wpTitle );

            hdcBitmap = DevOpenDC( hAnchorBlock, OD_MEMORY, "*", 3L,
                                   (PVOID)&dop, NULLHANDLE );
            hpsBitmap = GpiCreatePS( hAnchorBlock, hdcBitmap, &sizBitmap,
                                     PU_PELS | GPIA_ASSOC | GPIT_MICRO );

            memset( &bmp2, 0, sizeof( BITMAPINFOHEADER2 ));
            bmp2.cbFix         = sizeof( BITMAPINFOHEADER2 );
            bmp2.cx            = L_BITMAP_CX;
            bmp2.cy            = L_BITMAP_CY;
            bmp2.cPlanes       = 1;
            bmp2.cBitCount     = 4;
            bmp2.ulCompression = BCA_UNCOMP;
            bmp2.usUnits       = BRU_METRIC;
            bmp2.usRecording   = BRA_BOTTOMUP;
            bmp2.usRendering   = BRH_NOTHALFTONED;
            bmp2.ulColorEncoding = BCE_RGB;

            hBitmap = GpiCreateBitmap( hpsBitmap, &bmp2, 0L, NULL, NULL );
            GpiSetBitmap( hpsBitmap, hBitmap );
            GpiSetColor( hpsBitmap, CLR_BLACK );

            arcPara.lP = L_PUPIL_X;
            arcPara.lQ = L_PUPIL_Y;
            arcPara.lR = 0L;
            arcPara.lS = 0L;
            GpiSetArcParams( hpsBitmap, &arcPara );

            WinStartTimer( hAnchorBlock, hwnd, ID_TIMER_ABOUT, L_UPDATE_PERIOD );

            hptrBee[ 0 ] = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, ID_PTR_BEE_1 );
            hptrBee[ 1 ] = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, ID_PTR_BEE_2 );
            hpsStatic     = WinGetPS( hwndBitmap );

            mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );
            break;
        }

        case WM_ACTIVATE : {
            fActiv  = SHORT1FROMMP( mp1 );
            mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );
            break;
        }

        case WM_TIMER : {
            POINTL ptlPosition;
            RECTL  rectlDlg;
            static POINTL ptlPositionOld = { -1234, -5678 };

            Index = ( Index + 1 ) % 2;
            WinQueryPointerPos( HWND_DESKTOP, &ptlPosition );

            if (( ptlPositionOld.x != ptlPosition.x ) ||
                ( ptlPositionOld.y != ptlPosition.y )) {
                ptlPositionOld.x = ptlPosition.x;
                ptlPositionOld.y = ptlPosition.y;
                DrawEyes();
            }

            if ( fActiv ) {
                WinQueryWindowRect( hwnd, &rectlDlg );
                WinMapWindowPoints( hwnd, HWND_DESKTOP, (PVOID)&rectlDlg, 2L );
                if ( WinPtInRect( hAnchorBlock, &rectlDlg, &ptlPosition ))
                    WinSetPointer( HWND_DESKTOP, hptrBee[ Index ] );
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_MOUSEMOVE : {
            mReturn = fActiv ? MPFROMSHORT( FALSE )
                             : WinDefDlgProc( hwnd, msg, mp1, mp2 );
            break;
        }

        case WM_CONTROLPOINTER : {
            mReturn = fActiv ? MPFROMLONG( hptrBee[ Index ] )
                             : WinDefDlgProc( hwnd, msg, mp1, mp2 );
            break;
        }

        case WM_CLOSE   :
        case WM_COMMAND : {
            WinStopTimer( hAnchorBlock, hwnd, ID_TIMER_ABOUT );
            WinDestroyPointer( hptrBee[ 0 ] );
            WinDestroyPointer( hptrBee[ 1 ] );
            WinReleasePS( hpsStatic );
            GpiSetBitmap( hpsBitmap, NULLHANDLE );
            GpiDeleteBitmap( hBitmap );
            GpiDestroyPS( hpsBitmap );
            DevCloseDC( hdcBitmap );
            WinDismissDlg( hwnd, TRUE );
            mReturn = 0;
            break;
        }

        default :
            mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );
            break;
    }

    return mReturn;
}

static MRESULT EXPENTRY wpStatic( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
    MRESULT mReturn = pfnwpStaticOld( hwnd, msg, mp1, mp2 );
    if ( msg == WM_PAINT )
        DrawEyes();
    return mReturn;
}

static MRESULT EXPENTRY wpTitle( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
    return ( msg == WM_MOUSEMOVE )
           ? MPFROMSHORT( FALSE )
           : pfnwpTitleOld( hwnd, msg, mp1, mp2 );
}

static VOID DrawEyes( VOID ) {

    POINTL ptl;
    POINTL aptl[ 3 ] = {
        { L_LEFT_EYE_X  + L_BITMAP_CX / 2L, L_LEFT_EYE_Y  + L_BITMAP_CY / 2L },
        { L_RIGHT_EYE_X + L_BITMAP_CX / 2L, L_RIGHT_EYE_Y + L_BITMAP_CY / 2L },
        { 0L, 0L }
    };
    double dEyeAngleL, dEyeAngleR;

    WinQueryPointerPos( HWND_DESKTOP, &ptl );
    WinMapWindowPoints( hwndBitmap, HWND_DESKTOP, aptl, 2L );

    dEyeAngleL = atan2( (double)( ptl.y - aptl[ 0 ].y ),
                        (double)( ptl.x - aptl[ 0 ].x ));
    dEyeAngleR = atan2( (double)( ptl.y - aptl[ 1 ].y ),
                        (double)( ptl.x - aptl[ 1 ].x ));

    /* draw left eye */
    GpiErase( hpsBitmap );
    ptl.x = L_BITMAP_CX / 2L + (LONG)( D_PUPIL_MOVE_X * cos( dEyeAngleL ));
    ptl.y = L_BITMAP_CY / 2L + (LONG)( D_PUPIL_MOVE_Y * sin( dEyeAngleL ));
    GpiMove( hpsBitmap, &ptl );
    GpiFullArc( hpsBitmap, DRO_OUTLINEFILL, MAKEFIXED( 1, 0 ));
    aptl[ 0 ].x = L_LEFT_EYE_X;
    aptl[ 0 ].y = L_LEFT_EYE_Y;
    aptl[ 1 ].x = L_LEFT_EYE_X + L_BITMAP_CX;
    aptl[ 1 ].y = L_LEFT_EYE_Y + L_BITMAP_CY;
    GpiBitBlt( hpsStatic, hpsBitmap, 3L, aptl, ROP_SRCCOPY, BBO_IGNORE );

    /* draw right eye */
    GpiErase( hpsBitmap );
    ptl.x = L_BITMAP_CX / 2L + (LONG)( D_PUPIL_MOVE_X * cos( dEyeAngleR ));
    ptl.y = L_BITMAP_CY / 2L + (LONG)( D_PUPIL_MOVE_Y * sin( dEyeAngleR ));
    GpiMove( hpsBitmap, &ptl );
    GpiFullArc( hpsBitmap, DRO_OUTLINEFILL, MAKEFIXED( 1, 0 ));
    aptl[ 0 ].x = L_RIGHT_EYE_X;
    aptl[ 0 ].y = L_RIGHT_EYE_Y;
    aptl[ 1 ].x = L_RIGHT_EYE_X + L_BITMAP_CX;
    aptl[ 1 ].y = L_RIGHT_EYE_Y + L_BITMAP_CY;
    GpiBitBlt( hpsStatic, hpsBitmap, 3L, aptl, ROP_SRCCOPY, BBO_IGNORE );
}

/* EOF */
