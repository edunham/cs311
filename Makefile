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
