TEX = lexman.tex header.tex bib.tex
TEX += intro.tex
TEX += soft.tex files.tex README.tex makefile.tex
TEX += compiler.tex fig/llvm.png
TEX += lexer.tex regexp.tex tmp/empty.log
TEX += script/lexer.tex script/lpp.lpp script/lpp.tex
TEX += script/syntax.tex
# parser.tex header.tex cppcore.tex

#LST = lst/Makefile lst/mk.lpp

MK = tmp/mk.vars

LST = $(MK) tmp/Fi.dat tmp/pij.main 

PLOTS = fig/compiler1.png fig/compiler2.png

.PHONY: pdf
pdf: lexman.pdf
LATEX = pdflatex -halt-on-error
lexman.pdf: $(TEX) $(LST) $(PLOTS)
	mkdir -p tmp
	$(LATEX) $< && $(LATEX) $<
	
$(LST): lst/Makefile lst/mk.lpp lst/Fi.lpp lst/empty.lpp script/Makefile
	cd lst && $(MAKE) EXE=$(EXE)
	
fig/%.png: fig/%.dot
	dot -Tpng -o $@ $<
#fig/%.pdf: fig/%.svg
#	inkscape --file=$< --export-area-drawing --without-gui --export-pdf=$@

tmp/empty.log : empty.l Makefile
	lex -l empty.l
	gcc -std=c89 -Wpedantic -o tmp/empty.exe lex.yy.c
	tmp/empty.exe < lex.yy.c | head -n5 > $@