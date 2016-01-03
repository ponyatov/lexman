MODULE = bI
exec: ./$(MODULE)$(EXE)
	./$(MODULE)$(EXE) < $(MODULE).bI > $(MODULE).blog &&\
		tail $(TAIL) $(MODULE).blog
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
CFLAGS += -I. -std=gnu++11
./$(MODULE)$(EXE): $(C) $(H)
	$(CXX) $(CFLAGS) -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
