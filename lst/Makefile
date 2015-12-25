../tmp/mk.head: ./mk1$(EXE) ../script/Makefile
	./mk1$(EXE) < ../script/Makefile
./%$(EXE): %.cpp
	$(CXX) -o $@ $<
%.cpp: %.lpp Makefile
	flex -o $@ $<
