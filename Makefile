CXX = g++
CXXFLAGS = -Wall -std=c++14
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# List all object files (excluding test files)
OBJS = Entity.o Enemy.o Goblin.o GoblinBrute.o GoblinLord.o \
       Player.o Warrior.o Wizard.o Rogue.o \
       Knight.o Archmage.o Assassin.o \
       Controller.o Menu.o Environment.o \
       WaveManager.o \
       HUD.o \
       Leaderboard.o \
       main.o

# Main target
all: game

game: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o game $(SFML_FLAGS)

# Compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f *.o game leaderboard.txt

# Run the game
run: game
	./game

.PHONY: all clean run