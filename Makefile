CC=g++
CFLAGS=`pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0` -lsqlite3
SRC=main.cpp MealEntryWindow.cpp Database.cpp Meal.cpp CalorieTracker.cpp
OBJ=$(SRC:.cpp=.o)
EXEC=calorietracker

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

