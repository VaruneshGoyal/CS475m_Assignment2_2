CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = main1.cpp
BIN = main1

all	:	$(BIN)

$(BIN)	:	HNode.hpp HNode.cpp $(SRC) 
	$(CC) $(SRC) HNode.cpp -o $(BIN) $(LIBS) -std=c++11

clean	:
	rm -f $(BIN) *~ *.aux *.log
