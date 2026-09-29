.*==============================================================*
.*                                                              *
.* MINE2_ES.IPF - Ayuda en espanol para Mine/2                 *
.*                                                              *
.*==============================================================*
:userdoc.

:h1 res=3100 name=HELP_PAGE_GENERAL.Bienvenido a Mine/2
:i1 id=HELP.Buscaminas
:artwork align=center name='HELP\HEADER.BMP'.
:p.Mine/2 es un popular juego para un jugador.
:p.El objetivo del juego es encontrar todas las minas en el campo
de juego lo mas rapido posible sin descubrir ninguna.
:p.Informacion relacionada:
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_NEW.(re)iniciar:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOW.como jugar:elink.
:li.:link reftype=hd refid=HELP_PAGE_HINTS.trucos y consejos:elink.
:li.:link reftype=hd refid=HELP_PAGE_LEVEL.niveles:elink.
:li.:link reftype=hd refid=HELP_PAGE_HOF.salon de la fama:elink.
:li.:link reftype=hd refid=HELP_PAGE_EXIT.salir:elink.
:eul.

:h1 res=3101 name=HELP_PAGE_NEW.Nuevo Juego
:i2 refid=HELP.Nuevo Juego
:p.Con :hp2.Nuevo:ehp2. del menu Juego puede iniciar un nuevo juego
en cualquier momento.
:p.
:nt.Tambien puede hacer clic en
:artwork runin name='HELP\GAMEBUT0.BMP'.
o pulsar F2.:ent.

:h1 res=3102 name=HELP_PAGE_LEVEL.Niveles Predefinidos
:i2 refid=HELP.Niveles Predefinidos
:p.Puede elegir entre tres niveles predefinidos o definir el suyo propio.
:p.Seleccione un nivel desde el menu Opciones.
:ul compact.
:li.Novato
:li.Avanzado
:li.Profesional
:eul.
:ul compact.
:li.:link reftype=hd refid=HELP_PAGE_USERDEF.Personalizado:elink.
:eul.
:nt.Solo los niveles predefinidos son reconocidos por el
:link reftype=hd refid=HELP_PAGE_HOF.Salon de la Fama:elink..:ent.

:h1 res=3103 name=HELP_PAGE_USERDEF.Nivel Personalizado
:i2 refid=HELP.Nivel Personalizado
:p.Aqui puede especificar su propio campo de juego.
:xmp.
 altura &colon. de 8 a 40
 ancho  &colon. de 8 a 40
 minas  &colon. de 0 a altura*ancho*0.5
:exmp.
:p.Para campos anchos se recomienda una resolucion de 800x600 o superior.
:nt.Solo los
:link reftype=hd refid=HELP_PAGE_LEVEL.niveles predefinidos:elink. son reconocidos por el
:link reftype=hd refid=HELP_PAGE_HOF.Salon de la Fama:elink..:ent.

:h1 res=3104 name=HELP_PAGE_POINTER.Puntero
:i2 refid=HELP.Puntero
:p.Puede cambiar la forma del puntero del raton en el campo de juego
por una de las siguientes imagenes.
:ul compact.
:li.:artwork runin name='HELP\PTR1.BMP'. (predeterminado)
:li.:artwork runin name='HELP\PTR2.BMP'.
:li.:artwork runin name='HELP\PTR3.BMP'.
:li.:artwork runin name='HELP\PTR4.BMP'.
:eul.

:h1 res=3105 name=HELP_PAGE_SPECIAL.Opciones Especiales
:i2 refid=HELP.Opciones Especiales
:p.:hp2.Usar [?]:ehp2.
:p.Activa el estado desconocido para las casillas (marcado con interrogacion).
:p.:hp2.Seguridad:ehp2.
:p.Cuando esta activado, no se realiza ninguna accion si el puntero
del raton esta a menos de 2 pixels del borde de una casilla.
:p.:hp2.Bloques Grandes:ehp2.
:p.Aumenta el tamano de las casillas de 16 a 20 pixels.

:h1 res=3106 name=HELP_PAGE_HOF.Salon de la Fama
:i2 refid=HELP.Salon de la Fama
:p.El
:font facename=Helv size=24x18.
:sl compact.
:li. SALON
:li. DE LA
:li. FAMA
:esl.
:font facename=default size=0x0.
:p.registra los mejores tiempos y nombres de tres jugadores por nivel.

:h1 res=3107 name=HELP_PAGE_EXIT.Salir
:i2 refid=HELP.Salir
:p.Para salir de Mine/2 puede&colon.
:ul compact.
:li.Seleccionar Salir del menu Juego (Ctrl+X)
:li.Hacer doble clic en el menu de sistema
:eul.
:p.Todos los ajustes se guardan para la proxima sesion.

:h1 res=3108 name=HELP_PAGE_KEYS.Teclas
:i2 refid=HELP.Teclas
:p.:hp2.TECLAS DEL JUEGO:ehp2.
:dl tsize=10 break=all.
:dt.F2
:dd.Nuevo juego
:dt.F4
:dd.Estadisticas
:dt.Ctrl+N
:dd.Nuevo juego
:dt.Ctrl+Q
:dd.Abandonar partida
:dt.Ctrl+P
:dd.Pausar / reanudar
:dt.Ctrl+X
:dd.Salir del programa
:dt.Ctrl+S
:dd.Estadisticas
:dt.Ctrl+B
:dd.Activar/desactivar ejecucion en fondo
:dt.Esc
:dd.Abandonar partida
:edl.
:p.:hp2.TECLAS DE AYUDA:ehp2.
:dl tsize=10 break=all.
:dt.Esc
:dd.Panel de ayuda anterior
:dt.Alt+F4
:dd.Cerrar ayuda
:edl.

:h1 res=3109 name=HELP_PAGE_ABOUT.Acerca de Mine/2
:i2 refid=HELP.Acerca de
:hp1.
.ce Este programa fue escrito por&colon.
:artwork align=center name='HELP\MIKE.BMP'.
.ce Michael Brastle, Viena (Austria)
:ehp1.
:p.Portado a ArcaOS/eComStation/OS2 por la comunidad OS2World.

:h1 res=3110 name=HELP_PAGE_STATISTIC.Estadisticas
:i2 refid=HELP.Estadisticas
:p.El dialogo de estadisticas muestra el historial de juego.
:p.Para cada nivel se registra&colon.
:ul compact.
:li.Tiempo total de juego
:li.Partidas iniciadas
:li.Partidas ganadas
:li.Partidas perdidas
:li.Partidas abandonadas
:eul.

:h1 name=HELP_PAGE_HINTS.Trucos y Consejos
:i2 refid=HELP.Trucos
:p.No son necesarios :hp2.trucos ni consejos:ehp2.
:p.Pruebe en este orden&colon.
:ul compact.
:li.Preste atencion
:li.Combine
:li.Solo intente
:eul.

:h1 name=HELP_PAGE_HOW.Como Jugar
:i2 refid=HELP.Como jugar
:p.El area de juego consta del contador de minas, el temporizador y el campo.
:p.Al soltar el boton izquierdo del raton sobre una casilla, los resultados posibles son&colon.
:ul compact.
:li.:artwork runin name='HELP\NEIGH_0.BMP'. sin minas cercanas - seguro
:li.:artwork runin name='HELP\NEIGH_1.BMP'.
:artwork runin name='HELP\NEIGH_2.BMP'. ..
:artwork runin name='HELP\NEIGH_8.BMP'. numero de minas vecinas
:li.:artwork runin name='HELP\BOMBED.BMP'. mina - fin del juego
:eul.
:p.Si una casilla no tiene minas vecinas, todas las casillas circundantes
se descubren automaticamente.
:nt.El objetivo es descubrir todas las casillas :hp5.sin:ehp5. minas.:ent.
:p.Use el boton derecho del raton para cambiar el estado de una casilla&colon.
:ul compact.
:li.:artwork runin name='HELP\DEFAULT.BMP'. sin marcar (predeterminado)
:li.:artwork runin name='HELP\MARKED.BMP'. marcada como mina
:li.:artwork runin name='HELP\QUESTION.BMP'. desconocida (opcional)
:eul.
:p.Las casillas marcadas no se pueden descubrir accidentalmente.
:p.Si ha marcado todas las minas alrededor de una casilla numerada, haga clic
con ambos botones del raton simultaneamente para descubrir las vecinas restantes.

:euserdoc.
