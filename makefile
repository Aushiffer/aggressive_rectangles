CCFLAGS = -g -Wall -Werror -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_primitives
PROGRAM = aggressive_rectangles

all: $(PROGRAM)

$(PROGRAM): main.o rect.o joystick.o
	$(CC) -o $(PROGRAM) main.o rect.o joystick.o $(CCFLAGS) $(ALLEGRO_LIBS)

main.o: main.c
	$(CC) -c main.c $(CCFLAGS) $(ALLEGRO_LIBS)

rect.o: rect.c
	$(CC) -c rect.c $(CCFLAGS) $(ALLEGRO_LIBS)

joystick.o: joystick.c
	$(CC) -c joystick.c $(CCFLAGS)

clear:
	rm -f *.o

purge:
	rm -f *.ch *.o $(PROGRAM)