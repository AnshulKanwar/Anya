TARGET_EXEC := anya

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS = $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

CXXFLAGS = -std=c++20 -I ./include/

$(BUILD_DIR)/$(TARGET_EXEC):
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)