  
#pragma once

#include <iostream>
#include <stdlib.h> //for setw
#include <iomanip> //for getw
#include <fstream> //read and write files
#include <vector> //vectors
#include <sstream> //string stream
#include <cctype> //for to upper

#include "board.h"
#include "boats.h"
#include "helpers.h"

int set_up_player(Boats &_player, string name);
void set_up_comp(Boats &_comp);
void place_a_ship(Boats &player);
void place_remaining_ships(Boats &player);
void place_all_ships(Boats &player);
void reset_board(Boats &player);