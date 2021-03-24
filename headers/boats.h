#pragma once

#include <iostream>
#include <stdlib.h> //for setw
#include <iomanip> //for getw
#include <fstream> //read and write files
#include <vector> //vectors
#include <sstream> //string stream
#include <cctype> //for to upper
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "board.h"

using namespace std;

class Boats: public Board {
  private:
    void auto_place_ship(int ship_index);

  public:
    Boats();

    void print_boats();
    bool valid_boat_placement(vector<int> coordinate);
    int place_boat(vector<int> start_pos, char direction, string ship_name);
    bool all_ships_placed();
    
    int auto_place_all_ships();
    int auto_place_remaining_ships();
    bool boat_sank(int boat);
    bool all_boats_sank();
    int boats_remaining();
};

