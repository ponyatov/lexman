TEX = lexman.tex header.tex bib.tex
TEX += intro.tex
TEX += soft.tex

.PHONY: pdf
pdf: lexman.pdf
LATEX = pdflatex -halt-on-error
lexman.pdf: $(TEX)
	$(LATEX) $< && $(LATEX) $<