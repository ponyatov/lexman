# EXE = .exe|
# RES = res.res|
# TAIL = -n17|-n7
MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./$(MODULE)$(EXE)
	./$(MODULE)$(EXE) < $(MODULE).scr > $(MODULE).log && tail $(TAIL) $(MODULE).blog
.PHONY: clean	
clean:
	rm -rf *~ .*~ *.exe *.elf *.*log ypp.tab.?pp lex.yy.c $(RES)
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
# CXX = clang++
CXXFLAGS += -I. -std=gnu++11
./$(MODULE)$(EXE): $(C) $(H) $(RES)
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(RES)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@
