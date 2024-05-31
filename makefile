CCFLAGS = -g -Wall -Werror -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_primitives
PROGRAM = aggressive_rectangles

all: $(PROGRAM)

$(PROGRAM): main.o rect.o joystick.o fireball.o
	$(CC) -o $(PROGRAM) main.o rect.o joystick.o fireball.o $(CCFLAGS) $(ALLEGRO_LIBS)

main.o: src/main.c
	$(CC) -c src/main.c $(CCFLAGS) $(ALLEGRO_LIBS)

rect.o: src/rect.c
	$(CC) -c src/rect.c $(CCFLAGS)

joystick.o: src/joystick.c
	$(CC) -c src/joystick.c $(CCFLAGS)

fireball.o: src/fireball.c
	$(CC) -c src/fireball.c $(CCFLAGS)

clear:
	rm -f *.o

purge:
	rm -f *.ch *.o $(PROGRAM)
