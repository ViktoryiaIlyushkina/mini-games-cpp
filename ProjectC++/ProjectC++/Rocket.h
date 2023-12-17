#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <fstream>

#include "Useful.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ofstream;
using std::ifstream;

struct Player2 {
    string Name;
    int score;
    char lives[3];
};
Player2 GeneratePalyer2(Player2 RocketSpace) {
    RocketSpace.Name = EnterName(RocketSpace.Name);
    RocketSpace.score = 0;
    int lives_total = 3;

    for (int i = 0; i < lives_total; i++)
        RocketSpace.lives[i] = '+';

    return RocketSpace;
}
void ShowParameters(Player2 RocketSpace) {
    cout << endl << endl;
    cout << "Score: " << RocketSpace.score << endl;
    cout << "Lives: " << RocketSpace.lives[0] << ' ' << RocketSpace.lives[1] << ' ' << RocketSpace.lives[2] << endl;
}
int** Generate_spacemap(int** spacemap, int spacerows, int spacecolumns, int Rocket, int Rocket_stringid, int Rocket_columnid) { // создание маленькой карты
    for (int i = 0; i < spacerows; i++)
        spacemap[i] = new int[spacecolumns];

    for (int i = 0; i < spacerows; i++)
        for (int j = 0; j < spacecolumns; j++)
            spacemap[i][j] = 1;

    spacemap[Rocket_stringid][Rocket_columnid] = Rocket;

    return spacemap;
}
void Show_spacemap(int** spacemap, int spacerows, int spacecolumns) { // тестовое отображение маленькой карты
   

    cout << endl << endl;

    for (int i = 0; i < spacerows; i++) {
        cout << endl;
        for (int j = 0; j < spacecolumns; j++) 
            cout << spacemap[i][j] << ' ';
    }
}
string** Generate_SpaceMap(string** SpaceMap, int SpaceRows, int SpaceColumns) { // создание большой карты

    for (int i = 0; i < SpaceRows; i++)
        SpaceMap[i] = new string[SpaceColumns];

    for (int i = 0; i < SpaceRows; i++)
        for (int j = 0; j < SpaceColumns; j++) {
            SpaceMap[i][j] = ' ';
        }

    return SpaceMap;
}
char MoveRocket(char Move) {
    bool checkMove = 1;
    while (checkMove) {
        Move = _getch();

        if (Move == 'W' || Move == 'w' || Move == 'S' || Move == 's' || Move == 'D' || Move == 'd')
            checkMove = 0;
    }
    return Move;
}
void FindRocket(int**& spacemap, int spacerows, int& Rocket_stringid, int& Rocket_columnid) {

    int Rocketcolumn = 0;

    for (int i = 0; i < spacerows; i++){
            if (spacemap[i][Rocketcolumn] != 1) {
                Rocket_stringid = i;
                Rocket_columnid = Rocketcolumn;
            }
        }
}
void ClearRocketColumns(string**& SpaceMap, int** spacemap, int spacerows, int SpaceRows, int Rocket_columnid) {
    int SpaceColumns = 5;
    for (int i = 0; i < SpaceRows; i++)
        for (int j = 0; j < SpaceColumns; j++)
            SpaceMap[i][j] = ' ';

    for (int i = 0; i < spacerows; i++)
        for (int j = 0; j <= Rocket_columnid; j++) {
            int bigmap_i = 5 * i + 2;
            int bigmap_j = 5 * j + 2;
            if (spacemap[i][j] == 1)
                SpaceMap[bigmap_i][bigmap_j] = '*';
        }
}
string** UpdateRocket(string**& SpaceMap, int SpaceRows, int**& spacemap, int spacerows, int& Rocket_stringid, int& Rocket_columnid) {

    FindRocket(spacemap, spacerows, Rocket_stringid, Rocket_columnid);
    ClearRocketColumns(SpaceMap, spacemap, spacerows, SpaceRows, Rocket_columnid);

    int Symb_id = 0;
    int Rocket_num_id = 12;
    char RocketSymbols[25] = { '|', '\\', ' ',' ',' ','>', ' ','-', '\\',
        ' ','>',' ', ' ', ' ', '>', '>', ' ', '-', '/', ' ','|','/',' ',' ', ' '};

    int bigmap_stringid = 5 * Rocket_stringid + 2;
    int bigmap_columnid = 5 * Rocket_columnid + 2;
    RocketSymbols[Rocket_num_id] = spacemap[Rocket_stringid][Rocket_columnid] + '0';

    int draw_start_cell = -2;
    int draw_end_cell = 3;

    for (int i = draw_start_cell; i < draw_end_cell; i++) {
         cout << endl;
             for (int j = draw_start_cell; j < draw_end_cell; j++) {
                 SpaceMap[bigmap_stringid + i][bigmap_columnid + j] = RocketSymbols[Symb_id];
                 Symb_id++;
             }
    }
   return SpaceMap;
}
string** Update_SpaceMap(string** SpaceMap, int SpaceRows, int** spacemap, int spacerows, int spacecolumns, int& Rocket_stringid, int& Rocket_columnid) { // обновление большой карты 
 
    for (int i = 0; i < spacerows; i++)
        for (int j = 0; j < spacecolumns; j++) {
            int bigmap_stringid = 5 * i + 2;
            int bigmap_columnid = 5 * j + 2;
            HighlightCell_1(SpaceMap, bigmap_stringid, bigmap_columnid, ' ');
            if (spacemap[i][j] == 1)
                SpaceMap[bigmap_stringid][bigmap_columnid] = '*';
            else if (spacemap[i][j] != 1) {
                HighlightCell_1(SpaceMap, bigmap_stringid, bigmap_columnid, '~');
                    SpaceMap[bigmap_stringid][bigmap_columnid] = spacemap[i][j] / 10 + '0';
                    SpaceMap[bigmap_stringid][bigmap_columnid] += spacemap[i][j] % 10 + '0';
            }
        }

    UpdateRocket(SpaceMap, SpaceRows, spacemap, spacerows, Rocket_stringid, Rocket_columnid);

    return SpaceMap;
}
void Show_SpaceMap(string** SpaceMap, int SpaceRows, int SpaceColumns) {

    int InvisibleColumns_rangestart = 5;
    int InvisibleColumns_rangeend = 9;
    bool skip = 1;
    cout << "\x1B[2J\x1B[H";

    for (int i = 0; i < SpaceRows; i++) {
        cout << endl;
        for (int j = 0; j < SpaceColumns; j++) {
            if ((j < InvisibleColumns_rangestart) || (j > InvisibleColumns_rangeend)) {
                if (SpaceMap[i][j][0] != '0') {
                    cout << SpaceMap[i][j] << ' ';
                }
                else {
                    cout << SpaceMap[i][j][1] << ' ';
                }
            }
        }
    }
        cout << endl << endl;
}
int** Generate_Spacenumbers(int** spacemap, int spacerows, int spacecolumns, int& gap) { // появление чисел в космосе

    for (int i = 0; i < spacerows; i++) // новый появляющийся ряд чисел состоит из единиц
        spacemap[i][spacecolumns] = 1;

    if (gap == 2) { // каждый второй ряд вместо единицы - случайное двузначное число

        int starnum = 1 + rand() % (99 - 1 + 1);
        int starrow = rand() % 3;

        spacemap[starrow][spacecolumns] = starnum;

        gap = 0;
    }
    return spacemap;
}

int** Move_spacemap(int** spacemap, int spacerows, int spacecolumns, int& gap) { // сдвиг чисел в сторону ракеты

    spacemap = Generate_Spacenumbers(spacemap, spacerows, spacecolumns, gap);

    for (int i = 0; i < spacerows; i++)
        for (int j = 1; j < spacecolumns; j++)
            spacemap[i][j] = spacemap[i][j + 1];

    return spacemap;
}
void Minus_Life(Player2& RocketSpace) {

    for (int i = 2; i >= 0; i--)
        if (RocketSpace.lives[i] == '+') {
            RocketSpace.lives[i] = ' ';
            break;
        }
}
void Check_Divisibility(int Rocket, int number, Player2& RocketSpace) {

    if (number % Rocket == 0)
        RocketSpace.score += 1;
    else
        Minus_Life(RocketSpace);
}

void Check_Invisible_Column(int** spacemap, Player2& RocketSpace, int Rocket_stringid, int Rocket) {

    int Invisible_column = 1;

    if (spacemap[Rocket_stringid][Invisible_column] != 1)
        Check_Divisibility(Rocket, spacemap[Rocket_stringid][Invisible_column], RocketSpace);

}
bool CheckLives(Player2 RocketSpace, bool& playrocket) {

    if (RocketSpace.lives[0] == ' ') {
        playrocket = 0;
        cout << "\x1B[2J\x1B[H";
        cout << "\n\nGame over" << endl << endl;
    }
    return playrocket;
}
