.*==============================================================*
.*                                                              *
.* MINE2.IPF - Information Tag Language file for the Help       *
.*                                                              *
.*==============================================================*
:userdoc.

.*--------------------------------------------------------------*
.*  Main window extended help                                   *
.*--------------------------------------------------------------*
:h1 res=3100 name=HELP_PAGE_GENERAL.Welcome to mine-sweeping
:i1 id=HELP.Minesweeper
:artwork align=center name='HELP\HEADER.BMP'.
:p.This is a popular game for one person.
:p.The object of the game is to find all the mines on the playing
field as quickly as possible without uncovering any of them.
:p.Related Information:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW  .(re)start minesweeper:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW  .how to play:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.hints &amp. tricks:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.levels:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF  .hall of fame:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT .exit minesweeper:elink.
:eul.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <New>                                                       *
.*--------------------------------------------------------------*
:h1 res=3101 name=HELP_PAGE_NEW.New Game
:i2 refid=HELP.New Game
:p.With :hp2.New:ehp2. from the game menu bar you can start a new game
regardless of the state of the game.
:p.
:nt.A simpler way for this is to click on
:artwork runin name='HELP\GAMEBUT0.BMP'.
or press F2.:ent.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Novice>                                                    *
.*  <Advance>                                                   *
.*  <Professional>                                              *
.*--------------------------------------------------------------*
:h1 res=3102 name=HELP_PAGE_LEVEL.Predefined Levels
:i2 refid=HELP.Predefined Levels
:p.You can choose from three predefined levels or customizing your
own playing field.
:p.To change the current level select one of these items from the game menu.
:ul compact.
:li.Novice
:li.Advanced
:li.Professional
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.User defined:elink.
:eul.
:nt.Only the predefined levels are recognized by the
:link reftype=hd refid=HELP_PAGE_HOF.Hall Of Fame:elink..
:ent.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <User Defined>                                              *
.*--------------------------------------------------------------*
:h1 res=3103 name=HELP_PAGE_USERDEF.Userdefined Levels
:i2 refid=HELP.Userdefined Levels
:p.Here you can specify your own playing field.
:xmp.
 height &colon. from 8 to 40
 width  &colon. from 8 to 40
 mines  &colon. from 0 to height*width*0.5 .. (heavy stuff)
:exmp.
:p.For wide games a screen resolution of 800x600 or better is recommended.
:nt. Only the
:link reftype=hd refid=HELP_PAGE_LEVEL.predefined Levels:elink. are recognized by the
:link reftype=hd refid=HELP_PAGE_HOF.Hall Of Fame:elink..
:ent.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Pointer>                                                   *
.*--------------------------------------------------------------*
:h1 res=3104 name=HELP_PAGE_POINTER.Pointer
:i2 refid=HELP.Pointer
:p.It's possible to change the shape of the mousepointer in the
playing field to one of the following images.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (default)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Special>                                                   *
.*--------------------------------------------------------------*
:h1 res=3105 name=HELP_PAGE_SPECIAL.Special
:i2 refid=HELP.Special
:p.:hp2.Use [?]:ehp2.
:p.To use the unknown squarestate, use this item.
:p.:hp2.Safety:ehp2.
:p.When this item is enabled, no action is taken if the mousepointer
is less then 2 pels away from a squareborder.
:p.:hp2.Big Blocks:ehp2.
:p.With this item the square size is enlarged from 16 pels to 20 pels.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Hall of fame>                                              *
.*--------------------------------------------------------------*
:h1 res=3106 name=HELP_PAGE_HOF.Hall Of Fame
:i2 refid=HELP.Hall Of Fame
:p.The
:font facename=Helv size=24x18.
:sl compact.
:li. HALL
:li. OF
:li. FAME
:esl.
:font facename=default size=0x0.
:p.is a place where the fastest games and the names of three players
are recorded.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Exit>                                                      *
.*--------------------------------------------------------------*
:h1 res=3107 name=HELP_PAGE_EXIT.Exit
:i2 refid=HELP.Exit
:p.If you really want to leave you can
:ul compact.
:li.select exit from game menu bar  or
:li.doubleclick on the sysmenu  or
:li.press F3.
:eul.
:p.All settings are saved for your next try.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Keys help>                                                 *
.*--------------------------------------------------------------*
:h1 res=3108 name=HELP_PAGE_KEYS.Key assignments
:i2 refid=HELP.Keys
:p.The list of keys is arranged in groups.
:p.:hp2.ACCELERATOR KEYS:ehp2.
:dl tsize=5 break=all.
:dt.Esc
:dd.Minimize/restore the game or cancel the dialog
:dt.F1
:dd.Get help
:dt.F2
:dd.New game
:dt.F3
:dd.Exit
:dt.F4
:dd.Statistic information
:edl.
:p.:hp2.HELP KEYS:ehp2.
:dl tsize=5 break=all.
:dt.Esc
:dd.Previous help panel, or end help if only one panel is displayed
:dt.Alt
:dd.Switch TO/OUT action bar
:dt.Alt+F4
:dd.End help or end program
:edl.
:p.:hp2.SYSTEM KEYS:ehp2.
:dl tsize=5 break=all.
:dt.Alt+Esc
:dd.Switch to the next program, including full-screen programs
:dt.Ctrl+Esc
:dd.Switch to the task list
:edl.
:p.:hp2.WINDOW KEYS:ehp2.
:dl tsize=5 break=all.
:dt.Underlined letter
:dd.Move among the choices on the action bar and pull-down submenus or
execute the function chosen
:dt.Alt+Underlined letter
:dd.Execute the function chosen immediately
:edl.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <About>                                                     *
.*--------------------------------------------------------------*
:h1 res=3109 name=HELP_PAGE_ABOUT.Productinformation
:i2 refid=HELP.About me
:hp1.
.ce This program was written by&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael BrÅstle, Vienna (Austria)
:ehp1.

.*--------------------------------------------------------------*
.*  Help menu item                                              *
.*  <Statistics>                                                *
.*--------------------------------------------------------------*
:h1 res=3110 name=HELP_PAGE_STATISTIC.Statistics
:i2 refid=HELP.Statistics
:p.Sometimes it is nice to know something, sometimes not.
:xmp.
d&colon.\sources\private\c\mine2\code>wc *.*

    149     504    4723 7segment.c
     16      31     304 7segment.h
    361    1303   13895 dlgabout.c
    184     709    8018 dlghof.c
    188     700    7242 dlgstat.c
    267     922   10399 dlguser.c
     70     205    2163 error.c
     94     292    3713 help.c
    207     629    7156 mine2.h
    172     651    7500 stdmain.c
    582    2823   24085 wpfield.c
    556    2132   26456 wpmain.c
----------------------------------
   2846   10901  115654 total
:exmp.
.*--------------------------------------------------------------*
.*  Help item                                                   *
.*  <Hints & Tricks>                                            *
.*--------------------------------------------------------------*
:h1 name=HELP_PAGE_HINTS.Hints &amp. Tricks
:i2 refid=HELP.Hints &amp. Tricks
:p.No :hp2.hints &amp. tricks:ehp2. are necessary.
:p.But try it in this order&colon.
:ul compact.
:li.pay attention
:li.combine
:li.just try
:eul.

.*--------------------------------------------------------------*
.*  Help item                                                   *
.*  <How to Play>                                               *
.*--------------------------------------------------------------*
:h1 name=HELP_PAGE_HOW.How to play
:i2 refid=HELP.How to play
:p.The Minesweeper game area consists of the mine counter, the timer
and the playing field.
:p.If you release your left mouse bottom over a square, the following
results are possible.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. congratulation, no mines
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. mines as neighbors
:li.:artwork runin name='HELP\BOMBED.BMP'. bad &amp. end of the game.
:eul.
:p.If the square has no mines as neighbors, you can click on all squares around.
Since this is a stupid job, this is done by the program as long as squares
with no mines are found.
:nt.The target of the game is to find and uncover all squares
:hp5.without:ehp5. mines.:ent.
:p.When a mine is localized you can change the state of the square with
the right mouse button.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. unmarked (default)
:li.:artwork runin name='HELP\MARKED.BMP'. marked
:li.:artwork runin name='HELP\QUESTION.BMP'. unknown (optional)
:eul.
:p.Marked and unknown squares are prevented from uncovering and
every marked square decrements the mine counter.
:p.If you have marked all the mines around a numbered square, uncover
the remaining squares around it by clicking the numbered square with
the left and right mouse buttons simultaneously.

:euserdoc.

