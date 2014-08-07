
OPTS = -Wno-deprecated

all: guile

guile:
	swig -c++ -guile -Linkage module -package rainbrurpg -procdoc logger.texi -procdocformat texinfo logger.i
	g++ -c -fPIC $(OPTS) logger_wrap.cxx `guile-config compile`
	g++ -shared -fPIC $(OPTS) logger_wrap.o ../src/.libs/*.o -o logger.so -lboost_program_options

install: install-guile

install-guile:
	cp logger.so `guile-config info extensiondir`

clean:
	rm -fr *.so *.o logger_wrap.cxx *~ 