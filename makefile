CC = mpicc
CXX = mpicxx
CFLAGS = `pkg-config --cflags libmds`
CXXFLAGS = `pkg-config --cflags libmds`
LDFLAGS = `pkg-config --libs-only-L libmds`
LDLIBS = `pkg-config --libs-only-l libmds`

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
