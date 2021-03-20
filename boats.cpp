#include "headers/boats.h"

using namespace std;

void Boats::auto_place_ship(int ship_index) {
  vector<int> coordinates {0, 0};
  int boat_direction;
  // /* initialize random seed: */
  srand (time(NULL));

  bool valid_placement = false;

  while(valid_placement == false) {
    coordinates[0] = rand() % board_size; //x
    coordinates[1] = rand() % board_size; //y

    boat_direction = rand() % 2;
    
    // valid_placement = true;
    if(boat_direction == 0){ //horizontal
      for(int x=coordinates[0]; x<coordinates[0]+boats[ship_index].size; x++) {
        if (!valid_boat_placement({x, coordinates[1]})) {
          valid_placement = false;
          break;
        }
        else {
          valid_placement = true;
        }
      }
    }
    else {
      for(int y=coordinates[1]; y<coordinates[1]+boats[ship_index].size; y++) {
        if (!valid_boat_placement({coordinates[0], y})) {
          valid_placement = false;
          break;
        }
        else {
          valid_placement = true;
        }
      }
    }
  };
  // cout << coordinates[0] << " and " << coordinates[1] << " valid placement\n";
  
  if(boat_direction == 0){ //horizontal
      for(int x=coordinates[0]; x<coordinates[0]+boats[ship_index].size; x++) {
        board[x][coordinates[1]] = ship_index+1;
      }
    }
  else {
    for(int y=coordinates[1]; y<coordinates[1]+boats[ship_index].size; y++) {
      board[coordinates[0]][y] = ship_index+1;
    }
  }
  boats[ship_index].placed = true;
};

Boats::Boats() {}

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

bool Boats::valid_boat_placement(vector<int> _coordinate) {
  if (_coordinate[0] < board_size && _coordinate[1] < board_size) {
    if (board[_coordinate[0]][_coordinate[1]] == 0) {
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
      board[start_pos[0]][y] = ship_num;
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
      board[x][start_pos[1]] = ship_num;
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

int Boats::auto_place_all_ships() {
  for(int i=0; i<boats.size(); i++) {
    if (boats[i].placed) {
      return 1;
    }
    else {
      auto_place_ship(i);
    }
  }
  return 0;
};

int Boats::auto_place_remaining_ships() {
  bool ship_placed = false;
  for(int i=0; i<boats.size(); i++) {
    if (boats[i].placed == false) {
      auto_place_ship(i);
      ship_placed = true;
    }
  }
  if (ship_placed == false) {
    return 1;
  }
  return 0;
};

bool Boats::boat_sank(int boat) {
  if (boats[boat].hits == boats[boat].size) {
    boats[boat].sank = true;
    return true;
  }
  return false;
};

bool Boats::all_boats_sank() {
  for (int i=0; i < boats.size(); i++) {
    if (!boats[i].sank) {
      return false;
    }
  }
  return true;
};