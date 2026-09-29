
#ifndef _LANG_H_
#define _LANG_H_

/* Language table ‹¨«?" LANG_COUNT x STR_COUNT; indices defined in mine2.h */

const char * const lang_strings[ LANG_COUNT ][ STR_COUNT ] = {
    /* LANG_EN */ {
        "Mine/2",                    /* STR_TITLE            */
        "~Game",                     /* STR_GAME             */
        "~New Game\tCtrl+N",         /* STR_NEW_GAME         */
        "~Pause Game\tCtrl+P",       /* STR_PAUSE_GAME       */
        "~Quit Game\tCtrl+Q",        /* STR_QUIT_GAME        */
        "E~xit\tCtrl+X",             /* STR_EXIT             */
        "~Options",                  /* STR_OPTIONS          */
        "~Level",                    /* STR_LEVEL            */
        "N~ovice",                   /* STR_NOVICE           */
        "A~dvanced",                 /* STR_ADVANCED         */
        "~Professional",             /* STR_PROFESSIONAL     */
        "~User Defined...",          /* STR_USER_DEFINED     */
        "Poin~ter",                  /* STR_POINTER          */
        "~Special",                  /* STR_SPECIAL          */
        "S~tatistics...\tCtrl+S",    /* STR_STATISTICS       */
        "~Hall of Fame",             /* STR_HALL_OF_FAME     */
        "~Use [?]",                  /* STR_USE_QUESTION     */
        "~Safety",                   /* STR_SAFETY           */
        "~Big Blocks",               /* STR_BIG_BLOCKS       */
        "~Language",                 /* STR_LANGUAGE         */
        "~Background Run\tCtrl+B",   /* STR_BACKGROUND_RUN   */
        "~Save settings on exit",    /* STR_SAVE_ON_EXIT     */
        "~Help",                     /* STR_HELP_MENU        */
        "Help ~index...",            /* STR_HELP_INDEX       */
        "~General help...",          /* STR_GENERAL_HELP     */
        "~Using help...",            /* STR_USING_HELP       */
        "~Keys help...",             /* STR_KEYS_HELP        */
        "~About...",                 /* STR_ABOUT            */
        "Congratulations!",          /* STR_HOF_CONGRATS     */
        "press here to clear ->",    /* STR_HOF_CLEAR_1      */
        "<- confirm clearing",       /* STR_HOF_CLEAR_2      */
        "cleared!",                  /* STR_HOF_CLEARED      */
        "sec",                       /* STR_HOF_SEC          */
    },
    /* LANG_ES */ {
        "Mine/2",
        "~Juego",
        "~Nuevo juego\tCtrl+N",
        "~Pausar juego\tCtrl+P",
        "~Abandonar juego\tCtrl+Q",
        "S~alir\tCtrl+X",
        "~Opciones",
        "~Nivel",
        "N~ovato",
        "A~vanzado",
        "~Profesional",
        "~Personalizado...",
        "~Puntero",
        "~Especial",
        "~Estadisticas...\tCtrl+S",
        "~Salon de la Fama",
        "~Usar [?]",
        "~Seguridad",
        "~Bloques Grandes",
        "~Idioma",
        "~Ejecutar en fondo\tCtrl+B",
        "~Guardar ajustes al salir",
        "~Ayuda",
        "~Indice de ayuda...",
        "Ayuda ~general...",
        "~Usar la ayuda...",
        "Ayuda de ~teclas...",
        "~Acerca de...",
        "Felicitaciones!",           /* STR_HOF_CONGRATS     */
        "pulsa aqui para borrar ->", /* STR_HOF_CLEAR_1      */
        "<- confirmar borrado",      /* STR_HOF_CLEAR_2      */
        "borrado!",                  /* STR_HOF_CLEARED      */
        "seg",                       /* STR_HOF_SEC          */
    },
    /* LANG_NL */ {
        "Mine/2",
        "~Spel",
        "~Nieuw spel\tCtrl+N",
        "~Pauze\tCtrl+P",
        "~Spel stoppen\tCtrl+Q",
        "A~fsluiten\tCtrl+X",
        "~Opties",
        "~Niveau",
        "~Beginner",
        "~Gevorderd",
        "~Professioneel",
        "~Gebruiker...",
        "~Cursor",
        "~Speciaal",
        "~Statistieken...\tCtrl+S",
        "~Eregalerij",
        "~Vraagtekens",
        "~Veiligheid",
        "~Grote blokken",
        "~Taal",
        "~Achtergrond\tCtrl+B",
        "~Instellingen bewaren",
        "~Help",
        "Help~index...",
        "~Algemene help...",
        "Help ~gebruiken...",
        "~Toetsen help...",
        "~Over...",
        "Gefeliciteerd!",            /* STR_HOF_CONGRATS     */
        "druk hier om te wissen ->", /* STR_HOF_CLEAR_1      */
        "<- wissen bevestigen",      /* STR_HOF_CLEAR_2      */
        "gewist!",                   /* STR_HOF_CLEARED      */
        "sec",                       /* STR_HOF_SEC          */
    },
    /* LANG_DE */ {
        "Mine/2",
        "~Spiel",
        "~Neues Spiel\tCtrl+N",
        "~Pause\tCtrl+P",
        "Spiel ~beenden\tCtrl+Q",
        "~Beenden\tCtrl+X",
        "~Optionen",
        "~Schwierigkeit",
        "~Anfanger",
        "~Fortgeschritten",
        "~Profi",
        "~Benutzerdefiniert...",
        "~Zeiger",
        "~Extras",
        "~Statistik...\tCtrl+S",
        "~Bestenliste",
        "~Fragezeichen",
        "~Sicherheit",
        "~Grosse Felder",
        "~Sprache",
        "~Hintergrund\tCtrl+B",
        "~Einstellungen speichern",
        "~Hilfe",
        "Hilfe~index...",
        "~Allgemeine Hilfe...",
        "Hilfe ~verwenden...",
        "~Tastenhilfe...",
        "~Uber...",
        "Gluckwunsch!",                 /* STR_HOF_CONGRATS     */
        "hier klicken zum Loschen ->",  /* STR_HOF_CLEAR_1      */
        "<- Loschen bestatigen",        /* STR_HOF_CLEAR_2      */
        "geloscht!",                    /* STR_HOF_CLEARED      */
        "Sek",                          /* STR_HOF_SEC          */
    },
    /* LANG_FR */ {
        "Mine/2",
        "~Jeu",
        "~Nouveau jeu\tCtrl+N",
        "~Pause\tCtrl+P",
        "A~bandonner\tCtrl+Q",
        "~Quitter\tCtrl+X",
        "~Options",
        "~Niveau",
        "~Debutant",
        "~Avance",
        "~Professionnel",
        "~Personnalise...",
        "~Pointeur",
        "~Special",
        "~Statistiques...\tCtrl+S",
        "~Palmares",
        "~Points d'interrogation",
        "~Securite",
        "~Grandes cases",
        "~Langue",
        "~Arriere-plan\tCtrl+B",
        "~Sauvegarder les options",
        "~Aide",
        "~Index d'aide...",
        "Aide ~generale...",
        "~Utiliser l'aide...",
        "Aide des ~touches...",
        "~A propos...",
        "Felicitations!",               /* STR_HOF_CONGRATS     */
        "cliquez ici pour effacer ->",  /* STR_HOF_CLEAR_1      */
        "<- confirmer l'effacement",    /* STR_HOF_CLEAR_2      */
        "efface!",                      /* STR_HOF_CLEARED      */
        "sec",                          /* STR_HOF_SEC          */
    },
    /* LANG_IT */ {
        "Mine/2",
        "~Gioco",
        "~Nuova partita\tCtrl+N",
        "~Pausa\tCtrl+P",
        "A~bbandonare\tCtrl+Q",
        "~Esci\tCtrl+X",
        "~Opzioni",
        "~Livello",
        "~Principiante",
        "~Avanzato",
        "~Professionista",
        "~Personalizzato...",
        "~Puntatore",
        "~Speciale",
        "~Statistiche...\tCtrl+S",
        "~Albo d'oro",
        "~Punti interrogativi",
        "~Sicurezza",
        "~Blocchi grandi",
        "~Lingua",
        "~Esecuzione in sfondo\tCtrl+B",
        "~Salva opzioni all'uscita",
        "~Guida",
        "~Indice della guida...",
        "Guida ~generale...",
        "~Utilizzo della guida...",
        "Guida dei ~tasti...",
        "~Informazioni...",
        "Congratulazioni!",                 /* STR_HOF_CONGRATS     */
        "premi qui per cancellare ->",      /* STR_HOF_CLEAR_1      */
        "<- conferma cancellazione",        /* STR_HOF_CLEAR_2      */
        "cancellato!",                      /* STR_HOF_CLEARED      */
        "sec",                              /* STR_HOF_SEC          */
    },
};

#endif

/* EOF */
