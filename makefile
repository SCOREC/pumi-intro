CC = mpicc
CFLAGS = -I/Users/danibanez/code/core/install/include
LDFLAGS = -L/Users/danibanez/code/core/install/lib -lpcu

all: pumi_intro.pdf pcu1 pcu2

pumi_intro.pdf: pumi_intro.tex pcu1.c pcu2.c
	pdflatex pumi_intro.tex
	pdflatex pumi_intro.tex

pcu1: pcu1.c
pcu2: pcu2.c

.PHONY: clean
clean:
	rm -rf pumi_intro.pdf pcu1 *.aux *.log *.out
