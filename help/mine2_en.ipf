.*==============================================================*
.*                                                              *
.* MINE2_EN.IPF - English help for Mine/2                      *
.*                                                              *
.*==============================================================*
:userdoc.

:h1 res=3100 name=HELP_PAGE_GENERAL.Welcome to Mine/2
:i1 id=HELP.Minesweeper
:artwork align=center name='HELP\HEADER.BMP'.
:p.Mine/2 is a popular single-player game.
:p.The object of the game is to find all the mines on the playing
field as quickly as possible without uncovering any of them.
:p.Related Information:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW.(re)start:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW.how to play:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.hints &amp. tricks:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.levels:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF.hall of fame:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT.exit:elink.
:eul.

:h1 res=3101 name=HELP_PAGE_NEW.New Game
:i2 refid=HELP.New Game
:p.With :hp2.New:ehp2. from the Game menu you can start a new game
at any time, regardless of the current state.
:p.
:nt.You can also click on
:artwork runin name='HELP\GAMEBUT0.BMP'.
or press F2.:ent.

:h1 res=3102 name=HELP_PAGE_LEVEL.Predefined Levels
:i2 refid=HELP.Predefined Levels
:p.You can choose from three predefined levels or define your own.
:p.Select a level from the Options menu.
:ul compact.
:li.Novice
:li.Advanced
:li.Professional
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.User Defined:elink.
:eul.
:nt.Only the predefined levels are recognized by the
:link reftype=hd refid=HELP_PAGE_HOF.Hall of Fame:elink..:ent.

:h1 res=3103 name=HELP_PAGE_USERDEF.User Defined Level
:i2 refid=HELP.User Defined Level
:p.Here you can specify your own playing field.
:xmp.
 height &colon. from 8 to 40
 width  &colon. from 8 to 40
 mines  &colon. from 0 to height*width*0.5
:exmp.
:p.For wide fields a resolution of 800x600 or higher is recommended.
:nt.Only
:link reftype=hd refid=HELP_PAGE_LEVEL.predefined levels:elink. are recognized by the
:link reftype=hd refid=HELP_PAGE_HOF.Hall of Fame:elink..:ent.

:h1 res=3104 name=HELP_PAGE_POINTER.Pointer
:i2 refid=HELP.Pointer
:p.You can change the shape of the mouse pointer on the playing field
to one of the following images.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (default)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

:h1 res=3105 name=HELP_PAGE_SPECIAL.Special Options
:i2 refid=HELP.Special Options
:p.:hp2.Use [?]:ehp2.
:p.Enables the unknown square state (marked with a question mark).
:p.:hp2.Safety:ehp2.
:p.When enabled, no action is taken if the mouse pointer is less than
2 pixels away from a square border.
:p.:hp2.Big Blocks:ehp2.
:p.Enlarges the square size from 16 to 20 pixels.

:h1 res=3106 name=HELP_PAGE_HOF.Hall of Fame
:i2 refid=HELP.Hall of Fame
:p.The
:font facename=Helv size=24x18.
:sl compact.
:li. HALL
:li. OF
:li. FAME
:esl.
:font facename=default size=0x0.
:p.records the fastest times and names for three game levels.

:h1 res=3107 name=HELP_PAGE_EXIT.Exit
:i2 refid=HELP.Exit
:p.To exit Mine/2 you can:
:ul compact.
:li.Select Exit from the Game menu (Ctrl+X)
:li.Double-click the system menu
:eul.
:p.All settings are saved for your next session.

:h1 res=3108 name=HELP_PAGE_KEYS.Key Assignments
:i2 refid=HELP.Keys
:p.:hp2.GAME KEYS:ehp2.
:dl tsize=10 break=all.
:dt.F2
:dd.New game
:dt.F4
:dd.Statistics
:dt.Ctrl+N
:dd.New game
:dt.Ctrl+Q
:dd.Quit current game
:dt.Ctrl+P
:dd.Pause / resume
:dt.Ctrl+X
:dd.Exit program
:dt.Ctrl+S
:dd.Statistics
:dt.Ctrl+B
:dd.Toggle background run
:dt.Esc
:dd.Quit current game
:edl.
:p.:hp2.HELP KEYS:ehp2.
:dl tsize=10 break=all.
:dt.Esc
:dd.Previous help panel
:dt.Alt+F4
:dd.Close help
:edl.

:h1 res=3109 name=HELP_PAGE_ABOUT.About Mine/2
:i2 refid=HELP.About
:hp1.
.ce This program was written by&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael Brastle, Vienna (Austria)
:ehp1.
:p.Ported to ArcaOS/eComStation/OS2 by the OS2World community.

:h1 res=3110 name=HELP_PAGE_STATISTIC.Statistics
:i2 refid=HELP.Statistics
:p.The Statistics dialog shows your play history.
:p.For each level it records&colon.
:ul compact.
:li.Total play time
:li.Games started
:li.Games won
:li.Games lost
:li.Games aborted
:eul.

:h1 name=HELP_PAGE_HINTS.Hints &amp. Tricks
:i2 refid=HELP.Hints
:p.No :hp2.hints &amp. tricks:ehp2. are necessary.
:p.Try in this order&colon.
:ul compact.
:li.Pay attention
:li.Combine
:li.Just try
:eul.

:h1 name=HELP_PAGE_HOW.How to Play
:i2 refid=HELP.How to play
:p.The game area consists of the mine counter, the timer and the playing field.
:p.Releasing the left mouse button over a square gives one of these results&colon.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. no mines nearby - safe
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. number of neighboring mines
:li.:artwork runin name='HELP\BOMBED.BMP'. mine - game over
:eul.
:p.When a square has no neighboring mines, all surrounding squares are
uncovered automatically.
:nt.The goal is to uncover all squares :hp5.without:ehp5. mines.:ent.
:p.Use the right mouse button to cycle a square's state&colon.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. unmarked (default)
:li.:artwork runin name='HELP\MARKED.BMP'. flagged as mine
:li.:artwork runin name='HELP\QUESTION.BMP'. unknown (optional)
:eul.
:p.Flagged squares cannot be uncovered accidentally.
:p.If you have flagged all mines around a numbered square, click it
with both mouse buttons simultaneously to uncover the remaining neighbors.

:euserdoc.
