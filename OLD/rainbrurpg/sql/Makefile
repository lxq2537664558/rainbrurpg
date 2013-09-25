# Makefile for the MCD
#
# You must have the graphviz package
# installed to run it
default: mcd.dot 
	dot -Tps -l DFD.ps  mcd.dot -o output.ps
	ps2pdf13 output.ps mcd.pdf
	rm -f output.ps