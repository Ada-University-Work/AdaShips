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
### Use of good standards

I have strived to use good coding standards throughout my code. The standards are:

• Include good quality, clear, jargon free and up to date internal documentation / comments; adopt
the philosophy of writing comments for non-programmers.
• Eliminate or minimise code duplication & any unnecessary redundancy.
• Strive for simplicity in logic and flow.
• Use a consistent naming convention for functions, variables, objects, etc to provide clear contextual
value, improved comprehension and quick readability.
• Use appropriate and consistent indentation, logical grouping and spaced blocks within your
codebases; adopt tabs or a set number of spaces for indenting.
• Use spaces consistently to separate operators and delimiters.
• Be consistent when aligning braces; use a vertically or slanted style.
• Avoid deep nested conditionals.
• Avoid single (long) lines of code containing multiple operations; consider ‘one line one instruction”.
• Keep variable lifetimes and scope as short and as small as possible.
• Avoid multipurpose functions and variables.
• Conserve system resources.
• Minimise forced type conversion, coercion or casting.
• Know and test your code: adopt a personal and rigorous testing strategy; don’t just see it if works -
test and fix its limits.
• Test early and often, fail fast and resolve effectively.

### Development phases
I completed one epic per phase of development. These are outlined in my kanban board linked above.

### Code quality
After each code change I rigorously tested the programme, checking for any bugs. I tested using erroneous input, edge cases and standard input.

### Key design challeneges


# Known Issues
* spaces and non-standard capitalisation of the config file causes an error that breaks the programme. It is recommended you follow the current format when adding to the config file to prevent these errors.
* placing a ship hasn't been configured to work with board sizes bigger than 10
* in order for the code to technically support any number of boats I haven't added functionality to check whether the boats provided will fit in the specified board.