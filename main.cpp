#include "headers/main.h"
#include "headers/board.h"
#include "headers/boats.h"

using namespace std;

int set_up(Boats _player) {
  int menu_choice = -1;

  while (menu_choice != 0) {
    string ship_entered, coordinate;
    char reset_confirm;
    char ship_direction;
    vector<int> formatted_coordinate;
    int return_code;

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
        cout << "\nYour ship board:\n";
        _player.print_ship_board();

        cout << "Your ships:\n";
        _player.print_boats();

        cout << "\nEnter ship name: ";
        getline(cin, ship_entered);

        cout << "Enter where you want the ship to start (e.g. F7): ";
        getline(cin, coordinate);

        formatted_coordinate = _player.format_coordinate(coordinate);

        cout << "Is the ship vertical(V) or horizontal(H): ";
        ship_direction = cin.get();

        return_code = _player.place_boat(formatted_coordinate, ship_direction, ship_entered);
        
        if (return_code == 0){
          cout << "\nThe " << ship_entered << " ship is placed!\n";
          _player.print_ship_board();
        }
        else {
          cout << "\nInvalid config, ship has not been placed.\nPlease try again\n";
        }

        if (_player.all_ships_placed()) {
          cout << "\nall ships placed\n";
        };
        break;

      case 2:
        break;

      case 3:
        return_code =_player.auto_place_all_ships();
        if (return_code == 0) {
          cout << "\nAll ships are placed!\n";
          _player.print_ship_board();
          break;
        }
        else {
          cout << "\nERROR: Ships have already been placed!\nPlease reset the board first or choose 'Auto-place remaining ships'\n";
          break;
        }
      
      case 4:
        cout << "\nAre you sure you want to reset the whole board?(Y/N)\n";

        if( ! (cin >> reset_confirm)) { //catching erroneous input
          cout << "Invalid input\n";
          cin.clear(); //clearing the error from cin stream
          cin.ignore(10000, '\n');
          continue; //continuing to the next iteration of the loop
        }
        cin.ignore();

        if (tolower(reset_confirm) == 'y') {
          _player.reset_board();
          cout << "Board reset\n";
        }
        break;
    }
  }
  return 0;
}

int main() {
  int menu_choice = -1;
  cout << "Welcome to Adaships!" << endl;

  while (menu_choice != 0) {
    cout << "1. One player V computer game\n\nPlease select an option (or 0 to quit): ";
    if( ! (cin >> menu_choice)) { //catching erroneous input
      cout << "Invalid input\n";
      cin.clear(); //clearing the error from cin stream
      cin.ignore(10000, '\n');
      menu_choice = -1;
      continue; //continuing to the next iteration of the loop
    }
    if (menu_choice == 0) {
      break;
    }
    Boats player;
    //player.auto_place_all_ships();
    set_up(player);
  }
}
