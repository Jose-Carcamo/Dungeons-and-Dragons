#include <iostream>
#include <string>

using namespace std;

// Board dimensions defined as constants
const int ROWS = 5;
const int COLS = 5;

// Player class contains all player related data
class Player{
    public:

    // Constructor initializes the name and starting position
    Player(string name, int row, int col){
        m_name = name;
        m_row = row;
        m_col = col;
        m_score = 0; // Score starts from 0 points
        m_health = 3; // Health starts at 3 points
    }

    // Returns the player's name
    string GetName(){
        return m_name;
    }

    // Updates the player's position in the game
    void SetPosition(int row, int col){
        m_row = row;
        m_col = col;
    }

    // When a player steps on the T(trap tile), they lose -1 health point
    void Trap(){ 
        m_health -= 1;
    }

    // When a player collects a C(coin), they gain +1 score
    void Coin(){
        m_score += 1;
    }

    // Getter for the current row position
    int GetRow(){
        return m_row;
    }

    // Getter for the current column position
    int GetCol(){
        return m_col;
    }

    // Getter for current score
    int GetScore(){
        return m_score;
    }

    // Getter for current health
    int GetHealth(){
        return m_health;
    }

    private:

    string m_name; // Player's name
    int m_row;     // Player's current row coordinate on board
    int m_col;     // Player's current column coordinate on board
    int m_score;   // Player's current score
    int m_health;  // Player's current health
};

// Fills the board with empty cells and in game objects 
// T = Trap, X = Wall, C = Coin, E = Exit
void InitializeBoard(char board[ROWS][COLS]){
    // First filling in entire board with empty cells
    for (int i = 0; i < ROWS; i++){
        for (int x = 0; x < COLS; x++){
            board[i][x] = '.';
        }
    }
    
    // Replacing empty cells with in game objects
    board[0][3] = 'T';
    board[1][1] = 'X';
    board[2][2] = 'C';
    board[3][1] = 'X';
    board[3][3] = 'T';
    board[4][3] = 'C';
    board[4][4] = 'E';
    board[1][4] = 'C';
    board[4][0] = 'T';
}

// Prints out the current board, showing the position of the player with 'P'
void PrintBoard(char board[ROWS][COLS], Player p){
    for (int i = 0; i < ROWS; i++){
        for (int x = 0; x < COLS; x++){
            // Ensures P is displayed at current position
            if (i == p.GetRow() && x == p.GetCol()){
                cout << 'P' << " ";
            }
            else{
                cout << board[i][x] << " ";
            }
        }
        cout <<endl;
    }
    

}

int main(){
    // Gets the player's name from input
    string person;
    cout << "Enter player name: ";
    cin >> person;
    
    // Creates the player, starting at board[0][0]
    Player p(person, 0, 0);

    // Display starting stats
    cout << "Name: " << p.GetName() <<endl;
    cout << "Row: " << p.GetRow() <<endl;
    cout << "Col: " << p.GetCol() <<endl;
    cout << "Score: " << p.GetScore() <<endl;
    cout << "Health: " << p.GetHealth() <<endl;
    
    // Initialize board and display
    char board[ROWS][COLS];
    InitializeBoard(board);
    
    // Main game loop, runs until player either 
    // runs out of health or reaches exit
    do {
        PrintBoard(board, p);
        
        // Take in player input for movement
        char choice;
        enum Movement {W, A, S, D, INVALID};
        cout << "Make a move (w, a, s, d): ";
        cin >> choice;
        
        // Ensure new position is valid before declaring move
        Movement move;
        int newRow = p.GetRow();
        int newCol = p.GetCol();

        // Enum to assign input characters to a movement 
        switch(choice){
            case 'w':
                move = W;
                break;
            case 'a':
                move = A;
                break;
            case 's':
                move = S;     
                break;
            case 'd':
                move = D;
                break;
            default:
                move = INVALID;
                break;
        }

        // Apply the movement directions to a new position
        switch(move){
            case W:
                cout << "Move up" <<endl;
                newRow -= 1;
                break;
            case A:
                cout << "Move Left" <<endl;
                newCol -= 1;
                break;
            case S:
                cout << "Move Down" <<endl;
                newRow += 1;
                break;
            case D:
                cout << "Move Right" <<endl;
                newCol += 1;
                break;
            case INVALID:
                cout << "That is not a valid move. " <<endl;
                break;
        }
        
        // Checking to see if player is still within bounds
        if (newRow < 0 || newRow >= ROWS || newCol >= COLS || newCol < 0){
            newRow = p.GetRow();
            newCol = p.GetCol();
            cout << "That move goes off of the board. " <<endl;
        }

        // Wall checks preventing players from running into walls
        if (board[newRow][newCol] == 'X'){
            newRow = p.GetRow();
            newCol = p.GetCol();
            cout << "You hit a wall! " <<endl;
        }

        // Declaring the new position
        p.SetPosition(newRow, newCol);
    
        // Feature for collecting coins, updates score
        if (board[newRow][newCol] == 'C'){
            board[newRow][newCol] = '.'; // Removes coin from updated board
            p.Coin();
            cout << "You collected a coin!" <<endl;
            cout << "Health: " << p.GetHealth() <<endl;
            cout << "Score: " << p.GetScore() <<endl;
        }

        // Trap feature, triggers trap and removes 1 health point
        if (board[newRow][newCol] == 'T'){
            board[newRow][newCol] = '.'; // Removes trap after encounter
            p.Trap();
            cout << "You ran into a trap!" <<endl;
            cout << "Health: " << p.GetHealth() <<endl;
            cout << "Score: " << p.GetScore() <<endl;
        }   
        
    }while (board[p.GetRow()][p.GetCol()] != 'E' && p.GetHealth() > 0);
    
    // End game display message depending on win or lose scenario
    if (board[p.GetRow()][p.GetCol()] == 'E'){
        cout << "You have successfully escaped!" <<endl;
        cout << "Score: " << p.GetScore() <<endl;
        cout << "Health: " << p.GetHealth() <<endl;
    }
    
    else{
        cout << "You died!";
    }
    return 0;

}