# Variables for the sources and directories
SRC_DIR = ./src
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SOURCE = $(SRC_DIR)/asm/test.asm
OBJ_DIR = ./build/x86-64
ASM_OBJ_DIR = ./build/asm
CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SOURCES))
ASM_OBJECT = $(ASM_OBJ_DIR)/test.o
ASM_REPORT = $(ASM_OBJ_DIR)/test.report

# Output binary
MAIN_OUTPUT = $(OBJ_DIR)/main

# Compile C++ files
$(MAIN_OUTPUT): $(CPP_OBJECTS)
	g++ -lSDL2 -lSDL2_image -g -o $(MAIN_OUTPUT) $^
	@echo "Building CPP files done"

# Compile assembly file
$(ASM_OBJECT): $(ASM_SOURCE) | $(ASM_OBJ_DIR)
	acme --cpu 6502 -o $(ASM_OBJECT) --setpc 0 --report $(ASM_REPORT) $(ASM_SOURCE)
	@echo "Building assembly done"

# Target to run the program
run: $(MAIN_OUTPUT) $(ASM_OBJECT)
	./$(MAIN_OUTPUT) $(ASM_OBJECT) 5
	@echo "Running done"
debug: $(MAIN_OUTPUT) $(ASM_OBJECT)
	gdb $(MAIN_OUTPUT)
	@echo "Debugging done"
toAsm: $(MAIN_OUTPUT)
	objdump -d $(MAIN_OUTPUT) > $(OBJ_DIR)/main.asm
	@echo "Disassembling done"

# Pattern rule for building C++ object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ -lSDL2 -lSDL2_image -g -c $< -o $@

# Targets to create output directories
$(OBJ_DIR) $(ASM_OBJ_DIR):
	mkdir -p $@

# Clean target to remove generated files and directories
clean:
	rm -f $(CPP_OBJECTS) $(ASM_OBJECT) $(MAIN_OUTPUT)
	rm -rf $(OBJ_DIR) $(ASM_OBJ_DIR)
