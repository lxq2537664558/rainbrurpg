
# nom de la bibliothèque

CPP 	= g++

GCCOPTS	= -Wall -g

LIBCOM_OPTS = -I"../include/" -I"/usr/X11R6/include" -I"/usr/include/irrlicht" -I"/usr/include"

LIBFLT_OPTS = -I"/usr/X11R6/include" -L"/usr/X11R6/lib" 



# enlever -lXxf86vm
CLI_OPTS 	=  -I"../include/" -I"/usr/include/irrlicht" -I"/usr/include/mysql++" -L"/usr/X11R6/lib" $(LIBCRY_OPTS) $(LIBCOM_OPTS) $(LIBFLT_OPTS) -lrainbrurpg-commons -lcrypto++ -L"../lib" -lfltk -lIrrlicht -lGL  -lXext -lX11 -lglut -lGLU

CLI_BIN	= rainbruRPG


CLI_SRC 	= console.o		\
		  consoleobject.o	\
		  cocore.o		\
		  erconsole.o		\
		  ergame.o		\
		  ergameesc.o		\
		  gamestate.o		\
		  gsgame.o		\
		  gsgameesc.o		\
		  guimanager.o		\
		  irrfontmanager.o	\
		  launcher.o		\
		  launcheroptions.o	\
		  options.o		\
		  screenshotmanager.o	\
		  tokenizer.o		\
		  tokenizerdbg.o	\
		  xmloptions.o		\
		  boolattribute.o	\
		  fpsattribute.o	\
		  intattribute.o	\
		  showstatsattribute.o	\
		  objectattribute.o	\
		  main.o		\
		  gsconnection.o	\
		  erconnection.o	\
		  gscreateaccount.o	\
		  ercreateaccount.o	\
		  erchangepassword.o	\
		  gschangepassword.o	\
	    	  gsselectperso.o	\
		  erselectperso.o	\
		  gscreateperso.o	\
		  ercreateperso.o	\
		  guitransattribute.o	\
		  gameengine.o		


# The main cible
#--------------------
all: client


objectattribute.o: objectattribute.cpp objectattribute.h
	$(CPP) -c objectattribute.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

boolattribute.o: boolattribute.cpp boolattribute.h
	$(CPP) -c boolattribute.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

fpsattribute.o: fpsattribute.cpp fpsattribute.h
	$(CPP) -c fpsattribute.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

intattribute.o: intattribute.cpp intattribute.h
	$(CPP) -c intattribute.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

showstatsattribute.o: showstatsattribute.cpp showstatsattribute.h
	$(CPP) -c showstatsattribute.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

cocore.o: cocore.cpp cocore.h
	$(CPP) -c cocore.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

consoleobject.o: consoleobject.cpp consoleobject.h
	$(CPP) -c consoleobject.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

tokenizer.o: tokenizer.cpp tokenizer.h
	$(CPP) -c tokenizer.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

tokenizerdbg.o: tokenizerdbg.cpp tokenizerdbg.h
	$(CPP) -c tokenizerdbg.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

console.o: console.cpp console.h
	$(CPP) -c console.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

erconsole.o: erconsole.cpp erconsole.h
	$(CPP) -c erconsole.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

ergame.o: ergame.cpp ergame.h
	$(CPP) -c ergame.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

ergameesc.o: ergameesc.cpp ergameesc.h
	$(CPP) -c ergameesc.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gameengine.o: gameengine.cpp gameengine.h
	$(CPP) -c gameengine.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gamestate.o: gamestate.cpp gamestate.h
	$(CPP) -c gamestate.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gsgame.o: gsgame.cpp gsgame.h
	$(CPP) -c gsgame.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gsgameesc.o: gsgameesc.cpp gsgameesc.h
	$(CPP) -c gsgameesc.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

guimanager.o: guimanager.cpp guimanager.h
	$(CPP) -c guimanager.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

irrfontmanager.o: irrfontmanager.cpp irrfontmanager.h
	$(CPP) -c irrfontmanager.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

launcher.o: launcher.cpp launcher.h
	$(CPP) -c launcher.cpp $(LIBCOM_OPTS) $(GCCOPTS) $(LIBFLT_OPTS)

launcheroptions.o: launcheroptions.cpp launcheroptions.h
	$(CPP) -c launcheroptions.cpp $(LIBCOM_OPTS) $(GCCOPTS) $(LIBFLT_OPTS)

options.o: options.cpp options.h
	$(CPP) -c options.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

screenshotmanager.o: screenshotmanager.cpp screenshotmanager.h
	$(CPP) -c screenshotmanager.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

xmloptions.o: xmloptions.cpp xmloptions.h
	$(CPP) -c xmloptions.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

main.o: main.cpp 
	$(CPP) -c main.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gsconnection.o: gsconnection.cpp gsconnection.h
	$(CPP) -c gsconnection.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

erconnection.o: erconnection.cpp erconnection.h
	$(CPP) -c erconnection.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gscreateaccount.o: gscreateaccount.cpp gscreateaccount.h
	$(CPP) -c gscreateaccount.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

ercreateaccount.o: ercreateaccount.cpp ercreateaccount.h
	$(CPP) -c ercreateaccount.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gschangepassword.o: gschangepassword.cpp gschangepassword.h
	$(CPP) -c gschangepassword.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

erchangepassword.o: erchangepassword.cpp erchangepassword.h
	$(CPP) -c erchangepassword.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gsselectperso.o: gsselectperso.cpp gsselectperso.h
	$(CPP) -c gsselectperso.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

erselectperso.o: erselectperso.cpp erselectperso.h
	$(CPP) -c erselectperso.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

gscreateperso.o: gscreateperso.cpp gscreateperso.h
	$(CPP) -c gscreateperso.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

ercreateperso.o: ercreateperso.cpp ercreateperso.h
	$(CPP) -c ercreateperso.cpp $(LIBCOM_OPTS) $(GCCOPTS) 

guitransattribute.o: guitransattribute.cpp guitransattribute.h
	$(CPP) -c guitransattribute.cpp $(LIBCOM_OPTS) $(GCCOPTS) 






#=================================== ALL CIBLES

client: $(CLI_SRC)

	@echo
	@echo ======= Building RainbruRPG client
	@echo
	$(CPP) $(CLI_SRC) -o $(CLI_BIN) $(CLI_OPTS) $(GCCOPTS)
	cp $(CLI_BIN) ../bin/$(CLI_BIN)

default: all

install:
	cp lib$(CLI_BIN).so /usr/local/bin/

clean:
	rm *.o
	rm *~
	rm ../bin/$(CLI_BIN)
