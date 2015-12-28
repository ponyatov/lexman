
LPP = ../tmp/lpp.hpp ../tmp/lpp.strbuf ../tmp/lpp.options 

.PHONY: lst
lst: ../tmp/mk.head ../tmp/Fi.dat ../tmp/pij.main \
	../tmp/empty.1 ../tmp/empty.2 $(LPP)
	
../tmp/mk.head: ./mk$(EXE) ../script/Makefile
	./mk$(EXE) < ../script/Makefile
../tmp/Fi.dat: ./Fi$(EXE) ../../pij/pij2d/Fi.txt
	./Fi$(EXE) < ../../pij/pij2d/Fi.txt
../tmp/pij.main: ./pij$(EXE) ../../pij/pij2d/cpp.cpp
	./pij$(EXE) < ../../pij/pij2d/cpp.cpp
../tmp/empty.1 ../tmp/empty.2: ./empty$(EXE) ../empty.l 	
	./empty$(EXE) < ../empty.l
$(LPP): ./lpp$(EXE) ../script/lpp.lpp
	./lpp$(EXE) < ../script/lpp.lpp
	
./%$(EXE): %.cpp
	$(CXX) -o $@ $<
%.cpp: %.lpp Makefile
	flex -o $@ $<
