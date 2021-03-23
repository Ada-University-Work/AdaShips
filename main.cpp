#include "headers/main.h"

using namespace std;

int playerVcomp() {
  int set_up_return_code;
  Boats player;
  Boats comp;

  cin.ignore();

  system("clear");
  cout << "\nSETTING UP THE COMPUTERS BOARD:\n";
  set_up_comp(comp);

  system("clear");
  cout << "\nSETTING UP YOUR BOARD:\n";
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
  
  system("clear");
  cout << "\nSETTING UP PLAYER 1's BOARD:\n";
  set_up_return_code1 = set_up_player(player1);

  if (set_up_return_code1 == 1) {
    return 0;
  }

  system("clear");
  cout << "\nSETTING UP PLAYER 2's BOARD:\n";
  set_up_return_code2 = set_up_player(player2);

  if (set_up_return_code2 == 1) {
    return 0;
  }

  two_player_game(player1, player2);
  return 0;
}

int two_player_salvo() {
  int set_up_return_code1, set_up_return_code2;
  Boats player1;
  Boats player2;

  cin.ignore();
  
  system("clear");
  cout << "\nSETTING UP PLAYER 1's BOARD:\n";
  set_up_return_code1 = set_up_player(player1);

  if (set_up_return_code1 == 1) {
    return 0;
  }

  system("clear");
  cout << "\nSETTING UP PLAYER 2's BOARD:\n";
  set_up_return_code2 = set_up_player(player2);

  if (set_up_return_code2 == 1) {
    return 0;
  }

  two_player_game_salvo(player1, player2);
  return 0;
}

int playerVcomp_salvo() {
  int set_up_return_code;
  Boats player;
  Boats comp;

  cin.ignore();

  system("clear");
  cout << "\nSETTING UP THE COMPUTERS BOARD:\n";
  set_up_comp(comp);

  system("clear");
  cout << "\nSETTING UP YOUR BOARD:\n";
  set_up_return_code = set_up_player(player);

  if (set_up_return_code == 1) {
    return 1;
  }

  playerVcomputer_salvo(player, comp);
  return 0;
}

int main() {
  int menu_choice = -1, return_code;
  bool continue_playing = true;
  char temp;

  while (continue_playing == true) {
    system("clear");
    cout << "Welcome to Adaships!" << endl;

    cout << "\n1. One player V computer game\n2. Two player game\n3. One player V computer (salvo) game\n4. Two player (salvo) game\n\nPlease select an option (or 0 to quit): ";

    if( ! (cin >> menu_choice)) { //catching erroneous input
      cout << "Invalid input\n";
      cin.clear(); //clearing the error from cin stream
      cin.ignore(10000, '\n');
      menu_choice = -1;
      continue; //continuing to the next iteration of the loop
    }

    switch (menu_choice) {
      case 0:
        continue_playing = false;
        break;

      case 1:
        return_code = playerVcomp();
        if (return_code == 1) {
          continue_playing = false;
          break;
        }
        break;

      case 2:
        return_code = two_player();
        if (return_code == 1) {
          continue_playing = false;
          break;
        }
        break;

      case 3:
        return_code = playerVcomp_salvo();
        if (return_code == 1) {
          continue_playing = false;
          break;
        }
        break;

      case 4:
        return_code = two_player_salvo();
        if (return_code == 1) {
          continue_playing = false;
          break;
        }
        break;

      default:
        cout << "\nInvalid Input, press enter to try again...";
        temp = cin.get();
        
        break;
    }
  }
  cout << "\nGood bye\n";
}
