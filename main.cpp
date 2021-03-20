#include "headers/main.h"

using namespace std;

int playerVcomp() {
  int set_up_return_code;
  Boats player;
  Boats comp;

  cin.ignore();
  set_up_comp(comp);
  set_up_return_code = set_up_player(player);

  if (set_up_return_code == 1) {
    return 1;
  }

  playerVcomputer(player, comp);
  return 0;
}

int two_player() {
  int set_up_return_code1, set_up_return_code2;
  Boats player1;
  Boats player2;

  cin.ignore();
  
  set_up_return_code1 = set_up_player(player1, "PLAYER 1");
  set_up_return_code2 = set_up_player(player2, "PLAYER 2");

  if (set_up_return_code1 == 1 || set_up_return_code2 == 1) {
    return 1;
  }

  playerVcomputer(player1, player2);
  return 0;
}

int main() {
  int menu_choice = -1, return_code;
  
  cout << "Welcome to Adaships!" << endl;

  while (menu_choice != 0) {
    cout << "1. One player V computer game\n2. Two player game\n3. One player V computer (salvo) game\n4. Two player (salvo) game\n\nPlease select an option (or 0 to quit): ";
    if( ! (cin >> menu_choice)) { //catching erroneous input
      cout << "Invalid input\n";
      cin.clear(); //clearing the error from cin stream
      cin.ignore(10000, '\n');
      menu_choice = -1;
      continue; //continuing to the next iteration of the loop
    }

    switch (menu_choice) {
      case 0:
        break;

      case 1:
        return_code = playerVcomp();
        if (return_code == 1) {
          menu_choice = 0;
        }
        break;

      case 2:
        return_code = two_player();
        if (return_code == 1) {
          menu_choice = 0;
        }
        break;
      
      default:
        cout << "\nInvalid Input, please try again...\n";
        break;
    }
  }
  cout << "\nGood bye\n";
}
