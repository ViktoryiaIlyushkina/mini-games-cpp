#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <fstream>

#include "Useful.h"
#include "Examples Pyramid.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;


struct Player1 {
    string Name;
    int score;
    char lives [3];
    int key = 0;

};
Player1 GeneratePalyer1(Player1 Dungeon) {
    Dungeon.Name = EnterName(Dungeon.Name);
    Dungeon.score = 0;

    for (int i = 0; i < 3; i++)
    Dungeon.lives[i] = '+';

    Dungeon.key = 0;

    return Dungeon;
}
void ShowStatistics(Player1 Dungeon) {
    cout << endl << endl;
    cout << "Score: " << Dungeon.score << endl;
    cout << "Lives: " << Dungeon.lives[0] << ' ' << Dungeon.lives[1] << ' ' << Dungeon.lives[2] << endl;
    cout << "Key: " << Dungeon.key << endl << endl;
}
void Generate_SmallMap_Level(int** SmallDungeon) {

    SmallDungeon[1][3] = 1; // «аполнение эл-тов с примерами первой строки значени€ми "1"

    for (int i = 2; i < 5; i++)  // «аполнение эл-тов с примерами второй строки значени€ми "2"
        SmallDungeon[2][i] = 2;

    for (int i = 1; i < 6; i++) // «аполнение эл-тов с примерамии третьей строки значени€ми "3"
        SmallDungeon[3][i] = 3;

    for (int i = 2; i < 5; i++) {// «аполнение эл-тов с примерами четвертой строки значени€ми "4"
        if (i == 3) {
            i++;
        }
        SmallDungeon[4][i] = 4;
    }
    for (int i = 0; i < 7; i++) {// «аполнение эл-тов с примерами п€той строки значени€ми "5"
        if (i == 3) {
            i++;
        }
        SmallDungeon[5][i] = 5;
    }
    SmallDungeon[6][0] = 6; // «аполнение эл-тов с примерами шестой строки значени€ми "6"
    SmallDungeon[6][6] = 6;

    for (int i = 0; i < 7; i++) // «аполнение эл-тов с примерами седьмой строки значени€ми "7"
        SmallDungeon[7][i] = 7;

    SmallDungeon[8][3] = 8; // «аполнение эл-тов с примерами восьмой строки значени€ми "8"
}
void Generate_SmallMap_Random(int** SmallDungeon, int rows, int columns) {

    for (int i = 1; i < (rows - 1); i++) // «аполнение всех элементов значени€ми от "0" до "8"
        for (int j = 0; j < columns; j++)
            SmallDungeon[i][j] = i;

    int barrier;

    for (int i = 1; i < (rows - 1); i++) { // расставление до 3 барьеров на каждой строке
        barrier = rand() % 4;
        for (int j = 0; j < barrier; j++)
            if (j != 7) // на 7 строке не будет барьеров, чтобы не заблокировать выход
            SmallDungeon[i][rand() % 7] = 0;
    }
}
void ShowSmallDungeon(int** SmallDungeon, int rows, int columns) { // тестовое отображение маленькой карты

    for (int i = 0; i < rows; i++) {
        cout << endl;
        for (int j = 0; j < columns; j++)
            cout << SmallDungeon[i][j] << ' ';
    }
}

int** GenerateSmallDungeon(int** SmallDungeon, int rows, int columns, int level) {

    for (int i = 0; i < rows; i++) // «аполнение всех элементов значени€ми "0"
        for (int j = 0; j < columns; j++)
            SmallDungeon[i][j] = 0;

    if (level == 0) { 
        Generate_SmallMap_Level(SmallDungeon); // красива€ карта нарисована только дл€ 1 уровн€, остальные пока рандом
    }

    else { 
        Generate_SmallMap_Random(SmallDungeon, rows, columns); // рандом карты дл€ остальных уровней
    }

    return SmallDungeon;
}
void FindPlayer(int** SmallDungeon, int rows, int columns, int& string_index, int& column_index, int player_code) {

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (SmallDungeon[i][j] == player_code) {
                string_index = i;
                column_index = j;
            }

}
char Choose_Direction(char move) {
    bool checkmove = 1;
    while (checkmove) {
        move = _getch();

        if (move == 'W' || move == 'w' || move == 'S' || move == 's' || move == 'D' || move == 'd' || move == 'A' || move == 'a')
            checkmove = 0;
    }
    return move;
}
void Set_key(int** SmallDungeon, int rows, int columns, bool& nokey, 
    int& key_srtingid, int& key_columnid, int wall_code, int player_code) {

    while (nokey) { //рандом положени€ ключа
        key_srtingid = rand() % rows;
        key_columnid = rand() % columns;
        if (SmallDungeon[key_srtingid][key_columnid] > wall_code && SmallDungeon[key_srtingid][key_columnid] < player_code)
            nokey = 0;
    }
}

char** UpdateBigDungeon(char** BigDungeon, int** SmallDungeon, int rows, int columns, 
    int player_code, int plus_code, int minus_code, int monster_code, int exit_code) {

    for (int i = 0; i < (3 * rows); i++) // границы подземель€, барьеры, стены
        for (int j = 0; j < (3 * columns); j++)
            BigDungeon[i][j] = '.';

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            int bigmap_sringid = 3 * i + 1;
            int bigmap_columnid = 3 * j + 1;
            if (SmallDungeon[i][j] > 0 && SmallDungeon[i][j] < player_code) { // еще нерешенные примеры
                HighlightCell(BigDungeon, 3 * i, 3 * j, ' ');
                BigDungeon[bigmap_sringid][bigmap_columnid] = SmallDungeon[i][j]+ '0';
            }
            else if (SmallDungeon[i][j] == player_code) { // игрок
                HighlightCell(BigDungeon, 3 * i, 3 * j, '+');
                BigDungeon[bigmap_sringid][bigmap_columnid] = '@';
            }
            else if (SmallDungeon[i][j] == plus_code) { // правильно решенный пример
                HighlightCell(BigDungeon, 3 * i, 3 * j, ' ');
                BigDungeon[bigmap_sringid][bigmap_columnid] = '+';
            }
            else if (SmallDungeon[i][j] == minus_code) { // неправильно решенный пример
                HighlightCell(BigDungeon, 3 * i, 3 * j, ' ');
                BigDungeon[bigmap_sringid][bigmap_columnid] = '-';
            }
            else if (SmallDungeon[i][j] == monster_code) { // монстр
                HighlightCell(BigDungeon, 3 * i, 3 * j, '-');
                BigDungeon[bigmap_sringid][bigmap_columnid] = 'M';
            }
            else if (SmallDungeon[i][j] == exit_code) { // выход
                HighlightCell(BigDungeon, 3 * i, 3 * j, '#');
                BigDungeon[bigmap_sringid][bigmap_columnid] = 'E';
            }
        }
    return BigDungeon;
}

void ShowBigDungeon(char** BigDungeon, int rows, int columns) {

    cout << endl;

    for (int i = 0; i < (3 * rows); i++) {
        cout << endl;
        for (int j = 0; j < (3 * columns); j++)
            cout << BigDungeon[i][j] << ' ';
    }

    cout << endl << endl;
}
void ChooseMonsterDirection(int**& SmallDungeon, int columns, int player_stringid, int player_columnid, int monster_stringid, int monster_columnid, int& monster_ex_number) {

    // ћонстр идет вверх, если игрок выше монстра, вниз - если игрок ниже монстра
    if ((player_stringid < monster_stringid) && (SmallDungeon[monster_stringid - 1][monster_columnid] != 0))
        monster_ex_number = Up_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);
    else if ((player_stringid > monster_stringid) && (SmallDungeon[monster_stringid + 1][monster_columnid] != 0))
        monster_ex_number = Down_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);

    // Ќа остальных строках монстр идет влево, если находитс€ правее игрока, вправо - если находитс€ левее игрока
    else if ((player_columnid > monster_columnid) && (monster_columnid != columns - 1) &&
        (SmallDungeon[monster_stringid][monster_columnid + 1] != 0))
        monster_ex_number = Right_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);
    else if ((player_columnid < monster_columnid) && (monster_columnid != 0) &&
        (SmallDungeon[monster_stringid][monster_columnid - 1] != 0 != 0))
        monster_ex_number = Left_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);

    // ≈сли все вышеперечисленные варианты не подход€т из-за преп€тствий, то монстр идет туда, куда может
    else if ((monster_columnid != columns - 1) && (SmallDungeon[monster_stringid][monster_columnid + 1] != 0))
        monster_ex_number = Right_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);
    else if ((monster_columnid != 0) && (SmallDungeon[monster_stringid][monster_columnid - 1] != 0 != 0))
        monster_ex_number = Left_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);
    else if (SmallDungeon[monster_stringid - 1][monster_columnid] != 0)
        monster_ex_number = Up_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);
    else if (SmallDungeon[monster_stringid + 1][monster_columnid] != 0)
        monster_ex_number = Down_moving(SmallDungeon, monster_stringid, monster_columnid, 12, monster_ex_number);
}
void MinusLife(Player1& Dungeon, int lives) {

    for (int i = 2; i >= 0; i--)
        if (Dungeon.lives[i] == '+') {
            Dungeon.lives[i] = ' ';
            if (lives == 1)
                break;
        }
}

bool CheckLives(Player1 Dungeon, bool playdungeon, bool& exit) {

    if (Dungeon.lives[0] == ' ') {
        cout << "\x1B[2J\x1B[H";
        playdungeon = 0;
        exit = 0;
        cout << "\n\nGame over" << endl << endl;
    }
    return playdungeon;
}
void CheckExit(int** SmallDungeon, Player1 Dungeon, bool& playdungeon, int& level) {
    if ((SmallDungeon[8][3] == 9) && (Dungeon.key == 1)) {
        level++;
        playdungeon = 0;
    }
}

void MonsterExample(int** SmallDungeon, char** BigDungeon, int rows, int columns, int& monster_ex_number, int& ex_number, int* num, 
    int res, int user_res, bool& monster_existance, Player1& Dungeon, bool& playdungeon, bool& exit, 
    int player_code, int monster_code) {

    if ((monster_ex_number == player_code)||(ex_number == monster_code)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++) 
                if (SmallDungeon[i][j] == monster_code) 
                    SmallDungeon[i][j] = player_code;
 
     GenerateExample(num, res, 3);

     user_res = Enter_UserResult(user_res);

     if (user_res == res) {
         Dungeon.score += 10;
         ShowStatistics(Dungeon);
     }
     else{
         MinusLife(Dungeon, 3); 
         playdungeon = CheckLives(Dungeon, playdungeon, exit);
         exit = 0;
     }
     
     monster_existance = 0;
     if (ex_number == monster_code) 
         ex_number = monster_ex_number;
    }
}

int MoveMonster(char** BigDungeon, int** SmallDungeon, int rows, int columns, int monster_ex_number, int& ex_number, 
    int* num, int res, int user_res, bool& monster_existance, Player1& Dungeon, bool& playdungeon,
    int player_code, int plus_code, int minus_code, int monster_code, int exit_code, bool& exit) {
    
    int player_stringid, player_columnid, monster_stringid, monster_columnid;
    bool M = 0;
    bool P = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            if (SmallDungeon[i][j] == player_code) {
                player_stringid = i;
                player_columnid = j;
                P = 1;
            }
            if (SmallDungeon[i][j] == monster_code) {
                monster_stringid = i;
                monster_columnid = j;
                M = 1;  
            }
        }
if ((M == 1)&&(P == 1))
ChooseMonsterDirection(SmallDungeon, columns, player_stringid, player_columnid, monster_stringid, monster_columnid, monster_ex_number);

UpdateBigDungeon(BigDungeon, SmallDungeon, rows, columns, player_code, plus_code, minus_code, monster_code, exit_code);
ShowBigDungeon(BigDungeon, rows, columns);

MonsterExample(SmallDungeon, BigDungeon, rows, columns, monster_ex_number, ex_number, num, res, user_res,
    monster_existance, Dungeon, playdungeon, exit, player_code, monster_code);

return monster_ex_number;
}

void SearchKey(int** SmallDungeon, int rows, int columns, int key_srtingid, int key_columnid, int& key) {

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if ((SmallDungeon[i][j] == 9) && (key_srtingid == i) && (key_columnid == j)) {
                cout << "\nkey found" << endl;
                key = 1;
            }
}
void MovePlayer(int**& SmallDungeon, int string_index, int column_index, int mark, char move) {
    switch (move) {
    case 'W':
    case 'w':
        Up_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    case 'S':
    case 's':
        Down_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    case 'D':
    case 'd':
        Right_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    case 'A':
    case 'a':
        Left_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    }
}
void MovePlayer_ChangeExNumber(int**& SmallDungeon, int string_index, int column_index, int mark, char move, int& ex_number) {
    switch (move) {
    case 'W':
    case 'w':
        ex_number = Up_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    case 'S':
    case 's':
        ex_number = Down_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    case 'D':
    case 'd':
        ex_number = Right_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    case 'A':
    case 'a':
        ex_number = Left_moving(SmallDungeon, string_index, column_index, 9, mark);
        break;
    }
}

void PlayGame(int**& SmallDungeon, int rows, int columns, int x, int y, char**& BigDungeon, int& monster_ex_number,
    int& ex_number, int* num, int res, int user_res, bool& monster_existance, Player1& Dungeon, bool& playdungeon, int string_index,
    int column_index, int maxmin_columnindex, int& mark, int key_srtingid, int key_columnid, bool& repeat, char move, int level,
    int player_code, int plus_code, int minus_code, int monster_code, int exit_code, bool& exit) {


    if ((column_index != maxmin_columnindex) && (SmallDungeon[x][y] != 0)) {
        if (SmallDungeon[x][y] == plus_code || SmallDungeon[x][y] == minus_code) {
            ex_number = SmallDungeon[x][y];
            MovePlayer(SmallDungeon, string_index, column_index, mark, move);
            CheckExit(SmallDungeon, Dungeon, playdungeon, level);
            mark = ex_number;
        }
        else if (SmallDungeon[x][y] == exit_code) {
            ex_number = SmallDungeon[x][y];
            MovePlayer(SmallDungeon, string_index, column_index, mark, move);
            CheckExit(SmallDungeon, Dungeon, playdungeon, level);
            mark = ex_number;
        }
        else
            MovePlayer_ChangeExNumber(SmallDungeon, string_index, column_index, mark, move, ex_number);

        cout << "\x1B[2J\x1B[H";

        if (monster_existance == 0) {
            UpdateBigDungeon(BigDungeon, SmallDungeon, rows, columns, 
                player_code, plus_code, minus_code, monster_code, exit_code);
            ShowBigDungeon(BigDungeon, rows, columns);
        }

        if (Dungeon.key == 0)
            SearchKey(SmallDungeon, rows, columns, key_srtingid, key_columnid, Dungeon.key);
        repeat = 1;
    }
    else
        repeat = 0;
    if (monster_existance == 1) {
        monster_ex_number = MoveMonster(BigDungeon, SmallDungeon, rows, columns, monster_ex_number, ex_number,
            num, res, user_res, monster_existance, Dungeon, playdungeon,
            player_code, plus_code, minus_code, monster_code, exit_code, exit);
    }
}









