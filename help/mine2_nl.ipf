.*==============================================================*
.*                                                              *
.* MINE2_NL.IPF - Nederlandse hulp voor Mine/2                 *
.*                                                              *
.*==============================================================*
:userdoc.

:h1 res=3100 name=HELP_PAGE_GENERAL.Welkom bij Mine/2
:i1 id=HELP.Mijnenveld
:artwork align=center name='HELP\HEADER.BMP'.
:p.Mine/2 is een populair spel voor een speler.
:p.Het doel van het spel is om alle mijnen op het speelveld zo snel
mogelijk te vinden zonder er een op te graven.
:p.Verwante informatie:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW.(her)starten:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW.hoe te spelen:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.tips en trucs:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.niveaus:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF.eregalerij:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT.afsluiten:elink.
:eul.

:h1 res=3101 name=HELP_PAGE_NEW.Nieuw Spel
:i2 refid=HELP.Nieuw Spel
:p.Met :hp2.Nieuw:ehp2. in het menu Spel start u een nieuw spel,
ongeacht de huidige toestand.
:p.
:nt.U kunt ook klikken op
:artwork runin name='HELP\GAMEBUT0.BMP'.
of F2 drukken.:ent.

:h1 res=3102 name=HELP_PAGE_LEVEL.Voorgedefinieerde Niveaus
:i2 refid=HELP.Voorgedefinieerde Niveaus
:p.U kunt kiezen uit drie voorgedefinieerde niveaus of uw eigen veld defini‰ren.
:p.Selecteer een niveau via het menu Opties.
:ul compact.
:li.Beginner
:li.Gevorderd
:li.Professioneel
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.Gebruikersdefinitie:elink.
:eul.
:nt.Alleen de voorgedefinieerde niveaus worden herkend door de
:link reftype=hd refid=HELP_PAGE_HOF.Eregalerij:elink..:ent.

:h1 res=3103 name=HELP_PAGE_USERDEF.Gebruikersdefinitie
:i2 refid=HELP.Gebruikersdefinitie
:p.Hier kunt u uw eigen speelveld opgeven.
:xmp.
 hoogte &colon. van 8 tot 40
 breedte&colon. van 8 tot 40
 mijnen &colon. van 0 tot hoogte*breedte*0.5
:exmp.
:p.Voor brede velden wordt een resolutie van 800x600 of hoger aanbevolen.
:nt.Alleen
:link reftype=hd refid=HELP_PAGE_LEVEL.voorgedefinieerde niveaus:elink. worden herkend
door de :link reftype=hd refid=HELP_PAGE_HOF.Eregalerij:elink..:ent.

:h1 res=3104 name=HELP_PAGE_POINTER.Cursor
:i2 refid=HELP.Cursor
:p.U kunt de vorm van de muiscursor op het speelveld wijzigen
naar een van de volgende afbeeldingen.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (standaard)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

:h1 res=3105 name=HELP_PAGE_SPECIAL.Speciale Opties
:i2 refid=HELP.Speciale Opties
:p.:hp2.Vraagtekens:ehp2.
:p.Schakelt de onbekende toestand in voor vakjes (gemarkeerd met een vraagteken).
:p.:hp2.Veiligheid:ehp2.
:p.Als ingeschakeld, wordt er geen actie ondernomen als de muiscursor
minder dan 2 pixels van een vakjesrand verwijderd is.
:p.:hp2.Grote blokken:ehp2.
:p.Vergroot de vakjesgrootte van 16 naar 20 pixels.

:h1 res=3106 name=HELP_PAGE_HOF.Eregalerij
:i2 refid=HELP.Eregalerij
:p.De
:font facename=Helv size=24x18.
:sl compact.
:li. ERE-
:li. GA-
:li. LERIJ
:esl.
:font facename=default size=0x0.
:p.registreert de snelste tijden en namen voor drie niveaus.

:h1 res=3107 name=HELP_PAGE_EXIT.Afsluiten
:i2 refid=HELP.Afsluiten
:p.Om Mine/2 af te sluiten kunt u&colon.
:ul compact.
:li.Afsluiten selecteren in het menu Spel (Ctrl+X)
:li.Dubbelklikken op het systeemmenu
:eul.
:p.Alle instellingen worden bewaard voor de volgende sessie.

:h1 res=3108 name=HELP_PAGE_KEYS.Toetsen
:i2 refid=HELP.Toetsen
:p.:hp2.SPELTOETSEN:ehp2.
:dl tsize=10 break=all.
:dt.F2
:dd.Nieuw spel
:dt.F4
:dd.Statistieken
:dt.Ctrl+N
:dd.Nieuw spel
:dt.Ctrl+Q
:dd.Spel stoppen
:dt.Ctrl+P
:dd.Pauze / hervatten
:dt.Ctrl+X
:dd.Programma afsluiten
:dt.Ctrl+S
:dd.Statistieken
:dt.Ctrl+B
:dd.Achtergrond aan/uit
:dt.Esc
:dd.Spel stoppen
:edl.
:p.:hp2.HELPTOETSEN:ehp2.
:dl tsize=10 break=all.
:dt.Esc
:dd.Vorig helppaneel
:dt.Alt+F4
:dd.Help sluiten
:edl.

:h1 res=3109 name=HELP_PAGE_ABOUT.Over Mine/2
:i2 refid=HELP.Over
:hp1.
.ce Dit programma is geschreven door&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael Brastle, Wenen (Oostenrijk)
:ehp1.
:p.Geporteerd naar ArcaOS/eComStation/OS2 door de OS2World gemeenschap.

:h1 res=3110 name=HELP_PAGE_STATISTIC.Statistieken
:i2 refid=HELP.Statistieken
:p.Het statistiekendialoog toont uw spelgeschiedenis.
:p.Per niveau wordt bijgehouden&colon.
:ul compact.
:li.Totale speeltijd
:li.Gestarte spellen
:li.Gewonnen spellen
:li.Verloren spellen
:li.Afgebroken spellen
:eul.

:h1 name=HELP_PAGE_HINTS.Tips en Trucs
:i2 refid=HELP.Tips
:p.Er zijn geen :hp2.tips of trucs:ehp2. nodig.
:p.Probeer het in deze volgorde&colon.
:ul compact.
:li.Let goed op
:li.Combineer
:li.Probeer gewoon
:eul.

:h1 name=HELP_PAGE_HOW.Hoe te Spelen
:i2 refid=HELP.Hoe te spelen
:p.Het spelgebied bestaat uit de mijnteller, de timer en het speelveld.
:p.De linkermuisknop loslaten op een vakje geeft een van deze resultaten&colon.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. geen mijnen in de buurt - veilig
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. aantal aangrenzende mijnen
:li.:artwork runin name='HELP\BOMBED.BMP'. mijn - spel voorbij
:eul.
:p.Als een vakje geen aangrenzende mijnen heeft, worden alle omliggende
vakjes automatisch onthuld.
:nt.Het doel is alle vakjes :hp5.zonder:ehp5. mijnen te ontdekken.:ent.
:p.Gebruik de rechtermuisknop om de toestand van een vakje te wisselen&colon.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. ongemarkeerd (standaard)
:li.:artwork runin name='HELP\MARKED.BMP'. gemarkeerd als mijn
:li.:artwork runin name='HELP\QUESTION.BMP'. onbekend (optioneel)
:eul.
:p.Gemarkeerde vakjes kunnen niet per ongeluk worden onthuld.
:p.Als u alle mijnen rondom een genummerd vakje hebt gemarkeerd, klik
dan met beide muisknoppen tegelijk om de overige buren te ontdekken.

:euserdoc.
