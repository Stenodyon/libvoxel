NAME:=libvoxel

SRC_DIR:=src/
BUILD_DIR:=build/
TESTS_DIR:=tests/

FLAGS=-std=c++17 -Wall -Wextra -Wno-sign-compare -I./include/
LIBS=

# -----------------------------------------------------

ifeq ($(OS), WINDOWS_NT)
    EXT=.lib
else
    EXT=.a
endif

BIN:=$(NAME)$(EXT)
BIN_DEBUG:=$(NAME).debug$(EXT)
BIN_TEST:=$(NAME).test

LEX_SRC:=$(shell find $(SRC_DIR) -type f -name '*.l')
BISON_SRC:=$(shell find $(SRC_DIR) -type f -name '*.y')
SRC:=$(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ:=$(SRC:$(SRC_DIR)%.cpp=$(BUILD_DIR)%.o)

TEST_SRC:=$(shell find $(TESTS_DIR) -type f -name '*.cpp')
TEST_OBJ:=$(TEST_SRC:$(TESTS_DIR)%.cpp=$(BUILD_DIR)tests/%.o)

FLAGS+= -MT $@ -MMD -MP -MF $(dir $@).d/$(basename $(notdir $@)).d

default: release

release: FLAGS+= -O2
release: $(BIN)

debug: FLAGS+= -g -D _DEBUG
debug: $(BIN_DEBUG)

profile: FLAGS+= -pg
profile: debug

test: FLAGS+= -g -D _TESTING -I./tests/ `pkg-config --cflags gtest`
test: LIBS+= `pkg-config --libs gtest`
test: $(BIN_TEST)
	./$(BIN_TEST)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(INTERMEDIATES) $(BIN) $(BIN_DEBUG) $(BIN_TEST)

.PHONY: release debug profile test clean

$(BIN): $(OBJ)
	ar rvs $(BIN) $(OBJ)
	rm -f $(INTERMEDIATES)

$(BIN_DEBUG): $(OBJ)
	ar rvs $(BIN) $(OBJ)
	rm -f $(INTERMEDIATES)

$(BIN_TEST): $(TEST_OBJ)
	$(CXX) $(FLAGS) $(TEST_OBJ) $(LIBS) -L. -lvoxel -o $(BIN_TEST)
	rm -f $(INTERMEDIATES)

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $@).d
	$(CXX) -c $< $(FLAGS) -o $@

$(BUILD_DIR)tests/%.o: $(TESTS_DIR)%.cpp $(BIN)
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $@).d
	$(CXX) -c $< $(FLAGS) -I./src -o $@

include $(shell find $(DEP_DIR) -type f -name '*.d')
