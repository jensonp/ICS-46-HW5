CXX := g++
CXXFLAGS := -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -fsanitize=address,undefined 

SRC_DIR := src
TEST_DIR := gtest
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_NO_MAIN := $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))
OBJS := $(SRCS:.cpp=.o)
OBJS_NO_MAIN := $(SRCS_NO_MAIN:.cpp=.o)

TARGET := hw5
GTEST_TARGET := run_tests
GTEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
GTEST_OBJS := $(GTEST_SRCS:.cpp=.o)
LDFLAGS := -lgtest -lgtest_main -pthread -fsanitize=address,undefined

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(GTEST_OBJS) $(OBJS_NO_MAIN)
	$(CXX) $(CXXFLAGS) -o $(GTEST_TARGET) $^ $(LDFLAGS)
	./$(GTEST_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) $(GTEST_TARGET)

.PHONY: all test run clean
