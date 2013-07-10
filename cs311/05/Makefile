TARGET=writeup
HTML=main_html

default: pdf

dvi: ${TARGET}.tex 
#	run latex twice to get references correct
	latex ${TARGET}.tex

ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

pdf: ps
	ps2pdf ${TARGET}.ps

clean:
	rm *.aux
	rm *.out
	rm *.log
	rm *.dvi
	rm *.ps

CC = icc
CFLAGS = -Wall -std=c99 -openmp -O3 -g -I.
CTARGET = primes

SOURCE = primes.c

default:	compile

compile: ${SOURCE}
	${CC} ${CFLAGS} ${SOURCE} -o ${CTARGET} ${LDFLAGS}

debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${CTARGET} ${LDFLAGS} -DDEBUG
