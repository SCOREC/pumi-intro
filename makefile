CC = mpicc
CXX = mpicxx
COREDIR = $(HOME)/barn-shared/pumi/dbg
BZ2DIR = /gpfs/u/software/bgq/bzip2/xl/1.0.6
CFLAGS = -I$(COREDIR)/include
CXXFLAGS = -I$(COREDIR)/include
LDFLAGS = -L$(COREDIR)/lib -L$(BZ2DIR)/lib
LDLIBS = -lmds -lapf -lgmi -lpcu -lbz2

all: pumi_intro.pdf pcu1 pcu2 apf1 apf2 apf3

pumi_intro.pdf: pumi_intro.tex pcu1.c pcu2.c apf1.cc apf2.cc apf3.cc
	pdflatex pumi_intro.tex
	pdflatex pumi_intro.tex

pcu1: pcu1.c
pcu2: pcu2.c
apf1: apf1.cc
apf2: apf2.cc
apf3: apf3.cc

.PHONY: clean
clean:
	rm -rf pumi_intro.pdf pcu1 *.aux *.log *.out
