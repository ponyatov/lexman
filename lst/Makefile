../tmp/mk.head: ./mk ../script/Makefile
	./mk < ../script/Makefile
./mk: mk.cpp
	$(CXX) -o $@ $<
mk.cpp: mk.lpp
	flex -o $@ $<
