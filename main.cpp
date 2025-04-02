#include <iostream> // used for cin and cout
#include <conio.h> // used for _kbhit() and _getch()
#include <stdlib.h>// used for using rand() function
#include <windows.h>// used for hinding the cursor and sleep,system functions
#include<vector>


using namespace std;
const int height =30,width=20;
int score=0;

char a[height][width];
bool gameover =false;


class tetro_block{
public:
    vector<vector<int>> shape;
    int positiony=0,positionx=10;
    tetro_block(char c)
{
    if (c == 'l') // L-Block
    {
        shape =
        {
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0}
        };
    }
    else if (c == 'o') // O-Block (Square)
    {
        shape =
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
    }
    else if (c == 't') // T-Block
    {
        shape =
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        };
    }
    else if (c == 'j') // J-Block
    {
        shape =
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
    }
    else if (c == 's') // S-Block
    {
        shape =
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        };
    }
    else if (c == 'z') // Z-Block
    {
        shape =
        {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
    }
    else if (c == 'i') // I-Block
    {
        shape =
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        };
    }
}

    tetro_block& operator=(const tetro_block& other) {
        if (this != &other) {  // Prevent self-assignment
            shape = other.shape;  // Copy vector
            positiony = other.positiony;
            positionx = other.positionx;
        }
        return *this;
    }
    void hard_drop() {
    while (block_check()) {
        positiony++;  // Keep moving down until collision
    }
    positiony--; // Move back to last valid position
}

    void rotate() {
    vector<vector<int>> newShape(4, vector<int>(4, 0));

    // Rotate by 90 degrees (transpose + reverse rows)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
                //newShape[3 - j][i] = shape[i][j];
           newShape[j][3 - i] = shape[i][j];
        }
    }

    // Check if new shape fits within bounds and doesn't collide
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (newShape[i][j] == 1) {
                int y = positiony + i;
                int x = positionx + j;

                if (y >= height || x < 0 || x >= width || a[y][x] == 'L' || a[y][x] == '#') {
                    return; // Invalid rotation, so do nothing
                }
            }
        }
    }

    // Apply the valid rotation
    shape = newShape;
}

        bool block_check() {
    int new_positiony = positiony+1;  // Move one step down

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {  // If there's a block
                int y = new_positiony + i;
                int x = positionx + j;

                // Check if within bounds and not colliding with another tetromino
                if (y >= height || x < 0 || x >= width || a[y][x] == 'L'||a[y][x]=='#') {
                    return false;  // Collision detected
                }
            }
        }
    }
    return true;  // No collision
}
void soft_drop(tetro_block &t) {
    if (t.block_check()) { // Check if it can move down
        t.positiony++; // Move one step down
    }
}

};

class gameboard
{
public:
    void setup()
    {
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                if(i==height-1||j==0||j==width-1) a[i][j]='#';
                else a[i][j]=' ';
            }
        }
    }
    void drawtermino(tetro_block &t)
    {
                for (int i = 0; i < 4; i++) {        // Loop through tetromino shape
            for (int j = 0; j < 4; j++) {
                if (t.shape[i][j] == 1) {    // If there's a block
                    int y = t.positiony + i;
                    int x = t.positionx + j;

                    // Ensure within board bounds
                    if (y >= 0 && y < height-1 && x >= 0 && x < width-1) {
                        a[y][x] = 'O';  // Use 'L' to represent the tetromino
                    }
                }
            }
        }
    }

void draw() {
    // Move cursor to the top-left corner (0,0) to prevent flickering
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Draw the game board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
                if(a[i][j]=='#') cout<<a[i][j];
            else if(a[i][j]=='O'||a[i][j]=='L')cout << "\033[36m"<<'O'<<"\033[0m"; // Change color to sky blue
                else cout<<a[i][j];
        }
        cout << endl;
    }
    cout<<endl;
    cout<<"YOUR SCORE IS - "<<score<<endl;
}
void showNextBlock(char next) {
    vector<vector<int>> preview(4, vector<int>(4, 0));

    // Get shape of next block
    tetro_block temp(next);
    preview = temp.shape;

    cout << "\nNext Block:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << (preview[i][j] ? 'O' : ' ');
        }
        cout << endl;
    }
}


// Function to hide cursor
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false; // Hide cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void input(tetro_block &t) {
    if (_kbhit()) {
        char key = _getch();

        // Handle arrow keys (which return two values)
        if (key == 0 || key == -32) { // Arrow keys return an extra character
            key = _getch();
            switch (key) {
                case 75: // Left Arrow
                    if (canMove(t, -1)) t.positionx--;
                    break;
                case 77: // Right Arrow
                    if (canMove(t, 1)) t.positionx++;
                    break;
                case 72: // Up Arrow (Rotate)
                    t.rotate();
                    break;
                case 80: // Down Arrow (Soft Drop)
                    t.soft_drop(t);
                    break;
            }
        }
        else { // Handle normal keys (WASD, Space, etc.)
            switch (key) {
                case 'a': // Move Left
                    if (canMove(t, -1)) t.positionx--;
                    break;
                case 'd': // Move Right
                    if (canMove(t, 1)) t.positionx++;
                    break;
                case 'w': // Rotate
                    t.rotate();
                    break;
                case 's': // Soft Drop
                    t.soft_drop(t);
                    break;
                case ' ': // Hard Drop
                    t.hard_drop();
                    break;
                case 'q': // Quit
                    cout << "HOPE U ENJOYED THE GAME (_)"<<endl;
                                    cout << "  #####    ###    ##     ## ########     #######  ##     ## ######## ########  \n";
                cout << " ##   ##  ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## \n";
                cout << "##       ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## \n";
                cout << "##  #### #######  ## ### ## ######      ##     ## ##     ## ######   ########  \n";
                cout << "##   ##  ##   ##  ##     ## ##          ##     ##  ##   ##  ##       ##   ##   \n";
                cout << " ##   ## ##   ##  ##     ## ##          ##     ##   ## ##   ##       ##    ##  \n";
                cout << "  #####  ##   ##  ##     ## ########     #######     ###    ######## ##     ## \n";
                    exit(0);
                    break;
                case 'r':

    gameover = false;
    gameboard g;
    g.setup();
    g.draw();
        break;
            }
        }
    }
}



// Helper Function: Check if block can move left (-1) or right (+1)
bool canMove(tetro_block &t, int dx)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (t.shape[i][j] == 1) {  // If there's a block in the shape
                int newX = t.positionx + j + dx; // New X position
                int y = t.positiony + i;

                // Check if within bounds and not colliding
                if (newX < 1 || newX >= width - 1 || a[y][newX] == 'L' || a[y][newX] == '#') {
                    return false; // Invalid move
                }
            }
        }
    }
    return true; // Movement allowed
}
    void checkLines() {
        for (int i = height - 2; i > 0; i--) { // Start from the bottom row
            bool full = true;

            for (int j = 1; j < width - 1; j++) {
                if (a[i][j] != 'L') {
                    full = false;
                    break;
                }
            }

            if (full) {
                clearLine(i);
                i++; // Recheck the current line since all rows moved down
            }
        }
    }

    void clearLine(int line) {
        for (int j = 1; j < width - 1; j++) a[line][j] = ' '; // Clear the line

        // Move all rows above down
        for (int i = line; i > 0; i--)
            for (int j = 1; j < width - 1; j++)
                a[i][j] = a[i - 1][j];

        // Ensure the top row is empty
        for (int j = 1; j < width - 1; j++) a[0][j] = ' ';
        score+=100;
    }
};

int main()
{
    system("cls"); // Clear the terminal
    system("color 3"); // Change color to sky blue
    char blocks[] = {'l', 'o', 't', 'j', 's', 'z', 'i'};
    char p = blocks[rand() % 7]; // Randomly pick a tetromino
    char nextBlock = blocks[rand() % 7];  // Store next block type
    tetro_block l(p);

    gameboard g;
    g.setup();
    while(!gameover)
    {
        g.drawtermino(l);
        g.draw();
        g.showNextBlock(nextBlock);
        g.hideCursor();
        if(l.block_check()){
            for (int i = 0; i < 4; i++) {        // Loop through tetromino shape
            for (int j = 0; j < 4; j++) {
                if (l.shape[i][j] == 1) {    // If there's a block
                    int y = l.positiony + i;
                    int x = l.positionx + j;

                    // Ensure within board bounds
                    if (y >= 0 && y < height-1 && x >= 0 && x < width-1) {
                        a[y][x] = ' ';  // Use 'L' to represent the tetromino
                    }
                }
            }
        }
        l.positiony++;
        }
        else
        {
            for (int i = 0; i < 4; i++) {        // Loop through tetromino shape
            for (int j = 0; j < 4; j++) {
                if (l.shape[i][j] == 1) {    // If there's a block
                    int y = l.positiony + i;
                    int x = l.positionx + j;

                    // Ensure within board bounds
                    if (y >= 0 && y < height-1 && x >= 0 && x < width-1) {
                        a[y][x] = 'L';  // Use 'L' to represent the tetromino
                    }
                }
            }
        }
        g.checkLines();
            // Replace char randomBlock = blocks[rand() % 7];
        char randomBlock = nextBlock;  // Use stored next block
nextBlock = blocks[rand() % 7]; // Generate a new next block
tetro_block q(randomBlock);
l = q;
            if(!l.block_check()){
                    cout<<"YOU LOST!!  DO U WANT TO TRY AGAIN <y/n>:";
            char c;
            cin>>c;
            if(c=='y'){
                system("cls"); // Clear the terminal
                system("color 3"); // Change color to sky blue
                g.setup();
                // Replace char randomBlock = blocks[rand() % 7];
char randomBlock = nextBlock;  // Use stored next block
nextBlock = blocks[rand() % 7]; // Generate a new next block
tetro_block q(randomBlock);
l = q;
            }
            else if(c=='n'){
                break;
            }
            }
        }
        g.input(l);
        Sleep(70); // Pause for 100 milliseconds
        //system("cls");
    }
    cout << "HOPE U ENJOYED THE GAME (_)"<<endl<<endl;
                cout << "  #####    ###    ##     ## ########     #######  ##     ## ######## ########  \n";
                cout << " ##   ##  ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## \n";
                cout << "##       ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## \n";
                cout << "##  #### #######  ## ### ## ######      ##     ## ##     ## ######   ########  \n";
                cout << "##   ##  ##   ##  ##     ## ##          ##     ##  ##   ##  ##       ##   ##   \n";
                cout << " ##   ## ##   ##  ##     ## ##          ##     ##   ## ##   ##       ##    ##  \n";
                cout << "  #####  ##   ##  ##     ## ########     #######     ###    ######## ##     ## \n";
    return 0;
}
