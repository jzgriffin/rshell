PDFLATEX ?= pdflatex

.PHONY: all clean distclean
all: all-design
clean: clean-design
distclean: distclean-design

.PHONY: all-design clean-design distclean-design
all-design: Design.pdf
clean-design:
	$(RM) Design.aux Design.log
distclean-design: clean-design
	$(RM) Design.pdf

%.pdf: %.tex
	$(PDFLATEX) $(PDFLATEXFLAGS) $<
