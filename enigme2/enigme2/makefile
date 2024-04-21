prog: enigme.o main.o
	gcc enigme.o main.o -o prog -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -lSDL_gfx

main.o: main.c
	gcc -c main.c -o main.o

enigme.o: enigme.c
	gcc -c enigme.c -o enigme.o

