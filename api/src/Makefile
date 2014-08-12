all:
	g++ main.cpp -o guile-console `guile-config compile	` `guile-config link`

# Should correctly place guile wrapper .so files in this dir
copy-so:
	ln -s ../../logger/api/rainbrurpg-logger-guile.so /usr/lib/guile/2.0/extensions
