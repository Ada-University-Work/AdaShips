#include "headers/setup.h"

using namespace std;

void place_a_ship(Boats &player) {
  string ship_entered, coordinate;
  vector<int> formatted_coordinate;
  int return_code;
  char ship_direction;

  cout << "\nYour ship board:\n";
  player.print_ship_board();

  cout << "Your ships:\n";
  player.print_boats();

  cout << "\nEnter ship name: ";
  getline(cin, ship_entered);

  cout << "Enter where you want the ship to start (e.g. F7): ";
  getline(cin, coordinate);

  formatted_coordinate = player.format_coordinate(coordinate);

  cout << "Is the ship vertical(V) or horizontal(H): ";
  ship_direction = cin.get();

  return_code = player.place_boat(formatted_coordinate, ship_direction, lowercase_word(ship_entered));
  
  if (return_code == 0){
    cout << "\nThe " << ship_entered << " ship is placed!\n";
    player.print_ship_board();
  }
  else {
    cout << "\nInvalid config, ship has not been placed.\nPlease try again\n";
  }

  if (player.all_ships_placed()) {
    cout << "\nall ships placed\n";
  };
}

void place_remaining_ships(Boats &player){
  int return_code;
  return_code = player.auto_place_remaining_ships();
  if (return_code == 0) {
    cout << "\nAll remaining ships are placed!\n";
    player.print_ship_board();
  }
  else {
    cout << "\nERROR: All ships have already been placed.\nPlease reset the board first.\n";
  }
}

void place_all_ships(Boats &player){
  int return_code;
  return_code = player.auto_place_all_ships();

  if (return_code == 0) {
    cout << "\nAll ships are placed!\n";
    player.print_ship_board();
  }
  else {
    cout << "\nERROR: Ships have already been placed!\nPlease reset the board first or choose 'Auto-place remaining ships'\n";
  }
}

void reset_board(Boats &player){
  char reset_confirm;
  cout << "\nAre you sure you want to reset the whole board?(Y/N)\n";

  if( ! (cin >> reset_confirm)) { //catching erroneous input
    cout << "Invalid input\n";
    cin.clear(); //clearing the error from cin stream
    cin.ignore(10000, '\n');
  }
  cin.ignore();

  if (tolower(reset_confirm) == 'y') {
    player.reset_board();
    cout << "Board reset\n";
  }
}

void set_up_comp(Boats &_comp) {
  _comp.auto_place_all_ships();
}

int set_up_player(Boats &_player) {
  int menu_choice = -1;

  while (menu_choice != 0) {

    cout << "\nFirst you need to set up your board.\n";
    cout << "1. Place a ship\n2. Auto-place remaining ships\n3. Auto-place all ships\n4. Reset board\n5. Continue to game\nPlease select an option (or 0 to quit): ";
  
    if( ! (cin >> menu_choice)) { //catching erroneous input
      cout << "Invalid input\n";
      cin.clear(); //clearing the error from cin stream
      cin.ignore(10000, '\n');
      menu_choice = -1;
      continue; //continuing to the next iteration of the loop
    }
    cin.ignore();

    switch (menu_choice) {
      case 1:
        place_a_ship(_player);
        break;

      case 2:
        place_remaining_ships(_player);
        break;

      case 3:
        place_all_ships(_player);
        break;
      
      case 4:
        reset_board(_player);
        break;
      case 5:
        if (_player.all_ships_placed()) {
          cout << "\nContinuing to game...\n";
          return 0;
        }
        else {
          cout << "\nPlease place all ships before continuing\n";
          break;
        }
      default:
        cout << "\nInvalid Input, try again...\n";
        break;
    }
  }
  return 1;
}