#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <fstream>

#include "Pyramid.h"
#include "Dungeon.h"
#include "Examples Pyramid.h"
#include "Useful.h"
#include "Examples Dungeon.h"
#include "Rocket.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ofstream;
using std::ifstream;


int main() {
    srand(time(nullptr));

    int rank_places = 10;
    bool insert = 1;

    player current;

    bool menu = 1;

    while (menu) {

        if (menu != 0) {

            cout << "\tChoose Game: " << endl;
            cout << "1. Smart Architect." << endl;
            cout << "2. Mysterious Dungeon. " << endl;
            cout << "3. Space Rocket." << endl;
            cout << "4. Exit." << endl << endl;

            int Choose_game = 0;
           
            Choose_game = UserChoose_range(Choose_game,1, 4);

            if (Choose_game == 1) {

                // Мини-игра "Архитектор"

                Player Pyramid;
                Pyramid = GeneratePalyer(Pyramid);
                bool play = 1;

                while (play) {

                    int pyramid_complexity = 0;
                    cout << "\n\nChoose complexity level (1 - easy, 2 - middle, 3 - hard): ";
                    pyramid_complexity = UserChoose_range(pyramid_complexity, 1, 3);

                    int** SmallMap = GeneratePyramid(pyramid_complexity);
                    ClearPyramid(SmallMap, pyramid_complexity);
                    char** BigMap = GenerateMap(SmallMap, pyramid_complexity);

                    int levels_number = pyramid_complexity + 2;
                    int columns_number = 2 * pyramid_complexity + 3;


                    int lv = 0; // переменная, которая показывает уровень пирамиды, на котором находится блок
                    bool destroy = 0; // переменная для перезапуска цикла в случае ошибки
                    int* num = new int[5]; // массив для хранения чисел для примера.
                    int result, user_result;

                    for (int i = (levels_number - 1); i >= 0; i--) {// построение блоков.
                        for (int j = 0 + lv; j < columns_number - lv; j++) {

                            if (SmallMap[i][j] == 0) {
                                SmallMap[i][j] = lv + 1;
                                UpdateMap(BigMap, SmallMap, pyramid_complexity, 0);
                                cout << endl << endl;

                                GenerateExample(num, result, lv);
                                user_result = Enter_UserResult(user_result);
                                destroy = 0;

                                if (user_result == result) {
                                    cout << "\x1B[2J\x1B[H";
                                    UpdateMap(BigMap, SmallMap, pyramid_complexity);
                                    Pyramid.score += 1;
                                    cout << "\n\n" << "Your score: " << Pyramid.score << endl << endl;
                                }
                                else {
                                    cout << "Error" << endl;
                                    cout << "\x1B[2J\x1B[H";

                                    SmallMap[i][j] = 0;
                                    DestroyBlocks(SmallMap, BigMap, i, j, levels_number, columns_number);
                                    UpdateMap(BigMap, SmallMap, pyramid_complexity, 1);
                                    cout << endl << endl;

                                    destroy = 1;
                                    Pyramid.score -= ((lv + 1) * 2);

                                    cout << "\n\n" << "Your score: " << Pyramid.score << endl << endl;
                                    break;
                                }
                            }
                        }
                        if (destroy == 0)
                            lv++;
                        else {
                            i = levels_number;
                            lv = 0;
                        }
                    } 
                    UserChoose_continue(play);
                }

                current.Name = Pyramid.Name;
                current.score = Pyramid.score;

                ifstream in1("Pyramid_Wall_of_glory"); //создание оператора чтения сохраненного рейтинга из файла
                player* Pyramid_rank = new player[rank_places]; // создание массива объектов для занесения в него сохраненного рейтинга
                Get_Rank(Pyramid_rank, rank_places, in1); // занесение в массив сохраненного рейтинга

                player* Pyramid_rank_New = new player[10]; // создание массива объектов для занесения в него обновленного рейтинга
                // в массив обновленного рейтинга заносится старый рейтинг и текущий игрок

                Update_Rank(Pyramid_rank, Pyramid_rank_New, current, rank_places, insert);
                Show_Rank(Pyramid_rank_New, rank_places);

                ofstream out1("Pyramid_Wall_of_glory"); // cоздание оператора для вывода обновленного рейтинга в файл
                Save_Rank(Pyramid_rank_New, rank_places, out1);
            }

            else if (Choose_game == 2) {
                // Мини-игра "Подземелье"

                Player1 Dungeon;
                Dungeon = GeneratePalyer1(Dungeon);
                bool exit = 1;
                int level = 0;

                while (exit) {
                    if (exit == 1) {
                        bool playdungeon = 1;

                        int rows = 10;  int columns = 7; // маленькая карта
                        int** SmallDungeon = new int* [rows];
                        for (int i = 0; i < rows; i++)
                            SmallDungeon[i] = new int[columns];

                        SmallDungeon = GenerateSmallDungeon(SmallDungeon, rows, columns, level);

                        char** BigDungeon = new char* [(3 * rows)]; // большая карта
                        for (int i = 0; i < (3 * rows); i++)
                            BigDungeon[i] = new char[(3 * columns)];

                        // кодирование игрока, монстра, выхода, стены, плюса и минуса на маленькой карте
                        int player_code = 9;
                        int plus_code = 10;
                        int minus_code = 11;
                        int monster_code = 12;
                        int exit_code = 13;
                        int wall_code = 0;

                        int ex_number = 1;
                        SmallDungeon[1][3] = player_code; // стартовое положение игрока всегда середина первой строки

                        int* num1 = new int[5];

                        SmallDungeon[8][3] = 12; // стартовое положение монстра всегда середина восьмой строки
                        int monster_ex_number = exit_code; // выход всегда, где стартует монстр
                        bool monster_existance = 1;

                        bool nokey = 1;
                        int key_srtingid, key_columnid; // положение ключа
                        Set_key(SmallDungeon, rows, columns, nokey, key_srtingid, key_columnid, wall_code, player_code);

                        BigDungeon = UpdateBigDungeon(BigDungeon, SmallDungeon, rows, columns,
                            player_code, plus_code, minus_code, monster_code, exit_code);
                        ShowBigDungeon(BigDungeon, rows, columns);

                        int* numbers = new int[9]; // массив для хранения чисел для примера.
                        int res, user_res;
                        int mark;
                        bool repeat = 1; // переменная позволяет генерацию примера, но только если игрок стал на клетку с числом 

                        while (playdungeon) {
                            
                            CheckExit(SmallDungeon, Dungeon, playdungeon, level);

                            if (playdungeon == 1) {

                                int string_index, column_index; // текущее положение игрока
                                FindPlayer(SmallDungeon, rows, columns, string_index, column_index, player_code);

                                if ((ex_number <= 6) && (repeat == 1)) // генерация примера, если игрок стал на клетку с цифрой
                                    Generate_Example_Lv_1to6(numbers, res, ex_number);
                                else if (repeat == 1)
                                    Generate_Example_Lv_7to8(numbers, res, ex_number);

                                if ((ex_number < player_code) && (repeat == 1)) {
                                    user_res = Enter_UserResult(user_res); // ввод ответа игроком

                                    // проверка ответа
                                    if (user_res == res) {
                                        mark = plus_code;
                                        Dungeon.score += ex_number;
                                        ShowStatistics(Dungeon);
                                        CheckExit(SmallDungeon, Dungeon, playdungeon, level);
                                    }
                                    else {
                                        mark = minus_code;
                                        MinusLife(Dungeon, 1);
                                        ShowStatistics(Dungeon);
                                        playdungeon = CheckLives(Dungeon, playdungeon, exit);
                                        CheckExit(SmallDungeon, Dungeon, playdungeon, level);
                                    }
                                }
                                cout << endl;

                                if (exit == 0) 
                                    break;
                             
                                char move = 'q';
                                move = Choose_Direction(move);
                                cout << endl << endl;

                                switch (move) {
                                case 'W':
                                case 'w':
                                    PlayGame(SmallDungeon, rows, columns, (string_index - 1), (column_index), BigDungeon,
                                        monster_ex_number, ex_number, num1, res, user_res, monster_existance, Dungeon, playdungeon,
                                        string_index, column_index, 100, mark, key_srtingid, key_columnid, repeat, move, level,
                                        player_code, plus_code, minus_code, monster_code, exit_code, exit);
                                    break;

                                case 'S':
                                case 's':
                                    PlayGame(SmallDungeon, rows, columns, (string_index + 1), column_index, BigDungeon,
                                        monster_ex_number, ex_number, num1, res, user_res, monster_existance, Dungeon, playdungeon,
                                        string_index, column_index, 100, mark, key_srtingid, key_columnid, repeat, move, level,
                                        player_code, plus_code, minus_code, monster_code, exit_code, exit);
                                    break;

                                case 'D':
                                case 'd':
                                    PlayGame(SmallDungeon, rows, columns, string_index, (column_index + 1), BigDungeon,
                                        monster_ex_number, ex_number, num1, res, user_res, monster_existance, Dungeon, playdungeon,
                                        string_index, column_index, (columns - 1), mark, key_srtingid, key_columnid, repeat, move, level,
                                        player_code, plus_code, minus_code, monster_code, exit_code, exit);
                                    break;

                                case 'A':
                                case 'a':
                                    PlayGame(SmallDungeon, rows, columns, string_index, (column_index - 1), BigDungeon,
                                        monster_ex_number, ex_number, num1, res, user_res, monster_existance, Dungeon, playdungeon,
                                        string_index, column_index, 0, mark, key_srtingid, key_columnid, repeat, move, level,
                                        player_code, plus_code, minus_code, monster_code, exit_code, exit);
                                    break;
                                }
                            }
                        }
                        if (Dungeon.lives[0] == '+') {
                            cout << "\nCongratulations! You made it!" << endl;
                            UserChoose_continue(exit);
                            level++;

                            if (exit == 1) {
                                Set_key(SmallDungeon, rows, columns, nokey, key_srtingid, key_columnid, wall_code, player_code);
                                Dungeon.key = 0;
                            }
                        }
                    }
                }
                current.Name = Dungeon.Name;
                current.score = Dungeon.score;

                ifstream in2("Dungeon_Wall_of_glory"); //создание оператора чтения сохраненного рейтинга из файла
                player* Dungeon_rank = new player[rank_places]; // создание массива объектов для занесения в него сохраненного рейтинга
                Get_Rank(Dungeon_rank, rank_places, in2); // занесение в массив сохраненного рейтинга

                player* Dungeon_rank_New = new player[10]; // создание массива объектов для занесения в него обновленного рейтинга
                // в массив обновленного рейтинга заносится старый рейтинг и текущий игрок

                Update_Rank(Dungeon_rank, Dungeon_rank_New, current, rank_places, insert);
                Show_Rank(Dungeon_rank_New, rank_places);

                ofstream out2("Dungeon_Wall_of_glory"); // cоздание оператора для вывода обновленного рейтинга в файл
                Save_Rank(Dungeon_rank_New, rank_places, out2);

            }

            else if (Choose_game == 3) {
                // Мини-игра "Ракета"

                Player2 RocketSpace;
                RocketSpace = GeneratePalyer2(RocketSpace);

                int Rocket_num[6] = { 2,3,4,5,6,9 }; // массив для выбора числа на ракете

                int Rocket = Rocket_num[rand() % 6]; // ракета
                int Rocket_stringid = 1;
                int Rocket_columnid = 0;

                int spacerows = 3;
                int spacecolumns = 12;

                int** spacemap = new int* [spacerows]; // создание маленькой карты
                spacemap = Generate_spacemap(spacemap, spacerows, spacecolumns, Rocket, Rocket_stringid, Rocket_columnid);

                int SpaceRows = 5 * spacerows;
                int SpaceColumns = 5 * spacecolumns;


                string** SpaceMap = new string * [SpaceRows]; // создание большой карты
                Generate_SpaceMap(SpaceMap, SpaceRows, SpaceColumns);
                SpaceMap = Update_SpaceMap(SpaceMap, SpaceRows, spacemap, spacerows, spacecolumns, Rocket_stringid, Rocket_columnid);

                int gap = 0;
                bool playrocket = 1;
                char Move = 'q';

                do {

                    spacemap = Move_spacemap(spacemap, spacerows, spacecolumns, gap);
                    /* Show_spacemap(spacemap, spacerows, spacecolumns);*/ // тестовое 
                    SpaceMap = Update_SpaceMap(SpaceMap, SpaceRows, spacemap, spacerows, spacecolumns, Rocket_stringid, Rocket_columnid);
                    Show_SpaceMap(SpaceMap, SpaceRows, SpaceColumns);
                    gap++;

                    Check_Invisible_Column(spacemap, RocketSpace, Rocket_stringid, Rocket);
                    ShowParameters(RocketSpace);
                    playrocket = CheckLives(RocketSpace, playrocket);

                    if (playrocket == 1) {

                        Move = MoveRocket(Move);

                        switch (Move) {
                        case 'W':
                        case 'w':
                            if (Rocket_stringid > 0 && Rocket_stringid < spacerows) {
                                Up_moving(spacemap, Rocket_stringid, Rocket_columnid, Rocket, 1);
                                SpaceMap = Update_SpaceMap(SpaceMap, SpaceRows, spacemap, spacerows, spacecolumns, Rocket_stringid, Rocket_columnid);
                            }
                            else continue;
                            break;
                        case 'S':
                        case 's':
                            if (Rocket_stringid >= 0 && Rocket_stringid < (spacerows - 1)) {
                                Down_moving(spacemap, Rocket_stringid, Rocket_columnid, Rocket, 1);
                                SpaceMap = Update_SpaceMap(SpaceMap, SpaceRows, spacemap, spacerows, spacecolumns, Rocket_stringid, Rocket_columnid);
                            }
                            else continue;
                            break;
                        }
                    }
                } while (playrocket);

                cout << endl << endl;

                current.Name = RocketSpace.Name;
                current.score = RocketSpace.score;

                ifstream in3("Rocket_Wall_of_glory"); //создание оператора чтения сохраненного рейтинга из файла
                player* Rocket_rank = new player[rank_places]; // создание массива объектов для занесения в него сохраненного рейтинга
                Get_Rank(Rocket_rank, rank_places, in3); // занесение в массив сохраненного рейтинга

                player* Rocket_rank_New = new player[10]; // создание массива объектов для занесения в него обновленного рейтинга
                // в массив обновленного рейтинга заносится старый рейтинг и текущий игрок

                Update_Rank(Rocket_rank, Rocket_rank_New, current, rank_places, insert);
                Show_Rank(Rocket_rank_New, rank_places);

                ofstream out3("Rocket_Wall_of_glory"); // cоздание оператора для вывода обновленного рейтинга в файл
                Save_Rank(Rocket_rank_New, rank_places, out3);
            }

            else if (Choose_game == 4) {
                menu = 0;
            }
        }
    }
    return 0;
}