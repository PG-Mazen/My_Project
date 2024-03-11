// File: CS112_A1_T6_20230587.cpp

// Program: A board of 3 x 3 is displayed and player 1 takes odd numbers 1,
//          3, 5, 7, 9 and player 2 takes even numbers 0, 2, 4, 6, 8. Players take turns to write their
//          numbers. Odd numbers start. Use each number only once. The first person to complete a line
//          that adds up to 15 is the winner. The line can have both odd and even numbers.

// Author: Mazen Mohamed Abdelsalam Ali
// ID: 20230587
// Section: Hasn't been identified yet
// Version: 1
// Date: 3/3/2024

#include "iostream"
#include "vector"

using namespace std;


// print the grid in the screen
void print(vector<vector<char>> &grid) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            cout << grid[i][j] << ' ';
        cout << endl;
    }
}

// check if the game ends or not
bool check(vector<vector<char>> &grid) {
    // Check for a row with sum equals to 15
    for (int i = 0; i < 3; ++i) {
        int sum = 0;
        for (int j = 0; j < 3; ++j) {
            if (grid[i][j] == 'x') {
                sum = 0;
                break;
            }
            sum += (grid[i][j] - '0');
        }
        if (sum == 15)
            return true;
    }

    // Check for a column with sum equals to 15
    for (int i = 0; i < 3; ++i) {
        int sum = 0;
        for (int j = 0; j < 3; ++j) {
            if (grid[j][i] == 'x') {
                sum = 0;
                break;
            }
            sum += (grid[j][i] - '0');
        }
        if (sum == 15)
            return true;
    }
    return false;
}

// this function plays the game
void play() {
    // this 2D vector stores the values in the grid, 'x' means that the grid is empty
    vector<vector<char>> grid(3, vector<char>(3, 'x'));

    // this vector stores the taken values. If the index of the value is 1, then it is taken, if 0 then it is still not taken yet
    vector<int> numbers(10, 0);

    int cur_player = 1; // store which player has the turn now
    int count = 0;  // count the number of cells taken in the grid
    int value;  // stores the value that the user chose to put in the cell

    print(grid);

    cin.ignore();   // to ignore the '/n' character because after that, we will use 'getline' function
    do {
        if (cur_player == 1)
            cout << "Player " << cur_player << ": Choose an odd number from 1 to 9: ";
        else
            cout << "Player " << cur_player << ": Choose an even number from 0 to 8: ";

        // check if the user has entered an integer or something else
        try {
            string input;
            getline(cin, input);
            value = stoi(input);
        } catch (invalid_argument const &e) {
            if (cur_player == 1)
                cerr << "You have enter an invalid input, make sure that your input is an odd integer from 1 to 9"
                     << endl;
            else
                cerr << "You have enter an invalid input, make sure that your input is an even integer from 0 to 8"
                     << endl;
            continue;
        }

        if (cur_player == 1) {
            // check if the chosen value is within the range or not
            if (value % 2 == 0 || value > 9 || value < 1) {
                cout << "Please enter an odd number form 1 to 9: ";
                continue;
            }

            // check whether this value has been taken before or not
            if (numbers[value]) {
                cout << "This value has been chosen before, please consider choosing another odd value from 1 to 9";
                continue;
            }
        } else {
            // check if the chosen value is within the range or not
            if (value % 2 == 1 || value > 8 || value < 0) {
                cout << "Please enter an even number form 0 to 8: ";
                continue;
            }

            // check whether this value has been taken before or not
            if (numbers[value]) {
                cout << "This value has been chosen before, please consider choosing another even value from 0 to 8: ";
                continue;
            }
        }

        // mark the value as taken
        numbers[value] = 1;

        int row, column;    // stores the place where the user will put his value by representing it as row and column
        cout
                << "Enter which row and column you will choose, rows starts from 1 to 3 from top to bottom, and columns start from 1 to 3 from left to right"
                << endl;
        do {
            // check if the user has entered an integer or something else
            try {
                string input1, input2;
                cout << "The row you want is: ";
                getline(cin, input1);
                cout << "The column you want is: ";
                getline(cin, input2);
                row = stoi(input1);
                column = stoi(input2);
            } catch (invalid_argument const &e) {
                cerr
                        << "You have enter an invalid input, make sure that your input is an integer from 1 to 3 for each of the two input"
                        << endl;
                continue;
            }

            // check whether the chosen values are within the range or not
            if (row > 3 || row < 1 || column > 3 || column < 1) {
                cout << "Please make sure that your input is an integer from 1 to 3 for each of the two input" << endl;
                continue;
            }

            // check whether this cell has been taken before or not
            if (grid[row - 1][column - 1] != 'x')
                cout << "This place has been chosen before, please consider choosing another place: ";
            else
                break;
        } while (true);

        // update the grid taken in consideration that it stores char not int
        grid[row - 1][column - 1] = '0' + value;

        // print the new one
        print(grid);

        // Check if the game ends and announce the winner if it ends
        if (check(grid)) {
            cout << "Player " << cur_player << " wins" << endl;
            break;
        }

        ++count;
        // check if all the cells has been taken or not and if so and there is no winner then the game is draw
        if (count == 9) {
            cout << "Draw !" << endl;
            break;
        }

        // Change the player who has the next turn
        cur_player = (cur_player == 1 ? 2 : 1);

    } while (true);
}

int main() {
    char c;
    while (true) {
        // Welcome screen
        cout << "Welcome to Tic-Tac-Toe with numbers" << endl;
        cout << "A: Play the game\n" << "B: Exit" << endl;
        cin >> c;

        if (c == 'B' || c == 'b')
            break;      // Exit the game
        if (c == 'A' || c == 'a')
            play();     // Run the game
        else
            cout << "Please enter a valid option: ";
    }
}