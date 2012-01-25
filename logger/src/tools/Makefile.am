all: $(logreader_SOURCES)

.PHONY: $(logreader_SOURCES)

bin_PROGRAMS=logreader
logreader_SOURCES=MainWindow_ui.rb

SUFFIXES= .rb .ui

# Reminder for internal vars
# $@ The target name
# $< First dependency name
# $^ Dependencies list
# $? List of deps most recent than target
# $* File name without suffix
.ui.rb:
	$(TOOL_RBUIC) $*.ui -o $*_ui.rb

MainWindow_ui.rb: MainWindow.ui
	$(TOOL_RBUIC) MainWindow.ui -o MainWindow_ui.rb

clean-local: 
	rm -fr MainWindow_ui.rb

logreader_LINK = @true # Disable linking
