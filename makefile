################################################################################
# Shamelessly taken and modified from
# 1. https://github.com/mbcrawfo/GenericMakefile/blob/master/cpp/Makefile
# 2. https://gist.github.com/mauriciopoppe/de8908f67923091982c8c8136a063ea6
################################################################################
CC := g++
BIN_NAME := calc
T_BIN_NAME := tester
SRC_EXT := cpp

SRC_DIR := src
TEST_DIR := tests
INC_DIR := include

R_BUILD_DIR := build/release
D_BUILD_DIR := build/debug
T_BUILD_DIR := build/test

R_BIN_DIR := bin/release
D_BIN_DIR := bin/debug
T_BIN_DIR := bin/test

LIBS = 
COMPILE_FLAGS = -Wall -Wextra -g -fdiagnostics-color=always -std=c++17
INCLUDES = -I $(SRC_DIR) -I $(INC_DIR)
LINK_FLAGS =

R_COMPILE_FLAGS =
R_LINK_FLAGS =
D_COMPILE_FLAGS = -D DEBUG
D_LINK_FLAGS =
T_COMPILE_FLAGS = -D DEBUG -D TEST -pthread
T_LINK_FLAGS = -lgtest -lgtest_main -pthread

######################## escapeseq ########################
COLOR_RESET = \033[m
COLOR_DESCR = \033[;34m
COLOR_COMPL = \033[;34m
COLOR_DURAT = \033[;4m
COLOR_FADED = \033[;90m
COLOR_HEAD = \033[;33;4m
COLOR_MAJOR = \033[;33m

COLOR_ERROR = \033[;31m
TAB = \ \ \ \ 

######################### versioning ########################
USE_VERSION := true
VERSION := $(shell git describe --tags --long --dirty --always | \
		sed 's/v\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)-\?.*-\([0-9]*\)-\(.*\)/\1 \2 \3 \4 \5/g')
VERSION_MAJOR := $(word 1, $(VERSION))
VERSION_MINOR := $(word 2, $(VERSION))
VERSION_PATCH := $(word 3, $(VERSION))
VERSION_REVISION := $(word 4, $(VERSION))
VERSION_HASH := $(word 5, $(VERSION))
VERSION_STRING := \
	"$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_REVISION)-$(VERSION_HASH)"
override CXXFLAGS := $(CXXFLAGS) \
	-D VERSION_MAJOR=$(VERSION_MAJOR) \
	-D VERSION_MINOR=$(VERSION_MINOR) \
	-D VERSION_PATCH=$(VERSION_PATCH) \
	-D VERSION_REVISION=$(VERSION_REVISION) \
	-D VERSION_HASH=\"$(VERSION_HASH)\" \
	-D VERSION_STRING=\"$(VERSION_STRING)\"

######################## settings ########################

print-%: @echo $*=$($*)

release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(R_COMPILE_FLAGS)
release: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(R_LINK_FLAGS)
debug: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(D_COMPILE_FLAGS)
debug: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(D_LINK_FLAGS)
testbin: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(T_COMPILE_FLAGS)
testbin: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(T_LINK_FLAGS)

release: export SRCS := $(SRC_DIR)
release: export BUILD_DIR := $(R_BUILD_DIR)
release: export BIN_DIR := $(R_BIN_DIR)
debug: export SRCS := $(SRC_DIR)
debug: export BUILD_DIR := $(D_BUILD_DIR)
debug: export BIN_DIR := $(D_BIN_DIR)
testbin: export SRCS := $(SRC_DIR) $(TEST_DIR)
testbin: export BUILD_DIR := $(T_BUILD_DIR)
testbin: export BIN_DIR := $(T_BIN_DIR)
test: export BIN_DIR := $(T_BIN_DIR)

release: export TARGET_BIN_NAME = $(BIN_NAME)
debug: export TARGET_BIN_NAME = $(BIN_NAME)
testbin: export TARGET_BIN_NAME = $(T_BIN_NAME)
test: export TARGET_BIN_NAME = $(T_BIN_NAME)

SOURCES = $(shell find $(SRCS) -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
	| sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:%.$(SRC_EXT)=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

# For timing
TIME_FILE = $(dir $@).$(notdir $@)_time
START_TIME = date '+%s' > $(TIME_FILE)
END_TIME = read st < $(TIME_FILE) ; \
	$(RM) $(TIME_FILE) ; \
	st=$$((`date '+%s'` - $$st - 86400)) ; \
	echo `date -u -d @$$st '+%H:%M:%S'`

.PHONY: release
release: dirs
	@printf "%b" "$(COLOR_DESCR)Beginning release build"
ifeq ($(USE_VERSION), true)
	@printf " v$(VERSION_STRING) "
endif
	@printf "%b" "...$(COLOR_RESET)\n"
	@$(MAKE) all --no-print-directory

.PHONY: debug
debug: dirs
	@printf "%b" "$(COLOR_DESCR)Beginning debug build"
ifeq ($(USE_VERSION), true)
	@printf " v$(VERSION_STRING) "
endif
	@printf "%b" "...$(COLOR_RESET)\n"
	@$(MAKE) all --no-print-directory

.PHONY: testbin
testbin: dirs
	@printf "%b" "$(COLOR_DESCR)Beginning test build"
ifeq ($(USE_VERSION), true)
	@printf " v$(VERSION_STRING) "
endif
	@printf "%b" "...$(COLOR_RESET)\n"
	@rm -f $(BIN_DIR)/$(TARGET_BIN_NAME)
	@$(MAKE) all --no-print-directory

.PHONY: test
test: testbin
	@$(BIN_DIR)/$(TARGET_BIN_NAME) ; \
	exit $$?

all:
	@echo "$(COLOR_HEAD)Compiling$(COLOR_RESET)"
	@$(START_TIME)
	@printf "%b" "$(COLOR_DESCR)With cxxflags: $(COLOR_RESET)$(CXXFLAGS)\n"
	@printf "%b" "$(COLOR_DESCR)With includes: $(COLOR_RESET)$(INCLUDES)\n"
	@$(MAKE) $(BIN_DIR)/$(TARGET_BIN_NAME) --no-print-directory
	@printf "%b" "$(COLOR_MAJOR)Total build time: $(COLOR_RESET)$(COLOR_DURAT)"
	@$(END_TIME)
	@printf "%b" "$(COLOR_RESET)\n"

.PHONY: dirs
dirs:
	@printf "%b" "$(COLOR_DESCR)Creating directories...$(COLOR_RESET)"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_DIR)
	@echo " done"

.PHONY: clean
clean: clean-dumps
	@printf "%b" "$(COLOR_DESCR)Deleting directories...$(COLOR_RESET)"
	@$(RM) -r build
	@$(RM) -r bin
	@echo " done"

.PHONY: clean-dumps
clean-dumps:
	@printf "%b" "$(COLOR_DESCR)Deleting dumps...$(COLOR_RESET)"
	@$(RM) *.core
	@$(RM) *.stackdump
	@echo " done"

.PHONY: docs
docs:
	@echo "$(COLOR_DESCR)Making docs...$(COLOR_RESET)"
	@echo "$(COLOR_DESCR)Warning:$(COLOR_RESET) If you see ImportError: cannot import name 'main', run source pyenv/bin/activate first"
	@cd docs ; \
	doxygen Doxyfile > doxy.log ; \
	$(MAKE) html --no-print-directory

$(BIN_DIR)/$(TARGET_BIN_NAME): $(OBJECTS)
	@echo "\n$(COLOR_HEAD)Linking$(COLOR_RESET)"
	@echo "$(COLOR_DESCR)With flags:$(COLOR_RESET) $(LDFLAGS)"
	@echo "$(COLOR_DESCR)Target:$(COLOR_RESET) $@"
	@$(START_TIME)
	@echo "    Linking..."
	@$(CMD_PREFIX)$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@printf "%b" "    Linked in: $(COLOR_DURAT)"
	@$(END_TIME)
	@printf "%b" "$(COLOR_RESET)\n"
	
-include $(DEPS)

$(BUILD_DIR)/%.o: %.$(SRC_EXT)
	@printf "%b" "$(COLOR_COMPL)$< $(COLOR_RESET)-> $@\n"
	@$(START_TIME)
	@$(CMD_PREFIX)$(CC) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@ 2>&1 | sed 's/^/$(TAB)/'
	@printf "%b" "    Compiled in: $(COLOR_DURAT)"
	@$(END_TIME)
	@printf "%b" "$(COLOR_RESET)"