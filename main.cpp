#include <iostream>
#include <stdlib.h> //for setw
#include <iomanip> //for getw
#include <fstream> //read and write files
#include <vector> //vectors
#include <sstream> //string stream
using namespace std;

class Game {
  private:
    struct boat {
      string name;
      int size;
    };
    vector<boat> player_boats;
    vector<boat> enemy_boats;

    int player_board[80][80];
    int board_size;

    const int empty    = 0;  // contains water
    const int occupied = 1;  // contains a ship
    const int miss     = 2;  // shot into ocean
    const int hit      = 3;  // shot and hit

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
          player_boats.push_back(boat());
          enemy_boats.push_back(boat());

          while (getline(getline(ssb, boat_name, ','), boat_size)){
            player_boats[counter] = {boat_name, stoi(boat_size)};
            enemy_boats[counter] = {boat_name, stoi(boat_size)};
            counter++;
          }
        }
      };
      game_config.close(); //closing the data file to save memory
    }

  protected:

  public:
    Game() {
      loadData();
    }

    void initialise_board() {
      for (int y=0; y<board_size; y++) {
        for (int x=0; x<board_size; x++) {
          player_board[x][y] = 0;
        }     
      }
      player_board[3][7] = 2; 
    }

    void print_board() {
      for(char a = 'A'; a <= 'J'; a++) { //letter coordinates
        cout << setw(4) << a;
      }
      cout << endl;

      for(int j = 0; j < 10; j++) { //number coordinates
        if(j == board_size-1)
          cout << j+1;
        else
          cout << " " << j+1 ;
            
        for(int i = 0; i < 10 ; i++) {
          // cout << " " << i << j << " ";// << player_board[i][j];
          if(player_board[i][j] == occupied || player_board[i][j] == empty) {
            cout << setw(4) << " |" ;
          }
          else if(player_board[i][j] == miss ) {
            cout << setw(2) << "M" << setw(2) << "|";
          }
          else if(player_board[i][j] == hit ) {
            cout << setw(2) << "H" << setw(2) << "|";;
          }
        }
        cout << "\n";
      }
    }
};

int main() {
  Game my_game;
  my_game.initialise_board();
  my_game.print_board();
}