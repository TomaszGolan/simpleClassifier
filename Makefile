INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

INC = $(wildcard $(INC_DIR)/*.h)
SRC = $(wildcard $(SRC_DIR)/*.cxx)
OBJ = $(SRC:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o)

CXX = g++ -std=c++11 -Wall
CXXFLAGS = -I $(INC_DIR) -lboost_system -lboost_filesystem

BIN = runKNN

runKNN.dep = runKNN.o Point.o Classifier.o KNN.o

all: createFolders $(OBJ) $(BIN)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	@echo "\n##### Compiling $@ #####\n"
	$(CXX) -c $< -o $@  $(CXXFLAGS) #compiling

$(BIN):
	@echo "\n##### Linking $@ #####\n"
	$(CXX) $(addprefix $(OBJ_DIR)/, $($@.dep)) -o $(BIN_DIR)/$@ $(CXXFLAGS) 
	
createFolders:
		mkdir -p $(OBJ_DIR)
		mkdir -p $(BIN_DIR)
	
clean:
	@echo "\n##### Removing $(OBJ) $(addprefix $(BIN_DIR)/, $(BIN)) #####\n"
	@rm -f $(OBJ) $(addprefix $(BIN_DIR)/, $(BIN))

doxygen:
	doxygen docs/Doxyfile
	
make run:
	make
	./bin/runKNN
	./gnuplot/plotKNN.sh
