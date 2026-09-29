
# OpenWatcom 2.0 makefile for Mine/2
# Build: wmake -f makefile.wat

WATCOM  = $(%WATCOM)

CC      = wcc386
WLINK   = wlink
WRC     = wrc
WIPFC   = wipfc

OUT     = bin
HELPOUT = $(OUT)\help

CFLAGS  = -bt=os2 -5r -mf -zq -w3 -e25 -d0 -i=$(WATCOM)\h\os2 -i=src
LFLAGS  = option quiet, map
RCFLAGS = -r -bt=os2
BINDWF  = -q -bt=os2

OBJS = $(OUT)\stdmain.obj &
       $(OUT)\wpmain.obj  &
       $(OUT)\wpfield.obj &
       $(OUT)\7segment.obj &
       $(OUT)\dlgabout.obj &
       $(OUT)\dlghof.obj  &
       $(OUT)\dlgstat.obj &
       $(OUT)\dlguser.obj &
       $(OUT)\error.obj   &
       $(OUT)\help.obj

EXE = $(OUT)\mine2.exe
RES = $(OUT)\mine2.res

HELPFILES = $(HELPOUT)\mine2_en.hlp &
            $(HELPOUT)\mine2_es.hlp &
            $(HELPOUT)\mine2_nl.hlp &
            $(HELPOUT)\mine2_de.hlp &
            $(HELPOUT)\mine2_fr.hlp &
            $(HELPOUT)\mine2_it.hlp

all : $(EXE) $(HELPFILES) .symbolic

$(OUT) :
	@if not exist $(OUT) mkdir $(OUT)

$(HELPOUT) : $(OUT)
	@if not exist $(HELPOUT) mkdir $(HELPOUT)

$(HELPOUT)\mine2_en.hlp : help\mine2_en.ipf $(HELPOUT)
	$(WIPFC) -o $@ help\mine2_en.ipf

$(HELPOUT)\mine2_es.hlp : help\mine2_es.ipf $(HELPOUT)
	$(WIPFC) -o $@ help\mine2_es.ipf

$(HELPOUT)\mine2_nl.hlp : help\mine2_nl.ipf $(HELPOUT)
	$(WIPFC) -o $@ help\mine2_nl.ipf

$(HELPOUT)\mine2_de.hlp : help\mine2_de.ipf $(HELPOUT)
	$(WIPFC) -o $@ help\mine2_de.ipf

$(HELPOUT)\mine2_fr.hlp : help\mine2_fr.ipf $(HELPOUT)
	$(WIPFC) -o $@ help\mine2_fr.ipf

$(HELPOUT)\mine2_it.hlp : help\mine2_it.ipf $(HELPOUT)
	$(WIPFC) -o $@ help\mine2_it.ipf

$(EXE) : $(OBJS) $(RES)
	$(WLINK) $(LFLAGS) system os2v2 pm option stack=65536 name $@ file $(OUT)\stdmain.obj, $(OUT)\wpmain.obj, $(OUT)\wpfield.obj, $(OUT)\7segment.obj, $(OUT)\dlgabout.obj, $(OUT)\dlghof.obj, $(OUT)\dlgstat.obj, $(OUT)\dlguser.obj, $(OUT)\error.obj, $(OUT)\help.obj
	$(WRC) $(BINDWF) -fe=$@ $(RES) $@

$(RES) : src\mine2.rc src\mine2.dlg src\mine2.h $(OUT)
	$(WRC) $(RCFLAGS) -fo=$@ -i=src src\mine2.rc

$(OUT)\stdmain.obj  : src\stdmain.c  src\mine2.h src\7segment.h src\lang.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\stdmain.c

$(OUT)\wpmain.obj   : src\wpmain.c   src\mine2.h src\7segment.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\wpmain.c

$(OUT)\wpfield.obj  : src\wpfield.c  src\mine2.h src\7segment.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\wpfield.c

$(OUT)\7segment.obj : src\7segment.c src\mine2.h src\7segment.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\7segment.c

$(OUT)\dlgabout.obj : src\dlgabout.c src\mine2.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\dlgabout.c

$(OUT)\dlghof.obj   : src\dlghof.c   src\mine2.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\dlghof.c

$(OUT)\dlgstat.obj  : src\dlgstat.c  src\mine2.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\dlgstat.c

$(OUT)\dlguser.obj  : src\dlguser.c  src\mine2.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\dlguser.c

$(OUT)\error.obj    : src\error.c    src\mine2.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\error.c

$(OUT)\help.obj     : src\help.c     src\mine2.h $(OUT)
	$(CC) $(CFLAGS) -fo=$@ src\help.c

clean : .symbolic
	@if exist $(OUT)\*.obj del $(OUT)\*.obj >nul
	@if exist $(RES) del $(RES) >nul
	@if exist $(OUT)\mine2.map del $(OUT)\mine2.map >nul
	@if exist $(EXE) del $(EXE) >nul
	@if exist $(HELPOUT)\*.hlp del $(HELPOUT)\*.hlp >nul
