.*==============================================================*
.*                                                              *
.* MINE2_DE.IPF - Deutsche Hilfe fuer Mine/2                   *
.*                                                              *
.*==============================================================*
:userdoc.

:h1 res=3100 name=HELP_PAGE_GENERAL.Willkommen bei Mine/2
:i1 id=HELP.Minesweeper
:artwork align=center name='HELP\HEADER.BMP'.
:p.Mine/2 ist ein beliebtes Einzelspielerspiel.
:p.Ziel des Spiels ist es, alle Minen auf dem Spielfeld so schnell
wie moglich zu finden, ohne eine aufzudecken.
:p.Verwandte Informationen:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW.(neu)starten:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW.wie man spielt:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.Tipps und Tricks:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.Schwierigkeitsstufen:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF.Bestenliste:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT.Beenden:elink.
:eul.

:h1 res=3101 name=HELP_PAGE_NEW.Neues Spiel
:i2 refid=HELP.Neues Spiel
:p.Mit :hp2.Neues Spiel:ehp2. im Menu Spiel starten Sie jederzeit ein
neues Spiel, unabhaengig vom aktuellen Spielstand.
:p.
:nt.Sie koennen auch auf
:artwork runin name='HELP\GAMEBUT0.BMP'.
klicken oder F2 druecken.:ent.

:h1 res=3102 name=HELP_PAGE_LEVEL.Vordefinierte Schwierigkeitsstufen
:i2 refid=HELP.Schwierigkeitsstufen
:p.Sie koennen aus drei vordefinierten Stufen waehlen oder eine eigene
Feldgroesse festlegen.
:p.Waehlen Sie eine Stufe im Menu Optionen.
:ul compact.
:li.Anfaenger
:li.Fortgeschritten
:li.Profi
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.Benutzerdefiniert:elink.
:eul.
:nt.Nur die vordefinierten Stufen werden von der
:link reftype=hd refid=HELP_PAGE_HOF.Bestenliste:elink. erkannt.:ent.

:h1 res=3103 name=HELP_PAGE_USERDEF.Benutzerdefiniertes Spielfeld
:i2 refid=HELP.Benutzerdefiniert
:p.Hier koennen Sie ein eigenes Spielfeld festlegen.
:xmp.
 Hoehe  &colon. von 8 bis 40
 Breite &colon. von 8 bis 40
 Minen  &colon. von 0 bis Hoehe*Breite*0.5
:exmp.
:p.Fuer breite Felder wird eine Aufloesung von 800x600 oder hoeher empfohlen.
:nt.Nur
:link reftype=hd refid=HELP_PAGE_LEVEL.vordefinierte Stufen:elink. werden von der
:link reftype=hd refid=HELP_PAGE_HOF.Bestenliste:elink. erkannt.:ent.

:h1 res=3104 name=HELP_PAGE_POINTER.Zeiger
:i2 refid=HELP.Zeiger
:p.Sie koennen die Form des Mauszeigers auf dem Spielfeld aendern
in eines der folgenden Bilder.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (Standard)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

:h1 res=3105 name=HELP_PAGE_SPECIAL.Erweiterte Optionen
:i2 refid=HELP.Extras
:p.:hp2.Fragezeichen:ehp2.
:p.Schaltet den unbekannten Zustand fuer Felder ein (mit Fragezeichen markiert).
:p.:hp2.Sicherheit:ehp2.
:p.Wenn aktiviert, wird keine Aktion ausgefuehrt, wenn der Mauszeiger
weniger als 2 Pixel von einem Feldrand entfernt ist.
:p.:hp2.Grosse Felder:ehp2.
:p.Vergrossert die Feldgroesse von 16 auf 20 Pixel.

:h1 res=3106 name=HELP_PAGE_HOF.Bestenliste
:i2 refid=HELP.Bestenliste
:p.Die
:font facename=Helv size=24x18.
:sl compact.
:li. BESTEN-
:li. LISTE
:esl.
:font facename=default size=0x0.
:p.speichert die schnellsten Zeiten und Namen fuer drei Schwierigkeitsstufen.

:h1 res=3107 name=HELP_PAGE_EXIT.Beenden
:i2 refid=HELP.Beenden
:p.So beenden Sie Mine/2&colon.
:ul compact.
:li.Beenden im Menu Spiel auswaehlen (Strg+X)
:li.Doppelklick auf das Systemmenuefeld
:eul.
:p.Alle Einstellungen werden fuer die naechste Sitzung gespeichert.

:h1 res=3108 name=HELP_PAGE_KEYS.Tastenbelegung
:i2 refid=HELP.Tasten
:p.:hp2.SPIELTASTEN:ehp2.
:dl tsize=10 break=all.
:dt.F2
:dd.Neues Spiel
:dt.F4
:dd.Statistik
:dt.Strg+N
:dd.Neues Spiel
:dt.Strg+Q
:dd.Spiel beenden
:dt.Strg+P
:dd.Pause / fortsetzen
:dt.Strg+X
:dd.Programm beenden
:dt.Strg+S
:dd.Statistik
:dt.Strg+B
:dd.Hintergrundausfuehrung ein/aus
:dt.Esc
:dd.Spiel beenden
:edl.
:p.:hp2.HILFETASTEN:ehp2.
:dl tsize=10 break=all.
:dt.Esc
:dd.Vorherige Hilfeseite
:dt.Alt+F4
:dd.Hilfe schliessen
:edl.

:h1 res=3109 name=HELP_PAGE_ABOUT.Ueber Mine/2
:i2 refid=HELP.Ueber
:hp1.
.ce Dieses Programm wurde geschrieben von&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael Brastle, Wien (Oesterreich)
:ehp1.
:p.Portiert auf ArcaOS/eComStation/OS2 von der OS2World-Gemeinschaft.

:h1 res=3110 name=HELP_PAGE_STATISTIC.Statistik
:i2 refid=HELP.Statistik
:p.Der Statistikdialog zeigt Ihren Spielverlauf.
:p.Fuer jede Schwierigkeitsstufe wird gespeichert&colon.
:ul compact.
:li.Gesamtspielzeit
:li.Gestartete Spiele
:li.Gewonnene Spiele
:li.Verlorene Spiele
:li.Abgebrochene Spiele
:eul.

:h1 name=HELP_PAGE_HINTS.Tipps und Tricks
:i2 refid=HELP.Tipps
:p.Es sind keine :hp2.Tipps oder Tricks:ehp2. noetig.
:p.Versuchen Sie es in dieser Reihenfolge&colon.
:ul compact.
:li.Aufmerksam sein
:li.Kombinieren
:li.Einfach versuchen
:eul.

:h1 name=HELP_PAGE_HOW.Wie man spielt
:i2 refid=HELP.Spielanleitung
:p.Der Spielbereich besteht aus dem Minenzaehler, der Zeituhr und dem Spielfeld.
:p.Das Loslassen der linken Maustaste ueber einem Feld ergibt eines dieser Ergebnisse&colon.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. keine Minen in der Naehe - sicher
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. Anzahl benachbarter Minen
:li.:artwork runin name='HELP\BOMBED.BMP'. Mine - Spiel vorbei
:eul.
:p.Wenn ein Feld keine benachbarten Minen hat, werden alle umliegenden
Felder automatisch aufgedeckt.
:nt.Das Ziel ist es, alle Felder :hp5.ohne:ehp5. Minen aufzudecken.:ent.
:p.Benutzen Sie die rechte Maustaste, um den Zustand eines Feldes zu aendern&colon.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. nicht markiert (Standard)
:li.:artwork runin name='HELP\MARKED.BMP'. als Mine markiert
:li.:artwork runin name='HELP\QUESTION.BMP'. unbekannt (optional)
:eul.
:p.Markierte Felder koennen nicht versehentlich aufgedeckt werden.
:p.Wenn Sie alle Minen um ein nummeriertes Feld markiert haben, klicken Sie
mit beiden Maustasten gleichzeitig, um die verbleibenden Nachbarn aufzudecken.

:euserdoc.
