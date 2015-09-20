INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

INC = $(wildcard $(INC_DIR)/*.h)
SRC = $(wildcard $(SRC_DIR)/*.cxx)
OBJ = $(SRC:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o)

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I $(INC_DIR)

BIN = runKNN

runKNN.dep = runKNN.o Point.o Classifier.o KNN.o

all: $(OBJ) $(BIN)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	@echo "\n##### Compiling $@ #####\n"
	$(CXX) $(CXXFLAGS) -c $< -o $@  #compiling

$(BIN):
	@echo "\n##### Linking $@ #####\n"
	$(CXX) $(CXXFLAGS) $(addprefix $(OBJ_DIR)/, $($@.dep)) -o $(BIN_DIR)/$@ 
	
clean:
	@echo "\n##### Removing $(OBJ) $(addprefix $(BIN_DIR)/, $(BIN)) #####\n"
	@rm -f $(OBJ) $(addprefix $(BIN_DIR)/, $(BIN))

doxygen:
	doxygen docs/Doxyfile
