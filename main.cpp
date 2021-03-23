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

int playerVcomp_mines() {
  int set_up_return_code;
  Boats player;
  Boats comp;
  char temp;
  cin.ignore();

  system("clear");
  cout << "\nSETTING UP THE COMPUTERS BOARD:\n";
  set_up_comp(comp);

  system("clear");
  cout << "\nADDING COMPUTERS HIDDEN MINES:\n";
  set_up_mines(comp);

  system("clear");
  cout << "\nSETTING UP YOUR BOARD:\n";
  set_up_return_code = set_up_player(player);

  if (set_up_return_code == 1) {
    return 1;
  }

  system("clear");
  cout << "\nADDING YOUR HIDDEN MINES:\n";
  set_up_mines(player);

  playerVcomputer_mines(player, comp);
  return 0;
}

int two_player_mines() {
  int set_up_return_code1, set_up_return_code2;
  Boats player1;
  Boats player2;

  cin.ignore();
  
  system("clear");
  cout << "\nSETTING UP PLAYER 1'S BOARD:\n";
  set_up_return_code1 = set_up_player(player1);

  if (set_up_return_code1 == 1) {
    return 0;
  }

  system("clear");
  cout << "\nADDING PLAYER 1'S HIDDEN MINES:\n";
  set_up_mines(player1);

  system("clear");
  cout << "\nSETTING UP PLAYER 2'S BOARD:\n";
  set_up_return_code2 = set_up_player(player2);

  if (set_up_return_code2 == 1) {
    return 0;
  }

  system("clear");
  cout << "\nADDING PLAYER 2'S HIDDEN MINES:\n";
  set_up_mines(player2);

  two_player_game_mines(player1, player2);
  return 0;
}

int compVcomp_mines() {
  int set_up_return_code1, set_up_return_code2;
  Boats comp1;
  Boats comp2;

  cin.ignore();
  
  system("clear");
  cout << "\nSETTING UP COMPUTER 1'S BOARD:\n";
  set_up_comp(comp1);

  system("clear");
  cout << "\nADDING COMPUTER 1'S HIDDEN MINES:\n";
  set_up_mines(comp1);

  system("clear");
  cout << "\nSETTING UP COMPUTER 2'S BOARD:\n";
  set_up_comp(comp2);

  system("clear");
  cout << "\nADDING COMPUTER 2'S HIDDEN MINES:\n";
  set_up_mines(comp2);

  computerVcomputer_mines(comp1, comp2);
  return 0;
}

int main() {
  int menu_choice = -1, return_code;
  bool continue_playing = true;
  char temp;

  while (continue_playing == true) {
    system("clear");
    cout << "Welcome to Adaships!" << endl;

    cout << "\n1. One player V computer game\n2. Two player game\n3. One player V computer (salvo) game\n4. Two player (salvo) game\n5. One player v computer (hidden mines) game\n6. Two player game (hidden mines) game\n7. Computer v computer (hidden mines)\n\nPlease select an option (or 0 to quit): ";

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

      case 5:
        return_code = playerVcomp_mines();
        if (return_code == 1) {
          continue_playing = false;
          break;
        }
        break;

      case 6:
        return_code = two_player_mines();
        if (return_code == 1) {
          continue_playing = false;
          break;
        }
        break;

      case 7:
        return_code = compVcomp_mines();
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
