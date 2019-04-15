
OPATH=Object
RPATH=Resource
HPATH=Help
CPATH=Code
GPATH=Bitmap

BITMAPS = $(GPATH)\about.bmp $(GPATH)\fame.bmp $(GPATH)\digits2.bmp $(GPATH)\field.bmp $(GPATH)\fieldbig.bmp $(GPATH)\grid.bmp $(GPATH)\hof.bmp $(GPATH)\ptr1.bmp $(GPATH)\ptr2.bmp $(GPATH)\ptr3.bmp $(GPATH)\ptr4.bmp
ICONS   = $(GPATH)\mine2.ico $(GPATH)\mine1.ptr $(GPATH)\mine2.ptr $(GPATH)\mine3.ptr $(GPATH)\mine4.ptr
BUTTON  = $(GPATH)\button1.bmp $(GPATH)\button2.bmp $(GPATH)\button3.bmp $(GPATH)\button4.bmp $(GPATH)\button5.bmp
BEES    = $(GPATH)\bee1.ptr $(GPATH)\bee2.ptr
OBJS    = $(OPATH)\stdmain.obj $(OPATH)\wpmain.obj $(OPATH)\wpfield.obj $(OPATH)\error.obj $(OPATH)\help.obj $(OPATH)\7segment.obj $(OPATH)\dlgabout.obj $(OPATH)\dlguser.obj $(OPATH)\dlgstat.obj $(OPATH)\dlghof.obj

WOPT    = /W2 /Wall
WOPT    = /W3 /Wcmp+cnd+dcl+eff+enu+ext-gen+ini+obs+ord+par+ppc-pro+rea+ret+use
!IFDEF DEBUG
CC=icc /Q+ $(WOPT) /Ss /Ti+
CL=link386 /NOLOGO /ALIGN:4 /EXEPACK:2 /PACKC /PACKD /BASE:0x10000 /DEBUG
!ELSE
CC=icc /Q+ $(WOPT) /Ss /O+ /G5
CL=link386 /NOLOGO /ALIGN:4 /EXEPACK:2 /PACKC /PACKD /BASE:0x10000
!ENDIF
RC=rc -x2 -n
HC=ipfc -W3 -L:ENG -C:850
HP=ipfcprep -W -L -S

.SUFFIXES: .c .obj

{$(CPATH)}.c{$(OPATH)}.obj:
    $(CC) /C /Fo$@ $<

all: mine2.hlp mine2.exe

mine2.exe: $(OBJS) $(RPATH)\mine2.res $(RPATH)\mine2.def makefile
    $(CL) $(OBJS), $@, NUL, , $(RPATH)\mine2.def
    $(RC) $(RPATH)\mine2.res $@

$(OPATH)\7segment.obj: $(CPATH)\7segment.c $(CPATH)\mine2.h $(CPATH)\7segment.h makefile
$(OPATH)\dlgabout.obj: $(CPATH)\dlgabout.c $(CPATH)\mine2.h                     makefile
$(OPATH)\dlguser.obj:  $(CPATH)\dlguser.c  $(CPATH)\mine2.h                     makefile
$(OPATH)\dlghof.obj:   $(CPATH)\dlghof.c   $(CPATH)\mine2.h                     makefile
$(OPATH)\dlgstat.obj:  $(CPATH)\dlgstat.c  $(CPATH)\mine2.h                     makefile
$(OPATH)\stdmain.obj:  $(CPATH)\stdmain.c  $(CPATH)\mine2.h $(CPATH)\7segment.h makefile
$(OPATH)\wpfield.obj:  $(CPATH)\wpfield.c  $(CPATH)\mine2.h $(CPATH)\7segment.h makefile
$(OPATH)\wpmain.obj:   $(CPATH)\wpmain.c   $(CPATH)\mine2.h $(CPATH)\7segment.h makefile
$(OPATH)\error.obj:    $(CPATH)\error.c    $(CPATH)\mine2.h                     makefile
$(OPATH)\help.obj:     $(CPATH)\help.c     $(CPATH)\mine2.h                     makefile

$(RPATH)\mine2.res: $(RPATH)\mine2.rc $(CPATH)\mine2.h $(RPATH)\mine2.dlg $(BITMAPS) $(BUTTON) $(ICONS) $(BEES) makefile
    $(RC) -r $(RPATH)\mine2.rc

mine2.hlp: $(HPATH)\mine2.ipf makefile
    $(HC) $(HPATH)\mine2
    copy $(HPATH)\$@ $@

#$(HPATH)\mine2.ipf: $(HPATH)\mine2.ipp makefile
#    $(HP) $(HPATH)\mine2.ipp $(HPATH)\mine2.ipf -I$(CPATH);$(GPATH)

$(RPATH)\mine2.def: makefile
    @echo Creating .DEF file -- <<$@
NAME        mine/2 WINDOWAPI
DESCRIPTION '(C) 1997 Mike'
DATA        MULTIPLE
STACKSIZE   60000
PROTMODE
<<keep

clean:
    -del mine2.exe 2>NUL
    -del mine2.hlp 2>NUL
    -del $(OBJS) 2>NUL
    -del $(RPATH)\mine2.res 2>NUL
    -del $(RPATH)\mine2.def 2>NUL
    -del $(HPATH)\mine2.hlp 2>NUL

