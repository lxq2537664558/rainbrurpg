## Only copy php and html in local www directory for test purpose

SUBDIRS = unittest

install:
	cp -R *.php /var/www/rpg/admin
	cp -R *.html /var/www/rpg/admin
	cp -R unittest/*.php /var/www/rpg/admin/unittest

clean:
	rm -f *~
	rm -f *.log
	for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done
