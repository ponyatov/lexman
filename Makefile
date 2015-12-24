TEX = lexman.tex header.tex
TEX += intro.tex

.PHONY: pdf
pdf: lexman.pdf
LATEX = pdflatex -halt-on-error
lexman.pdf: $(TEX)
	$(LATEX) $< && $(LATEX) $<