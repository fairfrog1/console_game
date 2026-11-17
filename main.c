// Mine or die!

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "console.h"
#include "perlin_noise2d.h"
#include <time.h>

#define SCREENBUFFX 34
#define SCREENBUFFY 26
#define WORLDSIZEX  100
#define WORLDSIZEY  100

char worldbuff[WORLDSIZEY][WORLDSIZEX];

typedef struct Player {
    float x;
    float y;
    bool is_moving;
} Player;

typedef enum {
    EMPTY = 32,
    DIRT = 68,
    STONE = 83,
    SAND = 115,
    ORE = 111,
    DIAMOND = 100,
    WATERPOOL,
    LAVA,
    CRYSTAL
} Type;

int runnig = 1;
Player p = {WORLDSIZEX/2, WORLDSIZEY/2, true };
int f = 0;
int c = 0;
int x = WORLDSIZEX/2, y = WORLDSIZEY/2;

void gen_ply(int x, int y, int type, int steps) {
    int step = 0;
    while(step != steps) {
	step++;
	int n = rand() % 4;
	
	switch(n) {	    
	case 0 :
	    x++;
	    break;
	case 1 :
	    x--;
	    break;
	case 2:
	    y++;
	    break;
	case 3 :
	    y--;
	    break;
	}
	if(x >= 0 && x < WORLDSIZEX && y >= 0 && y < WORLDSIZEY &&
	       worldbuff[y][x] != type) worldbuff[y][x] = type;
    }
}

void buff_init() {
    
    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    worldbuff[i][j] = DIRT;
	}
    }// filling with dirt

    static float r = 0.0f;

    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 2.879) gen_ply(j,i,SAND,25);
	}
    }// filling with some sand

    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 1.33) gen_ply(j,i,STONE,17);
	}
    }// filling with some stone

    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 1.09) gen_ply(j,i,ORE,10);
	}
    }// filling with some ore

    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 0.10) gen_ply(j,i,DIAMOND,4);
	}
    }// filling with some diamonds
}

void rand_walk() {
    int step = 0;   
    worldbuff[y][x] = EMPTY;
    
    do {
	
	buff_init();
	x = WORLDSIZEX / 2;
	y = WORLDSIZEY / 2;		
	c = 0;
	step = 0;

	while(step != 27000) {
	    step++;
	    int n = rand() % 4;
	
	    switch(n) {	    
	    case 0 :
		x++;
		break;
	    case 1 :
		x--;
		break;
	    case 2:
		y++;
		break;
	    case 3 :
		y--;
		break;
	    }
	    if(x >= 0 && x < WORLDSIZEX && y >= 0 && y < WORLDSIZEY &&
	       worldbuff[y][x] != EMPTY)
	    {
		worldbuff[y][x] = EMPTY;
		c++;
	    }	    		    	
	}
    } while(c <= (WORLDSIZEX*WORLDSIZEY) * 0.47);
    
    // delete all single blocks in the space 
    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    int count = 0;
	    for(int f = 0; f < 3; f++) {
		for(int g = 0; g < 3; g++) {
		    if(worldbuff[i+f-1][j+g-1] != EMPTY) {
			if((i+f-1) != i || (j+g-1) != j) count++;
		    }
		}
	    }
	    if(count <= 2) {
		worldbuff[i][j] = EMPTY;		
	    }
	}
    }

    for(int i = 0; i < WORLDSIZEY; ++i) {
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    int count = 0;
	    for(int f = 0; f < 5; f++) {
		for(int g = 0; g < 5; g++) {
		    if(worldbuff[i+f-2][j+g-2] != EMPTY) {
			if((i+f-2) != i || (j+g-2) != j) count++;
		    }
		}
	    }
	    if(count <= 5) {
		worldbuff[i][j] = EMPTY;	    
	    }
	}
    }

    /* while(1) { */
    /* 	int px = rand() % WORLDSIZEX; */
    /* 	int py = rand() % WORLDSIZEY; */
    /* 	if(px == EMPTY && py == EMPTY){ */
    /* 	    worldbuff[py][px] = 'X'; */
    /* 	    break; */
    /* 	} */
    /* } */
}


void gen_random_world() {
    buff_init();
    rand_walk();
	    /* float n; */
	    /* float f = 7; */
	    /* float amp = 3; */
	    
	    /* for (int k = 0; k < 10; k++) */
            /* { */
	    /* 	n += Pnoise(i * f / WORLDSIZEY, j * f / WORLDSIZEX) * amp; */
	    /* 	f *= 2; */
	    /* 	amp /= 2; */
	    /* } */

	    /* // Contrast */
            /* n *= 0.8; */
            
            /* // Clipping */
            /* if (n > 1.0f) */
            /*     n = 1.0f; */
            /* else if (n < -1.0f) */
            /*     n = -1.0f; */

	    /* int result = (int)(((n + 1.0f) * 0.5) * 10); */
	 
	    /* printf((result > 9 ? "%d" : "%d "), result); */
	    /* if(result >= 5) worldworldbuff[i][j] = 219; */
	    /* else worldbuff[i][j] = ' '; */
}

void gen_space() {
    int pos = (get_buffer_width() / 2) - SCREENBUFFX / 2 - 1;
    for(int i = 0;i < pos;i++) putchar(' ');
}

void print() {
    for(int i = 0; i < WORLDSIZEY; ++i) {
	printf(i <= 9 ? "%d  " : "%d ", i);
	for(int j = 0; j < WORLDSIZEX; ++j) {
	    printf("%c", worldbuff[i][j]);
	}
	putchar('\n');
    }
	printf("%d\n", c);
}

void print_buff() {
    p.is_moving = false;
    f++;
    
    worldbuff[(int)p.y][(int)p.x] = 1;
    
    set_cursor((get_buffer_width() / 2) - SCREENBUFFX / 2 - 1, (get_buffer_height() / 2) - SCREENBUFFY / 2 - 1);
    
    putchar(218);
    for(int i = 0;i < SCREENBUFFX;i++) {
	putchar(196);
    }
    printf("%c\n", 191);
    gen_space();
    
    for(int i = 0;i < SCREENBUFFY;i++) {
	if(i > 0) gen_space();
	putchar(179);
	for(int j = 0;j < SCREENBUFFX;j++) {
	    char c = worldbuff[ p.y < WORLDSIZEY - SCREENBUFFY / 2 ? (p.y < SCREENBUFFY / 2 ? i : i + (int)p.y - (SCREENBUFFY / 2)) :	                                                                                                 (i + WORLDSIZEY - SCREENBUFFY) ]
		                  [ p.x < WORLDSIZEX - SCREENBUFFX / 2 ? (p.x < SCREENBUFFX / 2 ? j : j + (int)p.x - (SCREENBUFFX / 2)) :
				    (j + WORLDSIZEX - SCREENBUFFX) ];
	    if(c == SAND) {
		//set_color(BG_YELLOW | FG_WHITE);
		printf("\x1b[48;5;184m%c", 176);
	    }
	    else if(c == STONE) {
		set_color(BG_GREY | FG_WHITE);
		printf("%c", 177);
	    }
	    else if(c == ORE) {
		set_color(BG_GREY | FG_WHITE);
		printf("%c", 42);
	    }
	    else if(c == DIRT) { 		
		printf("\x1b[48;5;130m%c", 176);
	    }else {
		printf("%c", c);
	    }
	    set_color(BG_BLACK | FG_WHITE);	 
	}	
	printf("%c\n", 179);
    }
    gen_space();
    putchar(192);
    for(int i = 0;i < SCREENBUFFX;i++) {
	putchar(196);
    }
    printf("%c\n", 217);
    gen_space();
    printf("x: %f\ty: %f\tframes: %d", p.x, p.y, f);
}



int main(void) {
    // for(int i = 0; i < 255; i++) {
    // 	printf("%d %c\n", i, i);
    // }
    srand(time(NULL));
    hide_cursor();
    gen_random_world();
   
    system("cls");
    
    while(runnig) {
	
	if(_kbhit()) {
	    switch (_getch()) {
	    case 'w':
		p.is_moving = true;
		if(worldbuff[(int)p.y-1][(int)p.x] == EMPTY) p.y--;
		worldbuff[(int)p.y + 1][(int)p.x] = ' ';
		break;
	    case 's':
		p.is_moving = true;
		if(worldbuff[(int)p.y+1][(int)p.x] == EMPTY) p.y++;
		worldbuff[(int)p.y - 1][(int)p.x] = ' ';
		break;
	    case 'd':
		p.is_moving = true;
		if(worldbuff[(int)p.y][(int)p.x+1] == EMPTY) p.x++;
		worldbuff[(int)p.y][(int)p.x - 1] = ' ';
		break;
	    case 'a':
		p.is_moving = true;
		if(worldbuff[(int)p.y][(int)p.x-1] == EMPTY)p.x--;
		worldbuff[(int)p.y][(int)p.x + 1] = ' ';
		break;
	    case 'q':
		runnig = 0;
		break;
	    default:
		p.is_moving = false;
		break;
	    }
	}
	
	if(p.is_moving) print_buff();

    }
    return 0;
}
