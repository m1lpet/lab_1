CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = boardgame_db
OBJS = main.o BoardGame.o Database.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Database.h BoardGame.h
	$(CXX) $(CXXFLAGS) -c main.cpp

BoardGame.o: BoardGame.cpp BoardGame.h
	$(CXX) $(CXXFLAGS) -c BoardGame.cpp

Database.o: Database.cpp Database.h BoardGame.h
	$(CXX) $(CXXFLAGS) -c Database.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
