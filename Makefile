# Variables for the sources and directories
SRC_DIR = ./src
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SOURCE = $(SRC_DIR)/asm/test.asm
OBJ_DIR = ./build/x86-64
ASM_OBJ_DIR = ./build/asm
CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SOURCES))
ASM_OBJECT = $(ASM_OBJ_DIR)/test.o

# Output binary
MAIN_OUTPUT = $(OBJ_DIR)/main

# Compile C++ files
$(MAIN_OUTPUT): $(CPP_OBJECTS)
	g++ $^ -o $(MAIN_OUTPUT)
	@echo "Building CPP files done"

# Compile assembly file
$(ASM_OBJECT): $(ASM_SOURCE) | $(ASM_OBJ_DIR)
	acme --cpu 6502 -o $(ASM_OBJECT) --setpc 0 $(ASM_SOURCE)
	@echo "Building assembly done"

# Target to run the program
run: $(MAIN_OUTPUT) $(ASM_OBJECT)
	./$(MAIN_OUTPUT) $(ASM_OBJECT)
	@echo "Running done"

# Pattern rule for building C++ object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ -c $< -o $@

# Targets to create output directories
$(OBJ_DIR) $(ASM_OBJ_DIR):
	mkdir -p $@

# Clean target to remove generated files and directories
clean:
	rm -f $(CPP_OBJECTS) $(ASM_OBJECT) $(MAIN_OUTPUT)
	rm -rf $(OBJ_DIR) $(ASM_OBJ_DIR)
