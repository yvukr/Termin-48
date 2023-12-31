#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void output_array(); // generate a new integer at a random position - print board
void generate_rand(int& a, int& b); // generate random coordinates for new integer
void isPossibleMovement(); // checking if there are any possilbe moves
void userInput(); // takes user input 
void moveUp();
void shiftUp();
void moveLeft();
void shiftLeft();
void moveDown();
void shiftDown();
void moveRight();
void shiftRight();
void turnDone(); // counts the score on the board and calls output_array()

#define UWHT "\e[4;37m" // white underline
#define RESET "\e[0;39m" // reset font changes
#define BWHT "\e[1;37m" // white bold
#define BLKB "\e[40m" // black highlight
#define YELB "\e[43m" // yellow highlight
#define BHRED "\e[1;91m" // red bold



bool isGameActive = true; // Could potentially use this to declare whether the game is active or not. For example if the player has lost yet or not
bool possibleMovement = true;
double positions[16]; // just making this a global variable
double interface[4][4] = { //initializing array of zeros
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
    };
int score = 0;

int main() {

    srand(time(nullptr));
    output_array(); //displaying interface with a 2
    printf(BWHT"Score: %i\n", score); // prints score at the start
    printf(RESET);
    userInput(); // takes user input

    return 0;
}
















void generate_rand(int& a, int& b) {
    a = rand() % 4;
    b = rand() % 4;
}

void output_array() {
    int a;
    int b;
    generate_rand(a, b);

    if (interface[a][b] == 0) { // if spot is vacant, place the new number, if not, generate a different spot and restart function
        interface[a][b] = 2; //assigning generated random coordanates with 2
        
        for (int i = 0; i < 4; i++) { //display interface
            for (int j = 0; j < 4; j++) {
                if (interface[i][j] != 0) {
                    printf(YELB"%.f\t", interface[i][j]); // make numbers that aren't 0 highlight yellow
                    printf(RESET);
                }
                else {
                    printf(BLKB"%.f\t", interface[i][j]); // otherwise highlight black
                    printf(RESET);
                }
            }
            printf("\n");
        }  
    }
    else {
        int zeroPos = 16; // checking if there are possible spaces
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (interface[i][j] != 0) {
                    zeroPos--;
                }
            }
        }
        if(zeroPos == 0) { // if there is no available spaces for numbers to generate, check for possible moves
        isPossibleMovement();
            if (possibleMovement) {
                for (int i = 0; i < 4; i++) { //display interface
                    for (int j = 0; j < 4; j++) {
                        if (interface[i][j] != 0) {
                            printf(YELB"%.f\t", interface[i][j]); // make numbers that aren't 0 highlight yellow
                            printf(RESET);
                        }
                        else {
                            printf(BLKB"%.f\t", interface[i][j]); // otherwise highlight black
                            printf(RESET);
                        }
                    }
                    printf("\n");
                }
            }
            else {
                isGameActive = false;
            }
        }
        else {
            output_array(); // otherwise run the code again
        }
    }
}

void isPossibleMovement() {
    possibleMovement = true; // Assume there is a possible movement

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Check if there is a neighboring cell with the same value
            if ((i < 3 && interface[i][j] == interface[i + 1][j]) ||
                (i > 0 && interface[i][j] == interface[i - 1][j]) ||
                (j < 3 && interface[i][j] == interface[i][j + 1]) ||
                (j > 0 && interface[i][j] == interface[i][j - 1])) {
                // There is a possible movement
                return;
            }
        }
    }

    // No possible movement found
    possibleMovement = false;
}



void userInput() {

    do { // temporary solution for the player to move in a certain direction
        char direction;
        cout << UWHT"Direction (W, A, S, D): ";
        cin >> direction;
        cout << RESET;
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // just makes it so that the board is more visible, less messy from turn to turn

        // these cout statements can be replaced with other things such as running a funciton that actually executes moves
        switch(tolower(direction)) {
        case 'w':
            moveUp();
            break;
        case 'a':
           moveLeft();
            break;
        case 's':
            moveDown();
            break;
        case 'd':
            moveRight();
            break;
        // if the user inputs an invalid direction / does not input a character
        default:
            printf("please choose a valid direction\n");
            break;
        }
    }
    while(isGameActive == true);

}

void moveUp() {

    
    for (int i = 0; i < 4; i++){
    
    double newVal = 0;
        if (interface[0][i] == interface[1][i]) {  
            newVal = interface[1][i] + interface[0][i];
            score += newVal;
            interface[0][i] = newVal;
            interface[1][i] = 0; 
        }

        shiftUp(); 

        if (interface[2][i] == interface[1][i]) { 
            newVal = interface[2][i] + interface[1][i];
            score += newVal;
            interface[1][i] = newVal;
            interface[2][i] = 0; 
        }

        shiftUp(); 
        if (interface[3][i] == interface[2][i]) { 
            newVal = interface[3][i] + interface[2][i];
            score += newVal;
            interface[2][i] = newVal;
            interface[3][i] = 0; 
        }

    }
    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void shiftUp() { 

    for (int i = 0; i < 4; i++) {
        if (interface[0][i] == 0) { 
            if (interface[1][i] == 0) { 
                if (interface[2][i] == 0) {
                    swap(interface[3][i], interface[0][i]); 
                }
                else {
                    if (interface[3][i] == 0) { 
                        swap(interface[2][i], interface[0][i]); 
                    }
                    else {
                        swap(interface[2][i], interface[0][i]);
                        swap(interface[3][i], interface[1][i]);
                    }
                }
            }
            else { 
                if (interface[2][i] == 0) { 
                    if (interface[3][i] == 0) { 
                        swap(interface[1][i], interface[0][i]);
                    }
                    else {
                        swap(interface[2][i], interface[0][i]);
                        swap(interface[3][i], interface[1][i]);
                    }
                }
                else {
                    if (interface[0][i] == 0) {
                        swap(interface[1][i], interface[0][i]);
                        swap(interface[2][i], interface[1][i]);
                    }
                    else { 
                        swap(interface[1][i], interface[0][i]);
                        swap(interface[2][i], interface[1][i]);
                        swap(interface[3][i], interface[2][i]); 
                    }
                }
            }
        }
        else {
            if (interface[1][i] == 0) { 
                if (interface[2][i] == 0) { 
                    if (interface[3][i] != 0) { 
                        swap(interface[3][i], interface[1][i]); 
                    }
                }
                else {
                    if (interface[3][i] == 0) { 
                        swap(interface[2][i], interface[1][i]); 
                    }
                    else { 
                        if (interface[3][i] != 0) { 
                            swap(interface[2][i], interface[1][i]); 
                            swap(interface[3][i], interface[2][i]); 
                        }
                    }
                }
            }
            else {
                if (interface[2][i] == 0) { 
                    if (interface[3][i] != 0) { 
                        swap(interface[3][i], interface[2][i]); 
                    }
                }
            }
        }
    } 
}


void moveLeft() {

    
    for (int i = 0; i < 4; i++){

        double newVal = 0;
        if (interface[i][0] == interface[i][1]) { // 2 2 4 2 
            newVal = interface[i][0] + interface[i][1];
            score += newVal;
            interface[i][0] = newVal;
            interface[i][1] = 0; // 4 0 4 2
        }

        shiftLeft(); // 4 4 0 2

        if (interface[i][1] == interface[i][2]) { 
            newVal = interface[i][1] + interface[i][2];
            score += newVal;
            interface[i][1] = newVal;
            interface[i][2] = 0; 
        }

        shiftLeft(); // 4 4 2 0
        if (interface[i][2] == interface[i][3]) { 
            newVal = interface[i][2] + interface[i][3];
            score += newVal;
            interface[i][2] = newVal;
            interface[i][3] = 0; 
        }
    }
    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void shiftLeft() { 

    for (int i = 0; i < 4; i++) { 
        if (interface[i][0] == 0) { 
            if (interface[i][1] == 0) { 
                if (interface[i][2] == 0) { 
                    swap(interface[i][3], interface[i][0]); 
                }
                else { 
                    if (interface[i][3] == 0) { 
                        swap(interface[i][2], interface[i][0]); 
                    }
                    else { 
                        swap(interface[i][2], interface[i][0]);
                        swap(interface[i][3], interface[i][1]);
                    }
                }
            }
            else {
                if (interface[i][2] == 0) { 
                    if (interface[i][3] == 0) {
                        swap(interface[i][1], interface[i][0]); 
                    }
                    else { 
                        swap(interface[i][2], interface[i][0]);
                        swap(interface[i][3], interface[i][1]);
                    }
                }
                else {
                    if (interface[i][0] == 0) { 
                        swap(interface[i][1], interface[i][0]);
                        swap(interface[i][2], interface[i][1]); 
                    }
                    else { 
                        swap(interface[i][1], interface[i][0]);
                        swap(interface[i][2], interface[i][1]);
                        swap(interface[i][3], interface[i][2]); 
                    }
                }
            }
        }
        else {
            if (interface[i][1] == 0) { 
                if (interface[i][2] == 0) { 
                    if (interface[i][3] != 0) { 
                        swap(interface[i][3], interface[i][1]); 
                    }
                }
                else {
                    if (interface[i][3] == 0) { 
                        swap(interface[i][2], interface[i][1]); 
                    }
                    else { 
                        if (interface[i][3] != 0) { 
                            swap(interface[i][2], interface[i][1]); 
                            swap(interface[i][3], interface[i][2]); 
                        }
                    }
                }
            }
            else {
                if (interface[i][2] == 0) { 
                    if (interface[i][3] != 0) { 
                        swap(interface[i][3], interface[i][2]); 
                    }
                }
            }
        }
    } 

}

void moveDown() {

    
    for (int i = 0; i < 4; i++){
        
        double newVal = 0;
        if (interface[3][i] == interface[2][i]) { // 2 2 4 2 
            newVal = interface[3][i] + interface[2][i];
            score += newVal;
            interface[3][i] = newVal;
            interface[2][i] = 0; // 4 0 4 2
        }

        shiftDown(); // 4 4 0 2

        if (interface[2][i] == interface[1][i]) { 
            newVal = interface[2][i] + interface[1][i];
            score += newVal;
            interface[2][i] = newVal;
            interface[1][i] = 0; 
        }

        shiftDown(); // 4 4 2 0
        if (interface[1][i] == interface[0][i]) { 
            newVal = interface[1][i] + interface[0][i];
            score += newVal;
            interface[1][i] = newVal;
            interface[0][i] = 0; 
        }

    }
    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void shiftDown() { 

    for (int i = 0; i < 4; i++) { 
        if (interface[3][i] == 0) { 
            if (interface[2][i] == 0) {  
                if (interface[1][i] == 0) { 
                    swap(interface[0][i], interface[3][i]); 
                }
                else { 
                    if (interface[0][i] == 0) { 
                        swap(interface[1][i], interface[3][i]); 
                    }
                    else { 
                        swap(interface[1][i], interface[3][i]);
                        swap(interface[0][i], interface[2][i]);
                    }
                }
            }
            else {  
                if (interface[1][i] == 0) { 
                    if (interface[0][i] == 0) { 
                        swap(interface[2][i], interface[3][i]); 
                    }
                    else {  
                        swap(interface[1][i], interface[3][i]);
                        swap(interface[0][i], interface[2][i]); 
                    }
                }
                else { 
                    if (interface[0][i] == 0) {  
                        swap(interface[2][i], interface[3][i]);
                        swap(interface[1][i], interface[2][i]); 
                    }
                    else {  
                        swap(interface[2][i], interface[3][i]);
                        swap(interface[1][i], interface[2][i]);
                        swap(interface[0][i], interface[1][i]);  
                    }
                }
            }
        }
        else {
            if (interface[2][i] == 0) {  
                if (interface[1][i] == 0) { 
                    if (interface[0][i] != 0) { 
                        swap(interface[0][i], interface[2][i]); 
                    }
                }
                else {
                    if (interface[0][i] == 0) { 
                        swap(interface[1][i], interface[2][i]);
                    }
                    else { 
                        if (interface[0][i] != 0) { 
                            swap(interface[1][i], interface[2][i]); 
                            swap(interface[0][i], interface[1][i]);  
                        }
                    }
                }
            }
            else {
                if (interface[1][i] == 0) { 
                    if (interface[0][i] != 0) { 
                        swap(interface[0][i], interface[1][i]); 
                    }
                }
            }
        }
    } 
}

void moveRight() {

    
    for (int i = 0; i < 4; i++) {
        
        double newVal = 0;
        if (interface[i][3] == interface[i][2]) { // 2 4 2 2 
            newVal = interface[i][3] + interface[i][2];
            score += newVal;
            interface[i][3] = newVal;
            interface[i][2] = 0; // 2 4 0 4
        }

        shiftRight(); // 0 2 4 4

        if (interface[i][1] == interface[i][2]) { 
            newVal = interface[i][1] + interface[i][2];
            score += newVal;
            interface[i][2] = newVal;
            interface[i][1] = 0; 
        }

        shiftRight();

        if (interface[i][0] == interface[i][1]) { 
            newVal = interface[i][0] + interface[i][1];
            score += newVal;
            interface[i][1] = newVal;
            interface[i][0] = 0; 
        }
    }
    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void shiftRight() { 
    // key:
    // a, b, c, d = numbers/positions that haven't been checked yet
    // *  = any number that would happen to be in that position
    // 0 = self-explanatory
    // if 0 0 0 *, do nothing
    // if 0 0 * *, do nothing
    // if 0 * * *, do nothing
    // if * * * *, do nothing

    for (int i = 0; i < 4; i++) { // do this for 4 rows
        if (interface[i][3] == 0) { // if a b c 0
            if (interface[i][2] == 0) { // if a b 0 0 
                if (interface[i][1] == 0) { // if a 0 0 0
                    swap(interface[i][0], interface[i][3]); // case: * 0 0 0 
                }
                else { // if a * 0 0
                    if (interface[i][0] == 0) { // if 0 * 0 0
                        swap(interface[i][1], interface[i][3]); // case: 0 * 0 0
                    }
                    else { // if * * 0 0
                        swap(interface[i][1], interface[i][3]);
                        swap(interface[i][0], interface[i][2]);
                    }
                }
            }
            else { // if a b * 0
                if (interface[i][1] == 0) { // if a 0 * 0
                    if (interface[i][0] == 0) { // if 0 0 * 0
                        swap(interface[i][2], interface[i][3]); // case: 0 0 * 0
                    }
                    else { // if * 0 * 0
                        swap(interface[i][1], interface[i][3]);
                        swap(interface[i][0], interface[i][2]); // case * 0 * 0
                    }
                }
                else { // if a * * 0
                    if (interface[i][0] == 0) { // if 0 * * 0
                        swap(interface[i][2], interface[i][3]);
                        swap(interface[i][1], interface[i][2]); // case: 0 * * 0
                    }
                    else { // if * * * 0
                        swap(interface[i][2], interface[i][3]);
                        swap(interface[i][1], interface[i][2]);
                        swap(interface[i][0], interface[i][1]); // case: * * * 0
                    }
                }
            }
        }
        else {
            if (interface[i][2] == 0) { // if a b 0 *
                if (interface[i][1] == 0) { // if a 0 0 *
                    if (interface[i][0] != 0) { // if NOT 0 0 0 * 
                        swap(interface[i][0], interface[i][2]); // case: * 0 0 * 
                    }
                }
                else {
                    if (interface[i][0] == 0) { // if 0 * 0 *
                        swap(interface[i][1], interface[i][2]); // case: 0 * 0 *
                    }
                    else { 
                        if (interface[i][0] != 0) { // if 2 2 0 2
                            swap(interface[i][1], interface[i][2]); 
                            swap(interface[i][0], interface[i][1]); // case: * * 0 *
                        }
                    }
                }
            }
            else {
                if (interface[i][1] == 0) { // a 0 * *
                    if (interface[i][0] != 0) { // if NOT 0 0 * *
                        swap(interface[i][0], interface[i][1]); // case: * 0 * *
                    }
                }
            }
        }
    } 
}

void turnDone() {
    if (isGameActive == true) {
        printf(BWHT"Score: %i\n", score);
        printf(RESET);
    }
    else {
        printf(BHRED"GAME OVER");
        printf(RESET);
        printf(BWHT"\nFINAL SCORE: %i\n", score);
        printf(RESET);
    }
    
}