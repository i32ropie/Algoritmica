CPPFLAGS = -g -O3 -std=c++11 -c -lrt #-DNDEBUG
OBJECT = main.o
BIN = main

all: $(BIN)
	@rm -rf $(OBJECT)

$(BIN): $(OBJECT)
	g++ -o $(BIN) $(OBJECT)

$(OBJECT): *.cpp *.hpp
	g++ $(CPPFLAGS) main.cpp

clean:
	@rm -rf $(OBJECT) $(BIN) *.eps *.dat
