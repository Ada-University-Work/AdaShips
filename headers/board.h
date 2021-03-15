#pragma once

#include <iostream>
#include <stdlib.h> //for setw
#include <iomanip> //for getw
#include <fstream> //read and write files
#include <vector> //vectors
#include <sstream> //string stream
#include <cctype> //for to upper

#include "helpers.h"

using namespace std;

class Board {
  private:
    void load_data();
    void initialise_board(int board[80][80]);
    void print_board(int board[80][80]);

  protected:
    int target_board[80][80];
    int ship_board[80][80];
    int board_size;

    struct boat {
      string name;
      int size;
      bool placed;
    };
    vector<boat> boats;

  public:
    Board();

    void print_ship_board();
    void print_target_board();

    vector<int> format_coordinate(string coordinates);
    void reset_board();
};
