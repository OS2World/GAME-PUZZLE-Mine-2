
#ifndef _MINE2_H_
#define _MINE2_H_

    #define INCL_WIN
    #define INCL_GPI
    #define INCL_DOS
    #define INCL_ERRORS
    #include <os2.h>

    /* WC_CIRCULARSLIDER fallback if sliderdef.h not included by os2.h */
    #ifndef WC_CIRCULARSLIDER
    #define WC_CIRCULARSLIDER    "#65"
    #define CSS_POINTSELECT      0x0001
    #define CSS_NOTEXT           0x0002
    #define CSM_SETVALUE         0x0165
    #define CSM_QUERYVALUE       0x0166
    #define CSM_SETRANGE         0x0168
    #define CSM_SETINCREMENT     0x016A
    #define CSN_CHANGED          0x0001
    #endif

    #ifndef UINT
    typedef unsigned int UINT;
    #endif

    #ifndef min
    #define min(a,b) ((a)<(b)?(a):(b))
    #endif
    #ifndef max
    #define max(a,b) ((a)>(b)?(a):(b))
    #endif

    /* Resource IDs */
    #define ID_RESOURCE          1000
    #define ID_POINTER_1         1001
    #define ID_POINTER_2         1002
    #define ID_POINTER_3         1003
    #define ID_POINTER_4         1004
    #define ID_PTR_BEE_1         1005
    #define ID_PTR_BEE_2         1006

    /* Dialog IDs */
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
    #define ID_HOF_LBL_NOV       1207
    #define ID_HOF_LBL_ADV       1208
    #define ID_HOF_LBL_PRO       1209
    #define ID_HOF_LBL_SEC1      1210
    #define ID_HOF_LBL_SEC2      1211
    #define ID_HOF_LBL_SEC3      1212
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

    /* Bitmap resource IDs */
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
    #define ID_BMP_HOF           5011
    #define ID_BMP_PTR1          5021
    #define ID_BMP_PTR2          5022
    #define ID_BMP_PTR3          5023
    #define ID_BMP_PTR4          5024

    /* Child window IDs */
    #define ID_WIN_TIME          1900
    #define ID_WIN_COUNT         1901
    #define ID_WIN_BUTTON        1902
    #define ID_WIN_FIELD         1903

    /* Menu IDs - plan ranges */
    /* Game menu: 100-199 */
    #define IDM_NEW              100
    #define IDM_PAUSE            101
    #define IDM_QUIT             102
    #define IDM_EXIT             104
    /* Options menu: 200-299 */
    #define IDM_NOVICE           200
    #define IDM_ADVANCED         201
    #define IDM_PROFESSIONAL     202
    #define IDM_USERDLG          203
    #define IDM_STATISTIC        220
    #define IDM_HOF              221
    #define IDM_SPECIAL_QUE      225
    #define IDM_SPECIAL_SAV      226
    #define IDM_SPECIAL_BIG      227
    #define IDM_BACKGRND         230
    #define IDM_SAVEONEXIT       232
    /* Language submenu: 300-399 */
    #define IDM_LANG_EN          300
    #define IDM_LANG_ES          301
    #define IDM_LANG_NL          302
    #define IDM_LANG_DE          303
    #define IDM_LANG_FR          304
    #define IDM_LANG_IT          305
    /* Help menu: 900-999 */
    #define IDM_HELPUSING        901
    #define IDM_HELPGENERAL      902
    #define IDM_HELPKEYS         903
    #define IDM_HELPINDEX        904
    #define IDM_ABOUT            999
    /* Submenu cascade IDs: 5000+ */
    #define IDM_SUBMENU_GAME     5000
    #define IDM_SUBMENU_OPTIONS  5001
    #define IDM_SUBMENU_LEVEL    5002
    #define IDM_SUBMENU_POINTER  5003
    #define IDM_SUBMENU_SPECIAL  5004
    #define IDM_SUBMENU_LANG     5005
    #define IDM_SUBMENU_HELP     5006

    /* Internal posted command (not in menu) */
    #define ID_MENU_USERDEF      2114

    /* Help IDs */
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

    /* Timers */
    #define ID_TIMER_GAME        ( TID_USERMAX - 1 )
    #define ID_TIMER_ABOUT       ( TID_USERMAX - 2 )

    /* Custom messages */
    #define WM_USER_INIT         ( WM_USER + 1 )
    #define WM_USER_START        ( WM_USER + 2 )
    #define WM_USER_END          ( WM_USER + 3 )
    #define WM_USER_SET_BITMAP   ( WM_USER + 4 )
    #define WM_USER_SET_FOCUS    ( WM_USER + 5 )

    #define WM_ENTERWINDOW       0x041E
    #define WM_EXITWINDOW        0x041F

    /* Bitmap source cell sizes (actual pixels in the .bmp files) */
    #define BMP_CELL_CX          16
    #define BMP_CELL_CY          16
    #define BMP_CELL_CX_BIG      20
    #define BMP_CELL_CY_BIG      20

    /* Display cell sizes (2x zoom) */
    #define CELL_CX              32
    #define CELL_CY              32
    #define CELL_CX_BIG          40
    #define CELL_CY_BIG          40

    /* Field bitmap offsets */
    #define OFFSET_BOMB          9
    #define OFFSET_WRONGBOMB     10
    #define OFFSET_KILLERBOMB    11
    #define OFFSET_NORMAL        12
    #define OFFSET_PRESSED       13
    #define OFFSET_FLAG          14
    #define OFFSET_UNKNOWN       15

    #define SIZE_X_BMP_ABOUT     100
    #define SIZE_Y_BMP_ABOUT     80

    /* Strings */
    #define PSZ_TITLE            "Mine/2"
    #define PSZ_TITLE_HELP       "Help for Mine/2"
    #define PSZ_HELP_FILE_NAME   "mine2.hlp"

    /* INI settings */
    #define INI_FILENAME         "MINE2.INI"
    #define INI_APPLNAME         "MINE2"
    #define INI_KEYNAME          "GAMEDATA"
    #define INI_KEY_SAVEONEXIT   "SAVEONEXIT"
    #define INI_KEY_LANGUAGE     "LANGUAGE"
    #define INI_KEY_BACKGRND     "BACKGRND"

    #define MAX_HOFNAME          20
    #define PSZ_HOF_NOBODY       "nobody"
    #define PSZ_HOF_UNKNOWN      "unknown"

    /* Window classes */
    #define WC_MINE2             "WC_PRIVATE_MINE2"
    #define WC_MINEFIELD         "WC_PRIVATE_FIELD"

    /* Game data structure */
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

    #define INITVALUES  { IDM_ADVANCED          \
                        , 100, 410              \
                        , 16, 16               \
                        , 40                   \
                        , ID_POINTER_1         \
                        , 0                    \
                        , (USHORT)-1           \
                        , 0                    \
                        , { 999, 999, 999 }    \
                        , { { PSZ_HOF_NOBODY }, { PSZ_HOF_NOBODY }, { PSZ_HOF_NOBODY }} \
                        , { 0, 0, 0, 0 }       \
                        , { 0, 0, 0, 0 }       \
                        , { 0, 0, 0, 0 }       \
                        , { 0, 0, 0, 0 }       \
                        , { 1, 10, 0 }         \
                        }

    #define WinRC( hab ) ERRORIDERROR( WinGetLastError( hab ))

    /* Language support */
    #define LANG_EN              0
    #define LANG_ES              1
    #define LANG_NL              2
    #define LANG_DE              3
    #define LANG_FR              4
    #define LANG_IT              5
    #define LANG_COUNT           6

    /* Language string indices */
    #define STR_TITLE            0
    #define STR_GAME             1
    #define STR_NEW_GAME         2
    #define STR_PAUSE_GAME       3
    #define STR_QUIT_GAME        4
    #define STR_EXIT             5
    #define STR_OPTIONS          6
    #define STR_LEVEL            7
    #define STR_NOVICE           8
    #define STR_ADVANCED         9
    #define STR_PROFESSIONAL     10
    #define STR_USER_DEFINED     11
    #define STR_POINTER          12
    #define STR_SPECIAL          13
    #define STR_STATISTICS       14
    #define STR_HALL_OF_FAME     15
    #define STR_USE_QUESTION     16
    #define STR_SAFETY           17
    #define STR_BIG_BLOCKS       18
    #define STR_LANGUAGE         19
    #define STR_BACKGROUND_RUN   20
    #define STR_SAVE_ON_EXIT     21
    #define STR_HELP_MENU        22
    #define STR_HELP_INDEX       23
    #define STR_GENERAL_HELP     24
    #define STR_USING_HELP       25
    #define STR_KEYS_HELP        26
    #define STR_ABOUT            27
    #define STR_HOF_CONGRATS     28
    #define STR_HOF_CLEAR_1      29
    #define STR_HOF_CLEAR_2      30
    #define STR_HOF_CLEARED      31
    #define STR_HOF_SEC          32
    #define STR_COUNT            33

    extern const char * const lang_strings[ LANG_COUNT ][ STR_COUNT ];
    extern int current_lang;
    #define LS(i)  lang_strings[ current_lang ][ (i) ]

    /* Function declarations */
    MRESULT EXPENTRY wpMain( HWND, ULONG, MPARAM, MPARAM );
    MRESULT EXPENTRY wpField( HWND, ULONG, MPARAM, MPARAM );
    VOID DlgAbout( HWND );
    BOOL DlgUserDef( HWND );
    VOID DlgHallOfFame( HWND, INT iIndex );
    VOID DlgStatistic( HWND hwnd );
    BOOL HelpConstructor( PSZ pszExeFileName );
    VOID HelpMenuUpdate( VOID );
    VOID HelpDestructor( VOID );
    VOID HelpReload( VOID );
    VOID Error( PSZ pszFile, USHORT usLine, PSZ pszFormat, ... );
    VOID Resize( INT CellX, INT CellY );
    VOID set_language( int lang );

#endif

/* EOF */
