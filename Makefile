TEX = header.tex 
TEX += ../texheader/ebook.tex ../texheader/colors.tex ../texheader/cyr.tex
TEX += ../texheader/relsec.tex ../texheader/misc.tex ../texheader/comp.tex

TEX += lexman.tex bib.tex
#TEX += intro.tex
#TEX += soft.tex files.tex README.tex makefile.tex
#TEX += compiler.tex fig/llvm.png
#TEX += lexer.tex regexp.tex tmp/empty.log
#TEX += script/lexer.tex script/lpp.lpp script/lpp.tex
#TEX += script/syntax.tex script/script.bI
#TEX += parser.tex
#TEX += script/extensions.tex script/fileio.tex
TEX += antlr.tex
ANT += tmp/ant.gr tmp/ant.int tmp/ant.id tmp/ant.calc

#MK = tmp/mk.vars

#LST = $(MK) tmp/Fi.dat tmp/pij.main tmp/bi.comment

#PLOTS = fig/compiler1.png fig/compiler2.png

.PHONY: pdf
pdf: lexman.pdf
LATEX = pdflatex -halt-on-error
lexman.pdf: $(TEX) $(LST) $(PLOTS) $(ANT)
	mkdir -p tmp
	$(LATEX) lexman && $(LATEX) lexman

.PHONY: clean
clean:
	rm -rf *.*log *.out *.toc *.aux *.idx

$(LST): lst/Makefile lst/mk.lpp lst/Fi.lpp lst/empty.lpp script/Makefile
	cd lst && $(MAKE) EXE=$(EXE)

antlr.tex: $(ANT)
$(ANT): Jcalc/ANTLRgrammar.g4 Makefile
	egrep "^grammar" $< > tmp/ant.gr
	egrep "^(calc|expr|scalar)" $< > tmp/ant.calc
	egrep "^INT" $< > tmp/ant.int
	egrep "^ID" $< > tmp/ant.id

#fig/%.png: fig/%.dot
#	dot -Tpng -o $@ $<
##fig/%.pdf: fig/%.svg
##	inkscape --file=$< --export-area-drawing --without-gui --export-pdf=$@
#
#tmp/empty.log : empty.l Makefile
#	lex -l empty.l
#	gcc -std=c89 -Wpedantic -o tmp/empty.exe lex.yy.c
#	tmp/empty.exe < lex.yy.c | head -n5 > $@
