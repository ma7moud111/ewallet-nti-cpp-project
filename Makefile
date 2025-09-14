# Makefile for E-Wallet Application

# Project settings
PROJECT_NAME = ewallet
TARGET = $(PROJECT_NAME)
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -O2
LDFLAGS =

# Directory structure
SRCDIR = ./src
INCDIR = ./include
BUILDDIR = ./build
DATADIR = ./data
DOCSDIR = ./docs

# Source subdirectories
CORE_SRCDIR = $(SRCDIR)/core
SERVICES_SRCDIR = $(SRCDIR)/services
REPOS_SRCDIR = $(SRCDIR)/repositories
MODELS_SRCDIR = $(SRCDIR)/models
UI_SRCDIR = $(SRCDIR)/ui
CONFIG_SRCDIR = $(SRCDIR)/config

# Include subdirectories
CORE_INCDIR = $(INCDIR)/core
SERVICES_INCDIR = $(INCDIR)/services
REPOS_INCDIR = $(INCDIR)/repositories
MODELS_INCDIR = $(INCDIR)/models
UI_INCDIR = $(INCDIR)/ui
CONFIG_INCDIR = $(INCDIR)/config

# Build subdirectories
CORE_BUILDDIR = $(BUILDDIR)/core
SERVICES_BUILDDIR = $(BUILDDIR)/services
REPOS_BUILDDIR = $(BUILDDIR)/repositories
MODELS_BUILDDIR = $(BUILDDIR)/models
UI_BUILDDIR = $(BUILDDIR)/ui
CONFIG_BUILDDIR = $(BUILDDIR)/config

# Include paths
CXXFLAGS += -I$(CORE_INCDIR) -I$(SERVICES_INCDIR) -I$(REPOS_INCDIR) -I$(MODELS_INCDIR) -I$(UI_INCDIR) -I$(CONFIG_INCDIR)

# Source files by category
CORE_SRCS = $(wildcard $(CORE_SRCDIR)/*.cpp)
SERVICES_SRCS = $(wildcard $(SERVICES_SRCDIR)/*.cpp)
REPOS_SRCS = $(wildcard $(REPOS_SRCDIR)/*.cpp)
MODELS_SRCS = $(wildcard $(MODELS_SRCDIR)/*.cpp)
UI_SRCS = $(wildcard $(UI_SRCDIR)/*.cpp)
CONFIG_SRCS = $(wildcard $(CONFIG_SRCDIR)/*.cpp)

# All source files
SRCS = $(CORE_SRCS) $(SERVICES_SRCS) $(REPOS_SRCS) $(MODELS_SRCS) $(UI_SRCS) $(CONFIG_SRCS)

# Object files
CORE_OBJS = $(patsubst $(CORE_SRCDIR)/%.cpp,$(CORE_BUILDDIR)/%.o,$(CORE_SRCS))
SERVICES_OBJS = $(patsubst $(SERVICES_SRCDIR)/%.cpp,$(SERVICES_BUILDDIR)/%.o,$(SERVICES_SRCS))
REPOS_OBJS = $(patsubst $(REPOS_SRCDIR)/%.cpp,$(REPOS_BUILDDIR)/%.o,$(REPOS_SRCS))
MODELS_OBJS = $(patsubst $(MODELS_SRCDIR)/%.cpp,$(MODELS_BUILDDIR)/%.o,$(MODELS_SRCS))
UI_OBJS = $(patsubst $(UI_SRCDIR)/%.cpp,$(UI_BUILDDIR)/%.o,$(UI_SRCS))
CONFIG_OBJS = $(patsubst $(CONFIG_SRCDIR)/%.cpp,$(CONFIG_BUILDDIR)/%.o,$(CONFIG_SRCS))

# All object files
OBJS = $(CORE_OBJS) $(SERVICES_OBJS) $(REPOS_OBJS) $(MODELS_OBJS) $(UI_OBJS) $(CONFIG_OBJS)

# Build directories to create
BUILD_DIRS = $(BUILDDIR) $(CORE_BUILDDIR) $(SERVICES_BUILDDIR) $(REPOS_BUILDDIR) $(MODELS_BUILDDIR) $(UI_BUILDDIR) $(CONFIG_BUILDDIR) $(DATADIR)

# Phony targets
.PHONY: all build clean run setup help dirs

# Default target
all: build

# Setup project structure
setup: dirs
	@echo "Setting up project structure..."
	@mkdir -p $(INCDIR)/core $(INCDIR)/services $(INCDIR)/repositories $(INCDIR)/models $(INCDIR)/ui $(INCDIR)/config
	@mkdir -p $(SRCDIR)/core $(SRCDIR)/services $(SRCDIR)/repositories $(SRCDIR)/models $(SRCDIR)/ui $(SRCDIR)/config
	@mkdir -p $(DOCSDIR)
	@touch $(DATADIR)/.gitkeep
	@echo "Project structure created successfully!"

# Create build directories
dirs:
	@mkdir -p $(BUILD_DIRS)

# Build target
build: dirs $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Build completed successfully!"

# Compile core source files
$(CORE_BUILDDIR)/%.o: $(CORE_SRCDIR)/%.cpp
	@echo "Compiling core: $<"
	$(CXX) $< -c -o $@ $(CXXFLAGS)

# Compile services source files
$(SERVICES_BUILDDIR)/%.o: $(SERVICES_SRCDIR)/%.cpp
	@echo "Compiling services: $<"
	$(CXX) $< -c -o $@ $(CXXFLAGS)

# Compile repositories source files
$(REPOS_BUILDDIR)/%.o: $(REPOS_SRCDIR)/%.cpp
	@echo "Compiling repositories: $<"
	$(CXX) $< -c -o $@ $(CXXFLAGS)

# Compile models source files
$(MODELS_BUILDDIR)/%.o: $(MODELS_SRCDIR)/%.cpp
	@echo "Compiling models: $<"
	$(CXX) $< -c -o $@ $(CXXFLAGS)

# Compile UI source files
$(UI_BUILDDIR)/%.o: $(UI_SRCDIR)/%.cpp
	@echo "Compiling UI: $<"
	$(CXX) $< -c -o $@ $(CXXFLAGS)

# Compile config source files
$(CONFIG_BUILDDIR)/%.o: $(CONFIG_SRCDIR)/%.cpp
	@echo "Compiling config: $<"
	$(CXX) $< -c -o $@ $(CXXFLAGS)

# Run the application
run: $(TARGET)
	@echo "Running $(PROJECT_NAME)..."
	./$(TARGET)

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILDDIR)
	@rm -f $(TARGET)
	@echo "Clean completed!"

# Deep clean including data files
clean-all: clean
	@echo "Cleaning data files..."
	@rm -f $(DATADIR)/*.csv
	@echo "Deep clean completed!"

# Install dependencies (placeholder)
install-deps:
	@echo "No external dependencies required for this project."

# Show help
help:
	@echo "E-Wallet Application Build System"
	@echo "================================="
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build the application (default)"
	@echo "  build      - Build the application"
	@echo "  run        - Build and run the application"
	@echo "  clean      - Remove build files"
	@echo "  clean-all  - Remove build files and data files"
	@echo "  setup      - Create project directory structure"
	@echo "  dirs       - Create build directories"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Project structure:"
	@echo "  src/       - Source files organized by category"
	@echo "  include/   - Header files organized by category"
	@echo "  build/     - Object files (auto-generated)"
	@echo "  data/      - CSV data files (auto-generated)"
	@echo "  docs/      - Documentation"
	@echo ""
	@echo "Build settings:"
	@echo "  Compiler:  $(CXX)"
	@echo "  Standard:  C++20"
	@echo "  Target:    $(TARGET)"

# Debug target to print variables
debug:
	@echo "=== Debug Information ==="
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "BUILD_DIRS: $(BUILD_DIRS)"