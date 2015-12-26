.PHONY: ../tmp/mk.head
../tmp/mk.head: ./mk$(EXE) ../script/Makefile
	./mk$(EXE) < ../script/Makefile
./%$(EXE): %.cpp
	$(CXX) -o $@ $<
%.cpp: %.lpp Makefile
	flex -o $@ $<
