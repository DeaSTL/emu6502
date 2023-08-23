# Variables for the sources and objects
SRC_DIR = ./src
ASM_SRC_DIR = $(SRC_DIR)/asm
CPP_SOURCES = $(addprefix $(SRC_DIR)/, main.cpp math.cpp flag.cpp increment.cpp load.cpp compare.cpp branches.cpp memory.cpp misc.cpp)
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)
ASM_SOURCE = $(ASM_SRC_DIR)/test.asm

# Output directories
ASM_DIR = ./build/asm
X86_64_DIR = ./build/x86-64

# Output binaries
ASM_OBJECT = $(ASM_DIR)/test.o
MAIN_OUTPUT = $(X86_64_DIR)/main.o

# Compile C++ files
$(MAIN_OUTPUT): $(CPP_OBJECTS) | $(X86_64_DIR)
	g++ $^ -o $(MAIN_OUTPUT)
	@echo "Building CPP files done"

# Compile assembly file
$(ASM_OBJECT): $(ASM_SOURCE) | $(ASM_DIR)
	acme --cpu 6502 -o $(ASM_OBJECT) --setpc 0 $(ASM_SOURCE)
	@echo "Building assembly done"

# Target to run the program
run: $(MAIN_OUTPUT) $(ASM_OBJECT)
	./$(MAIN_OUTPUT) $(ASM_OBJECT)
	@echo "Running done"

# Pattern rule for building C++ object files
%.o: %.cpp
	g++ -c $< -o $@

# Targets to create output directories
$(ASM_DIR):
	mkdir -p $(ASM_DIR)

$(X86_64_DIR):
	mkdir -p $(X86_64_DIR)

# Clean target to remove generated files and directories
clean:
	rm -f $(CPP_OBJECTS) $(ASM_OBJECT) $(MAIN_OUTPUT)
	rm -rf $(ASM_DIR) $(X86_64_DIR)
