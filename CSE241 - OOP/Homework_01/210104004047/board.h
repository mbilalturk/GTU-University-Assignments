#ifndef BOARD_H
#define BOARD_H

#include <vector>
using namespace std;

// Board class
class Board {
    public:
        // Constructor for generating a board
        Board();

        // Getting input from user
        void getInput(); 

        // Getting input from file
        void getInput(string filename); 
        
        // Display the board in the screen
        void drawBoard() const;
        
        // Write the board to a file which is taken filename as a parameter
        void drawBoard(string filename) const; 

        // Inner class for holding pieces
        class Piece;
    private:
        // 2D vector to hold direction of board 
        vector<vector<char> > board;

        // A vector to hold a white pieces for player who plays with white pieces
        vector<Piece> whitePieces;

        // A vector to hold a black pieces for player who plays with black pieces
        vector<Piece> blackPieces;
        
        // A function that sets the board with direction that are taken as a parameter
        bool setBoard(int px, int py, int nx, int ny);

        // A function that checks if input is valid
        bool isValidInput(int v) const;

        // A function that checks if movement is valid
        bool isValidMovement(int px, int py, int nx, int ny) const;

        // A function that checks if a way beetween new location and previous location is clear
        // which means there are no pieces beetween those
        bool isClear(int px, int py, int nx, int ny) const;

        // A function that checks if piece is black
        bool isBlack(int x, int y) const;

        // A function that checks if piece is white
        bool isWhite(int x, int y) const;

        // A function that convert char to integer
        int charToInt(char c);

        // A function that checks if game is over
        bool isGameOver();

        // A function that checks if piece is under attack
        bool isUnderAttack(int px, int py) const;

        // A function that calculates score
        // Type is 'W' which indicates white or 'B' which indicates black 
        int calculateScore(char type) const;

        // Functions that get piece from whitePieces or blakcPieces vectors
        int getIndexOfPiece(int x, int y) const;
        int getIndexOfPiece(char type) const;

        // Functions that can be used to give a suggestion
        string getSuggest(int px, int py, int nx, int ny) const;
        string getSuggest() const;

        // Indicator to determine which player will play
        static bool isWhitesTurn;
};

// Inner class of Board class named Piece 
class Board::Piece {
    public:
        // Constructor for generate a piece
        Piece(int _x, int _y, char _type, bool _alive);

        // Getters for private variables
        int getXDirection() const { return pos[0]; }
        int getYDirection() const { return pos[1]; }
        char getPieceType() const { return pieceType; }
        bool getAlive() const { return alive; }

        // Setter for private variables
        void setXDirection(int _x);
        void setYDirection(int _y);
        void setType(char _pieceType);
        void setAlive(bool);

        // A function that is used to determine a value of each piece
        int calculatePieceValue(char type) const;        
    private:
        // A vector that holds position of piece
        vector<int> pos;
        
        // A variable to hold type of piece 
        char pieceType;

        // A variable that holds if piece is still alive
        bool alive;

        // A function that checks if location of piece is valid
        bool isValidPiece(int v) const;
};

#endif
