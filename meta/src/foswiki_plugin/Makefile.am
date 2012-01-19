#foswiki_prefix = $(prefix)

foswiki_prefix= @foswikidir@

fwdocdir = $(foswiki_prefix)/data/System
fwdoc_DATA= RainbrurpgMetaserverPlugin.txt

fwsourcedir = $(foswiki_prefix)/lib/Foswiki/Plugins/
fwsource_DATA = RainbrurpgMetaserverPlugin.pm

fwfuncdir = $(foswiki_prefix)/lib/Foswiki/Plugins/RainbrurpgMetaserverPlugin
fwfunc_DATA = functions.pm

EXTRA_DIST = $(fwdoc_DATA) $(fwsource_DATA) $(fwfunc_DATA) 

TESTS=functions_Test.pl