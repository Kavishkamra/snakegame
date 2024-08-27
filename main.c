#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 40

int gameover;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int direction; // 0: up, 1: down, 2: left, 3: right

void setup() {
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    direction = 3; // Initial direction: right
}

void draw() {
    system("clear"); // Use "cls" for Windows
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1) {
                printf("#");
            } else if (i == x && j == y) {
                printf("O");
            } else if (i == fruitX && j == fruitY) {
                printf("*");
            } else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    char c;
    if (scanf("%c", &c)) {
        switch (c) {
            case 'w': direction = 0; break;
            case 's': direction = 1; break;
            case 'a': direction = 2; break;
            case 'd': direction = 3; break;
            case 'x': gameover = 1; break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direction) {
        case 0: y--; break;
        case 1: y++; break;
        case 2: x--; break;
        case 3: x++; break;
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
    if (x <= 0 || x >= WIDTH-1 || y <= 0 || y >= HEIGHT-1) {
        gameover = 1;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = 1;
        }
    }
}

int main() {
    srand(time(0));
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        usleep(100000); // Delay to slow down the game loop
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
