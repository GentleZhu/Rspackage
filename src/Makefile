#
CXX = g++
#
CFLAGS = -c -Wall
LDFLAGS= 
#
OBJ = rating.o rating_m.o basicSolver.o basicSolver_m.o basicMF.o basicMF_m.o basicKNN.o main.o
BIN = main
all: $(BIN)

rating.o: ./data/rating.cc
rating_m.o: ./data/matrix/rating_m.cc
basicSolver.o: ./algorithms/basicSolver.cc
basicSolver_m.o: ./algorithms/matrix/basicSolver_m.cc
basicMF.o: ./algorithms/basicMF.cc
basicMF_m.o: ./algorithms/matrix/basicMF_m.cc
basicKNN.o: ./algorithms/basicKNN.cc
main.o: main.cc

$(OBJ): 
	$(CXX) $(CFLAGS) -o $@ $(filter %.cc %.c, $^)

$(BIN): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@
