#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZEY 50
#define SIZEX 50

char buff[SIZEY][SIZEX] = {0};
int x = SIZEX/2, y = SIZEY/2;

typedef enum {
    EMPTY = 46,
    DIRT = 68,
    STONE = 83,
    SAND = 115,
    ORE = 111,
    DIAMOND = 100,
    WATERPOOL,
    LAVA,
    CRYSTAL
} Type;

typedef struct {
    int x, y;
    Type type;
    bool solid;  
} Block;

//Block world[SIZEY * SIZEX];


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
	if(x >= 0 && x < SIZEX && y >= 0 && y < SIZEY &&
	       buff[y][x] != type) buff[y][x] = type;
    }
}
void buff_init() {
    
    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    buff[i][j] = DIRT;
	}
    }// filling with dirt

    static float r = 0.0f;

    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 2.879) gen_ply(j,i,SAND,25);
	}
    }// filling with some sand

    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 1.33) gen_ply(j,i,STONE,17);
	}
    }// filling with some stone

    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 1.09) gen_ply(j,i,ORE,10);
	}
    }// filling with some ore

    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    r = rand() % 100;	
	    if(r < 0.10) gen_ply(j,i,DIAMOND,4);
	}
    }// filling with some diamonds
}

 
int c = 0;

void print() {
    for(int i = 0; i < SIZEY; ++i) {
	printf(i <= 9 ? "%d  " : "%d ", i);
	for(int j = 0; j < SIZEX; ++j) {
	    printf("%c", buff[i][j]);
	}
	putchar('\n');
    }
	printf("%d\n", c);
}

void rand_walk() {
    int step = 0;   
    buff[y][x] = '.';
    
    do {
	
	buff_init();
	x = SIZEX/2;
	y = SIZEY/2;		
	c = 0;
	step = 0;

	while(step != 8000) {
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
	    if(x >= 0 && x < SIZEX && y >= 0 && y < SIZEY &&
	       buff[y][x] != '.')
	    {
		buff[y][x] = '.';
		c++;
	    }	    		    	
	}
    } while(c <= (SIZEX*SIZEY) * 0.47);
    print();
    
    // delete all single blocks in the space 
    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    int count = 0;
	    for(int f = 0; f < 3; f++) {
		for(int g = 0; g < 3; g++) {
		    if(buff[i+f-1][j+g-1] != EMPTY) {
			if((i+f-1) != i || (j+g-1) != j) count++;
		    }
		}
	    }
	    if(count <= 2) {
		buff[i][j] = EMPTY;		
	    }
	}
    }

    for(int i = 0; i < SIZEY; ++i) {
	for(int j = 0; j < SIZEX; ++j) {
	    int count = 0;
	    for(int f = 0; f < 5; f++) {
		for(int g = 0; g < 5; g++) {
		    if(buff[i+f-2][j+g-2] != EMPTY) {
			if((i+f-2) != i || (j+g-2) != j) count++;
		    }
		}
	    }
	    if(count <= 5) {
		buff[i][j] = EMPTY;	    
	    }
	}
    }

    while(1) {
	int px = rand() % SIZEX;
	int py = rand() % SIZEY;
	if(px == EMPTY && py == EMPTY){
	    buff[py][px] = 'X';
	    break;
	}
    }
}
    
int main(void) {
    srand(time(NULL));
    
    buff_init();
    print();
    rand_walk(); 
    print();
    
    return 0;
}
