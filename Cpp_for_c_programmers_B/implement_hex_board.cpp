#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

enum class Color{EMPTY, BLUE, RED};

//To store matrix cell coordinates
class Point {
    public:
        int x;
        int y;
        Point() {};
        Point(int x_in, int y_in) {
            x = x_in; y = y_in;
        }
};
 
// A Data Structure for queue used in BFS
class QueueNode {
    public:
        Point pt;  // The coordinates of a cell
        int dist;  // cell's distance of from the source
        QueueNode() {};
        QueueNode(Point pt_in, int distance) {
            pt.x = pt_in.x;
            pt.y = pt_in.y; 
            dist = distance;
        }
};

class Board {
    private:
        int size;
        vector<vector<Color>> board;
        vector<vector<Color>> player1;
        vector<vector<Color>> player2;
        Color player1Color;
        Color player2Color;
    public:
        Board(int boardSize);
        Board(int boardSize, Color colorForPlayer1);
        Board(int boardSize, Color colorForPlayer1, vector<vector<Color>> givenBoard);
        int getBoardSize();                     // get board size
        vector<vector<Color>> getBoard();       // return board
        vector<vector<Color>> getPlayer1Move(); // return player1
        vector<vector<Color>> getPlayer2Move(); // return player2
        Color getPlayer1Color();                // return player 1 color
        Color getPlayer2Color();                // return player 2 color
        int isLegalCell(int x, int y);          // Check if legal cell
        int isLegalMove(int x, int y);      // Check if legal move
        void setPlayerMove(int x, int y, Color PlayerColor);    // set player next move;
        int BFS(vector<vector<Color>> hexBoard, Point src, Point dest, Color playerColor);
        int isPlayerWin(Color playerColor);    // determine if the player wins
        void drawBoard();
};

Board::Board(int boardSize) {
    size = boardSize;
    board = vector<vector<Color>> (size, vector<Color>(size,Color::EMPTY));
    player1Color = Color::BLUE;
    player2Color = Color::RED;
}

Board::Board(int boardSize, Color colorForPlayer1) {
    size = boardSize;
    board = vector<vector<Color>> (size, vector<Color>(size,Color::EMPTY));
    player1Color = colorForPlayer1;
    player2Color = (colorForPlayer1 == Color::BLUE) ? Color::RED : Color::BLUE;
}

Board::Board(int boardSize, Color colorForPlayer1, vector<vector<Color>> givenBoard) {
    size = boardSize;
    board = givenBoard;
    player1Color = colorForPlayer1;
    player2Color = (colorForPlayer1 == Color::BLUE) ? Color::RED : Color::BLUE;
}

int Board::getBoardSize() {
    return size;
}

vector<vector<Color>> Board::getBoard(){
    return board;
}

vector<vector<Color>> Board::getPlayer1Move() {
    return player1;
}

vector<vector<Color>> Board::getPlayer2Move() {
    return player2;
}

Color Board::getPlayer1Color() {
    return player1Color;
}

Color Board::getPlayer2Color() {
    return player2Color;
}

int Board::isLegalCell(int x, int y) {
    if ((x>=0 && x<size) && (y>=0 && y<size)) {
        return 1;
    }
    return 0;
}

int Board::isLegalMove(int x, int y) {
    if (isLegalCell(x, y) && board[x][y] == Color::EMPTY) {
        return 1;
    }
    return 0;
}

void Board::setPlayerMove(int x, int y, Color playerColor) {
    if (isLegalMove(x, y) == 0) {
        cout << "Illegal Move!";
        return;
    }
    board[x][y] = playerColor;
}

int Board::BFS(vector<vector<Color>> hexBoard, Point src, Point dest, Color playerColor)
{
    // check source and destination cell
    // of the matrix have value 1
    if (hexBoard[src.x][src.y] != playerColor || hexBoard[dest.x][dest.y] != playerColor)
        return -1;

    vector<vector<bool>> explored(hexBoard.size(), vector<bool>(hexBoard.size(), false));
     
    // Mark the source cell as visited
    explored[src.x][src.y] = true;
 
    // Create a queue for BFS
    queue<QueueNode> q;
     
    // Distance of source cell is 0
    QueueNode s = {src, 0};
    q.push(s);  // Enqueue source cell

    // These arrays are used to get row and column
    // numbers of 6 neighbours of a given cell
    int rowNum[] = {-1, -1,  0, 0,  1, 1};
    int colNum[] = { 0,  1, -1, 1, -1, 0};

    // Do a BFS starting from source cell
    while (!q.empty()) {
        QueueNode curNode = q.front();
        Point pt = curNode.pt;
 
        // If we have reached the destination cell,
        // we are done
        if (pt.x == dest.x && pt.y == dest.y)
            return curNode.dist;
 
        // Otherwise dequeue the front
        // cell in the queue
        // and enqueue its adjacent cells
        q.pop();
 
        for (int i = 0; i < 6; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];
             
            // if adjacent cell is valid, has path and
            // not visited yet, enqueue it.
            if (isLegalCell(row, col) && hexBoard[row][col] == playerColor &&
               !explored[row][col])
            {
                // mark cell as visited and enqueue it
                explored[row][col] = true;
                QueueNode Adjcell = { {row, col}, curNode.dist + 1 };
                q.push(Adjcell);
            }
        }
    }
 
    // Return -1 if destination cannot be reached
    return -1;
}

int Board::isPlayerWin(Color playerColor) {
    // Check if there is a path from src to dest based on player Color
    for (int start=0; start<size; ++start) {
        for (int end=0; end<size; ++end) {
            Point src, dest;
            if (playerColor == Color::BLUE) {
                src = {0, start}; 
                dest = {size-1,end};
            }
            else if (playerColor == Color::RED) {
                src = {start, 0}; 
                dest = {end, size-1};
            }
            if (BFS(board, src, dest, playerColor) >= 1) {
                return 1;
            }
        }
    }
    return 0;
}

void Board::drawBoard() {
    string frontSpace = "";
    vector<vector<Color>> hexBoard = getBoard();
    for (int i=0; i<size*2-1; ++i) {
        cout << frontSpace; // Add space to skew the board
        if (i%2 == 0) {
            for (int j=0; j<size; ++j) {
                if (hexBoard[i/2][j] == Color::BLUE) {
                    cout << "B";
                }
                else if(hexBoard[i/2][j] == Color::RED) {
                    cout << "R";
                }
                else {
                    cout << ".";
                }
                if (j!=size-1) {
                    cout << " - ";
                }
            }
        }
        else {
            for (int j=0; j<size; ++j) {
                cout << "\\";
                if (j!=size-1) {
                    cout << " / ";
                }
            }
        }
        cout << endl;
        frontSpace += " ";
    }
}

// Helper functions
int getRandomCell(int baseNum) {
    return rand()%baseNum;
}

// Simulation
class MonteCarlo {
    public:
        double calProbSingleCell(Board& board, vector<int> cellPosition, Color curColor);
        void setComMove(Board& board);
        void playGame(Board& board);
};

void MonteCarlo::setComMove(Board& board) {
    // Set computer move based on the max probability on the board
    double maxProb = 0;
    vector<int> bestPos;
    double curProb = 0;
    for (int i=0; i<board.getBoardSize(); ++i) {
        for (int j=0; j<board.getBoardSize(); ++j) {
            if (!board.isLegalMove(i, j)) {
                continue;
            }
            curProb = calProbSingleCell(board, vector<int> {i,j}, board.getPlayer2Color()); // player 2: computer
            if (curProb > maxProb) {
                bestPos.clear();
                maxProb = curProb;
                bestPos = {i, j};
            }
            // cout << "Prob at [" << i << "," << j << "]: " << curProb << endl;
        }
    }
    board.setPlayerMove(bestPos[0], bestPos[1], board.getPlayer2Color());
}

double MonteCarlo::calProbSingleCell(Board& board, vector<int> cellPosition, Color curColor) {
    // This calculate probability at the given cell
    int winCount = 0;
    int simNum = 200;
    int x = cellPosition[0];
    int y = cellPosition[1];
    Color setColor = curColor;
    Color comColor = board.getPlayer2Color();
    Color playerColor = board.getPlayer1Color();
    int boardSize = board.getBoardSize();
    
    for (int n=0; n<simNum; ++n) {
        // Simulate the move to find its winning probability
        Board simBoard = board;
        simBoard.setPlayerMove(x, y, setColor);
        while (true) {
            for (int i=0; i<static_cast<int>(pow(boardSize,2)*1.5); ++i) {
                int randomCell = getRandomCell(pow(boardSize,2)+1);
                int x_temp = randomCell/boardSize;
                int y_temp = randomCell%boardSize;
                if (!simBoard.isLegalMove(x_temp, y_temp)) {
                    continue;
                }
                curColor = (curColor==Color::RED) ? Color::BLUE: Color::RED;
                simBoard.setPlayerMove(x_temp, y_temp, curColor);
            }
            if (simBoard.isPlayerWin(comColor)) {
                winCount++;
                break;
            }
            else if (simBoard.isPlayerWin(playerColor)) {
                break;
            }
        }
    }
    return (1.0*winCount)/simNum;
}

void MonteCarlo::playGame(Board& board) {
    // Playing hex game
    Color curMove = Color::BLUE;
    while (true) {
        board.drawBoard();
        int x, y;
        if (curMove == board.getPlayer1Color()) {
            cout << "Player Turn! Please specify [x,y] coordinate." << endl;
            while (true) {
                cout << "x: ";
                cin >> x;
                cout << "y: ";
                cin >> y;
                if (board.isLegalMove(x, y)) {
                    board.setPlayerMove(x, y, board.getPlayer1Color());
                    break;
                }
                else {
                    cout << "Invalid move!" << endl;
                    cout << "Please choose [x,y] again!" << endl;
                }
            }
        }
        else {
            setComMove(board);
        }
        curMove = (curMove==Color::BLUE) ? Color::RED : Color::BLUE;
        if (board.isPlayerWin(board.getPlayer1Color())) {
            cout << "Player win!!" << endl;
            break;
        }
        else if (board.isPlayerWin(board.getPlayer2Color())) {
            cout << "Computer win!!" << endl;
            break;
        }
    }
}

int main() {
    srand(time(0));
    cout << "Hex board:" << endl;
    int size = 11;
    Color playerColor;
    // Set color of the player on the hex board
    string playerColor_in;
    cout << "Which color do you want to play? Blue color will always go first." << endl;
    cout << "Type: blue or red only. Example: blue" << endl;
    cout << "if you want to exit, type: q " << endl;
    while (true) {
        cin >> playerColor_in;
        if (playerColor_in == "blue") {
            cout << "Player color: BLUE" << endl;
            playerColor = Color::BLUE;
            break;
        }
        else if (playerColor_in == "red") {
            cout << "Player color: RED" << endl;
            playerColor = Color::RED;
            break;
        }
        else if (playerColor_in == "q") {
            return 0;
        }
        else {
            cout << "Please type again!" << endl;
            cout << "Only red or blue " << endl;
        }
    }
     
    Board board(size, playerColor);
    MonteCarlo simulation;
    simulation.playGame(board);
    board.drawBoard();
    return 0;
}