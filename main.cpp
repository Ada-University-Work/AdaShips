#include <iostream>
#include <stdlib.h> //for setw
#include <iomanip> //for getw
#include <fstream> //read and write files
#include <vector> //vectors
#include <sstream> //string stream
#include <cctype> //for to upper
using namespace std;

class Board {
  private: //can only be accessed by class members
    void loadData() {
      string type, data, str_board_size, boat_name, boat_size;
      int counter = 0;

      ifstream game_config("adaship_config.ini"); //opening data file to read it

      while (getline(getline(game_config, type, ':'), data)){ //looping through each line of the file
        if (type == "Board") {
            stringstream ss(data);
            getline(ss, str_board_size, 'x');
            board_size = stoi(str_board_size);
        }
        else if (type == "Boat") {
          stringstream ssb(data);
          boats.push_back(boat());

          while (getline(getline(ssb, boat_name, ','), boat_size)){
            boats[counter] = {boat_name, stoi(boat_size), false};
            counter++;
          }
        }
      };
      game_config.close(); //closing the data file to save memory
    }

    void initialise_board(int board[80][80]) {
      for (int y=0; y<board_size; y++) {
        for (int x=0; x<board_size; x++) {
          board[x][y] = 0;
        }     
      }
    }

    void print_board(int board[80][80]) {
      const int empty    = 0;  // contains water
      const int occupied = -1;  // contains a ship
      const int miss     = -2;  // shot into ocean
      const int hit      = -3;  // shot and hit

      int counter = 0;

      for(int j = 0; j < 10; j++) { //number coordinates
        cout << setw(4) << j+1;
      }
      cout << endl;

      for(char a = 'A'; a <= 'J'; a++) { //letter coordinates
        cout << " " << a ;

        for(int i = 0; i < 10 ; i++) {

          if(board[i][counter] == occupied || board[i][counter] == empty) {
            cout << setw(4) << " |" ;
          }
          else if(board[i][counter] == miss ) {
            cout << setw(2) << "M" << setw(2) << "|";
          }
          else if(board[i][counter] == hit ) {
            cout << setw(2) << "H" << setw(2) << "|";;
          }
          else {
            char boat_initial = toupper(boats[board[i][counter]-1].name.at(0));
            cout << setw(2) << boat_initial << setw(2) << "|";
          }
        }
        cout << "\n";
        counter++;
      }
      cout << "\n";
    }

  protected: //can be accessed by class members and child classes
    int target_board[80][80];
    int ship_board[80][80];
    int board_size;

    struct boat {
      string name;
      int size;
      bool placed;
    };
    vector<boat> boats;

  public: //can be accessed anywhere
    Board() {
      loadData();
      initialise_board(target_board);
      initialise_board(ship_board);
    }

    void print_ship_board() {
      print_board(ship_board);
    }
    void print_target_board() {
      print_board(target_board);
    }

    vector<int> format_coordinate(string coordinates) {
      const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      int x_value = 0, y_value = 0, y_start_pos;

      // find the position of the first alpha character in coordinates
      for (int i=0; i < coordinates.length(); i++) {
        if (isalpha(coordinates[i])) {
          y_start_pos = i;
          break;
        }
      }
      if (y_start_pos==0) throw 20;

      // calculate the x coordinate
      string x_coordinates;
      for (int x=0; x < y_start_pos; x++) {
        x_coordinates += coordinates[x];
      }
      x_value = stoi(x_coordinates)-1;

      // calculate the y coordinate
      int result = 0;
      for (int y=y_start_pos; y < coordinates.length(); y++){
        result = result * 26 + (alpha.find(toupper(coordinates[y]))) + 1;
      }
      y_value = result-1;

      cout << "x " << x_value << "  y " << y_value << endl;
      return {x_value, y_value};
    }
};

class Boats: public Board {
  public:
    Boats() {
      cout << "initialised boats\n";
    }

    void print_boats() {
      for (int i=0; i<boats.size(); i++) {
        if (boats[i].placed == true) {
          cout << boats[i].name << setw(20-boats[i].name.length()) << ": ✓" << endl;  
        }
        else {
          cout << boats[i].name << setw(20-boats[i].name.length()) << ": X" << endl;
        }
      }
    }

    bool valid_boat_placement(vector<int> coordinate) {
      if (coordinate[0] < board_size && coordinate[1] < board_size) {
        if (ship_board[coordinate[0]][coordinate[1]] == 0) {
          return true;
        }
      }
      return false;
    }

    int place_boat(vector<int> start_pos, char direction, string ship_name) {
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
    }

    bool all_ships_placed() {
      for (int i=0; i<boats.size(); i++) {
        if(!boats[i].placed) {
          return false;
        }
      }
      return true;
    }
};

int set_up(Boats _player) {
  int menu_choice = -1;

  while (menu_choice != 0) {
    string ship_entered, coordinate;
    char ship_direction;

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

        vector<int> formatted_coordinate = _player.format_coordinate(coordinate);

        cout << "Is the ship vertical(V) or horizontal(H): ";
        ship_direction = cin.get();

        int return_code = _player.place_boat(formatted_coordinate, ship_direction, ship_entered);
        
        if (return_code == 0){
          cout << "\nThe " << ship_entered << " ship is placed!\n";
          _player.print_ship_board();
        }
        else {
          cout << "\nInvalid config, ship has not been placed.\nPlease try again\n";
        }

        if (_player.all_ships_placed()) {
          cout << "\nall ships placed\n";
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
    set_up(player);
    cout << "lol";
  } 
  

  // Boats player;
  // player.print_boats();
  // player.print_target_board();
  // player.print_ship_board();

  // // player.place_boat(first_coordinate, last_coordinate, "Carrier");
  // int return_code = player.place_boat({5,0}, 'V', "Carrier");
  // if (return_code == 1) {
  //   cout << "incorrect ship placement";
  // }
  // return_code = player.place_boat({7,7}, 'V', "Battleship");
  // if (return_code == 1) {
  //   cout << "incorrect ship placement";
  // }
  // return_code = player.place_boat({6,7}, 'H', "Battleship");
  // if (return_code == 1) {
  //   cout << "incorrect ship placement";
  // }
  // return_code = player.place_boat({6,5}, 'V', "Destroyer");
  // if (return_code == 1) {
  //   cout << "incorrect ship placement";
  // }
  // player.print_ship_board();

  // Board my_game;
  // my_game.initialise_board();
  // my_game.print_board();
}