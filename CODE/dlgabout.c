#pragma strings( readonly )

#include "mine2.h"
#include <string.h>
#include <math.h>

extern HAB hAnchorBlock;

#define L_UPDATE_PERIOD        50L             // mseconds

#define L_BITMAP_CX            18L
#define L_BITMAP_CY            26L             // size of bitmap
#define L_LEFT_EYE_X           20L
#define L_LEFT_EYE_Y           26L             // lowerleft position of left eye
#define L_RIGHT_EYE_X          60L
#define L_RIGHT_EYE_Y          26L             // lowerleft position of right eye
#define L_PUPIL_X               3L
#define L_PUPIL_Y               3L             // size of the pupil
#define D_PUPIL_MOVE_X        ( (double) 6L )
#define D_PUPIL_MOVE_Y        ( (double)10L )  // max pupildistance from center

HDC      hdcBitmap;
HPS      hpsBitmap;
HBITMAP  hBitmap;
HWND     hwndBitmap;
HPS      hpsStatic;
PFNWP    pfnwpStaticOld = NULL;
PFNWP    pfnwpTitleOld = NULL;
HPOINTER hptrBee[ 2 ] = { NULLHANDLE, NULLHANDLE };
INT      Index = 0;
BOOL     fActiv = FALSE;

BOOL rc;

MRESULT EXPENTRY DlgFktAbout( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY wpStatic( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY wpTitle( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
VOID DrawEyes( VOID );

// ===========================================================================
VOID DlgAbout( HWND hwnd ) {
// ===========================================================================

    if ( ! WinDlgBox( HWND_DESKTOP     // parent
                    , hwnd             // owner
                    , DlgFktAbout      // function
                    , NULLHANDLE       // .dll as resource
                    , ID_DLG_ABOUT     // ID in resource
                    , NULL )) {        // inidata
        Error( __FILE__, __LINE__
             , "WinDlgBox failed. rc(0x%X)", WinRC( hAnchorBlock ));
    } /* endif */
}

// ===========================================================================
MRESULT EXPENTRY DlgFktAbout( HWND   hwnd, ULONG  msg, MPARAM mp1, MPARAM mp2 ) {
// ===========================================================================

    MRESULT  mReturn;

    switch ( msg ) {

        case WM_INITDLG : {

            SIZEL sizBitmap  = { L_BITMAP_CX, L_BITMAP_CY };
            BITMAPINFOHEADER2 bmp2;
            const DEVOPENSTRUC dop        = { NULL
                                            , "DISPLAY"
                                            , NULL
                                            , NULL
                                            , NULL
                                            , NULL
                                            , NULL
                                            , NULL
                                            , NULL };
            ARCPARAMS arcPara;
            RECTL rectlDialog;
            RECTL rectlBitmap;

            hwndBitmap = WinWindowFromID( hwnd, ID_BMP_ABOUT );
            WinQueryWindowRect( hwnd, &rectlDialog );
            WinQueryWindowRect( hwndBitmap, &rectlBitmap );
            WinSetWindowPos( hwndBitmap             // Window handle
                           , HWND_TOP               // Relative window placement order
                           , ( rectlDialog.xRight - rectlBitmap.xRight ) / 2L // Window position, x-coordinate
                           , rectlDialog.yTop / 2L   // Window position, y-coordinate
                           , 0L                     // Window size x
                           , 0L                     // Window size y
                           , SWP_MOVE | SWP_SHOW ); // Window positioning options

            pfnwpStaticOld = WinSubclassWindow( hwndBitmap, wpStatic );
            pfnwpTitleOld  = WinSubclassWindow( WinWindowFromID( hwnd, FID_TITLEBAR ), wpTitle );

            // --- create bitmap in memory -----------------------------------

            hdcBitmap = DevOpenDC( hAnchorBlock        // Anchor-block handle
                                 , OD_MEMORY           // Type of device context
                                 , "*"                 // Device-information token
                                 , 3L                  // Number of items
                                 , (PVOID)&dop         // Open-device-context data area
                                 , NULLHANDLE );       // Compatible-device-context handle
            hpsBitmap = GpiCreatePS( hAnchorBlock      // Anchor-block handle
                                   , hdcBitmap         // Device-context handle
                                   , &sizBitmap        // Presentation-page size
                                   ,   PU_PELS         // Options
                                     | GPIA_ASSOC
                                     | GPIT_MICRO );

            // --- initialize BITMAPINFOHEADER2 ------------------------------

            memset( &bmp2, 0, sizeof( BITMAPINFOHEADER2 ));

            bmp2.cbFix           = sizeof( BITMAPINFOHEADER2 );
            bmp2.cx              = L_BITMAP_CX;
            bmp2.cy              = L_BITMAP_CY;
            bmp2.cPlanes         = 1;
            bmp2.cBitCount       = 4;
            bmp2.ulCompression   = BCA_UNCOMP;
            bmp2.cxResolution    = 0;
            bmp2.cyResolution    = 0;
            bmp2.cclrUsed        = 0;
            bmp2.cclrImportant   = 0;
            bmp2.usUnits         = BRU_METRIC;
            bmp2.usRecording     = BRA_BOTTOMUP;
            bmp2.usRendering     = BRH_NOTHALFTONED;
            bmp2.cSize1          = 0;
            bmp2.cSize2          = 0;
            bmp2.ulColorEncoding = BCE_RGB;
            bmp2.ulIdentifier    = 0;

            // --- create bitmap ---------------------------------------------

            hBitmap = GpiCreateBitmap( hpsBitmap // Presentation-space handle
                                     , &bmp2     // Bit-map information header
                                     , 0L        // Options
                                     , NULL      // Buffer address
                                     , NULL );   // Bit-map information table
            GpiSetBitmap( hpsBitmap  // Presentation-space handle
                        , hBitmap ); // Handle of the bit map to be set
            GpiSetColor( hpsBitmap, CLR_BLACK );

            // --- draw eyes into the bitmap ---------------------------------

            arcPara.lP = L_PUPIL_X;
            arcPara.lQ = L_PUPIL_Y;
            arcPara.lR = 0L;
            arcPara.lS = 0L;
            GpiSetArcParams( hpsBitmap, &arcPara );

            // --- start timer for periodic update ---------------------------

            WinStartTimer( hAnchorBlock        // Anchor-block handle
                         , hwnd                // Window-handle
                         , ID_TIMER_ABOUT      // Timer identifier
                         , L_UPDATE_PERIOD );  // Delay time in milliseconds

            hptrBee[ 0 ] = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, ID_PTR_BEE_1 );
            hptrBee[ 1 ] = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, ID_PTR_BEE_2 );
            hpsStatic = WinGetPS( hwndBitmap );

            mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );

            break;
        }

        case WM_ACTIVATE: {

            fActiv = SHORT1FROMMP( mp1 );
            mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );

            break;
        }

        case WM_TIMER: {

            POINTL ptlPosition;
            RECTL  rectlDlg;
            static POINTL ptlPositionOld = { -1234, -5678 };

            Index = ( Index + 1 ) % 2;

            // --- get mouse-coordinates -------------------------------------

            WinQueryPointerPos( HWND_DESKTOP, &ptlPosition );

            if (( ptlPositionOld.x != ptlPosition.x ) || ( ptlPositionOld.y != ptlPosition.y )) {

                ptlPositionOld.x = ptlPosition.x;
                ptlPositionOld.y = ptlPosition.y;

                DrawEyes();

            } /* endif */

            if ( fActiv ) {
                WinQueryWindowRect( hwnd, &rectlDlg );
                WinMapWindowPoints( hwnd
                                  , HWND_DESKTOP
                                  , (PVOID)&rectlDlg
                                  , 2L );
                if ( WinPtInRect( hAnchorBlock, &rectlDlg, &ptlPosition )) {
                    WinSetPointer( HWND_DESKTOP, hptrBee[ Index ] );
                } /* endif */
            } /* endif */
            mReturn = MRFROMLONG( 0L );

            break;

        }

        case WM_MOUSEMOVE : {

            if ( fActiv ) {
                mReturn = MPFROMSHORT( FALSE );
            } else {
                mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );
            } /* endif */
            break;
        }


        case WM_CONTROLPOINTER : {

            if ( fActiv ) {
                mReturn = MPFROMLONG( hptrBee[ Index ] );
            } else {
                mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );
            } /* endif */
            break;
        }

        case WM_CLOSE   :
        case WM_COMMAND : {

            // --- termination -----------------------------------------------

            WinStopTimer( hAnchorBlock // Anchor-block handle
                        , hwnd         // Window handle that is part of the timer identification
                        , ID_TIMER_ABOUT ); // Timer identifier

            WinDestroyPointer( hptrBee[ 0 ] );
            WinDestroyPointer( hptrBee[ 1 ] );
            WinReleasePS( hpsStatic );

            GpiSetBitmap( hpsBitmap     // Presentation-space handle
                        , NULLHANDLE ); // Free current bitmap
            GpiDeleteBitmap( hBitmap );
            GpiDestroyPS( hpsBitmap );
            DevCloseDC( hdcBitmap );

            WinDismissDlg( hwnd
                         , TRUE );
            mReturn = 0;

            break;
        }

        default : {

            mReturn = WinDefDlgProc( hwnd, msg, mp1, mp2 );
            break;
        }
    }

    return mReturn;
}

// ===========================================================================
MRESULT EXPENTRY wpStatic( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
// ===========================================================================

    MRESULT  mReturn;

    mReturn = pfnwpStaticOld( hwnd, msg, mp1, mp2 );
    if ( msg == WM_PAINT ) {
        DrawEyes();
    } /* endif */

    return mReturn;
}

// ===========================================================================
MRESULT EXPENTRY wpTitle( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {
// ===========================================================================

    MRESULT  mReturn;

    if ( msg == WM_MOUSEMOVE ) {
        mReturn = MPFROMSHORT( FALSE );
    } else {
        mReturn = pfnwpTitleOld( hwnd, msg, mp1, mp2 );
    } /* endif */

    return mReturn;
}

// ===========================================================================
VOID DrawEyes( VOID ) {
// ===========================================================================

    // --- init ------------------------------------------------------

    POINTL ptl;
    POINTL aptl[ 3 ]  = { { L_LEFT_EYE_X  + L_BITMAP_CX / 2L 
                          , L_LEFT_EYE_Y  + L_BITMAP_CY / 2L }  // position in Bitmap
                        , { L_RIGHT_EYE_X + L_BITMAP_CX / 2L 
                          , L_RIGHT_EYE_Y + L_BITMAP_CY / 2L }   // position in Bitmap
                        , { 0L
                          , 0L }};
    double dEyeAngleL, dEyeAngleR;

    WinQueryPointerPos( HWND_DESKTOP, &ptl );

    // --- calculate EyeCenter in world-coordinates ------------------
    
    WinMapWindowPoints( hwndBitmap
                      , HWND_DESKTOP
                      , aptl
                      , 2L );
    
    // --- calculate new eye-angles left -----------------------------
    
    dEyeAngleL = atan2( (double)( ptl.y - aptl[ 0 ].y )
                      , (double)( ptl.x - aptl[ 0 ].x ));
    dEyeAngleR = atan2( (double)( ptl.y - aptl[ 1 ].y )
                      , (double)( ptl.x - aptl[ 1 ].x ));
    
    // --- draw new position left ------------------------------------
    
    GpiErase( hpsBitmap );
    ptl.x  = L_BITMAP_CX / 2L + (LONG)( D_PUPIL_MOVE_X * cos( dEyeAngleL ));
    ptl.y  = L_BITMAP_CY / 2L + (LONG)( D_PUPIL_MOVE_Y * sin( dEyeAngleL ));
    GpiMove( hpsBitmap, &ptl );
    GpiFullArc( hpsBitmap, DRO_OUTLINEFILL, MAKEFIXED(1,0));
    
    // --- display pupil left ----------------------------------------

    aptl[ 0 ].x = L_LEFT_EYE_X;
    aptl[ 0 ].y = L_LEFT_EYE_Y;
    aptl[ 1 ].x = L_LEFT_EYE_X + L_BITMAP_CX;
    aptl[ 1 ].y = L_LEFT_EYE_Y + L_BITMAP_CY;
    GpiBitBlt( hpsStatic, hpsBitmap, 3L, aptl, ROP_SRCCOPY, BBO_IGNORE );
    
    // --- draw new position right -----------------------------------
    
    GpiErase( hpsBitmap );
    ptl.x = L_BITMAP_CX / 2L + (LONG)( D_PUPIL_MOVE_X * cos( dEyeAngleR ));
    ptl.y = L_BITMAP_CY / 2L + (LONG)( D_PUPIL_MOVE_Y * sin( dEyeAngleR ));
    GpiMove( hpsBitmap, &ptl );
    GpiFullArc( hpsBitmap, DRO_OUTLINEFILL, MAKEFIXED(1,0));
    
    // --- display pupil right ---------------------------------------

    aptl[ 0 ].x = L_RIGHT_EYE_X;
    aptl[ 0 ].y = L_RIGHT_EYE_Y;
    aptl[ 1 ].x = L_RIGHT_EYE_X + L_BITMAP_CX;
    aptl[ 1 ].y = L_RIGHT_EYE_Y + L_BITMAP_CY;
    GpiBitBlt( hpsStatic, hpsBitmap, 3L, aptl, ROP_SRCCOPY, BBO_IGNORE );
}

// --- EOF ---------------------------------------------------------------------------------------------------
