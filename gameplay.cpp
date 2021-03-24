#include "headers/gameplay.h"

using namespace std;

//helper functions

vector<int> format_valid_coordinate(string coordinate, Boats enemy) {
  vector<int> formatted_coordinate;
  int return_code;
  try {
    formatted_coordinate = enemy.format_coordinate(coordinate);
  } catch(int error) {
    throw ("\nInvalid coordinate: format needs to be 'LetterNumber LetterNumber' e.g. 'A9 B6 F2'\n");
  }
  return_code = enemy.valid_coordinate(formatted_coordinate);
  if (return_code == false) {
    throw("Coordinate number " + coordinate + " is invalid: out of board range\n");
  }
  return formatted_coordinate;
}

vector<string> split_coordinates(string coordinates) {
  vector<string> split_coordinates;
  istringstream iss(coordinates);

  for(string s; iss >> s; ) {
    split_coordinates.push_back(s);
  }
  return split_coordinates;
};

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

// firing functions

int fire_normal(Boats &_enemy) {
  bool valid_coordinate = false;
  string coordinate_str;
  vector<int> coordinate;
  int boat_hit;

  while (valid_coordinate == false) {
    cout << "\n\nEnter a coordinate to fire at: ";
    getline(cin, coordinate_str);
    try {
      coordinate = format_valid_coordinate(coordinate_str, _enemy);
    }
    catch(string error) {
      cout << error;
      continue;
    }
    valid_coordinate = true;
  }

  boat_hit = _enemy.fire(coordinate);
  return boat_hit;
}

vector<int> fire_salvo(Boats &_player, Boats &_enemy) {
  bool valid_coordinate = false;
  string coordinates_str;
  int boat_hit;

  vector<string> coordinates_vector; //all coordinates as strings
  vector<int> coordinate; //one coordinate formatted into integers
  vector<vector<int>> formatted_coordinates; //all formatted coordinates
  
  vector<int> boats_hit;
  int turns = _player.boats_remaining();

  while (valid_coordinate == false) {
    cout << "\n\nEnter " << turns << " coordinates to fire at: ";
    getline(cin, coordinates_str);

    formatted_coordinates.clear();
    coordinates_vector = split_coordinates(coordinates_str);
    
    // checking user entered correct amount of coordinates
    if (coordinates_vector.size() != turns) {
      cout << "\nIncorrect number of coordinates entered: please try again\n";
      continue;
    }
    // looping through each coordinate
    for(int i=0; i < coordinates_vector.size(); i++) {
      try {
        coordinate = format_valid_coordinate(coordinates_vector[i], _enemy);
      }
      catch(string error) {
        cout << error;
        continue;
      }
      valid_coordinate = true;
      formatted_coordinates.push_back(coordinate);
    }
  }

  for (int y=0; y < formatted_coordinates.size(); y++){
    boat_hit = _enemy.fire(formatted_coordinates[y]);
    boats_hit.push_back(boat_hit);
  }
  return boats_hit;
}

vector<int> fire_mine(Boats &_enemy) {
  bool valid_coordinate = false;
  string coordinate_str;
  vector<int> coordinate;
  vector<int> boats_hit;

  while (valid_coordinate == false) {
    cout << "\n\nEnter a coordinate to fire at: ";
    getline(cin, coordinate_str);
    try {
      coordinate = format_valid_coordinate(coordinate_str, _enemy);
    }
    catch(string error) {
      cout << error;
      continue;
    }
    valid_coordinate = true;
  }

  boats_hit = _enemy.fire_mines(coordinate);
  return boats_hit;
}

// turn functions

int player_turn(Boats &player, Boats &enemy) {
  bool valid_menu_choice = true;
  int boat_hit, won = 0; // 1 = won the game, -1 = quit, 0 = not won

  cout << "\nYour ship board:\n";
  player.print_ship_board();

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  do {
    switch (player_turn_menu()){
      case 0:
        return -1;
      case 1:
        valid_menu_choice = true;
        boat_hit = fire_normal(enemy);
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

int player_turn_salvo(Boats &player, Boats &enemy) {
  bool valid_menu_choice = true;
  int won = 0; // 1 = won the game, -1 = quit, 0 = not won
  vector<int> boats_hit;

  cout << "\nYour ship board:\n";
  player.print_ship_board();

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  do {
    switch (player_turn_menu()){
      case 0:
        return -1;
      case 1:
        valid_menu_choice = true;
        boats_hit = fire_salvo(player, enemy);
        break;
      case 2:
        valid_menu_choice = true;
        boats_hit = enemy.auto_fire_salvo(player.boats_remaining());
        break;
      default:
        cout << "\nInvalid option\n";
        valid_menu_choice = false;
        break;
    }
  } while (!valid_menu_choice);

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  for (int i=0; i < boats_hit.size(); i++) {
    if (boats_hit[i] > -1) {
      if(enemy.boat_sank(boats_hit[i])){
        cout << "The boat has been sank!\n";
      }
    }
  }

  if(enemy.all_boats_sank()) {
    cout << "All boats have sank!\n";
    won = 1;
  }
  
  if (won != 1) {
    cout << "\nPress enter to end your turn...";
    char temp = cin.get();
    cin.clear();
  }
  return won;
}


int player_turn_mines(Boats &player, Boats &enemy) {
  bool valid_menu_choice = true;
  int won = 0; // 1 = won the game, -1 = quit, 0 = not won
  vector<int> boats_hit;

  cout << "\nYour ship board:\n";
  player.print_ship_board();

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  do {
    switch (player_turn_menu()){
      case 0:
        return -1;
      case 1:
        valid_menu_choice = true;
        boats_hit = fire_mine(enemy);
        break;
      case 2:
        valid_menu_choice = true;
        boats_hit = enemy.auto_fire_mines();
        break;
      default:
        cout << "\nInvalid option\n";
        valid_menu_choice = false;
        break;
    }
  } while (!valid_menu_choice);

  cout << "\nYour target board:\n";
  enemy.print_target_board();

  for (int i=0; i < boats_hit.size(); i++) {
    if (boats_hit[i] > -1) {
      if(enemy.boat_sank(boats_hit[i])){
        cout << "The boat has been sank!\n";
      }
    }
  }

  if(enemy.all_boats_sank()) {
    cout << "All boats have sank!\n";
    won = 1;
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

bool comp_turn_salvo(Boats &enemy, Boats &comp) {
  int boat_hit, won = 0;
  vector<int> boats_hit;

  cout << "\nThe computers ship board:\n";
  comp.print_ship_board();

  cout << "\nThe computers target board:\n";
  enemy.print_target_board();

  boats_hit = enemy.auto_fire_salvo(comp.boats_remaining());

  cout << "\nThe computers target board:\n";
  enemy.print_target_board();
  
  for (int i=0; i < boats_hit.size(); i++) {
    if (boats_hit[i] > -1) {
      if(enemy.boat_sank(boats_hit[i])){
        cout << "The boat has been sank!\n";
      }
    }
  }
  if(enemy.all_boats_sank()) {
    cout << "All boats have sank!\n";
    won = 1;
  }

  cout << "\nPress enter to end the turn...";
  
  char temp = cin.get();
  cin.clear();

  return won;
}

bool comp_turn_mines(Boats &enemy, Boats &comp) {
  int boat_hit, won = 0;
  vector<int> boats_hit;

  cout << "\nThe computers ship board:\n";
  comp.print_ship_board();

  cout << "\nThe computers target board:\n";
  enemy.print_target_board();

  boats_hit = enemy.auto_fire_mines();

  cout << "\nThe computers target board:\n";
  enemy.print_target_board();
  
  for (int i=0; i < boats_hit.size(); i++) {
    if (boats_hit[i] > -1) {
      if(enemy.boat_sank(boats_hit[i])){
        cout << "The boat has been sank!\n";
      }
    }
  }
  if(enemy.all_boats_sank()) {
    cout << "All boats have sank!\n";
    won = 1;
  }

  cout << "\nPress enter to end the turn...";
  char temp = cin.get();
  cin.clear();

  return won;
}

// game mode functions

void playerVcomputer(Boats &_player, Boats &_comp) {
  bool comp_won = false;
  int player_won = 0;

  while (player_won == 0 && comp_won == false) {
    system("clear");
    cout << "\nIT'S YOUR TURN:\n";
    player_won = player_turn(_player, _comp); // 1 = won the game, -1 = quit, 0 = not won
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

void playerVcomputer_salvo(Boats &_player, Boats &_comp) {
  bool comp_won = false;
  int player_won = 0;

  while (player_won == 0 && comp_won == false) {
    system("clear");
    cout << "\nIT'S YOUR TURN:\n";
    player_won = player_turn_salvo(_player, _comp); // 1 = won the game, -1 = quit, 0 = not won
    if (player_won!=0) {
      continue;
    }
    system("clear");
    cout << "\nIT'S THE COMPUTERS TURN:\n";
    comp_won = comp_turn_salvo(_player, _comp);
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

void playerVcomputer_mines(Boats &_player, Boats &_comp) {
  bool comp_won = false;
  int player_won = 0;

  while (player_won == 0 && comp_won == false) {
    system("clear");
    cout << "\nIT'S YOUR TURN:\n";
    player_won = player_turn_mines(_player, _comp); // 1 = won the game, -1 = quit, 0 = not won
    if (player_won!=0) {
      continue;
    }
    system("clear");
    cout << "\nIT'S THE COMPUTERS TURN:\n";
    comp_won = comp_turn_mines(_player, _comp);
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

void two_player_game(Boats &_player1, Boats &_player2) {
  int player2_won = 0, player1_won = 0;

  while (player1_won == 0 && player2_won == 0) {
    system("clear");
    cout << "\nPLAYER 1'S TURN:\n";
    player1_won = player_turn(_player1, _player2); // 1 = won the game, -1 = quit, 0 = not won
    if (player1_won != 0) {
      continue;
    }
    system("clear");
    cout << "\nPLAYER 2'S TURN:\n";
    player2_won = player_turn(_player2, _player1);
  }

  if (player1_won == -1 || player2_won == -1) {
    cout << "\nQuiting game...\n\n";
  }
  else if (player1_won == 1) {
    cout << "\nPLAYER 1 WINS! :)\n\n";
  }
  
  else if (player2_won == 1) {
    cout << "\nPLAYER 2 WINS! :)\n\n";
  }

  cout << "\nPress enter to return to menu...";
  char temp = cin.get();
  cin.clear();
}

void two_player_game_salvo(Boats &_player1, Boats &_player2) {
  int player2_won = 0, player1_won = 0;

  while (player1_won == 0 && player2_won == 0) {
    system("clear");
    cout << "\nPLAYER 1'S TURN:\n";
    player1_won = player_turn_salvo(_player1, _player2); // 1 = won the game, -1 = quit, 0 = not won
    if (player1_won != 0) {
      continue;
    }
    system("clear");
    cout << "\nPLAYER 2'S TURN:\n";
    player2_won = player_turn_salvo(_player2, _player1);
  }

  if (player1_won == -1 || player2_won == -1) {
    cout << "\nQuiting game...\n\n";
  }
  else if (player1_won == 1) {
    cout << "\nPLAYER 1 WINS! :)\n\n";
  }
  
  else if (player2_won == 1) {
    cout << "\nPLAYER 2 WINS! :)\n\n";
  }

  cout << "\nPress enter to return to menu...";
  char temp = cin.get();
  cin.clear();
}

void two_player_game_mines(Boats &_player1, Boats &_player2) {
  int player2_won = 0, player1_won = 0;

  while (player1_won == 0 && player2_won == 0) {
    system("clear");
    cout << "\nPLAYER 1'S TURN:\n";
    player1_won = player_turn_mines(_player1, _player2); // 1 = won the game, -1 = quit, 0 = not won
    if (player1_won != 0) {
      continue;
    }
    system("clear");
    cout << "\nPLAYER 2'S TURN:\n";
    player2_won = player_turn_mines(_player2, _player1);
  }

  if (player1_won == -1 || player2_won == -1) {
    cout << "\nQuiting game...\n\n";
  }
  else if (player1_won == 1) {
    cout << "\nPLAYER 1 WINS! :)\n\n";
  }
  
  else if (player2_won == 1) {
    cout << "\nPLAYER 2 WINS! :)\n\n";
  }

  cout << "\nPress enter to return to menu...";
  char temp = cin.get();
  cin.clear();
}

void computerVcomputer_mines(Boats &_comp1, Boats &_comp2) {
  int comp2_won = 0, comp1_won = 0;

  while (comp1_won == 0 && comp2_won == 0) {
    system("clear");
    cout << "\nCOMPUTER 1'S TURN:\n";
    comp1_won = comp_turn_mines(_comp2, _comp1); // 1 = won the game, -1 = quit, 0 = not won
    if (comp1_won != 0) {
      continue;
    }
    system("clear");
    cout << "\nCOMPUTER 2'S TURN:\n";
    comp2_won = comp_turn_mines(_comp1, _comp2);
  }

  if (comp1_won == 1) {
    cout << "\nCOMPUTER 1 WINS! :)\n\n";
  }
  
  else if (comp2_won == 1) {
    cout << "\nCOMPUTER 2 WINS! :)\n\n";
  }

  cout << "\nPress enter to return to menu...";
  char temp = cin.get();
  cin.clear();
}
