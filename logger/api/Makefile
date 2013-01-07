
all: guile

guile:
	swig -c++ -guile -module logger logger.i
	g++ -c -fPIC logger_wrap.cxx `guile-config compile`
	g++ -shared -fPIC logger_wrap.o ../src/.libs/*.o -o logger.so -lboost_program_options

install: install-guile

install-guile:
	cp logger.so `guile-config info extensiondir`

clean:
	rm -fr *.so *.o logger_wrap.cxx *~ 