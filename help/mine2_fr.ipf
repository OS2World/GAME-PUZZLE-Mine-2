.*==============================================================*
.*                                                              *
.* MINE2_FR.IPF - Aide en francais pour Mine/2                 *
.*                                                              *
.*==============================================================*
:userdoc.

:h1 res=3100 name=HELP_PAGE_GENERAL.Bienvenue dans Mine/2
:i1 id=HELP.Demineur
:artwork align=center name='HELP\HEADER.BMP'.
:p.Mine/2 est un jeu populaire pour un seul joueur.
:p.Le but du jeu est de trouver toutes les mines sur le champ
de jeu aussi vite que possible sans en decouvrir aucune.
:p.Informations connexes:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW.(re)demarrer:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW.comment jouer:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.conseils et astuces:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.niveaux:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF.palmares:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT.quitter:elink.
:eul.

:h1 res=3101 name=HELP_PAGE_NEW.Nouvelle Partie
:i2 refid=HELP.Nouvelle Partie
:p.Avec :hp2.Nouveau jeu:ehp2. dans le menu Jeu, vous pouvez demarrer
une nouvelle partie a tout moment.
:p.
:nt.Vous pouvez aussi cliquer sur
:artwork runin name='HELP\GAMEBUT0.BMP'.
ou appuyer sur F2.:ent.

:h1 res=3102 name=HELP_PAGE_LEVEL.Niveaux Predefinis
:i2 refid=HELP.Niveaux
:p.Vous pouvez choisir parmi trois niveaux predefinis ou definir le votre.
:p.Selectionnez un niveau dans le menu Options.
:ul compact.
:li.Debutant
:li.Avance
:li.Professionnel
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.Personnalise:elink.
:eul.
:nt.Seuls les niveaux predefinis sont reconnus par le
:link reftype=hd refid=HELP_PAGE_HOF.Palmares:elink..:ent.

:h1 res=3103 name=HELP_PAGE_USERDEF.Niveau Personnalise
:i2 refid=HELP.Personnalise
:p.Ici vous pouvez specifier votre propre champ de jeu.
:xmp.
 hauteur &colon. de 8 a 40
 largeur &colon. de 8 a 40
 mines   &colon. de 0 a hauteur*largeur*0.5
:exmp.
:p.Pour les grands champs, une resolution de 800x600 ou plus est recommandee.
:nt.Seuls les
:link reftype=hd refid=HELP_PAGE_LEVEL.niveaux predefinis:elink. sont reconnus par le
:link reftype=hd refid=HELP_PAGE_HOF.Palmares:elink..:ent.

:h1 res=3104 name=HELP_PAGE_POINTER.Pointeur
:i2 refid=HELP.Pointeur
:p.Vous pouvez changer la forme du pointeur de la souris sur le champ
de jeu pour l'une des images suivantes.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (par defaut)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

:h1 res=3105 name=HELP_PAGE_SPECIAL.Options Speciales
:i2 refid=HELP.Options Speciales
:p.:hp2.Points d'interrogation:ehp2.
:p.Active l'etat inconnu pour les cases (marque d'un point d'interrogation).
:p.:hp2.Securite:ehp2.
:p.Quand cette option est activee, aucune action n'est effectuee si le pointeur
de la souris est a moins de 2 pixels d'un bord de case.
:p.:hp2.Grandes cases:ehp2.
:p.Agrandit la taille des cases de 16 a 20 pixels.

:h1 res=3106 name=HELP_PAGE_HOF.Palmares
:i2 refid=HELP.Palmares
:p.Le
:font facename=Helv size=24x18.
:sl compact.
:li. PAL-
:li. MA-
:li. RES
:esl.
:font facename=default size=0x0.
:p.enregistre les meilleurs temps et noms pour trois niveaux.

:h1 res=3107 name=HELP_PAGE_EXIT.Quitter
:i2 refid=HELP.Quitter
:p.Pour quitter Mine/2, vous pouvez&colon.
:ul compact.
:li.Selectionner Quitter dans le menu Jeu (Ctrl+X)
:li.Double-cliquer sur le menu systeme
:eul.
:p.Tous les parametres sont sauvegardes pour votre prochaine session.

:h1 res=3108 name=HELP_PAGE_KEYS.Raccourcis Clavier
:i2 refid=HELP.Touches
:p.:hp2.TOUCHES DE JEU:ehp2.
:dl tsize=10 break=all.
:dt.F2
:dd.Nouvelle partie
:dt.F4
:dd.Statistiques
:dt.Ctrl+N
:dd.Nouvelle partie
:dt.Ctrl+Q
:dd.Abandonner la partie
:dt.Ctrl+P
:dd.Pause / reprendre
:dt.Ctrl+X
:dd.Quitter le programme
:dt.Ctrl+S
:dd.Statistiques
:dt.Ctrl+B
:dd.Execution en arriere-plan on/off
:dt.Esc
:dd.Abandonner la partie
:edl.
:p.:hp2.TOUCHES D'AIDE:ehp2.
:dl tsize=10 break=all.
:dt.Esc
:dd.Panneau d'aide precedent
:dt.Alt+F4
:dd.Fermer l'aide
:edl.

:h1 res=3109 name=HELP_PAGE_ABOUT.A Propos de Mine/2
:i2 refid=HELP.A propos
:hp1.
.ce Ce programme a ete ecrit par&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael Brastle, Vienne (Autriche)
:ehp1.
:p.Porte sur ArcaOS/eComStation/OS2 par la communaute OS2World.

:h1 res=3110 name=HELP_PAGE_STATISTIC.Statistiques
:i2 refid=HELP.Statistiques
:p.Le dialogue Statistiques affiche votre historique de jeu.
:p.Pour chaque niveau, il enregistre&colon.
:ul compact.
:li.Temps de jeu total
:li.Parties demarrees
:li.Parties gagnees
:li.Parties perdues
:li.Parties abandonnees
:eul.

:h1 name=HELP_PAGE_HINTS.Conseils et Astuces
:i2 refid=HELP.Conseils
:p.Aucun :hp2.conseil ni astuce:ehp2. n'est necessaire.
:p.Essayez dans cet ordre&colon.
:ul compact.
:li.Faire attention
:li.Combiner
:li.Essayer tout simplement
:eul.

:h1 name=HELP_PAGE_HOW.Comment Jouer
:i2 refid=HELP.Comment jouer
:p.La zone de jeu se compose du compteur de mines, de la minuterie et du champ.
:p.Relacher le bouton gauche de la souris sur une case donne l'un de ces resultats&colon.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. aucune mine a proximite - sur
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. nombre de mines voisines
:li.:artwork runin name='HELP\BOMBED.BMP'. mine - jeu termine
:eul.
:p.Quand une case n'a pas de mines voisines, toutes les cases avoisinantes
sont automatiquement decouvertes.
:nt.Le but est de decouvrir toutes les cases :hp5.sans:ehp5. mines.:ent.
:p.Utilisez le bouton droit de la souris pour changer l'etat d'une case&colon.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. non marque (par defaut)
:li.:artwork runin name='HELP\MARKED.BMP'. signale comme mine
:li.:artwork runin name='HELP\QUESTION.BMP'. inconnu (optionnel)
:eul.
:p.Les cases signalees ne peuvent pas etre decouvertes accidentellement.
:p.Si vous avez signale toutes les mines autour d'une case numerotee, cliquez
avec les deux boutons de la souris simultanement pour decouvrir les voisines restantes.

:euserdoc.
