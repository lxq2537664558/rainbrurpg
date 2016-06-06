SUBDIRS=src

EXTRA_DIST=COPYING

# Here I use the --transform flag of tar to modify on-the-fly the directories
# inside the created archive to look up the foswiki directory structure.
plugin:
	@echo "Making archive to install metaserver in '$(webname)' web :"
	@tar -jcf foswiki-rainbrurpg-metaserver-plugin-$(VERSION).tar.bz2    \
	  --exclude="*~" --exclude="Makefile*" src/foswiki_plugin/* \
	  --transform s:src/foswiki_plugin/MetaServerWeb:data/$(webname):   \
	  --transform s:src/foswiki_plugin/ServerDetail.txt:data/Main/ServerDetail.txt: \
	  --transform s:src/foswiki_plugin/functions.pm:lib/Foswiki/Plugin/RainbrurpgMetaserverPlugin/functions.pm:  \
	  --transform s:src/foswiki_plugin/RainbrurpgMetaserverPlugin.txt:/data/System/RainbrurpgMetaserverPlugin.txt: \
	  --transform s:src/foswiki_plugin/:lib/Foswiki/Plugin/: 	   
	@echo "Archive name is foswiki-rainbrurpg-metaserver-plugin-$(VERSION).tar.bz2"