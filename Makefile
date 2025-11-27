CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -MMD -MP
SRCDIR = src
OBJDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = game

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS) | data
	$(CXX) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

data:
	mkdir -p data

clean:
	rm -rf $(OBJDIR) $(TARGET) data/match_history.json

run: all
	./$(TARGET)

-include $(OBJECTS:.o=.d)