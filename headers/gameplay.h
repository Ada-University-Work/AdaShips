#include <iostream>
#include <vector> //vectors
#include <limits>
#include <sstream> //string stream

#include "board.h"
#include "boats.h"

void playerVcomputer(Boats &_player, Boats &_comp);
void playerVcomputer_salvo(Boats &_player, Boats &_comp);
void playerVcomputer_mines(Boats &_player, Boats &_comp);

void two_player_game(Boats &_player1, Boats &_player2);
void two_player_game_salvo(Boats &_player1, Boats &_player2);
void two_player_game_mines(Boats &_player1, Boats &_player2);

void computerVcomputer_mines(Boats &_comp1, Boats &_comp2);
