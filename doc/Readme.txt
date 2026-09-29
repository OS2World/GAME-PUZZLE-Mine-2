Mine/2 - Minesweeper Clone for ArcaOS / eComStation / OS/2
============================================================
Version 1.1

DESCRIPTION
-----------
Mine/2 is a Minesweeper clone for OS/2 Presentation Manager.
Originally written by Mike (Vienna, Austria) in 1997 using IBM VisualAge C++.
Ported to OpenWatcom 2.0 by the OS2World community in 2025.

Features:
  - Three skill levels: Novice, Advanced, Professional
  - User-defined field size and mine count
  - Hall of Fame for best times per level
  - Statistics tracking (play time, wins, losses, aborts)
  - 6-language UI: English, Spanish, Dutch, German, French, Italian
  - Language-specific IPF help files
  - Custom pointer graphics (4 styles)
  - Background run when minimized (Ctrl+B)
  - Settings saved to MINE2.INI on exit
  - 7-segment LED display for timer and mine count
  - Animated eyes in the About dialog

LICENSE
-------
  GNU General Public License v3 (GPLv3)
  See doc\License.txt for the full license text.

REQUIREMENTS
------------
  - OS/2 Warp 4, eComStation, or ArcaOS
  - 32-bit Presentation Manager

INSTALLATION
------------
  1. Copy mine2.exe to any folder.
  2. Create a help\ subfolder next to mine2.exe.
  3. Copy the help\mine2_*.hlp files into that help\ subfolder.
  Run mine2.exe.

  The application locates help files automatically based on the selected
  language (e.g. help\mine2_en.hlp for English).

KEYBOARD SHORTCUTS
------------------
  F2 / Ctrl+N   New game
  F4 / Ctrl+S   Statistics
  Ctrl+P        Pause / resume game
  Ctrl+Q        Quit current game (stops timer, stays open)
  Ctrl+X        Exit application
  Ctrl+B        Toggle background run when minimized
  Escape        Quit current game

COMPILING FROM SOURCE
---------------------
  Requirements:
    - OpenWatcom 2.0  (wmake, wcc386, wlink, wrc, wipfc)
    - OS/2 Toolkit 4.5

  Build (on ArcaOS / OS2):
    compile-wat.cmd

  Or directly:
    wmake -f makefile.wat

  Output:
    bin\mine2.exe
    bin\help\mine2_en.hlp  (and es, nl, de, fr, it)

SETTINGS
--------
  Settings are stored in MINE2.INI in the current directory.
  Delete MINE2.INI to reset all settings to defaults.

  Keys saved: level, field size, mine count, pointer style,
              language, background-run flag, save-on-exit flag.

CREDITS
-------
  Original author:  Mike, Vienna, Austria (1997)
  OS/2 port:        OS2World community (2025)
  OS2World site:    https://www.os2world.com
