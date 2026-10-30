CXX = g++
CXXFLAGS = -std=c++20 -Wall -fsanitize=address -fsanitize=undefined -pedantic
BUILD_DIR = build
OUT_EXE = utms.out

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

SRCS := $(wildcard code/src/*.cpp) $(wildcard utils/*.cpp) $(wildcard server/*.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

INC_DIRS := code/include utils server
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
