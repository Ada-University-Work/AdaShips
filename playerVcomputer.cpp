#include "headers/playerVcomputer.h"

using namespace std;

int player_turn_menu() {
  int menu_choice;
  cout << "\n\nIt is you turn, what would you like to do?\n1. Fire a torpedo\n2. Auto fire\nPlease select and option (or 0 to quit): ";
  if( ! (cin >> menu_choice)) { //catching erroneous input
    cout << "\nInvalid input\n";
    cin.clear(); //clearing the error from cin stream
    cin.ignore(10000, '\n');
    menu_choice = player_turn_menu();
  }
  else {
    cin.ignore(10000, '\n');
  }
  return menu_choice;
}

int player1_turn(Boats &player1, Boats &enemy) {
  bool valid_coordinate = false, returnCode, valid_menu_choice = true;
  string coordinate_str;
  vector<int> coordinate;
  int boat_hit, won = 0; // 1 = won the game, -1 = quit, 0 = not won

  cout << "\nYour ship board:\n";
  player1.print_ship_board();

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  do {
    switch (player_turn_menu()){
      case 0:
        return -1;
      case 1:
        valid_menu_choice = true;
        while (valid_coordinate == false) {
          cout << "\n\nEnter a coordinate to fire at: ";
          getline(cin, coordinate_str);
          try {
            coordinate = enemy.format_coordinate(coordinate_str);
          } catch(int error) {
            cout << "\nInvalid coordinate: format needs to be LetterNumber e.g. A9\n";
            continue;
          }
          returnCode = enemy.valid_coordinate(coordinate);
          if (returnCode == false) {
            cout << "\nInvalid coordinate: out of board range\n";
            continue;
          }
          valid_coordinate = true;
        }
        boat_hit = enemy.fire(coordinate);
        break;
      case 2:
        valid_menu_choice = true;
        boat_hit = enemy.auto_fire();
        break;
      default:
        cout << "\nInvalid option\n";
        valid_menu_choice = false;
        break;
    }
  } while (!valid_menu_choice);

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  if (boat_hit > -1) {
    if(enemy.boat_sank(boat_hit)){
      cout << "The boat has been sank!\n";
      if(enemy.all_boats_sank()) {
        cout << "All boats have sank!\n";
        won = 1;
      }
    }
  }
  
  if (won != 1) {
    cout << "\nPress enter to end your turn...";
    char temp = cin.get();
    cin.clear();
  }
  
  return won;
}

bool comp_turn(Boats &enemy, Boats &comp) {
  int boat_hit, won = 0;

  cout << "\nThe computers ship board:\n";
  comp.print_ship_board();

  cout << "\nThe computers target board:\n";
  enemy.print_target_board();

  boat_hit = enemy.auto_fire();
  cout << "\nThe computers target board:\n";
  enemy.print_target_board();
  
  if (boat_hit > -1) {
    if(enemy.boat_sank(boat_hit)){
      cout << "The boat has been sank!\n";
      if(enemy.all_boats_sank()) {
        cout << "All boats have sank!\n";
        won = 1;
      }
    }
  }
  
  cout << "\nPress enter to end the turn...";
  
  char temp = cin.get();
  cin.clear();
  return won;
}

void playerVcomputer(Boats &_player, Boats &_comp) {
  bool comp_won = false;
  int player_won = 0;

  while (player_won == 0 && comp_won == false) {
    system("clear");
    cout << "\nIT'S YOUR TURN:\n";
    player_won = player1_turn(_player, _comp);
    if (player_won!=0) {
      continue;
    }
    system("clear");
    cout << "\nIT'S THE COMPUTERS TURN:\n";
    comp_won = comp_turn(_player, _comp);
  }

  if (player_won == 1) {
    cout << "\nYou won! :)\n\n";
  }
  else if (player_won == -1) {
    cout << "\nQuiting game...\n\n";
  }
  else {
    cout << "\nYou lost! :(\n\n";
  }

  cout << "\nPress enter to return to menu...";
  char temp = cin.get();
  cin.clear();
}
