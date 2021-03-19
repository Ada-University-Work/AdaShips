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
        boats[counter] = {lowercase_word(boat_name), stoi(boat_size), false, 0, false};
        counter++;
      }
    }
  };
  game_config.close(); //closing the data file to save memory
};

void Board::initialise_board() {
  for (int y=0; y<board_size; y++) {
    for (int x=0; x<board_size; x++) {
      board[x][y] = 0;
    }     
  }
};

Board::Board() {
  load_data();
  initialise_board();
};

void Board::print_ship_board() {
  int empty = 0;  // contains water
  int counter = 0;
  char boat_initial;
  string boat_name;

  for(int a = 0; a < board_size; a++) { //number coordinates
    if (a>=26 && a<52){
      cout << setw(3) << 'A' << (char)((a-26)+'A');
    }
    else if (a>=52 && a<78) {
      cout << setw(3) << 'B' << (char)((a-52)+'A');
    }
    else if (a>=78) {
      cout << setw(3) << 'C' << (char)((a-78)+'A');
    }
    else {
      cout << setw(3) << " " << (char)(a +'A') ;
    }
  }
  cout << endl;

  for(int j = 0; j < board_size; j++) { //letter coordinates
    if(j >= 9){
      cout << j+1;
    }
    else {
      cout << " " << j+1;
    }

    for(int i = 0; i < board_size ; i++) {
      // cout << "in loop\n";

      if(board[i][counter] == empty) {
        cout << setw(4) << " |" ;
      }
      else {
        boat_name = boats[(board[i][counter])-1].name;
        boat_initial = toupper(boat_name[0]);

        cout << setw(2) << boat_initial << setw(2) << "|";
      }
    }
    cout << "\n";
    counter++;
  }
  cout << "\n";
};

void Board::print_target_board() {
  const int empty    = 0;  // contains water
  const int miss     = -1;  // shot into ocean
  const int hit      = -2;  // shot and hit

  int counter = 0;

  for(int a = 0; a < board_size; a++) { //number coordinates
    if (a>=26 && a<52){
      cout << setw(3) << 'A' << (char)((a-26)+'A');
    }
    else if (a>=52 && a<78) {
      cout << setw(3) << 'B' << (char)((a-52)+'A');
    }
    else if (a>=78) {
      cout << setw(3) << 'C' << (char)((a-78)+'A');
    }
    else {
      cout << setw(3) << " " << (char)(a +'A') ;
    }
  }
  cout << endl;

  for(int j = 0; j < board_size; j++) { //letter coordinates
    if(j >= 9){
      cout << j+1;
    }
    else {
      cout << " " << j+1;
    }

    for(int i = 0; i < board_size ; i++) {

      if(board[i][counter] == miss ) {
        cout << setw(2) << "M" << setw(2) << "|";
      }
      else if(board[i][counter] == hit ) {
        cout << setw(2) << "H" << setw(2) << "|";;
      }
      else {
        cout << setw(4) << " |";
      }
    }
    cout << "\n";
    counter++;
  }
  cout << "\n";
};

vector<int> Board::format_coordinate(string coordinates) {
  const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int x_value = 0, y_value = 0, y_start_pos;

  // find the position of the first alpha character in coordinates
  for (int i=0; i < coordinates.length(); i++) {
    if (isdigit(coordinates[i])) {
      y_start_pos = i;
      break;
    }
  }
  if (y_start_pos==0) throw 20;

  // calculate the x coordinate
  int x_coordinates = 0;
  for (int x=0; x < y_start_pos; x++) {
    x_coordinates = x_coordinates * 26 + (alpha.find(toupper(coordinates[x]))) + 1;
  }
  x_value = x_coordinates-1;

  // calculate the y coordinate
  string y_coordinates;
  for (int y=y_start_pos; y < coordinates.length(); y++){
    y_coordinates += coordinates[y];
  }
  y_value = stoi(y_coordinates)-1;

  cout << "x " << x_value << "  y " << y_value << endl;
  return {x_value, y_value};
};

void Board::reset_board() {
  initialise_board();
  for(int i=0; i < boats.size(); i++) {
    boats[i].placed = false;
  };
};

bool Board::valid_coordinate(vector<int> coordinate) {
  if(coordinate[0] < board_size && coordinate[1] < board_size) {
    return true;
  }
  else {
    return false;
  }
};

int Board::fire(vector<int> coordinate) {
  int boat_num = board[coordinate[0]][coordinate[1]];

  if (board[coordinate[0]][coordinate[1]] == 0) {
    cout << "\nMISS\n";
    board[coordinate[0]][coordinate[1]] = -1;
    return false;
  }
  else if (board[coordinate[0]][coordinate[1]] < 0) {
    cout << "\nYou have already fired there\n";
    return false;
  }
  else if (board[coordinate[0]][coordinate[1]] > 0) {
    cout <<"\nHIT\n";
    board[coordinate[0]][coordinate[1]] = -2;
    boats[boat_num-1].hits ++;
    return boat_num-1;
  }
  return -1;
};

bool Board::is_valid_target(vector<int> _coordinate) {
  if (_coordinate[0] < board_size && _coordinate[1] < board_size) { //if position within board
    if (board[_coordinate[0]][_coordinate[1]] >= 0) { //if position hasn't already been hit
      return true;
    }
  }
  return false;
}

int Board::auto_fire() {
  vector<int> coordinates {0, 0};
  bool valid_target = false;

  srand (time(NULL));

  while(valid_target == false) {
    coordinates[0] = rand() % board_size; //x
    coordinates[1] = rand() % board_size; //y

    if(is_valid_target(coordinates)) {
      return fire(coordinates);
    }
    else {
      continue;
    }
  }
  return 0;
};
