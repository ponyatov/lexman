
LPP = ../tmp/lpp.hpp ../tmp/lpp.strbuf ../tmp/lpp.options

bI = ../tmp/bi.comment ../tmp/bi.int ../tmp/bi.hex ../tmp/bi.bin ../tmp/bi.num

YPP = ../tmp/ypp.str ../tmp/ypp.sym ../tmp/ypp.num

HPP = ../tmp/hpp.sym ../tmp/hpp.str ../tmp/hpp.num \
	../tmp/hpp.int ../tmp/hpp.hex ../tmp/hpp.bin
	
CPP = ../tmp/cpp.sym

.PHONY: lst
lst: ../tmp/mk.head ../tmp/Fi.dat ../tmp/pij.main \
	../tmp/empty.1 ../tmp/empty.2 $(LPP) $(YPP) $(bI) $(HPP) $(CPP)
	
../tmp/mk.head: ./mk$(EXE) ../script/Makefile
	./mk$(EXE) < ../script/Makefile
../tmp/Fi.dat: ./Fi$(EXE) ../../pij/pij2d/Fi.txt
	./Fi$(EXE) < ../../pij/pij2d/Fi.txt
../tmp/pij.main: ./pij$(EXE) ../../pij/pij2d/cpp.cpp
	./pij$(EXE) < ../../pij/pij2d/cpp.cpp
../tmp/empty.1 ../tmp/empty.2: ./empty$(EXE) ../empty.l 	
	./empty$(EXE) < ../empty.l
$(YPP): ./ypp$(EXE) ../script/ypp.ypp
	./ypp$(EXE) < ../script/ypp.ypp
$(LPP): ./lpp$(EXE) ../script/lpp.lpp
	./lpp$(EXE) < ../script/lpp.lpp
$(HPP): ./hpp$(EXE) ../script/hpp.hpp
	./hpp$(EXE) < ../script/hpp.hpp
$(CPP): ./cpp$(EXE) ../script/cpp.cpp
	./cpp$(EXE) < ../script/cpp.cpp
$(bI): ./script$(EXE) ../script/script.bI
	./script$(EXE) < ../script/script.bI
	
./%$(EXE): %.cpp
	$(CXX) -o $@ $<
%.cpp: %.lpp Makefile
	flex -o $@ $<
