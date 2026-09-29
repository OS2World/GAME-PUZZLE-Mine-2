# Mine/2 - Minesweeper Clone for ArcaOS / eComStation / OS/2

Mine/2 is a Minesweeper clone for the OS/2 Presentation Manager.
Originally written by Mike (Vienna, Austria) in 1997.

![Mine/2](/doc/Mine2.png)

## Version

1.1

## License

GNU General Public License v3 (GPLv3) — see `doc/License.txt`

## Features

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

## Compile Tools

- OpenWatcom 2.0 (`wmake`, `wcc386`, `wlink`, `wrc`)
- OS/2 Toolkit 4.5
- wipfc (included with OpenWatcom 2.0) — for help files

## Build

```
compile-wat.cmd
```

Output: `bin\mine2.exe`, `bin\help\mine2_*.hlp`

## Requirements

- OS/2 Warp 4, eComStation, or ArcaOS
- 32-bit Presentation Manager

## Authors

- Original: Michael Bruestle (Mike, Vienna) — 1997
- OS/2 port: OS2World community — 2025

## Links

- OS2World: https://www.os2world.com
