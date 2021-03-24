# Ada Ships

This repo is assignment 2 of the Advanced Programming module.
The supported platform is replit.com - you can run the code by going to the link below and clicking 'Run'.
[link to code on replit.com](https://replit.com/@CharlieHodgkins/AdaShips#main.cpp)


## Challenge Outline
### Summary and Proposed Solution
For the second assignment of the Advanced Programming module I was tasked with creating a c++ game that emulated the classic board game 'battleships'. 

The game involves two players who both have a board, a target board and a set number of ships with specific sizes. Each player then has to place all of their ships onto their board. Then the two players take turns 'firing', one player chooses a position on their target board and the other player tells them if they have a ship there or not/ if its a hit or miss. This will be represented on the first players target board and the second players ship board. Once a ship has been hit at every position it occupies then that ship has been 'destroyed'. The first player to destroy all of the other players ships wins!

The assignment requires all of the standard battleship game functionality as well as some additionbal features.

The main requirements of the game for the assignment are:
- the size of the board and details on the ships should be stored in a seperate text or ini file and be read by the programme
- the board locations should be referenced using a single notation type coordinate system e.g. (A5, D2, F10)
- the board must have letters along the X axis to represent each column and numbers along the Y axis to represent each row
- players ships can be placed horizontally or vertically and cannot be placed on another ship or at all outside of the board's boundaries
- the programme should display wether a ship has been hit or if it has been destroyed/ sank
- there are multiple 'game modes':
  - player versus computer
  - player versus player
  - player versus computer salvo game
  - player versus player salvo game
  - player versus computer with hidden mines
  - player versus player with hidden mines
  - computer versus computer with hidden mines

My initial design for the game is to have a board class that stores information on the board and target board and has methods that will print the boards and fire at a position etc, it will also have a child class for boats that stores information about the boats and has methods to display and place the boats etc. Each user will have their own instance of the classes so that the users boats and boards are kept seperate from eachother. 
The main file will have the main menu in it where the user can choose which gamemode they want. This will then call the relevant functions.
I will also have a set up file for all functions related to setting up the players board which will be called from the main file.
Finally I will have a gameplay file to store functions related to the seperate game modes and functionality for the main 'combat' phase that uses a loop to repeat each players turn until either player has won.

### UML Diagram
A UML flowchart diagram depicting my proposed solution I have outlined above.

![Flowchart](/adaships-flowchart.png)

### Initial Working Plan
My initial plan for this assignment is to split the requirements into large tasks/ epics and then break these down into a set of smaller tasks. Initially I will work on setting up the above mentioned classes and have them store dummy data, the second itteration will be creating a method(s) to read the data from a seperate file and store it within the class. The next itteration will be creating and displaying an empty board and so on. 
I plan approach each task like this using the agile methology by making a small addition/ change, testing it works, refining the code and then moving onto the second addition. This will ensure my code always refactored and allows any bugs to be identified as early as possible so that I can easily find the cause and remediate it quickly. This itterative approach with frequent testing will mean my code is to a high quality and standard.

### Analysis and Decomposition + Design Ideas
I have broken down this task into key epics and then split each epic into smaller tasks each with acceptance criteria. 
I've made tickets for each task on a kanban board so I can record my progress.

[link to kanban board](https://trello.com/b/puDcYRLf)

## Development
### Use of Good Standards
I have strived to use good coding standards throughout my code. The standards are:

- Include good quality, clear, jargon free and up to date internal documentation / comments; adopt
the philosophy of writing comments for non-programmers.
- Eliminate or minimise code duplication & any unnecessary redundancy.
- Strive for simplicity in logic and flow.
- Use a consistent naming convention for functions, variables, objects, etc to provide clear contextual value, improved comprehension and quick readability.
- Use appropriate and consistent indentation, logical grouping and spaced blocks within your codebases; adopt tabs or a set number of spaces for indenting.
- Use spaces consistently to separate operators and delimiters.
- Be consistent when aligning braces; use a vertically or slanted style.
- Avoid deep nested conditionals.
- Avoid single (long) lines of code containing multiple operations; consider ‘one line one instruction”.
- Keep variable lifetimes and scope as short and as small as possible.
- Avoid multipurpose functions and variables.
- Conserve system resources.
- Minimise forced type conversion, coercion or casting.
- Know and test your code: adopt a personal and rigorous testing strategy; don’t just see it if works - test and fix its limits.
- Test early and often, fail fast and resolve effectively.

To ensure I follow these standards I will repeatedly refelct on my code and review if there are any chnages needed to follow these standards and refactor it if needed.

### Development Phases
I completed one epic per phase of development. These are outlined in my kanban board linked above.
Firstly I set up the main structure of my code by creating the classes and the menu at the start of the game. During this phase I found that it is best practice to have a header file for each file of code where the classes and functions are defined and all libaries are included. After discovering this I decided to implement it in my code because I think it makes things clearer and it's easier to use code from other files in another file.

### Code Quality
After each code change I rigorously tested the programme, checking for any bugs. I tested using erroneous input, edge cases and standard input to make my testing more robust and ensure my code was too a high quality. 
After finding a bug I would jott it down in  the 'known issues' section of this read me. Then I would fix it the bug and remove it from the list or if finding a solution would have been more effort than the value I would gain I would leave it in the known issues section and move on.

### Key Design Challeneges
The biggest design challege of this project is how to store information for each 'tile' on the board. Initially I decided I needed a 2 dimensional list of some type. This is so that every item of the first list represents a column and then each item has an item for each row. Meaning I can refernece an item in the board by doing `list[X coordinate][Y coordinate]` so if I wanted to get item F2 of the board i would do `list[5][1]` because the list is 0 indexed but the board is not.
Initially I decided to use a vector for the list type because the size of a vector doesn't need to be specified when it is instansiated meaning I can set the size dynamically. This is beneficial because one of the requirements is to be able to change the size of the board using the config file and using a vector would allow me to initialise the board vector in the header file but set the size once the code has read the config file.
I ran into a multitude of issues trying to implement this. My main issue was that with a vector you can't use bracket notation to add a value if there isn't a value set at that position yet, where as you can with an array, you instead need to use the `vector.push_back(item)` function. I spent a lot of time trying to get this to work and eventually I decided that I wouldn't add much more value by using a vector instead of an array so it was taking more time than it was worth. So I changed my initial plan and instead used a 2D array. This meant I had to set the size to initialise it, becacause, per the assignment breif, the board can only be a maximum of 80 by 80 I statically set the array sizes to be 80. This means I needed another variable to store the board size for that game so I added this as a public class varaible. Then when I want to itterate through each item on the board, I dont itterate through all 80 items every time, as this would be unecessary and waste memory, I instead itterate through it up to the size of the board-size variable I have set.

Another key design challenge was how to store the boat information. Initially was going to use a 2D vector for the dynamic size and because i needed to store two bits of information about each boat. But after some research I relaised it would be more effective to use a structure for each boat. Each boat structure has a name and size attribute. I initiliase this structure at compile time in the board header file and then create a new instance of this structure for every boat listed in the config fie.
```
struct boat {
  string name;
  int size;
};
```
To store every boat I pushed each instance of the structure into a vector called 'boats' this allows me to track how many boats are in the game (by using `boats.size()`) and to keep all the information stored so it can be easily accessed by other class methods. Also using a structure for each boat allows me to easily add new information to be stored for each boat in future code iterations. For example I realised during the set up phase that I would need to track which boats had been placed so I added a bool attribute 'placed' to the structure to track this.

## Evaluation

### Analysis
Throughout the coding process I continually refactored my code as needed and worked with an itterative apprach to each task meaning the first itteration for a task was very unrefined and then in the second itteration I would refactor it to make it more concise.
One example of this was the fire_mines function. My first iterration included the same if and else if statements. The else if checks if there is a mine at the position the user is firing at. If there is a mine there I called the fire_mines function again 8 more times and passed in the coodinates of the positions surrounding the mines. This section of code was 30 lines long and included a lot of repetition so I knew it needed to be refactored but I initially solved the problem this way to check for bugs or problems with my logic. Once I had ensured that worked correctly I started my second itteration and refactored this down. Instead of calling the function again manually 8 times I used two for loops to loop through the ranges of the x and y coordinates that the coordinates surround a tile will follow (x-1 to x+1 and y-1 to y+1) then inside these for loops I called the function once passing in the itterables as coordinates. This shortened 30 lines of code into 5.
```
for(int X=x-1; X <= x+1; X++){
  for(int Y=y-1; Y <= y+1; Y++){
    returned_vector = fire_mines({X, Y});
    boats_hit.insert(boats_hit.end(), returned_vector.begin(), returned_vector.end());
  }
}
```

### Implementation
I used advanced programming principles throughout my code, including class inheritance ( the boat inherits the board class) and recursion in my fire_mines function etc.

### Feature Showcase

### Improved Targetting Algorithm
I did not get to this section of the assignment because I ran out of time to completed but my basic plan for tackling this problem is outlined in this ticket:
[link to ticket for improved targetting algorithm](https://trello.com/c/VqPQuMip)

### Reflective Review
In review I beleive I have used a wide range of standards and advanced programming princliples. But due to running out of time my gameplay functions are largely un-refacttored and have a 'code smell' because there is a lot of code repetition due to the different game play modes being generally the same but instead calling different functions.
If I had more time I would implement more OOP principles and refactor these by serperating out the repreated sections of code into their own functions and then calling this functions everywhere that part of code is used. This function orientated approach would improve clarity and readability.

# Known Issues
* spaces and non-standard capitalisation of the config file causes an error that breaks the programme. It is recommended you follow the current format when adding to the config file to prevent these errors.
* placing a ship hasn't been configured to work with board sizes bigger than 10
* in order for the code to technically support any number of boats I haven't added functionality to check whether the boats provided will fit in the specified board.