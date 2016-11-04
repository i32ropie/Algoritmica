CPPFLAGS = -g -Wall -Wextra -std=c++11 -c
OBJECT = main.o
BIN = main


all: $(BIN)
	rm -f $(OBJECT)

$(BIN): $(OBJECT)
	g++ -o $(BIN) $(OBJECT)

$(OBJECT): *.cpp *.hpp
	g++ $(CPPFLAGS) *.cpp

clean:
	rm -f $(OBJECT) $(BIN)