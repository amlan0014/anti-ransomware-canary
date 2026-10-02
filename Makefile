CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

LDFLAGS = -lcrypto

TARGET = anti_ransomware

SOURCES = \
	src/main.cpp \
	src/canary_manager.cpp \
	src/filesystem_monitor.cpp \
	src/integrity_manager.cpp \
	src/event_processor.cpp \
	src/alert_manager.cpp \
	src/event_logger.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)