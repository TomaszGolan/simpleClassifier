INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

INC = $(wildcard $(INC_DIR)/*.h)
SRC = $(wildcard $(SRC_DIR)/*.cxx)
OBJ = $(SRC:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o)

CXX = g++ -std=c++11 -Wall
CXXFLAGS = -I $(INC_DIR) -lboost_system -lboost_filesystem

BIN = $(BIN_DIR)/runKNN $(BIN_DIR)/runSVM

$(BIN_DIR)/runKNN.dep = runKNN.o Point.o Classifier.o KNN.o utils.o

$(BIN_DIR)/runSVM.dep = runSVM.o Point.o Classifier.o SVM.o utils.o

all: init $(OBJ) $(BIN)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	@tabs 10
	@echo -ne 'Compiling \033[1m$@\033[0m...'
	@$(CXX) -c $< -o $@  $(CXXFLAGS)
	@echo -e '\tdone'
	
$(BIN):
	@tabs 10
	@echo -ne 'Linking \033[1m$@\033[0m...'
	@$(CXX) $(addprefix $(OBJ_DIR)/, $($@.dep)) -o $@ $(CXXFLAGS) 
	@echo -e '\tdone'
	
init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	
clean:
	@echo -ne 'Removing \033[1m$(OBJ) $(BIN)\033[0m...'
	@rm -f $(OBJ) $(BIN)
	@echo ' done'

doxygen:
	@echo -ne 'Generating \033[1mdocs/Doxyfile\033[0m...'
	@doxygen docs/Doxyfile > docs/Doxyfile.log
	@echo " done"
