#include "headers/board.h"
using namespace std;

void Board::load_data() {
  string type, data, str_board_size, boat_name, boat_size;
  int counter = 0;

  ifstream game_config("adaship_config.ini"); //opening data file to read it

  while (getline(getline(game_config, type, ':'), data)){ //looping through each line of the file
    if (type == "Board") {
        stringstream ss(data);
        getline(ss, str_board_size, 'x');
        board_size = stoi(str_board_size);
        cout << "\nboard size = " << board_size << endl;
    }
    else if (type == "Boat") {
      stringstream ssb(data);
      boats.push_back(boat());

      while (getline(getline(ssb, boat_name, ','), boat_size)){
        boats[counter] = {lowercase_word(boat_name), stoi(boat_size), false};
        counter++;
      }
    }
  };
  game_config.close(); //closing the data file to save memory
};

void Board::initialise_board(int board[80][80]) {
  for (int y=0; y<board_size; y++) {
    for (int x=0; x<board_size; x++) {
      board[x][y] = 0;
    }     
  }
};

void Board::print_board(int board[80][80]) {
  const int empty    = 0;  // contains water
  const int occupied = -1;  // contains a ship
  const int miss     = -2;  // shot into ocean
  const int hit      = -3;  // shot and hit

  int counter = 0;

  for(int j = 0; j < board_size; j++) { //number coordinates
    cout << setw(4) << j+1;
  }
  cout << endl;

  for(char a = 0; a < board_size; a++) { //letter coordinates
    if (a>=26 && a<52){
      cout << 'A' << (char)((a-26)+'A');
    }
    else if (a>=52 && a<78) {
      cout << 'B' << (char)((a-52)+'A');
    }
    else if (a>=78) {
      cout << 'C' << (char)((a-78)+'A');
    }
    else {
      cout << " " << (char)(a +'A') ;
    }

    for(int i = 0; i < board_size ; i++) {

      if(board[i][counter] == occupied || board[i][counter] == empty) {
        cout << setw(4) << " |" ;
      }
      else if(board[i][counter] == miss ) {
        cout << setw(2) << "M" << setw(2) << "|";
      }
      else if(board[i][counter] == hit ) {
        cout << setw(2) << "H" << setw(2) << "|";;
      }
      else {
        char boat_initial = toupper(boats[board[i][counter]-1].name.at(0));
        cout << setw(2) << boat_initial << setw(2) << "|";
      }
    }
    cout << "\n";
    counter++;
  }
  cout << "\n";
};

Board::Board() {
  load_data();
  initialise_board(target_board);
  initialise_board(ship_board);
};

void Board::print_ship_board() {
  print_board(ship_board);
};

void Board::print_target_board() {
  print_board(target_board);
};

vector<int> Board::format_coordinate(string coordinates) {
  const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int x_value = 0, y_value = 0, y_start_pos;

  // find the position of the first alpha character in coordinates
  for (int i=0; i < coordinates.length(); i++) {
    if (isalpha(coordinates[i])) {
      y_start_pos = i;
      break;
    }
  }
  if (y_start_pos==0) throw 20;

  // calculate the x coordinate
  string x_coordinates;
  for (int x=0; x < y_start_pos; x++) {
    x_coordinates += coordinates[x];
  }
  x_value = stoi(x_coordinates)-1;

  // calculate the y coordinate
  int result = 0;
  for (int y=y_start_pos; y < coordinates.length(); y++){
    result = result * 26 + (alpha.find(toupper(coordinates[y]))) + 1;
  }
  y_value = result-1;

  cout << "x " << x_value << "  y " << y_value << endl;
  return {x_value, y_value};
};

void Board::reset_board() {
  initialise_board(ship_board);
  for(int i=0; i < boats.size(); i++) {
    boats[i].placed = false;
  };
};