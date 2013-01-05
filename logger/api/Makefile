
all: guile

guile:
	swig -c++ -guile logger.i
	g++ -c -fPIC logger_wrap.cxx
	g++ -shared -fPIC logger_wrap.o ../src/.libs/*.o -o logger.so

install: install-guile

install-guile:
	cp logger.so `guile-config info extensiondir`

clean:
	rm -fr *.so *.o logger_wrap.cxx *~