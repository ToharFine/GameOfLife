#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 20

static int** screen;

static void initScreen(){
    screen = (int**) malloc(HEIGHT * sizeof(int*));

    for(int i = 0; i < HEIGHT; ++i){
        screen[i] = (int*) calloc(WIDTH, sizeof(int));
    }

}

static void randomizeScreen(){
      for(int i = 0; i < HEIGHT; ++i){
        srand(time(NULL)+i);
        for(int j = 0; j < WIDTH; ++j){
            if(rand() % 7 == 0){
                screen[i][j] = 1;
            }
            
            // printf("%d\n", rand());
        }
    }
}

static void printScreen(){
    for(int i = 0; i < HEIGHT; ++i){
        for(int j = 0; j < WIDTH; ++j){
            if(screen[i][j]){
                fprintf(stdout,"[]");
            } else{
                fprintf(stdout,"  ");
            }
            // printf("%d", screen[i][j]);
        }
        fprintf(stdout,"  %d\n", i);
    }
    fprintf(stdout,"\n\n");
}

static int countAliveNeighbors(int x, int y){
    int cells = 0;
    
    int minEdgeX = 0 < x;
    int maxEdgeX = (WIDTH - 1) > x;
    int minEdgeY = 0 < y;
    int maxEdgeY = (HEIGHT - 1) > y;

    if(minEdgeX)
        cells += screen[y][x-1];
    if(maxEdgeX)
        cells += screen[y][x+1];
    if(minEdgeY)
        cells += screen[y-1][x];
    if(maxEdgeY)
        cells += screen[y+1][x];
    if(minEdgeX && minEdgeY)
        cells += screen[y-1][x-1];
    if(maxEdgeX && minEdgeY)
        cells += screen[y-1][x+1];
    if(maxEdgeX && maxEdgeY)
        cells += screen[y+1][x+1];
    if(minEdgeX && maxEdgeY)
        cells += screen[y+1][x-1];
    
    return cells;
}

static void applyRules(int x, int y){
    int ncells = countAliveNeighbors(x,y);
    if(screen[y][x] && (ncells < 2 || ncells > 3)){
        screen[y][x] = 0;
    } else if(!screen[y][x] && ncells == 3){
        screen[y][x] = 1;
    }
}

static void gameTurn(){
    for(int i = 0; i < HEIGHT; ++i){
        for(int j = 0; j < WIDTH; ++j){   
            // printf("y: %d x: %d |", i, j);
            applyRules(j,i);
        }
    }
}

int main(int argc, char const *argv[])
{
    char buff[10024];
    memset( buff, '\0', sizeof( buff ));
    setvbuf(stdout, buff, _IOFBF, 10024);

    printf("start\n");

    initScreen();
    randomizeScreen();

    printScreen();

    for (int i = 0; i < 100; i++)
    {
        Sleep(500);
        gameTurn();
        printScreen();
        fflush(stdout);
    }
    
    
    // printScreen();

    printf("end");
    
    free(screen);

    return 0;
}