#include "headers/board.h"
#include "headers/boats.h"

using namespace std;

Boats::Boats() {
  cout << "initialised boats\n";
}

void Boats::print_boats() {
  for (int i=0; i<boats.size(); i++) {
    if (boats[i].placed == true) {
      cout << boats[i].name << setw(20-boats[i].name.length()) << ": ✓" << endl;  
    }
    else {
      cout << boats[i].name << setw(20-boats[i].name.length()) << ": X" << endl;
    }
  }
}

bool Boats::valid_boat_placement(vector<int> coordinate) {
  if (coordinate[0] < board_size && coordinate[1] < board_size) {
    if (ship_board[coordinate[0]][coordinate[1]] == 0) {
      return true;
    }
  }
  return false;
}

int Boats::place_boat(vector<int> start_pos, char direction, string ship_name) {
  int ship_length=0, ship_num;

  for (int i=0; i < boats.size(); i++) {
    if (boats[i].name == ship_name) { //validate ship name in menu
      ship_length = boats[i].size;
      ship_num = i+1;
      break;
    } 
  }
  if (boats[ship_num-1].placed == true) {
    cout << "\nShip has already been placed\n";
    return 1;
  }
  if (ship_length==0) {
    cout << "\nInvalid ship name\n";
    return 1;
  }

  if (toupper(direction) == 'V') { 
    for (int y=start_pos[1]; y < start_pos[1]+ship_length; y++ ) {
      if (!valid_boat_placement({start_pos[0], y})) {
        cout << "\nShip cannot be placed at those coordinates\n";
        return 1;
      }
    }
    for (int y=start_pos[1]; y < start_pos[1]+ship_length; y++ ) {
      ship_board[start_pos[0]][y] = ship_num;
      boats[ship_num-1].placed = true;
    }
  }
  else if (toupper(direction) == 'H') { 
    for (int x=start_pos[0]; x < start_pos[0]+ship_length; x++ ) {
      if (!valid_boat_placement({x, start_pos[1]})) {
        cout << "\nShip cannot be placed at those coordinates\n";
        return 1;
      }
    }
    for (int x=start_pos[0]; x < start_pos[0]+ship_length; x++ ) {
      ship_board[x][start_pos[1]] = ship_num;
      boats[ship_num-1].placed = true;
    }
  }
  return 0;
};

bool Boats::all_ships_placed() {
  for (int i=0; i<boats.size(); i++) {
    if(!boats[i].placed) {
      return false;
    }
  }
  return true;
};

void Boats::auto_place_ship(int ship_index) {
  // vector<int> coordinates;
  // /* initialize random seed: */
  // srand (time(NULL));

  // coordinates[0] = rand() % board_size; //x
  // coordinates[1] = rand() % board_size; //y

  // int boat_direction = rand() % 2;
  // if(boat_direction == 0){ //horizontal
  //   for(int a=coordinates[0]; a<boats[ship_index].size; a++) {

  //   }
  // }
};

void Boats::auto_place_all_ships() {
  auto_place_ship(0);
};
