
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mine2.h"
#include "7segment.h"

#define NOTHING -2

extern HAB      hAnchorBlock;
extern HWND     hwndFrame;
extern HWND     hwndClient;
extern HWND     hwndCount;
extern HWND     hwndTime;
extern HWND     hwndButton;
extern HWND     hwndField;
extern HPOINTER hPointer;
extern INIDATA  IniData;
extern SIZEL    sizelCell;
extern SIZEL    sizelBmpCell;

static HDC   hdcSrc    = NULLHANDLE;
static HPS   hpsSrc    = NULLHANDLE;
static HBITMAP hbmSrc  = NULLHANDLE;
static HPS   hpsWindow = NULLHANDLE;
static ULONG idBitmapCurrent = ID_BMP_BUTTON_NORMAL;
static LONG  Hidden     = 0;
static PBYTE FieldData  = NULL;
static BOOL  fGameInProcess = FALSE;
static BOOL  fStartTimer    = FALSE;
static BOOL  fButton1       = FALSE;
static BOOL  fButton2       = FALSE;

static VOID BlitIt( LONG x, LONG y, LONG offset );
static VOID SetButtonBitmap( ULONG idBitmap );
static VOID InitField( INT iBombs );
static VOID IncField( LONG x, LONG y );
static VOID SkipMines( LONG x, LONG y );
static VOID MarkMineArea( LONG x, LONG y );
static UINT Marked( LONG x, LONG y );
static UINT Click( LONG x, LONG y );
static VOID GameEnd( BOOL Winner );
static VOID Press( LONG x, LONG y, BOOL fBig );
static VOID Press2( LONG x, LONG y, LONG What );

MRESULT EXPENTRY wpField( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ) {

    MRESULT mReturn;

    switch ( msg ) {

        case WM_CREATE : {
            SIZEL sizelField = { 0L, 0L };
            DEVOPENSTRUC dop = { NULL, "DISPLAY", NULL, NULL, NULL, NULL, NULL, NULL, NULL };

            srand( WinGetCurrentTime( hAnchorBlock ));

            hdcSrc = DevOpenDC( hAnchorBlock, OD_MEMORY, "*", 3L,
                                (PVOID)&dop, NULLHANDLE );
            hpsSrc = GpiCreatePS( hAnchorBlock, hdcSrc, &sizelField,
                                  PU_PELS | GPIA_ASSOC | GPIT_MICRO );
            hbmSrc = GpiLoadBitmap( hpsSrc, NULLHANDLE,
                                    (ULONG)( IniData.Big ? ID_BMP_FIELD_BIG : ID_BMP_FIELD ),
                                    0L, 0L );
            GpiSetBitmap( hpsSrc, hbmSrc );
            hpsWindow = WinGetPS( hwnd );
            FieldData = NULL;
            mReturn = MRFROMSHORT( FALSE );
            break;
        }

        case WM_DESTROY : {
            WinSetCapture( HWND_DESKTOP, NULLHANDLE );
            WinReleasePS( hpsWindow );
            if ( FieldData != NULL ) free( FieldData );
            GpiSetBitmap( hpsSrc, NULLHANDLE );
            GpiDeleteBitmap( hbmSrc );
            GpiDestroyPS( hpsSrc );
            DevCloseDC( hdcSrc );
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_USER_SET_BITMAP : {
            GpiSetBitmap( hpsSrc, NULLHANDLE );
            GpiDeleteBitmap( hbmSrc );
            hbmSrc = GpiLoadBitmap( hpsSrc, NULLHANDLE,
                                    (ULONG)( SHORT1FROMMP( mp1 ) ? ID_BMP_FIELD_BIG : ID_BMP_FIELD ),
                                    0L, 0L );
            GpiSetBitmap( hpsSrc, hbmSrc );
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_MOUSEMOVE : {
            WinSetPointer( HWND_DESKTOP, hPointer );
            if ( fGameInProcess && fButton1 ) {
                Press( SHORT1FROMMP( mp1 ) / sizelCell.cx,
                       SHORT2FROMMP( mp1 ) / sizelCell.cy,
                       fButton2 );
            }
            mReturn = MPFROMSHORT( FALSE );
            break;
        }

        case WM_EXITWINDOW : {
            if ( fGameInProcess && fButton1 )
                Press( NOTHING, NOTHING, fButton2 );
            mReturn = WinDefWindowProc( hwnd, msg, mp1, mp2 );
            break;
        }

        case WM_BUTTON1DOWN :
        case WM_BUTTON2DOWN : {
            if ( WinQueryActiveWindow( HWND_DESKTOP ) != hwndFrame ) {
                WinSetActiveWindow( HWND_DESKTOP, hwndFrame );
            } else if ( fGameInProcess ) {
                WinSetCapture( HWND_DESKTOP, hwnd );
                if ( msg == WM_BUTTON1DOWN ) {
                    fButton1 = TRUE;
                    fButton2 = (BOOL)( (ULONG)WinGetKeyState( HWND_DESKTOP, VK_BUTTON2 ) & 0x8000 ? TRUE : FALSE );
                    SetButtonBitmap( ID_BMP_BUTTON_O );
                } else {
                    fButton1 = (BOOL)( (ULONG)WinGetKeyState( HWND_DESKTOP, VK_BUTTON1 ) & 0x8000 ? TRUE : FALSE );
                    fButton2 = TRUE;
                }
                if ( fButton1 ) {
                    Press( SHORT1FROMMP( mp1 ) / sizelCell.cx,
                           SHORT2FROMMP( mp1 ) / sizelCell.cy,
                           fButton2 );
                }
            }
            mReturn = MPFROMSHORT( FALSE );
            break;
        }

        case WM_BUTTON1UP :
        case WM_BUTTON2UP : {
            if ( fGameInProcess ) {
                LONG x = SHORT1FROMMP( mp1 ) / sizelCell.cx;
                LONG y = SHORT2FROMMP( mp1 ) / sizelCell.cy;

                WinSetCapture( HWND_DESKTOP, NULLHANDLE );
                if ( fButton1 ) SetButtonBitmap( ID_BMP_BUTTON_NORMAL );
                if ( fButton1 ) Press( NOTHING, NOTHING, fButton2 );

                if (( x < 0 ) || ( x >= IniData.cx ) || ( y < 0 ) || ( y >= IniData.cy )) {
                    ;
                } else if ( IniData.Safety &&
                            !((((SHORT1FROMMP(mp1)+2) % sizelCell.cx) > 3) &&
                              (((SHORT2FROMMP(mp1)+2) % sizelCell.cy) > 3))) {
                    ;
                } else if ( fButton1 & fButton2 ) {
                    UINT uMarked, uFailed;
                    UINT uValue = FieldData[ x * IniData.cy + y ];
                    if ( uValue < 8 ) {
                        uMarked  = Marked( x  , y+1 ) + Marked( x  , y-1 );
                        uMarked += Marked( x+1, y   ) + Marked( x-1, y   );
                        uMarked += Marked( x+1, y+1 ) + Marked( x+1, y-1 );
                        uMarked += Marked( x-1, y+1 ) + Marked( x-1, y-1 );
                        if ( uValue == uMarked ) {
                            uFailed  = Click( x  , y+1 ) + Click( x  , y-1 );
                            uFailed += Click( x+1, y   ) + Click( x-1, y   );
                            uFailed += Click( x+1, y+1 ) + Click( x+1, y-1 );
                            uFailed += Click( x-1, y+1 ) + Click( x-1, y-1 );
                            if ( uFailed > 0 ) GameEnd( FALSE );
                            else if ( Hidden == 0 ) GameEnd( TRUE );
                        }
                    }
                } else if ( fButton1 ) {
                    if ( !fStartTimer ) {
                        WinPostMsg( hwndClient, WM_USER_START, 0, 0 );
                        fStartTimer = TRUE;
                    }
                    if ( Click( x, y )) GameEnd( FALSE );
                    else if ( Hidden == 0 ) GameEnd( TRUE );
                } else if ( fButton2 ) {
                    UINT uValue = FieldData[ x * IniData.cy + y ];
                    if ( uValue & 0x80 ) {
                        LONG Offset;
                        LONG lCount = (LONG)WinQueryWindowULong( hwndCount, QWL_VALUE );
                        uValue += 0x10;
                        switch (( uValue >> 4 ) & 0x03 ) {
                            case 0x01: Offset = OFFSET_FLAG; lCount--; break;
                            case 0x02:
                                if ( IniData.Questionmark ) {
                                    Offset = OFFSET_UNKNOWN;
                                } else {
                                    Offset = OFFSET_NORMAL; uValue &= 0x8F;
                                }
                                lCount++;
                                break;
                            default: Offset = OFFSET_NORMAL; uValue &= 0x8F; break;
                        }
                        WinSetWindowULong( hwndCount, QWL_VALUE, (ULONG)lCount );
                        WinInvalidateRect( hwndCount, NULL, FALSE );
                        BlitIt( x, y, Offset );
                        FieldData[ x * IniData.cy + y ] = (BYTE)uValue;
                    }
                }
                fButton1 = fButton2 = FALSE;
            }
            mReturn = MPFROMSHORT( FALSE );
            break;
        }

        case WM_PAINT : {
            LONG  x, y;
            UINT  uValue;
            RECTL rectl;
            HPS   hps = WinBeginPaint( hwnd, NULLHANDLE, &rectl );
            if ( FieldData != NULL ) {
                for ( x = 0; x < IniData.cx; x++ ) {
                    for ( y = 0; y < IniData.cy; y++ ) {
                        uValue = FieldData[ x * IniData.cy + y ];
                        if ( uValue & 0x80 ) {
                            switch (( uValue >> 4 ) & 0x03 ) {
                                case 0x01: uValue = OFFSET_FLAG;    break;
                                case 0x02: uValue = OFFSET_UNKNOWN; break;
                                default:   uValue = OFFSET_NORMAL;  break;
                            }
                        } else {
                            uValue &= 0x0F;
                        }
                        BlitIt( x, y, (LONG)uValue );
                    }
                }
            }
            WinEndPaint( hps );
            mReturn = MRFROMLONG( 0L );
            break;
        }

        case WM_USER_INIT : {
            fStartTimer = FALSE;
            SetButtonBitmap( ID_BMP_BUTTON_NORMAL );
            WinSetWindowULong( hwndCount, QWL_VALUE, IniData.Mines );
            WinInvalidateRect( hwndCount, NULL, FALSE );
            Hidden = IniData.cx * IniData.cy - IniData.Mines;
            if ( FieldData != NULL ) free( FieldData );
            FieldData = malloc( (ULONG)( IniData.cx * IniData.cy ));
            InitField( IniData.Mines );
            WinInvalidateRect( hwnd, NULL, FALSE );
            WinEnableWindow( hwnd, TRUE );
            fGameInProcess = TRUE;
            mReturn = MRFROMLONG( 0L );
            break;
        }

        default :
            mReturn = WinDefWindowProc( hwnd, msg, mp1, mp2 );
            break;
    }

    return mReturn;
}

static VOID BlitIt( LONG x, LONG y, LONG offset ) {
    POINTL aptl[ 4 ];
    /* dest */
    aptl[ 0 ].x = x * sizelCell.cx;
    aptl[ 0 ].y = y * sizelCell.cy;
    aptl[ 1 ].x = aptl[ 0 ].x + sizelCell.cx;
    aptl[ 1 ].y = aptl[ 0 ].y + sizelCell.cy;
    /* source (actual bitmap pixels) */
    aptl[ 2 ].x = offset * sizelBmpCell.cx;
    aptl[ 2 ].y = 0L;
    aptl[ 3 ].x = aptl[ 2 ].x + sizelBmpCell.cx;
    aptl[ 3 ].y = sizelBmpCell.cy;
    GpiBitBlt( hpsWindow, hpsSrc, 4L, aptl, ROP_SRCCOPY, BBO_IGNORE );
}

static VOID SetButtonBitmap( ULONG idBitmap ) {
    if ( idBitmapCurrent != idBitmap ) {
        WNDPARAMS wndParams;
        BTNCDATA  btnCData;
        idBitmapCurrent = idBitmap;
        wndParams.fsStatus  = WPM_CTLDATA;
        wndParams.cbCtlData = sizeof( btnCData );
        wndParams.pCtlData  = &btnCData;
        WinSendMsg( hwndButton, WM_QUERYWINDOWPARAMS, MPFROMP( &wndParams ), 0 );
        GpiDeleteBitmap( btnCData.hImage );
        btnCData.hImage = GpiLoadBitmap( hpsWindow, NULLHANDLE, idBitmap, 0L, 0L );
        WinSendMsg( hwndButton, WM_SETWINDOWPARAMS, MPFROMP( &wndParams ), 0 );
    }
}

static VOID InitField( INT iBombs ) {
    LONG x, y;
    memset( FieldData, 0x80, (ULONG)( IniData.cx * IniData.cy ));
    while ( iBombs > 0 ) {
        x = rand() % IniData.cx;
        y = rand() % IniData.cy;
        if ( FieldData[ x * IniData.cy + y ] != ( OFFSET_BOMB | 0x80 )) {
            FieldData[ x * IniData.cy + y ] = OFFSET_BOMB | 0x80;
            IncField( x  , y+1 ); IncField( x  , y-1 );
            IncField( x+1, y   ); IncField( x-1, y   );
            IncField( x+1, y+1 ); IncField( x+1, y-1 );
            IncField( x-1, y+1 ); IncField( x-1, y-1 );
            iBombs--;
        }
    }
}

static VOID IncField( LONG x, LONG y ) {
    if (( x >= 0 ) && ( x < IniData.cx ) && ( y >= 0 ) && ( y < IniData.cy )) {
        if ( FieldData[ x * IniData.cy + y ] != ( OFFSET_BOMB | 0x80 ))
            FieldData[ x * IniData.cy + y ]++;
    }
}

static UINT Marked( LONG x, LONG y ) {
    if (( x >= 0 ) && ( x < IniData.cx ) && ( y >= 0 ) && ( y < IniData.cy ))
        if ( FieldData[ x * IniData.cy + y ] & 0x10 )
            return 1;
    return 0;
}

static UINT Click( LONG x, LONG y ) {
    UINT Failed = 0, uValue;
    if (( x >= 0 ) && ( x < IniData.cx ) && ( y >= 0 ) && ( y < IniData.cy )) {
        uValue = FieldData[ x * IniData.cy + y ];
        if (( uValue & 0xF0 ) == 0x80 ) {
            uValue &= 0x0F;
            if ( uValue == OFFSET_BOMB ) {
                BlitIt( x, y, OFFSET_KILLERBOMB );
                FieldData[ x * IniData.cy + y ] = OFFSET_KILLERBOMB;
                Failed = 1;
            } else if ( uValue == 0 ) {
                SkipMines( x, y );
            } else {
                BlitIt( x, y, (LONG)uValue );
                FieldData[ x * IniData.cy + y ] = (BYTE)uValue;
                Hidden--;
            }
        }
    }
    return Failed;
}

static VOID MarkMineArea( LONG x, LONG y ) {
    register UINT uValue;
    if (( x >= 0 ) && ( x < IniData.cx ) && ( y >= 0 ) && ( y < IniData.cy )) {
        uValue = FieldData[ x * IniData.cy + y ];
        if (( uValue & 0x50 ) == 0 ) {
            FieldData[ x * IniData.cy + y ] = (BYTE)( uValue | 0x40 );
            if (( uValue & 0x0F ) == 0 ) {
                MarkMineArea( x  , y+1 ); MarkMineArea( x  , y-1 );
                MarkMineArea( x+1, y   ); MarkMineArea( x-1, y   );
                MarkMineArea( x+1, y+1 ); MarkMineArea( x+1, y-1 );
                MarkMineArea( x-1, y+1 ); MarkMineArea( x-1, y-1 );
            }
        }
    }
}

static VOID SkipMines( LONG x, LONG y ) {
    UINT uValue;
    MarkMineArea( x, y );
    for ( x = 0; x < IniData.cx; x++ ) {
        for ( y = 0; y < IniData.cy; y++ ) {
            uValue = FieldData[ x * IniData.cy + y ];
            if ( uValue & 0x40 ) {
                FieldData[ x * IniData.cy + y ] = (BYTE)( uValue & 0x3F );
                if ( uValue & 0x80 ) {
                    BlitIt( x, y, (LONG)( uValue & 0x0F ));
                    Hidden--;
                }
            }
        }
    }
}

static VOID GameEnd( BOOL Winner ) {
    LONG x, y;
    UINT uValue;
    LONG ShowWhat = Winner ? OFFSET_FLAG : OFFSET_BOMB;
    SetButtonBitmap( (ULONG)( Winner ? ID_BMP_BUTTON_OK : ID_BMP_BUTTON_FAIL ));
    WinPostMsg( hwndClient, WM_USER_END, MPFROMSHORT( Winner ), 0 );
    for ( x = 0; x < IniData.cx; x++ ) {
        for ( y = 0; y < IniData.cy; y++ ) {
            uValue = FieldData[ x * IniData.cy + y ];
            if ( uValue & 0x80 ) {
                if (( uValue & 0x0F ) == OFFSET_BOMB ) {
                    BlitIt( x, y, ShowWhat );
                    FieldData[ x * IniData.cy + y ] = (BYTE)ShowWhat;
                } else if (( uValue & 0xF0 ) == 0x90 ) {
                    BlitIt( x, y, OFFSET_WRONGBOMB );
                    FieldData[ x * IniData.cy + y ] = OFFSET_WRONGBOMB;
                }
            }
        }
    }
    if ( Winner ) {
        WinSetWindowULong( hwndCount, QWL_VALUE, 0L );
        WinInvalidateRect( hwndCount, NULL, FALSE );
    }
    fGameInProcess = FALSE;
}

static VOID Press2( LONG x, LONG y, LONG What ) {
    if (( x >= 0 ) && ( x < IniData.cx ) && ( y >= 0 ) && ( y < IniData.cy ))
        if (( FieldData[ x * IniData.cy + y ] & 0xF0 ) == 0x80 )
            BlitIt( x, y, What );
}

static VOID Press( LONG x, LONG y, BOOL fBig ) {
    static LONG Oldx    = NOTHING, Oldy = NOTHING;
    static BOOL OldfBig = FALSE;

    if (( x != Oldx ) || ( y != Oldy ) || ( fBig != OldfBig )) {
        if ( Oldx != NOTHING ) {
            Press2( Oldx, Oldy, OFFSET_NORMAL );
            if ( OldfBig ) {
                Press2( Oldx  , Oldy+1, OFFSET_NORMAL );
                Press2( Oldx  , Oldy-1, OFFSET_NORMAL );
                Press2( Oldx+1, Oldy  , OFFSET_NORMAL );
                Press2( Oldx-1, Oldy  , OFFSET_NORMAL );
                Press2( Oldx+1, Oldy+1, OFFSET_NORMAL );
                Press2( Oldx+1, Oldy-1, OFFSET_NORMAL );
                Press2( Oldx-1, Oldy+1, OFFSET_NORMAL );
                Press2( Oldx-1, Oldy-1, OFFSET_NORMAL );
            }
            Oldx = NOTHING;
        }
        if (( x >= 0 ) && ( x < IniData.cx ) && ( y >= 0 ) && ( y < IniData.cy )) {
            Press2( x, y, OFFSET_PRESSED );
            Oldx = x; Oldy = y; OldfBig = fBig;
            if ( fBig ) {
                Press2( x  , y+1, OFFSET_PRESSED );
                Press2( x  , y-1, OFFSET_PRESSED );
                Press2( x+1, y  , OFFSET_PRESSED );
                Press2( x-1, y  , OFFSET_PRESSED );
                Press2( x+1, y+1, OFFSET_PRESSED );
                Press2( x+1, y-1, OFFSET_PRESSED );
                Press2( x-1, y+1, OFFSET_PRESSED );
                Press2( x-1, y-1, OFFSET_PRESSED );
            }
        }
    }
}

/* EOF */
