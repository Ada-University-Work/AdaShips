#include "headers/playerVcomputer.h"

using namespace std;

void player_turn(Boats &_player, Boats &_comp) {
  bool valid_coordinate = false;
  string coordinate_str;
  vector<int> coordinate;

  cout << "\nYour ship board:\n";
  _player.print_ship_board();

  cout << "\nYour target board:\n";
  _comp.print_target_board();

  while (valid_coordinate == false) {
    cout << "\n\nEnter a coordinate to fire at: ";
    getline(cin, coordinate_str);
    coordinate = _comp.format_coordinate(coordinate_str);

    valid_coordinate = _comp.valid_coordinate(coordinate);
    if (valid_coordinate == false) {
      cout << "\nInvalid coordinate\n";
    }
  }
  
  cout << "\nfire!\n";
}

void playerVcomputer(Boats &_player, Boats &_comp) {
  cout << "game play\n";
  player_turn(_player, _comp);
}

