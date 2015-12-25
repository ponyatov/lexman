TEX = lexman.tex header.tex bib.tex
TEX += intro.tex
TEX += soft.tex files.tex README.tex makefile.tex
TEX += compiler.tex fig/llvm.png
#TEX += lexer.tex parser.tex header.tex cppcore.tex

#LST = lst/Makefile lst/mk.lpp

MK = tmp/mk.vars

LST = $(MK)

PLOTS = fig/compiler1.png fig/compiler2.png

.PHONY: pdf
pdf: lexman.pdf
LATEX = pdflatex -halt-on-error
lexman.pdf: $(TEX) $(LST) $(PLOTS)
	mkdir -p tmp
	$(LATEX) $< && $(LATEX) $<
	
$(MK): lst/Makefile lst/mk.lpp script/Makefile
	cd lst && make
	
fig/%.png: fig/%.dot
	dot -Tpng -o $@ $<	