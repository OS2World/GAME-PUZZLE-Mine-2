
/* 7-Segment Control
   Class Name  : 7SEGMENT
   Message WM_VALUE: MPFROMLONG(value)
*/

#include <string.h>
#include "mine2.h"
#include "7segment.h"

MRESULT EXPENTRY wp7Seg( HWND hwnd, ULONG ulMessage, MPARAM mp1, MPARAM mp2 );
static VOID Redraw7Seg( HWND hwnd, HPS hps );

HBITMAP  _hbm7Seg;
ULONG    _ul7SegCount = 0;

BOOL Register7SegClass( HAB hab ) {
    return WinRegisterClass( hab, CLASS7SEG, wp7Seg, 0, sizeof( LONG ));
}

MRESULT EXPENTRY wp7Seg( HWND hwnd, ULONG ulMessage, MPARAM mp1, MPARAM mp2 ) {

    MRESULT mReturn;
    HPS     hPresSpace;

    switch( ulMessage ) {

        case WM_CREATE : {
            WinSetWindowUShort( hwnd, QWL_VALUE, 0 );
            if ( _ul7SegCount == 0 ) {
                hPresSpace = WinGetPS( hwnd );
                _hbm7Seg = GpiLoadBitmap( hPresSpace, NULLHANDLE,
                                          ID_BMP_7SEG, 0L, 0L );
                WinReleasePS( hPresSpace );
            }
            _ul7SegCount++;
            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        case WM_PAINT : {
            hPresSpace = WinBeginPaint( hwnd, NULLHANDLE, NULL );
            Redraw7Seg( hwnd, hPresSpace );
            WinEndPaint( hPresSpace );
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_DESTROY : {
            _ul7SegCount--;
            if ( _ul7SegCount == 0 ) {
                hPresSpace = WinGetPS( hwnd );
                GpiSetBitmap( hPresSpace, NULLHANDLE );
                GpiDeleteBitmap( _hbm7Seg );
                WinReleasePS( hPresSpace );
            }
            mReturn = MRFROMLONG( 0L );
            break;
        }

        default :
            mReturn = WinDefWindowProc( hwnd, ulMessage, mp1, mp2 );
            break;
    }

    return mReturn;
}

static VOID Redraw7Seg( HWND hwnd, HPS hps ) {

    LONG   lValue = (LONG)WinQueryWindowULong( hwnd, QWL_VALUE );
    INT    iLoop;
    RECTL  rectl7Seg  = { 0L, 0L, SIZE_BMP_CX, SIZE_BMP_CY };
    POINTL pointl7Seg = { 0L, 0L };
    INT    Digits[ AKTIV_DIGITS ];

    if ( lValue == 0 ) {
        Digits[ 0 ] = 0;
        for ( iLoop = 1; iLoop < AKTIV_DIGITS; iLoop++ )
            Digits[ iLoop ] = OFFSET_BMP_BLANK;
    } else if ( lValue > 0 ) {
        for ( iLoop = 0; iLoop < AKTIV_DIGITS; iLoop++ ) {
            if ( lValue > 0 ) {
                Digits[ iLoop ] = lValue % 10;
                lValue /= 10;
            } else {
                Digits[ iLoop ] = OFFSET_BMP_BLANK;
            }
        }
    } else {
        lValue = -lValue;
        Digits[ AKTIV_DIGITS - 1 ] = OFFSET_BMP_MINUS;
        for ( iLoop = 0; iLoop < ( AKTIV_DIGITS - 1 ); iLoop++ ) {
            if ( lValue > 0 ) {
                Digits[ iLoop ] = lValue % 10;
                lValue /= 10;
            } else {
                Digits[ iLoop ] = OFFSET_BMP_BLANK;
            }
        }
    }

    for ( iLoop = AKTIV_DIGITS - 1; iLoop >= 0; iLoop-- ) {
        rectl7Seg.xLeft  = SIZE_BMP_CX * Digits[ iLoop ];
        rectl7Seg.xRight = rectl7Seg.xLeft + SIZE_BMP_CX;
        WinDrawBitmap( hps, _hbm7Seg, &rectl7Seg, &pointl7Seg,
                       0L, 0L, DBM_NORMAL );
        pointl7Seg.x += SIZE_BMP_CX;
    }
}

/* EOF */
