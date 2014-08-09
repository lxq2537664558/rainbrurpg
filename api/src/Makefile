all: copy-so 
	g++ main.cpp -o guile-console `guile-config compile	` `guile-config link`

# Should correctly place guile wrapper .so files in this dir
copy-so:
	rm -fr logger.so
	ln -s ../../logger/api/logger.so .
