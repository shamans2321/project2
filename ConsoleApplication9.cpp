﻿#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//птица

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
                    '|','_','_','_',' ','>' };
int birdPos = 6;
int score = 0;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

//поле

void drawBorder() {

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0); cout << "-";
        gotoxy(i, SCREEN_HEIGHT); cout << "-";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "|";
        gotoxy(SCREEN_WIDTH, i); cout << "|";
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH, i); cout << "|";
    }
}
void genPipe(int ind) {
    gapPos[ind] = 3 + rand() % 14;
}

//стены

void drawPipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "|0|";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "|0|";
        }
    }
}
void erasePipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
        }
    }
}

void drawBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos); cout << bird[i][j];
        }
    }
}
void eraseBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos); cout << " ";
        }
    }
}

int collision() {
    if (pipePos[0] >= 61) {
        if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE) {
            return 1;
        }
    }
    return 0;
}
void debug() {

}

void gameover() {
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- вы проиграли ----" << endl;
    cout << "\t\t--------------------------" << endl << endl;
    cout << "\t\t ваш результат:"  << score << endl;
    cout << "\t\t нажмите на энтер что бы вернуться в меню.";
    _getch();
}
void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

void instructions() {

    system("cls");
    cout << "инструкция";
    cout << "\n----------------";
    cout << "\n жми пробел что бы летать";
    cout << "\n\nнажми энтер что бы вернуться в меню";
    _getch();
}

void play() {

    birdPos = 6;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    score = 0;
    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system("cls");
    drawBorder();
    genPipe(0);
    updateScore();

    gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD (ну типа)";
    gotoxy(WIN_WIDTH + 6, 4); cout << "-------------";
    gotoxy(WIN_WIDTH + 6, 6); cout << "-------------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "управление ";
    gotoxy(WIN_WIDTH + 7, 13); cout << "------------ ";
    gotoxy(WIN_WIDTH + 2, 14); cout << "пробел=летать";

    gotoxy(10, 5); cout << "нажмите энтер чтобы летать";
    _getch();
    gotoxy(10, 5); cout << "                      ";

    while (1) {
        // проверка на нажатие 
        if (_kbhit()) { 
            char ch = _getch();
            if (ch == 32) { //пробел
                if (birdPos > 3)
                    birdPos -= 3;
            }
            if (ch == 27) {//ескейп
                break;
            }
        }

        drawBird();
        drawPipe(0);
        drawPipe(1);
        debug();
        if (collision() == 1) {
            gameover();
            return;
        }
        Sleep(100); // остановка
        eraseBird(); // удаление птахи
        erasePipe(0); // удаление препятствий
        erasePipe(1); // удаление препятствий
        birdPos += 1;

        if (birdPos > SCREEN_HEIGHT - 2) {
            gameover();
            return; // Проверка позиции птици на выход за границ
        }

        if (pipeFlag[0] == 1)
            pipePos[0] += 2; 
        //Если флаг pipeFlag[0] равен 1, то позиция первой трубы увеличивается на 2 . точно также и для второй
        if (pipeFlag[1] == 1)
            pipePos[1] += 2;

        if (pipePos[0] >= 40 && pipePos[0] < 42) {
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            genPipe(1); // труба находится в диапазоне от 40 до 42  флаг наличия трубы созд новая труба
        }
        if (pipePos[0] > 68) { //проверка того что труба вышла за пределы экрана
            score++;
            updateScore(); // увеличение счёта
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1]; // обновляют позиции трубы и расстояние
            gapPos[0] = gapPos[1];
        }

    }

}

int main()
{
    setlocale(LC_ALL, "RU");
    setcursor(0, 0);
    srand((unsigned)time(NULL)); // случайные числа

    //    меню

    do {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |      Flappy Bird       | ";
        gotoxy(10, 7); cout << " --------------------------";
        gotoxy(10, 9); cout << "1. начать игру";
        gotoxy(10, 10); cout << "2. инструкция";
        gotoxy(10, 11); cout << "3. выйти";
        char op = _getche();

        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') exit(0);

    } while (1);

    return 0;
}