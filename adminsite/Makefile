## Only copy php and html in local www directory for test purpose

SUBDIRS = unittest
INSTALL_DIR = /var/www/rpg/admin

install:
	rm -fR $(INSTALL_DIR)/*
	cp -R *.php $(INSTALL_DIR)
	cp -R *.html $(INSTALL_DIR)
	mkdir $(INSTALL_DIR)/unittest
	cp -R unittest/*.php $(INSTALL_DIR)/unittest

clean:
	rm -f *~
	rm -f *.log
	for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done
