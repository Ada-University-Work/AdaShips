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
            boats[counter] = {boat_name, stoi(boat_size)};
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
};

class Boats: public Board {
  public:
    Boats() {
      cout << "initialised boats\n";
    }

    void print_boats() {
      for (int i=0; i<boats.size(); i++) {
        cout << boats[i].name << endl;
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
      int ship_length, ship_num;

      for (int i=0; i < boats.size(); i++) {
        if (boats[i].name == ship_name) { //validate ship name in menu
          ship_length = boats[i].size;
          ship_num = i+1;
        } 
      }

      if (toupper(direction) == 'V') { 
        for (int y=start_pos[1]; y < start_pos[1]+ship_length; y++ ) {
          if (!valid_boat_placement({start_pos[0], y})) {
            return 1;
          }
        }
        for (int y=start_pos[1]; y < start_pos[1]+ship_length; y++ ) {
          ship_board[start_pos[0]][y] = ship_num;
        }
      }
      else if (toupper(direction) == 'H') { 
        for (int x=start_pos[0]; x < start_pos[0]+ship_length; x++ ) {
          if (!valid_boat_placement({x, start_pos[1]})) {
            return 1;
          }
        }
        for (int x=start_pos[0]; x < start_pos[0]+ship_length; x++ ) {
          ship_board[x][start_pos[1]] = ship_num;
        }
      }
      return 0;
    }
};

int main() {
  Boats player;
  player.print_boats();
  player.print_target_board();
  player.print_ship_board();

  // player.place_boat(first_coordinate, last_coordinate, "Carrier");
  int return_code = player.place_boat({5,0}, 'V', "Carrier");
  if (return_code == 1) {
    cout << "incorrect ship placement";
  }
  return_code = player.place_boat({7,7}, 'V', "Battleship");
  if (return_code == 1) {
    cout << "incorrect ship placement";
  }
  return_code = player.place_boat({6,7}, 'H', "Battleship");
  if (return_code == 1) {
    cout << "incorrect ship placement";
  }
  return_code = player.place_boat({6,5}, 'V', "Destroyer");
  if (return_code == 1) {
    cout << "incorrect ship placement";
  }
  player.print_ship_board();

  // Board my_game;
  // my_game.initialise_board();
  // my_game.print_board();
}