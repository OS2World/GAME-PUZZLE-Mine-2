#pragma strings( readonly )

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mine2.h"

extern HWND hwndFrame;

#define MESSAGE_SIZE 1024              // max Errorstringlength

// ---------------------------------------------------------------------------

void Error( PSZ pszFile, USHORT usLine, PSZ pszFormat, ... ) {

    PSZ     pszMsg;
    va_list VaribleArgumentList;

    (VOID)pszFile;
    (VOID)usLine;

    // --- allocate memory for Errorstring -----------------------------------

    if (( pszMsg = (PSZ)malloc( MESSAGE_SIZE * sizeof( CHAR ))) == NULL ) {

        DosBeep( 1000                      // Frequency (Hz)
               , 2000 );                   // Duration  (ms)

    } else {

        HWND  hwndMBOwner = HWND_DESKTOP;
        ULONG ulMBStyles  = MB_OK | MB_MOVEABLE;

        if ( hwndFrame != NULLHANDLE ) {
            hwndMBOwner = hwndFrame;
            ulMBStyles |= MB_APPLMODAL; // Parent != Owner
        } /* endif */

        // --- copy Argumentlist into Errorstring -----------------------------

        va_start( VaribleArgumentList, pszFormat );

        vsprintf( pszMsg, pszFormat, VaribleArgumentList );

        va_end( VaribleArgumentList );

        pszMsg[ MESSAGE_SIZE - 1 ] = '\0';     // terminate

        // --- notification of the user ---------------------------------------

        WinAlarm( HWND_DESKTOP          // Desktop-window handle
                , WA_ERROR );           // Alarm style

        WinMessageBox( HWND_DESKTOP     // Parent-window handle
                     , hwndMBOwner      // Requested owner-window handle
                     , pszMsg           // Messagebox window message
                     , "Error"          // Messagebox window title
                     , 0                // Messagebox window identity
                     , ulMBStyles );    // Messagebox window style

        // --- free memory ----------------------------------------------------

        free( pszMsg );

    } /*endif */

    return;
}

// --- EOF ------------------------------------------------------
