#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "board.h"

using namespace std;

// Initializing isWhitesTurn static variable
bool Board::isWhitesTurn = true;

// Constructor for generating a board
Board::Board() : whitePieces(16), blackPieces(16)
{
    int index = 0;

    // filling whitePieces vector and blackPieces vector with their type and locations
    for (int x = 0; x < 8; ++x)
    {
        char name;
        switch (x)
        {
        case 0:
            name = 'r';
            break;
        case 1:
            name = 'n';
            break;
        case 2:
            name = 'b';
            break;
        case 3:
            name = 'q';
            break;
        case 4:
            name = 'k';
            break;
        case 5:
            name = 'b';
            break;
        case 6:
            name = 'n';
            break;
        case 7:
            name = 'r';
            break;
        }
        whitePieces[index].setYDirection(1);
        whitePieces[index].setXDirection(x);
        whitePieces[index].setType(toupper(name));
        whitePieces[index].setAlive(true);

        blackPieces[index].setYDirection(8);
        blackPieces[index].setXDirection(x);
        blackPieces[index].setType(name);
        blackPieces[index].setAlive(true);

        ++index;
    }

    for (int x = 0; x < 8; ++x)
    {
        whitePieces[index].setYDirection(2);
        whitePieces[index].setXDirection(x);
        whitePieces[index].setType('P');
        whitePieces[index].setAlive(true);

        blackPieces[index].setYDirection(7);
        blackPieces[index].setXDirection(x);
        blackPieces[index].setType('p');
        blackPieces[index].setAlive(true);
        ++index;
    }

    // Generating board using whitePieces vector and blackPieces vector
    int indexW = 15;
    int indexB = 0;

    board.resize(8);
    for (int y = board.size() - 1; y >= 0; --y)
    {
        board[y].resize(8);
        for (int x = 0; x < board[y].size(); ++x)
        {
            if (y == 0 || y == 1)
            {
                board[y][x] = whitePieces[indexW].getPieceType();
                --indexW;
            }
            else if (y == 6 || y == 7)
            {
                board[y][x] = blackPieces[indexB].getPieceType();
                ++indexB;
            }
            else
                board[y][x] = '.';
        }
    }

    // Changing Q and K so that they are not in the same line
    whitePieces[4].setType('Q');
    whitePieces[3].setType('K');
    blackPieces[4].setType('k');
    blackPieces[3].setType('q');
}

// Constructor for generate a piece
Board::Piece::Piece(int _x = 0, int _y = 0, char _type = '0', bool _alive = true)
{
    // Assigning values to variables by checking if they are valid
    pieceType = _type;
    if (isValidPiece(_x) && isValidPiece(_y))
    {
        pos.resize(2);
        pos[0] = _x;
        pos[1] = _y;
    }
    else
    {
        cout << "Piece cannot generated as requested!!!";
        exit(1);
    }
}

// Display the board in the screen
void Board::drawBoard() const
{
    for (int i = board.size() - 1; i >= 0; --i)
    {
        cout << i + 1 << " | ";
        for (int j = 0; j < board[i].size(); ++j)
            cout << board[i][j] << "  ";
        cout << endl;
    }
    cout << "    -----------------------\n";
    cout << "    a  b  c  d  e  f  g  h\n\n";
}

// Write the board to a file which is taken filename as a parameter
void Board::drawBoard(string filename) const
{
    ofstream fout;
    fout.open(filename, ios::app);

    // If file has opened succesfully
    if (fout.is_open())
    {
        for (int i = board.size() - 1; i >= 0; --i)
        {
            fout << i + 1 << " | ";

            for (int j = 0; j < board[i].size(); ++j)
            {
                fout << board[i][j] << "  ";
            }
            fout << endl;
        }

        fout << "    -----------------------\n";
        fout << "    a  b  c  d  e  f  g  h\n\n";

        fout.close();
    }
    else
    {
        cerr << "Board could not write to a " << filename << " !\n";
    }
}

// Getting input from a user
void Board::getInput()
{
    string input;
    string outputFileName = "output.txt";
    int px, py, nx, ny;
    bool isValid = true;
    bool gameOver = false;

    // while game is not over, continue
    while (!gameOver)
    {
        do
        {
            drawBoard();

            if (Board::isWhitesTurn)
                cout << "[White's Turn]\n";
            else
                cout << "[Black's Turn]\n";

            // Getting input
            cout << "Enter your move: ";
            getline(cin, input);

            if (input.size() == 4)
            {
                px = charToInt(input[0]);
                py = charToInt(input[1]);
                nx = charToInt(input[2]);
                ny = charToInt(input[3]);
            }
            else if (input == "suggest")
            {
                cout << "Suggestion is: " << getSuggest() << endl
                     << endl;
                isValid = false;
                continue;
            }
            else
            {
                cout << "Try to enter valid input!!!\n";
                isValid = false;
                continue;
            }
            cout << endl
                 << endl;

            // Condition for checking if piece are picked correctly
            if ((isWhitesTurn && !isWhite(px, py)) || (!isWhitesTurn && !isBlack(px, py)))
            {
                cout << "You must pick your pieces!!!\n";
                isValid = false;
            }

            // Conditions for checking if input is valid
            else if (isValidInput(px) && isValidInput(nx) && isValidInput(py) && isValidInput(ny))
            {
                isValid = setBoard(px, py, nx, ny);
            }
            else
            {
                cout << "Invalid input! Try Again!!!\n";
                isValid = false;
            }
        } while (!isValid);

        // Drawing board to a file
        drawBoard(outputFileName);

        if (isGameOver())
            gameOver = true;

        // Changing a turn between white and black
        if (Board::isWhitesTurn)
            Board::isWhitesTurn = false;
        else
            Board::isWhitesTurn = true;
    }

    // If game is over calculate score and display it
    int whiteScore = calculateScore('W');
    int blackScore = calculateScore('B');

    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;

    // A condition to determine a winner
    if (whiteScore > blackScore)
        cout << "White won!!!\n";
    else if (blackScore > whiteScore)
        cout << "Black won!!!\n";
    else
        cout << "Draw!!!\n";
}

// Getting input from file
void Board::getInput(string filename)
{
    ifstream fin;

    // Opening file to be read the file
    fin.open(filename, ios::in);

    // a string variable for drawing a board to a file
    string outputFileName = "output.txt";
    string input;
    int px, py, nx, ny;

    // If it is opend succesfully
    if (fin.is_open())
    {

        // Getting line as a input and assign them to a variables
        while (getline(fin, input))
        {
            px = charToInt(input[0]);
            py = charToInt(input[1]);
            nx = charToInt(input[2]);
            ny = charToInt(input[3]);

            // Checking inputs if they are valid and calling setBoard() function to change the board
            if (isValidInput(px) && isValidInput(nx) && isValidInput(py) && isValidInput(ny))
                setBoard(px, py, nx, ny);

            if (Board::isWhitesTurn)
                Board::isWhitesTurn = false;
            else
                Board::isWhitesTurn = true;

            drawBoard(outputFileName);
        }
    }
    fin.close();
}

// A function that converts integer to a string form
string Board::getSuggest(int px, int py, int nx, int ny) const
{
    char p = static_cast<char>(px + 97);
    char n = static_cast<char>(nx + 97);
    return p + to_string(py) + n + to_string(ny);
}

// A function that gives a suggestion
string Board::getSuggest() const
{
    string suggestion;
    int px, py, nx, ny;
    int minScore(1000);
    const vector<Piece> &pieces = (isWhitesTurn) ? whitePieces : blackPieces;
    char enemyType = (isWhitesTurn) ? 'B' : 'W';

    // Trying to find a minimum enemy score by checking the all valid conditions
    for (int i = 0; i < pieces.size(); ++i)
    {
        if (pieces[i].getAlive())
        {
            for (int x = 0; x < 8; ++x)
            {
                for (int y = 1; y <= 8; ++y)
                {
                    int currx = pieces[i].getXDirection();
                    int curry = pieces[i].getYDirection();

                    // If movement is valid and a way is clear which is checking if
                    // this is valid condition, then calculating score to find minimum enemy score
                    if (isValidMovement(currx, curry, x, y) && isClear(currx, curry, x, y))
                    {
                        int enemyScore = calculateScore(enemyType);
                        if (enemyScore < minScore)
                        {
                            minScore = enemyScore;
                            px = currx;
                            py = curry;
                            nx = x;
                            ny = y;
                        }
                    }
                }
            }
        }
    }

    // Giving a suggestion as a string
    suggestion = getSuggest(px, py, nx, ny);
    return suggestion;
}

// A function that convert char to integer
int Board::charToInt(char c)
{
    int value = -1; // Sentinel value

    switch (c)
    {
    case 'a':
        value = 0;
        break;
    case '1':
    case 'b':
        value = 1;
        break;
    case '2':
    case 'c':
        value = 2;
        break;
    case '3':
    case 'd':
        value = 3;
        break;
    case '4':
    case 'e':
        value = 4;
        break;
    case '5':
    case 'f':
        value = 5;
        break;
    case '6':
    case 'g':
        value = 6;
        break;
    case '7':
    case 'h':
        value = 7;
        break;
    case '8':
        value = 8;
        break;
    default:
        break;
    }

    return value;
}

// A function that checks if input is valid
bool Board::isValidInput(int v) const
{
    if (v < 0 || v > 8)
        return false;
    return true;
}

// Function that gets piece from whitePieces or blakcPieces vectors by taking location of piece
int Board::getIndexOfPiece(int x, int y) const
{
    int index = -1; // Sentinel value
    const vector<Piece> &pieces = (isWhitesTurn) ? whitePieces : blackPieces;

    for (int i = 0; i < pieces.size(); ++i)
    {
        if (x == pieces[i].getXDirection() && y == pieces[i].getYDirection() && pieces[i].getAlive())
            index = i;
    }

    return index;
}

// Function that gets piece from whitePieces or blakcPieces vectors by taking type of piece
int Board::getIndexOfPiece(char type) const
{
    int index = -1; // Sentinel value
    const vector<Piece> &pieces = (isWhitesTurn) ? blackPieces : whitePieces;

    for (int i = 0; i < pieces.size(); ++i)
    {
        if (type == pieces[i].getPieceType() && pieces[i].getAlive())
            index = i;
    }

    return index;
}

// A function that sets the board with direction that are taken as a parameter
bool Board::setBoard(int px, int py, int nx, int ny)
{
    int indexW = 0;
    int indexB = 0;
    bool isDone = false; // Flag to determine if move is valid
    int indexOfKing = 0;

    if (Board::isWhitesTurn)
    {
        // Determining location of enemy king to determine is king is check
        int index = getIndexOfPiece('k');
        int kx = blackPieces[index].getXDirection();
        int ky = blackPieces[index].getYDirection();

        indexW = getIndexOfPiece(px, py);

        // Checking if movement is valid
        if (isValidMovement(px, py, nx, ny))
        {
            if (isBlack(nx, ny))
            {
                for (int i = 0; i < 15; ++i)
                {
                    if (blackPieces[i].getXDirection() == nx && blackPieces[i].getYDirection() == ny)
                    {
                        blackPieces[i].setType('.');    // If piece is eleminated, making type of piece '.'
                        blackPieces[i].setAlive(false); // If piece is eleminated, making alive false
                        break;
                    }
                }
            }

            // Rearrange a board with new state
            whitePieces[indexW].setXDirection(nx);
            whitePieces[indexW].setYDirection(ny);
            board[py - 1][px] = '.';
            board[ny - 1][nx] = whitePieces[indexW].getPieceType();
            isDone = true;

            // If king is underattack, display "check!" massage to warn players
            if (isUnderAttack(kx, ky))
            {
                cout << "Check!\n";
            }
        }
        else
        {
            cout << "Invalid Movement! Try Again!!!\n";
            isDone = false;
        }
    }
    else
    {
        // Determining location of enemy king to determine is king is check
        int index = getIndexOfPiece('K');
        int kx = whitePieces[index].getXDirection();
        int ky = whitePieces[index].getYDirection();

        indexB = getIndexOfPiece(px, py);

        // Checking if movement is valid
        if (isValidMovement(px, py, nx, ny))
        {
            if (isWhite(nx, ny))
            {
                for (int i = 0; i < 15; ++i)
                {
                    if (whitePieces[i].getXDirection() == nx && whitePieces[i].getYDirection() == ny)
                    {
                        whitePieces[i].setType('.');    // If piece is eleminated, making type of piece '.'
                        whitePieces[i].setAlive(false); // If piece is eleminated, making alive false
                        break;
                    }
                }
            }

            // Rearrange a board with new state
            blackPieces[indexB].setXDirection(nx);
            blackPieces[indexB].setYDirection(ny);
            board[py - 1][px] = '.';
            board[ny - 1][nx] = blackPieces[indexB].getPieceType();
            isDone = true;

            // If king is underattack, display "check!" massage to warn players
            if (isUnderAttack(kx, ky))
            {
                cout << "Check!\n";
            }
        }
        else
        {
            cout << "Invalid Movement! Try Again!!!\n";
            isDone = false;
        }
    }

    return isDone;
}

// A function that checks if movement is valid
bool Board::isValidMovement(int px, int py, int nx, int ny) const
{
    int IndexOfPiece = getIndexOfPiece(px, py);
    char typeOfPiece;
    bool isValid = false;

    // If index is sentinel value, return false
    if (IndexOfPiece == -1)
        return false;

    // Determining which pieces will be using to check if it is valid during movement
    if (isWhitesTurn)
        typeOfPiece = whitePieces[IndexOfPiece].getPieceType();
    else
        typeOfPiece = blackPieces[IndexOfPiece].getPieceType();

    // Determining if movement is valid by checking all state
    // Lovercase letters indicate black pieces, uppercase letters indicate white pieces
    switch (typeOfPiece)
    {
    case 'r':
        if (isBlack(nx, ny))
            isValid = false;
        else if (isWhite(nx, ny))
        {
            if (isClear(px, py, nx, ny) && ((px == nx && py != ny) || (px != nx && py == ny)))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny) && ((px == nx && py != ny) || (px != nx && py == ny)))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'R':
        if (isWhite(nx, ny))
            isValid = false;
        else if (isBlack(nx, ny))
        {
            if (isClear(px, py, nx, ny) && ((px == nx && py != ny) || (px != nx && py == ny)))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny) && ((px == nx && py != ny) || (px != nx && py == ny)))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'n':
        if (isBlack(nx, ny))
            isValid = false;
        else if (isWhite(nx, ny))
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx + 1 && py == ny - 2) || (px == nx - 1 && py == ny - 2) ||
                    (px == nx + 1 && py == ny + 2) || (px == nx - 1 && py == ny + 2) ||
                    (px == nx - 2 && py == ny + 1) || (nx == nx - 2 && py == ny + 1) ||
                    (px == nx + 2 && py == ny - 1) || (px == nx + 2 && py == ny - 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx + 1 && py == ny - 2) || (px == nx - 1 && py == ny - 2) ||
                    (px == nx + 1 && py == ny + 2) || (px == nx - 1 && py == ny + 2) ||
                    (px == nx - 2 && py == ny + 1) || (nx == nx - 2 && py == ny + 1) ||
                    (px == nx + 2 && py == ny - 1) || (px == nx + 2 && py == ny - 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        break;

    case 'N':
        if (isWhite(nx, ny))
            isValid = false;
        else if (isBlack(nx, ny))
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx + 1 && py == ny - 2) || (px == nx - 1 && py == ny - 2) ||
                    (px == nx + 1 && py == ny + 2) || (px == nx - 1 && py == ny + 2) ||
                    (px == nx - 2 && py == ny + 1) || (nx == nx - 2 && py == ny + 1) ||
                    (px == nx + 2 && py == ny - 1) || (px == nx + 2 && py == ny - 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx + 1 && py == ny - 2) || (px == nx - 1 && py == ny - 2) ||
                    (px == nx + 1 && py == ny + 2) || (px == nx - 1 && py == ny + 2) ||
                    (px == nx - 2 && py == ny + 1) || (nx == nx - 2 && py == ny + 1) ||
                    (px == nx + 2 && py == ny - 1) || (px == nx + 2 && py == ny - 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        break;

    case 'b':
        if (isBlack(nx, ny))
            isValid = false;
        else if (isWhite(nx, ny))
        {
            if (isClear(px, py, nx, ny) && (abs(px - nx) == abs(ny - py)))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny) && (abs(px - nx) == abs(ny - py)))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'B':
        if (isWhite(nx, ny))
            isValid = false;
        else if (isBlack(nx, ny))
        {
            if (isClear(px, py, nx, ny) && (abs(px - nx) == abs(ny - py)))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny) && (abs(px - nx) == abs(ny - py)))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'q':
        if (isBlack(nx, ny))
            isValid = false;
        else if (isWhite(nx, ny))
        {
            if (isClear(px, py, nx, ny))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'Q':
        if (isWhite(nx, ny))
            isValid = false;
        else if (isBlack(nx, ny))
        {
            if (isClear(px, py, nx, ny))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'k':
        if (isBlack(nx, ny))
            isValid = false;
        else if (isWhite(nx, ny))
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx && py == ny - 1) || (px == nx && py == ny + 1) ||
                    (px == nx - 1 && py == ny - 1) || (px == nx - 1 && py == ny) || (px == nx - 1 && py == ny + 1) ||
                    (px == nx + 1 && py == ny - 1) || (px == nx + 1 && py == ny) || (px == nx + 1 && py == ny + 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx && py == ny - 1) || (px == nx && py == ny + 1) ||
                    (px == nx - 1 && py == ny - 1) || (px == nx - 1 && py == ny) || (px == nx - 1 && py == ny + 1) ||
                    (px == nx + 1 && py == ny - 1) || (px == nx + 1 && py == ny) || (px == nx + 1 && py == ny + 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        break;

    case 'K':
        if (isWhite(nx, ny))
            isValid = false;
        else if (isBlack(nx, ny))
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx && py == ny - 1) || (px == nx && py == ny + 1) ||
                    (px == nx - 1 && py == ny - 1) || (px == nx - 1 && py == ny) || (px == nx - 1 && py == ny + 1) ||
                    (px == nx + 1 && py == ny - 1) || (px == nx + 1 && py == ny) || (px == nx + 1 && py == ny + 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny))
            {
                if ((px == nx && py == ny - 1) || (px == nx && py == ny + 1) ||
                    (px == nx - 1 && py == ny - 1) || (px == nx - 1 && py == ny) || (px == nx - 1 && py == ny + 1) ||
                    (px == nx + 1 && py == ny - 1) || (px == nx + 1 && py == ny) || (px == nx + 1 && py == ny + 1))
                    isValid = true;
            }
            else
                isValid = false;
        }
        break;

    case 'p':
        if (isBlack(nx, ny))
            isValid = false;
        else if (isWhite(nx, ny))
        {
            if (isClear(px, py, nx, ny) && ((px == nx + 1 && py == ny + 1) || (px == nx - 1 && py == ny + 1)))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny) && ((px == nx && py == ny + 2 && py == 7) || (px == nx && py == ny + 1)))
                isValid = true;
            else
                isValid = false;
        }
        break;

    case 'P':
        if (isWhite(nx, ny))
            isValid = false;
        else if (isBlack(nx, ny))
        {
            if (isClear(px, py, nx, ny) && ((px == nx + 1 && py == ny - 1) || (px == nx - 1 && py == ny - 1)))
                isValid = true;
            else
                isValid = false;
        }
        else
        {
            if (isClear(px, py, nx, ny) && ((px == nx && py == ny - 2 && py == 2) || (px == nx && py == ny - 1)))
                isValid = true;
            else
                isValid = false;
        }
        break;

    default:
        isValid = false;
    }

    return isValid;
}

// A function that checks if piece is black
bool Board::isBlack(int x, int y) const
{
    switch (board[y - 1][x])
    {
    case 'r':
    case 'n':
    case 'b':
    case 'q':
    case 'p':
        return true;
    }
    return false;
}

// A function that checks if piece is white
bool Board::isWhite(int x, int y) const
{
    switch (board[y - 1][x])
    {
    case 'R':
    case 'N':
    case 'B':
    case 'Q':
    case 'P':
        return true;
    }
    return false;
}

// A function that checks if a way beetween new location and previous location is clear
// which means there are no pieces beetween those
bool Board::isClear(int px, int py, int nx, int ny) const
{
    bool isClear = true;
    int start, end;
    int IndexOfPiece = getIndexOfPiece(px, py);
    char typeOfPiece;

    // If index is sentinel value, return false
    if (IndexOfPiece == -1)
        return false;

    // Determining which pieces will be using to check if it is valid during movement
    if (isWhitesTurn)
        typeOfPiece = whitePieces[IndexOfPiece].getPieceType();
    else
        typeOfPiece = blackPieces[IndexOfPiece].getPieceType();

    // Determining if movement is valid by checking all state
    // Lovercase letters indicate black pieces, uppercase letters indicate white pieces
    switch (typeOfPiece)
    {
    case 'r':
    case 'R':
        if (px == nx)
        {
            start = min(py, ny);
            end = max(py, ny);
            for (int i = start; i < end - 1; ++i)
            {
                if (board[i][px] != '.')
                    isClear = false;
            }
        }
        else
        {
            start = min(px, nx);
            end = max(px, nx);
            for (int i = start + 1; i <= end - 1; ++i)
            {
                if (board[py - 1][i] != '.')
                    isClear = false;
            }
        }
        break;

    case 'n':
    case 'N':
        isClear = true;
        break;

    case 'b':
    case 'B':
        for (int i = 1; i < abs(px - nx); ++i)
        {
            if (py < ny && px < nx)
            {
                if (board[py - 1 + i][px + i] != '.')
                    isClear = false;
            }
            else if (py < ny && px > nx)
            {
                if (board[py - 1 + i][px - i] != '.')
                    isClear = false;
            }
            else if (py > ny && px < nx)
            {
                if (board[py - 1 - i][px + i] != '.')
                    isClear = false;
            }
            else if (py > ny && px > nx)
            {
                if (board[py - 1 - i][px - i] != '.')
                    isClear = false;
            }
        }
        break;

    case 'q':
    case 'Q':
        if (px == nx && py != ny)
        {
            start = min(py, ny);
            end = max(py, ny);
            for (int i = start; i < end - 1; ++i)
            {
                if (board[i][px] != '.')
                    isClear = false;
            }
        }
        else if (px != nx && py == ny)
        {
            start = min(px, nx);
            end = max(px, nx);
            for (int i = start + 1; i <= end - 1; ++i)
            {
                if (board[py - 1][i] != '.')
                    isClear = false;
            }
        }
        else
        {
            for (int i = 1; i < abs(px - nx); ++i)
            {
                if (py < ny && px < nx)
                {
                    if (board[py - 1 + i][px + i] != '.')
                        isClear = false;
                }
                else if (py < ny && px > nx)
                {
                    if (board[py - 1 + i][px - i] != '.')
                        isClear = false;
                }
                else if (py > ny && px < nx)
                {
                    if (board[py - 1 - i][px + i] != '.')
                        isClear = false;
                }
                else if (py > ny && px > nx)
                {
                    if (board[py - 1 - i][px - i] != '.')
                        isClear = false;
                }
            }
        }
        break;

    case 'p':
        if (isWhite(nx, ny))
        {
            if ((px == nx + 1 && py == ny + 1) || (px == nx - 1 && py == ny + 1))
                isClear = true;
            else
                isClear = false;
        }
        else
        {
            if ((px == nx && py == ny + 2 && py == 7) || (px == nx && py == ny + 1))
                isClear = true;
            else
                isClear = false;
        }
        break;

    case 'P':
        if (isBlack(nx, ny))
        {
            if (((px == nx + 1 && py == ny - 1) || (px == nx - 1 && py == ny - 1)))
                isClear = true;
            else
                isClear = false;
        }
        else
        {
            if (((px == nx && py == ny - 2 && py == 2) || (px == nx && py == ny - 1)))
                isClear = true;
            else
                isClear = false;
        }
        break;
    default:
        isClear = true;
    }
    return isClear;
}

// A function that checks if piece is under attack
bool Board::isUnderAttack(int px, int py) const
{
    bool isUnderAttack = false;
    const vector<Piece> &pieces = (isWhitesTurn) ? whitePieces : blackPieces;

    // Getting location of piece to check if it is under attack
    for (int i = 0; i < pieces.size(); ++i)
    {
        int x = pieces[i].getXDirection();
        int y = pieces[i].getYDirection();

        // Checking if movement is valid, a way is clear and the piece is alive
        if (isValidMovement(x, y, px, py) && isClear(x, y, px, py) && pieces[i].getAlive())
        {
            isUnderAttack = true;
            break;
        }
    }

    return isUnderAttack;
}

// A function that checks if game is over
bool Board::isGameOver()
{
    bool isGameOver = true;
    int index, kx, ky;
    vector<Piece> &pieces = (isWhitesTurn) ? blackPieces : whitePieces;

    // Determining the locations of white-side king or black-side king by checking a turn
    if (Board::isWhitesTurn)
    {
        index = getIndexOfPiece('k');
        kx = blackPieces[index].getXDirection();
        ky = blackPieces[index].getYDirection();
    }
    else
    {
        index = getIndexOfPiece('K');
        kx = whitePieces[index].getXDirection();
        ky = whitePieces[index].getYDirection();
    }

    // If a king is under attack, checking there is any state
    // that can be performed to get rid of being under attack
    if (isUnderAttack(kx, ky))
    {
        for (int x = 0; x < 8; ++x)
        {
            for (int y = 1; y <= 8; ++y)
            {
                // Checking if there is any state by changing a location of a king
                // to get rid of being under attack, if there is at least one state
                // make isGameOver false
                if (isValidMovement(kx, ky, x, y) && isClear(kx, ky, x, y) && !isUnderAttack(x, y))
                {
                    isGameOver = false;
                    break;
                }
                else
                {
                    // There might be no state to get rid of changing a location of a king so that
                    // if there is any state that makes the king is not under attack by changing
                    // the location of a teammate piece. This algorithm is checking if there is
                    // any valid movement to make the king safe
                    for (int i = 0; i < pieces.size(); ++i)
                    {
                        if (pieces[i].getAlive())
                        {
                            for (int x = 0; x < 8; ++x)
                            {
                                for (int y = 1; y <= 8; ++y)
                                {
                                    int currx = pieces[i].getXDirection();
                                    int curry = pieces[i].getYDirection();

                                    if (isValidMovement(currx, curry, x, y) && isClear(currx, curry, x, y))
                                    {
                                        // If movement is valid and a way is clear, make a movement to check
                                        // if king is still under attack
                                        char tempType = pieces[i].getPieceType();
                                        int tempX = pieces[i].getXDirection();
                                        int tempY = pieces[i].getYDirection();
                                        pieces[i].setXDirection(x);
                                        pieces[i].setYDirection(y);

                                        board[tempY - 1][tempX] = '.';
                                        board[y - 1][x] = tempType;

                                        // If the king is still under attack, make isGameOver true
                                        if (isUnderAttack(kx, ky))
                                            isGameOver = true;
                                        // If the king is safe after movement which means there is at least
                                        // a state the king is safe, game is still going on
                                        else
                                        {
                                            isGameOver = false;
                                            board[tempY - 1][tempX] = tempType;
                                            board[y - 1][x] = '.';
                                            pieces[i].setXDirection(currx);
                                            pieces[i].setYDirection(curry);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
        isGameOver = false;

    return isGameOver;
}

// A function that checks if location of piece is valid
bool Board::Piece::isValidPiece(int v) const
{
    if (v < 0 || v > 8)
        return false;
    return true;
}

// Setter for x direction of a piece
void Board::Piece::setXDirection(int _x)
{
    // Checking if input is valid
    if (isValidPiece(_x))
        pos[0] = _x;
    else
        cout << "x couldn't change!";
}

// Setter for y direction of a piece
void Board::Piece::setYDirection(int _y)
{
    // Checking if input is valid
    if (isValidPiece(_y))
        pos[1] = _y;
    else
        cout << "x couldn't change!";
}

// Setter for type of a piece
void Board::Piece::setType(char _pieceType)
{
    pieceType = _pieceType;
}

// Setter for alive condition of a piece
void Board::Piece::setAlive(bool _alive)
{
    alive = _alive;

    // If piece is eliminaed, set the location -1 which is sentinel value
    if (!alive)
    {
        pos[0] = -1;
        pos[1] = -1;
    }
}

// A function that calculates score
// Type is 'W' which indicates white or 'B' which indicates black
int Board::calculateScore(char type) const
{
    int score = 0;

    const vector<Piece> &pieces = (type == 'W' || type == 'w') ? whitePieces : blackPieces;

    // Calculating score of each alive pieces, then add them up to score variable
    for (int i = 0; i < pieces.size(); ++i)
    {
        if (pieces[i].getAlive())
        {
            int x = pieces[i].getXDirection();
            int y = pieces[i].getYDirection();
            char c = pieces[i].getPieceType();

            int value = pieces[i].calculatePieceValue(c);

            // if any piece is under attack, reduce by half
            if (isUnderAttack(x, y))
                value -= value / 2;

            score += value;
        }
    }

    return score;
}

// A function that is used to determine a value of each piece
int Board::Piece::calculatePieceValue(char type) const
{
    int pieceValue = 0;

    // Determining a pieceValue by checking type of a piece
    switch (type)
    {
    case 'p':
    case 'P':
        pieceValue = 1;
        break;
    case 'n':
    case 'N':
        break;
    case 'b':
    case 'B':
        pieceValue = 3;
        break;
    case 'r':
    case 'R':
        pieceValue = 5;
        break;
    case 'q':
    case 'Q':
        pieceValue = 9;
        break;

    case 'k':
    case 'K':
        pieceValue = 200;
        break; // Random huge number to be understood its importance

    default:
        break;
    }

    return pieceValue;
}
