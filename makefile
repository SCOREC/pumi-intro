CC = mpicc
CXX = mpicxx
CFLAGS = -I/Users/danibanez/code/core/install/include
CXXFLAGS = -I/Users/danibanez/code/core/install/include
LDFLAGS = -L/Users/danibanez/code/core/install/lib -lmds -lapf -lgmi -lpcu

all: pumi_intro.pdf pcu1 pcu2 apf1 apf2

pumi_intro.pdf: pumi_intro.tex pcu1.c pcu2.c apf2.cc
	pdflatex pumi_intro.tex
	pdflatex pumi_intro.tex

pcu1: pcu1.c
pcu2: pcu2.c
apf1: apf1.cc
apf2: apf2.cc

.PHONY: clean
clean:
	rm -rf pumi_intro.pdf pcu1 *.aux *.log *.out
