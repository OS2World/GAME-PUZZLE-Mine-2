.*==============================================================*
.*                                                              *
.* MINE2_IT.IPF - Guida in italiano per Mine/2                 *
.*                                                              *
.*==============================================================*
:userdoc.

:h1 res=3100 name=HELP_PAGE_GENERAL.Benvenuto in Mine/2
:i1 id=HELP.Puntaminatore
:artwork align=center name='HELP\HEADER.BMP'.
:p.Mine/2 e un popolare gioco per giocatore singolo.
:p.L'obiettivo del gioco e trovare tutte le mine sul campo di gioco
nel piu breve tempo possibile senza scoprirne nessuna.
:p.Informazioni correlate:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW.(ri)avviare:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW.come giocare:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.consigli e trucchi:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.livelli:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF.albo d'oro:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT.uscire:elink.
:eul.

:h1 res=3101 name=HELP_PAGE_NEW.Nuova Partita
:i2 refid=HELP.Nuova Partita
:p.Con :hp2.Nuova partita:ehp2. nel menu Gioco puoi avviare una nuova
partita in qualsiasi momento.
:p.
:nt.Puoi anche fare clic su
:artwork runin name='HELP\GAMEBUT0.BMP'.
o premere F2.:ent.

:h1 res=3102 name=HELP_PAGE_LEVEL.Livelli Predefiniti
:i2 refid=HELP.Livelli
:p.Puoi scegliere tra tre livelli predefiniti o definire il tuo campo personale.
:p.Seleziona un livello dal menu Opzioni.
:ul compact.
:li.Principiante
:li.Avanzato
:li.Professionista
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.Personalizzato:elink.
:eul.
:nt.Solo i livelli predefiniti sono riconosciuti dall'
:link reftype=hd refid=HELP_PAGE_HOF.Albo d'Oro:elink..:ent.

:h1 res=3103 name=HELP_PAGE_USERDEF.Livello Personalizzato
:i2 refid=HELP.Personalizzato
:p.Qui puoi specificare il tuo campo di gioco personalizzato.
:xmp.
 altezza &colon. da 8 a 40
 larghezza&colon. da 8 a 40
 mine    &colon. da 0 ad altezza*larghezza*0.5
:exmp.
:p.Per campi larghi si raccomanda una risoluzione di 800x600 o superiore.
:nt.Solo i
:link reftype=hd refid=HELP_PAGE_LEVEL.livelli predefiniti:elink. sono riconosciuti dall'
:link reftype=hd refid=HELP_PAGE_HOF.Albo d'Oro:elink..:ent.

:h1 res=3104 name=HELP_PAGE_POINTER.Puntatore
:i2 refid=HELP.Puntatore
:p.Puoi cambiare la forma del puntatore del mouse sul campo di gioco
scegliendo una delle seguenti immagini.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (predefinito)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

:h1 res=3105 name=HELP_PAGE_SPECIAL.Opzioni Speciali
:i2 refid=HELP.Opzioni Speciali
:p.:hp2.Punti interrogativi:ehp2.
:p.Attiva lo stato sconosciuto per le caselle (contrassegnate con un punto interrogativo).
:p.:hp2.Sicurezza:ehp2.
:p.Se attivata, nessuna azione viene eseguita se il puntatore del mouse
e a meno di 2 pixel dal bordo di una casella.
:p.:hp2.Blocchi grandi:ehp2.
:p.Aumenta la dimensione delle caselle da 16 a 20 pixel.

:h1 res=3106 name=HELP_PAGE_HOF.Albo d'Oro
:i2 refid=HELP.Albo d'Oro
:p.L'
:font facename=Helv size=24x18.
:sl compact.
:li. ALBO
:li. D'ORO
:esl.
:font facename=default size=0x0.
:p.registra i tempi piu veloci e i nomi per tre livelli di gioco.

:h1 res=3107 name=HELP_PAGE_EXIT.Uscire
:i2 refid=HELP.Uscire
:p.Per uscire da Mine/2 puoi&colon.
:ul compact.
:li.Selezionare Esci nel menu Gioco (Ctrl+X)
:li.Fare doppio clic sul menu di sistema
:eul.
:p.Tutte le impostazioni vengono salvate per la prossima sessione.

:h1 res=3108 name=HELP_PAGE_KEYS.Tasti
:i2 refid=HELP.Tasti
:p.:hp2.TASTI DI GIOCO:ehp2.
:dl tsize=10 break=all.
:dt.F2
:dd.Nuova partita
:dt.F4
:dd.Statistiche
:dt.Ctrl+N
:dd.Nuova partita
:dt.Ctrl+Q
:dd.Abbandonare la partita
:dt.Ctrl+P
:dd.Pausa / riprendi
:dt.Ctrl+X
:dd.Uscire dal programma
:dt.Ctrl+S
:dd.Statistiche
:dt.Ctrl+B
:dd.Esecuzione in sfondo on/off
:dt.Esc
:dd.Abbandonare la partita
:edl.
:p.:hp2.TASTI DELLA GUIDA:ehp2.
:dl tsize=10 break=all.
:dt.Esc
:dd.Pannello di guida precedente
:dt.Alt+F4
:dd.Chiudere la guida
:edl.

:h1 res=3109 name=HELP_PAGE_ABOUT.Informazioni su Mine/2
:i2 refid=HELP.Informazioni
:hp1.
.ce Questo programma e stato scritto da&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael Brastle, Vienna (Austria)
:ehp1.
:p.Portato su ArcaOS/eComStation/OS2 dalla comunita OS2World.

:h1 res=3110 name=HELP_PAGE_STATISTIC.Statistiche
:i2 refid=HELP.Statistiche
:p.Il dialogo Statistiche mostra la cronologia di gioco.
:p.Per ogni livello viene registrato&colon.
:ul compact.
:li.Tempo di gioco totale
:li.Partite avviate
:li.Partite vinte
:li.Partite perse
:li.Partite abbandonate
:eul.

:h1 name=HELP_PAGE_HINTS.Consigli e Trucchi
:i2 refid=HELP.Consigli
:p.Non sono necessari :hp2.consigli ne trucchi:ehp2..
:p.Prova in questo ordine&colon.
:ul compact.
:li.Presta attenzione
:li.Combina
:li.Prova e basta
:eul.

:h1 name=HELP_PAGE_HOW.Come Giocare
:i2 refid=HELP.Come giocare
:p.L'area di gioco e composta dal contatore di mine, dal timer e dal campo.
:p.Rilasciare il pulsante sinistro del mouse su una casella fornisce uno di questi risultati&colon.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. nessuna mina nelle vicinanze - sicuro
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. numero di mine vicine
:li.:artwork runin name='HELP\BOMBED.BMP'. mina - partita finita
:eul.
:p.Quando una casella non ha mine vicine, tutte le caselle circostanti
vengono scoperte automaticamente.
:nt.L'obiettivo e scoprire tutte le caselle :hp5.senza:ehp5. mine.:ent.
:p.Usa il pulsante destro del mouse per cambiare lo stato di una casella&colon.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. non contrassegnata (predefinito)
:li.:artwork runin name='HELP\MARKED.BMP'. contrassegnata come mina
:li.:artwork runin name='HELP\QUESTION.BMP'. sconosciuta (opzionale)
:eul.
:p.Le caselle contrassegnate non possono essere scoperte accidentalmente.
:p.Se hai contrassegnato tutte le mine intorno a una casella numerata, fai clic
con entrambi i pulsanti del mouse simultaneamente per scoprire le caselle vicine rimanenti.

:euserdoc.
