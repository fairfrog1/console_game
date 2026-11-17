all: out

main: main.c
	cc -c main.c

perlin: perlin_noise2D.c perlin_noise2D.h
	cc -c perlin_noise2D.c

out: main.o perlin_noise2D.o
	cc main.o perlin_noise2D.o -o console_game.exe
