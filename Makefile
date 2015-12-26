TEX = lexman.tex header.tex bib.tex
TEX += intro.tex
TEX += soft.tex files.tex README.tex makefile.tex
TEX += compiler.tex fig/llvm.png
TEX += lexer.tex regexp.tex # parser.tex header.tex cppcore.tex

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
	cd lst && $(MAKE) EXE=$(EXE)
	
fig/%.png: fig/%.dot
	dot -Tpng -o $@ $<	

lexer.tex: tmp/Fi.txt	
tmp/Fi.txt: ../pij/pij2d/Fi.txt
	head -n5 $< > $@
	echo "\n...\n" >> $@
	tail -n5 $< >> $@
