
#ifndef _MINE2_H_
#define _MINE2_H_

    #define INCL_DOS
    #define INCL_WIN
    #define INCL_GPI
    #define INCL_ERRORS
    #include <os2.h>

    #define ID_RESOURCE          1000
    #define ID_POINTER_1         1001
    #define ID_POINTER_2         1002
    #define ID_POINTER_3         1003
    #define ID_POINTER_4         1004
    #define ID_PTR_BEE_1         1005
    #define ID_PTR_BEE_2         1006

    #define ID_DLG_ABOUT         1100
    #define ID_DLG_USERDEF       1110
    #define ID_HSL_CX            1111
    #define ID_VSL_CY            1112
    #define ID_CSL_MINES         1113
    #define ID_BGR_RECTL_X       1114
    #define ID_BGR_RECTL_Y       1115
    #define ID_BMP_GRID          1116

    #define ID_DLG_HOF           1200
    #define ID_TXT_NOV_NAME      1201 
    #define ID_TXT_ADV_NAME      1202 
    #define ID_TXT_PRO_NAME      1203 
    #define ID_TXT_NOV_TIME      1204 
    #define ID_TXT_ADV_TIME      1205 
    #define ID_TXT_PRO_TIME      1206
    #define ID_BUT_CLEAR_1       1291
    #define ID_BUT_CLEAR_2       1292
    #define ID_TXT_CLEAR         1299

    #define ID_DLG_STAT          1300
    #define ID_BUT_RESET         1301
    #define ID_TXT_RESET         1302
    #define ID_TXT_FIRST_GAME    1303
    #define ID_TXT_TIME_BASE     1310
    #define ID_TXT_STARTED_BASE  1320
    #define ID_TXT_WON_BASE      1330
    #define ID_TXT_LOST_BASE     1340
    #define ID_TXT_ABORT_BASE    1350

    #define ID_WIN_TIME          1900
    #define ID_WIN_COUNT         1901
    #define ID_WIN_BUTTON        1902
    #define ID_WIN_FIELD         1903

    #define ID_MENU_GAME         2100
    #define ID_MENU_NEWGAME      2101
    #define ID_MENU_NOVICE       2111
    #define ID_MENU_ADVANCED     2112
    #define ID_MENU_PROFESSIONAL 2113
    #define ID_MENU_USERDEF      2114
    #define ID_MENU_USERDLG      2115
    #define ID_MENU_POINTER      2120
    #define ID_MENU_STATISTIC    2122
    #define ID_MENU_SPECIAL      2130
    #define ID_MENU_SPECIAL_BIG  2131
    #define ID_MENU_SPECIAL_SAV  2132
    #define ID_MENU_SPECIAL_QUE  2133
    #define ID_MENU_HALL_OF_FAME 2140
    #define ID_MENU_EXIT         2199
    #define ID_MENU_HELP         2200
    #define ID_MENU_HELPINDEX    2201
    #define ID_MENU_HELPGENERAL  2202
    #define ID_MENU_HELPUSING    2203
    #define ID_MENU_HELPKEYS     2204
    #define ID_MENU_ABOUT        2299

    #define ID_HELP_TABLE        3000
    #define ID_SUBTABLE_MENU     3001
    #define ID_SUBTABLE_ABOUT    3002
    #define ID_SUBTABLE_USERDEF  3003
    #define ID_SUBTABLE_HOF      3004
    #define ID_SUBTABLE_STAT     3005

    #define HELP_PAGE_GENERAL    3100
    #define HELP_PAGE_NEW        3101
    #define HELP_PAGE_LEVEL      3102
    #define HELP_PAGE_USERDEF    3103
    #define HELP_PAGE_POINTER    3104
    #define HELP_PAGE_SPECIAL    3105
    #define HELP_PAGE_HOF        3106
    #define HELP_PAGE_EXIT       3107
    #define HELP_PAGE_KEYS       3108
    #define HELP_PAGE_ABOUT      3109
    #define HELP_PAGE_STATISTIC  3110

    #define ID_KEY_NEW           4102
    #define ID_KEY_EXIT          4103
    #define ID_KEY_STATISTIC     4104
    #define ID_KEY_ESCAPE        4199

    #define ID_BMP_FAME          5001
    #define ID_BMP_ABOUT         5002
    #define ID_BMP_7SEG          5003
    #define ID_BMP_BUTTON_NORMAL 5004
    #define ID_BMP_BUTTON_O      5005
    #define ID_BMP_BUTTON_FAIL   5006
    #define ID_BMP_BUTTON_OK     5007
    #define ID_BMP_BUTTON_HINT   5008
    #define ID_BMP_FIELD         5009
    #define ID_BMP_FIELD_BIG     5010

    #define CELL_CX                16
    #define CELL_CY                16
    #define CELL_CX_BIG            20
    #define CELL_CY_BIG            20

    #define OFFSET_BOMB             9
    #define OFFSET_WRONGBOMB       10
    #define OFFSET_KILLERBOMB      11
    #define OFFSET_NORMAL          12
    #define OFFSET_PRESSED         13
    #define OFFSET_FLAG            14
    #define OFFSET_UNKNOWN         15

    #define SIZE_X_BMP_ABOUT     100
    #define SIZE_Y_BMP_ABOUT      80

    #define PSZ_TITLE                "Mine/2"
    #define PSZ_TITLE_HELP           "Help for Mine/2"
    #define PSZ_HELP_FILE_NAME       "mine2.hlp"

    #define INI_FILENAME             "MINE2.INI"
    #define INI_APPLNAME             "MINE2"
    #define INI_KEYNAME              "GAMEDATA"

    #define WC_MINE2     "WC_PRIVATE_MINE2"
    #define WC_MINEFIELD "WC_PRIVATE_FIELD"

    #define ID_TIMER_GAME             ( TID_USERMAX - 1 )
    #define ID_TIMER_ABOUT            ( TID_USERMAX - 2 )

    #define WM_USER_INIT              ( WM_USER + 1 )
    #define WM_USER_START             ( WM_USER + 2 )
    #define WM_USER_END               ( WM_USER + 3 )
    #define WM_USER_SET_BITMAP        ( WM_USER + 4 )
    #define WM_USER_SET_FOCUS         ( WM_USER + 5 )

    #define WM_ENTERWINDOW 0x41E
    #define WM_EXITWINDOW  0x41F

    #define MAX_HOFNAME       20

    typedef struct {
        USHORT GameType;        
        USHORT x, y;
        USHORT cx, cy;
        USHORT Mines;
        USHORT Pointer;
        USHORT Big;
        USHORT Questionmark;
        USHORT Safety;
        USHORT HofTime[ 3 ];
        CHAR   HofName[ 3 ][ MAX_HOFNAME ];
        ULONG  PlayTime[ 4 ];
        ULONG  GamesStarted[ 4 ];
        ULONG  GamesWon[ 4 ];
        ULONG  GamesLost[ 4 ];
        FDATE  FirstGame;
    } INIDATA;

    #define PSZ_HOF_NOBODY  "nobody"
    #define PSZ_HOF_UNKNOWN "unknown"

    #define INITVALUES  { ID_MENU_ADVANCED     \
                        , 100, 410             \
                        , 16, 16               \
                        , 40                   \
                        , ID_POINTER_1         \
                        , 0                    \
                        , (USHORT)-1           \
                        , 0                    \
                        , { 999, 999, 999 }    \
                        , { { PSZ_HOF_NOBODY }, { PSZ_HOF_NOBODY }, { PSZ_HOF_NOBODY }}  \
                        , { 0, 0, 0, 0 }       \
                        , { 0, 0, 0, 0 }       \
                        , { 0, 0, 0, 0 }       \
                        , { 0, 0, 0, 0 }       \
                        , { 1, 10, 0 }         \
                        }

    #define WinRC( hab ) ERRORIDERROR( WinGetLastError( hab ))

    MRESULT EXPENTRY wpMain( HWND, ULONG, MPARAM, MPARAM );
    MRESULT EXPENTRY wpField( HWND, ULONG, MPARAM, MPARAM );
    VOID DlgAbout( HWND );
    BOOL DlgUserDef( HWND );
    VOID DlgHallOfFame( HWND, INT iIndex );
    VOID DlgStatistic( HWND hwnd );
    BOOL HelpConstructor( PSZ pszExeFileName );
    VOID HelpMenuUpdate( VOID );
    VOID HelpDestructor( VOID );
    VOID Error( PSZ pszFile, USHORT usLine, PSZ pszFormat, ... );
    VOID Resize( INT CellX, INT CellY );
 

#endif

// --- EOF ---------------------------------------------------------------------------------------------------
