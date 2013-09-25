
# nom de la bibliothèque

CPP 	= g++

GCCOPTS	= #-Wall

LIBCOM_OPTS = -I"../../include/" 
LIBFLT_OPTS = -I"/usr/X11R6/include" -L"/usr/X11R6/lib" -lfltk -lXext -lX11 -lm

XIDENT_OPTS 	=  -I"/usr/include/mysql++" $(LIBCRY_OPTS) $(LIBCOM_OPTS) $(LIBFLT_OPTS) -lrainbrurpg-commons -L"../../lib"

XIDENT_BIN	= xident


XIDENT_SRC 	= xidentwindow.o	\
		  playerlist.o		\
		  addplayer.o		\
		  serverlist.o		\
		  playernotepad.o	\
		  xmlserverlist.o	\
		  addserver.o		\
		  xident.o		\
	 	  showcurlerror.o

all: xident


xidentwindow.o: xidentwindow.cpp xidentwindow.h
	$(CPP) -c xidentwindow.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

playerlist.o: playerlist.cpp playerlist.h
	$(CPP) -c playerlist.cpp $(LIBCOM_OPTS) $(GCCOPTS)

addplayer.o: addplayer.cpp addplayer.h
	$(CPP) -c addplayer.cpp $(LIBCOM_OPTS)  $(GCCOPTS)

serverlist.o: serverlist.cpp serverlist.h
	$(CPP) -c serverlist.cpp $(LIBCOM_OPTS) $(GCCOPTS)

playernotepad.o: playernotepad.cpp playernotepad.h
	$(CPP) -c playernotepad.cpp $(LIBCOM_OPTS) $(GCCOPTS)

xmlserverlist.o: xmlserverlist.cpp xmlserverlist.h
	$(CPP) -c xmlserverlist.cpp $(LIBCOM_OPTS) $(GCCOPTS)

addserver.o: addserver.cpp addserver.h
	$(CPP) -c addserver.cpp $(LIBCOM_OPTS) $(GCCOPTS)

xident.o: xident.cpp
	$(CPP) -c xident.cpp $(LIBCOM_OPTS) $(GCCOPTS)

showcurlerror.o: showcurlerror.cpp showcurlerror.h
	$(CPP) -c showcurlerror.cpp $(LIBCOM_OPTS) $(GCCOPTS)


#=================================== ALL CIBLES

xident: $(XIDENT_SRC)

	@echo
	@echo ======= Building X Ident maintenance program
	@echo
	$(CPP) $(XIDENT_SRC) -o $(XIDENT_BIN) $(XIDENT_OPTS) $(GCCOPTS)
	cp $(XIDENT_BIN) ../../bin/$(XIDENT_BIN)

default: all

clean:
	rm -f *.o
	rm -f *~
	rm -f xident
