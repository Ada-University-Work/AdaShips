#include <iostream>
#include <stdlib.h> //for setw
#include <iomanip> //for getw
#include <fstream> //read and write files
using namespace std;

int board[10][10]; // Two-dimensional array for gameboard.

// class Board {
//   public:
//     int board;
//     string myString;
// };

void initialise_board( int array1[ 10 ][ 10 ] ) {
  // create a blank board   
  for (int x=0; x<10; x++) {
    for (int y=0; y<10; y++) {
      array1[x][y] = 0;
    }     
  }     
}

void print_board(int array2[10][10]) {
  const int empty    = 0;  // contains water
  const int occupied = 1;  // contains a ship
  const int miss     = 2;  // shot into ocean
  const int hit      = 3;  // shot and hit

  for(char a = 'A'; a <= 'J'; a++) { //letter coordinates
    cout << setw(5) << a;
  }
  cout << endl;

  for(int i = 1; i <= 10; i++) { //number coordinates
    if(i == 10)
      cout << i;
    else
      cout << " " << i ;
        
    for(int j = 0; j < 10 ; j++) {
      if(array2[i][j] == occupied || array2[i][j] == empty) {
        cout << setw(5) << " |" ;
      }
      else if(array2[i][j] == miss ) {
        cout << setw(5) << "O|";
      }
      else if(array2[i][j] == hit ) {
        cout << setw(5) << "X|";
      }
    }
    cout << "\n";
  }
}


int main() {
  string myText;

  // Read from the text file
  ifstream MyReadFile("adaship_config.ini");

  // Use a while loop together with the getline() function to read the file line by line
  while (getline (MyReadFile, myText)) {
    // Output the text from the file
    cout << myText;
  }

  // Close the file
  MyReadFile.close();

  initialise_board(board);
  print_board(board);
}