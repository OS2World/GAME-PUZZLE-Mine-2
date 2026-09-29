
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mine2.h"

extern HWND hwndFrame;

#define MESSAGE_SIZE 1024

void Error( PSZ pszFile, USHORT usLine, PSZ pszFormat, ... ) {

    PSZ     pszMsg;
    va_list VaribleArgumentList;

    (VOID)pszFile;
    (VOID)usLine;

    if (( pszMsg = (PSZ)malloc( MESSAGE_SIZE * sizeof( CHAR ))) == NULL ) {

        DosBeep( 1000, 2000 );

    } else {

        HWND  hwndMBOwner = HWND_DESKTOP;
        ULONG ulMBStyles  = MB_OK | MB_MOVEABLE;

        if ( hwndFrame != NULLHANDLE ) {
            hwndMBOwner = hwndFrame;
            ulMBStyles |= MB_APPLMODAL;
        }

        va_start( VaribleArgumentList, pszFormat );
        vsprintf( pszMsg, pszFormat, VaribleArgumentList );
        va_end( VaribleArgumentList );

        pszMsg[ MESSAGE_SIZE - 1 ] = '\0';

        WinAlarm( HWND_DESKTOP, WA_ERROR );
        WinMessageBox( HWND_DESKTOP, hwndMBOwner, pszMsg, "Error",
                       0, ulMBStyles );

        free( pszMsg );
    }
}

/* EOF */
