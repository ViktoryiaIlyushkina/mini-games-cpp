#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>
#include "Useful.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Player {
    string Name;
    int score;
};

Player GeneratePalyer(Player Pyramid) {
    Pyramid.Name = EnterName(Pyramid.Name);
    Pyramid.score = 0;

    return Pyramid;
}

int** GeneratePyramid(int pyramid_complexity) {

    int levels_number = pyramid_complexity + 2;
    int columns_number = 2 * pyramid_complexity + 3;

    int** SmallMap = new int* [levels_number];

    for (int i = 0; i < levels_number; i++)
        SmallMap[i] = new int[columns_number];

    return SmallMap;
}
void ShowSmallMap(int** SmallMap, int levels_number, int columns_number) {//отображение маленькой карты(тестовое)
    for (int i = 0; i < levels_number; i++) {
        cout << endl;
        for (int j = 0; j < columns_number; j++)
            cout << SmallMap[i][j] << ' ';
    }
}
void ClearPyramid(int** SmallMap, int pyramid_complexity) {

    int levels_number = pyramid_complexity + 2;
    int columns_number = 2 * pyramid_complexity + 3;

    int decrease = 1 + pyramid_complexity;
    for (int i = 0; i < levels_number; i++) {// Заполнение элементов, которые являются частью пирамиды  значениями "0".
        for (int j = (0 + decrease); j < (columns_number - decrease); j++) {
            SmallMap[i][j] = 0;
        }
        decrease--;
    }

    for (int i = 0; i < levels_number; i++)
        for (int j = 0; j < columns_number; j++) // Заполнение остальных элементов значениями "9".
            if (SmallMap[i][j] != 0)
                SmallMap[i][j] = 9;
}

char** GenerateMap(int** SmallMap, int pyramid_complexity) {

    int levels_number = pyramid_complexity + 2;
    int columns_number = 2 * pyramid_complexity + 3;

    char** BigMap = new char* [(5 * levels_number)]; // Создание двумерного массива (Маленькая карта х5). 
    for (int i = 0; i < (5 * levels_number); i++)
        BigMap[i] = new char[(5 * columns_number)];

    for (int i = 0; i < (5 * levels_number); i++) // Карта невидима, пока не появится блок. 
        for (int j = 0; j < (5 * columns_number); j++)
            BigMap[i][j] = ' ';

    return BigMap;
}
void Fillblock(char**& BigMap, int x, int y) {
    char symb = 35 + rand() % (38 - 35 + 1);

    for (int i = (x - 2); i <= (x + 2); i++) {
        for (int j = (y - 2); j <= (y + 2); j++) {
            if (BigMap[i][j] == BigMap[x][y])
                continue;
            else
                BigMap[i][j] = symb;
        }
    }
    HighlightCell(BigMap, (x-1), (y-1), ' ');
}
void UpdateMap(char** BigMap, int** SmallMap, int pyramid_complexity, bool fill = 1) {
    // функция обновления большой карты

    int levels_number = pyramid_complexity + 2;
    int columns_number = 2 * pyramid_complexity + 3;

    for (int i = 0; i < levels_number; i++)
        for (int j = 0; j < columns_number; j++)
            if ((SmallMap[i][j] == 0) || (SmallMap[i][j] == 9)) {
                BigMap[5 * i + 2][5 * j + 2] = ' ';
            }
            else if ((SmallMap[i][j] > 0) && (SmallMap[i][j] < 9)) {
                BigMap[5 * i + 2][5 * j + 2] = SmallMap[i][j] + '0';
                if (fill == 1) // только после правильного решения сработает функция заполнения блока
                    Fillblock(BigMap, (5 * i + 2), (5 * j + 2));
            }
    if (fill == 0)
        for (int i = 0; i < (5 * levels_number); i++) {
            cout << endl;
            for (int j = 0; j < (5 * columns_number); j++)
                cout << BigMap[i][j] << ' ';
        }
}

void EmptyBlock(char**& BigMap, int x, int y) {

    for (int i = (x - 2); i <= (x + 2); i++) {
        for (int j = (y - 2); j <= (y + 2); j++) {
            if (BigMap[i][j] == BigMap[x][y])
                continue;
            else
                BigMap[i][j] = ' ';
        }
    }
}
void DestroyBlocks(int**& SmallMap, char**& BigMap, int string_index, int column_index, int levels_number, int columns_number) {
    for (int i = string_index; i < (levels_number - 1); i++) {
        if (SmallMap[i][column_index] == 0) {
            SmallMap[i + 1][column_index] = 0;
            EmptyBlock(BigMap, (5 * (i + 1) + 2), (5 * column_index + 2));
        }
    }
}

