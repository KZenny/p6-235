/**
 * @class ChessBoard
 * @brief Represents an 8x8 board of Chess Pieces used to play chess
 */

#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "pieces_module.hpp"
#include "Move.hpp"

namespace BoardColorizer {
    /*
    Specify the colors we have color codes for.
    */
    const std::unordered_set<std::string> ALLOWED_COLORS({"BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE"});

    /**
     * Colors the given text using the specified color code.
     *
     * This function uses ANSI escape sequences to color the input text.
     *
     * @param text The text to be colored.
     * @param color The desired color name.
     * @return The colored text string, or the original text if the color is not found.
     */
    std::string colorText(const std::string& text, const std::string& color);
};
class ChessBoard {
    private:
        // Define board size (8x8)
        static const int BOARD_LENGTH = 8;
        
        bool playerOneTurn;
        
        std::string p1_color;
        std::string p2_color;

        // Track the board state & all pieces that were ever in play
        std::vector<std::vector<ChessPiece*>> board;
        std::list<ChessPiece*> pieces;

        std::stack<Move> past_moves_; // Stores all previously executed moves

    public:
        /**
         * Default / Parameterized constructor. 
         * @pre assignedColorP1 & assignedColorP2 represent colors present in the ALLOWED_COLORS list
         * 
         * @param assignedColorP1 A string denoting the color to use for Player One
         * @param assignedColorP2 A string denoting the color to use for Player Two
         * 
         * @post The board is setup with the following restrictions:
         * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
         *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
         *          - Pieces on the BOTTOM half of the board are set to be "moving up" | of color "BLACK"
         *          - Pieces on the UPPER half of the board are set to be NOT "moving up"| of color "WHITE"
         *          - Their row & col members reflect their position on the board
         *          - All other parameters are default initialized.
         *   
         *      - Pawns (P), Rooks(R), Bishops(B), Kings(K), Queens(Q), and Knights(N) are placed in the following format (ie. the standard setup for chess):
         *          
         *          7 | R N B K Q B N R
         *          6 | P P P P P P P P
         *          5 | * * * * * * * *
         *          4 | * * * * * * * *
         *          3 | * * * * * * * *
         *          2 | * * * * * * * *
         *          1 | P P P P P P P P
         *          0 | R N B K Q B N R
         *              +---------------
         *              0 1 2 3 4 5 6 7
         *      
         *          (With * denoting empty cells)
         * 
         * 2) playerOneTurn is set to true.
         * 3) p1_color is set to "BLACK", and p2_color is set to "WHITE" if not provided, or they are equal
         */
        ChessBoard(const std::string& assignedColorP1 = "BLACK", const std::string& assignedColorP2 = "WHITE");

        /**
         * Constructs a ChessBoard object.
         *
         * This constructor initializes the chessboard with the provided 2D vector of 
         * ChessPiece* pointers. It also tracks all non-null pieces on the board.
         *
         * @param instance The state of the chessboard to copy, represented as a 
         *                 2D vector of ChessPiece* pointers.
         * @param p1Turn   A boolean indicating whether it's Player 1's turn to play.
         */
        ChessBoard(const std::vector<std::vector<ChessPiece*>>& board, const bool& p1Turn);

        /**
         * @brief Getter for board_ member
         */
        std::vector<std::vector<ChessPiece*>> getBoardState() const;

        /**
        * @brief Moves the piece at (row,col) to (new_row, new_col), if possible
        * 
        * @return True if the move was successfullcol executed. 
        * 
        *      A move is possible if:
        *      1) (row,col) is a valid space on the board ( ie. within [0, BOARD_LENGTH) )
        *      2) There exists a piece at (row,col)
        *      3) The color of the piece equals the color of the current player whose turn it is
        *      4) The piece "can move" to the target location (new_row, new_col) 
        *           and (if applicable) the piece being captured is not of type "KING"
        * 
        *      Otherwise the move is invalid and nothing occurs / false is returned.
        * 
        * @post If the move is possible, it is executed
        *      - board is updated to reflect the move
        *      - The moved piece's row and col members are updated to reflect the move
        *      If a pawn is moved from its start position, its double_jumpable_ flag is set to false.. 
        */
        bool move(const int& x, const int& y, const int& new_x, const int& new_y);

        /**
         * @brief Gets the ChessPiece (if any) at (row, col) on the board
         * 
         * @param row The row of the cell
         * @param col The column of the cell
         * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
         */
        ChessPiece* getCell(const int& row, const int& col) const;

        /**
         * @brief Destructor. 
         * @post Deallocates all ChessPiece pointers that were ever used on the board.
         */
        ~ChessBoard();
        
        /**
         * @brief Utility display function that prints out colored text
         *        based on the players' colors
         * @pre P1_COLOR & P2_COLOR are exist 
         *      within the BoardColorizer ALLOWED_COLORS vector
         * 
         * @post Display row / column headers & symbols for pieces on the board
         *       where each piece is colored based on the color representing the 
         *       player they belong to
         */
        void display() const;

        /**
        * @brief Attempts to execute a round of play on the chessboard. A round consists of the 
         * following sequence of actions:
         * 
         * 1) Prompts the user to select a piece by entering two space-separated integers 
         *    or type anything else to undo the last move
         * 2) Records their input, or returns the result of attempting to undo the previous action
         * 3) Prompt the user to select a target square to move the piece 
         *    or type anything else to undo.
         * 4) Records their input, or returns the result of attempting to undo the previous action
         * 5) Attempt to execute the move, using move()
         * 6) If the move is successful, records the action by pushing a Move to past_moves_.
         * 7) If the move OR undo is successful, toggles the `playerOneTurn` boolean member of `ChessBoard`
         * 
         * @return Returns true if the round has been completed successfully, that is:
         *      - If a pieced was succesfully moved.
         *      - Or a move was successfully undone.
         * @post The `past_moves_` stack & `playerOneTurn` members are updated as described above
         */
        bool attemptRound();

        /**
         * @brief Reverts the most recent action executed by a player,
         *        if there is a `Move` object in the `past_moves_` stack
         * 
         *        This is done by updating the moved piece to its original
         *        position, and the captured piece (if applicable) to the target
         *        position specified by the `Move` object at the top of the stack
         * 
         * @return True if the action was undone succesfully.
         *         False otherwise (ie. if there are no moves to undo)
         * 
         * @post 1) Reverts the `board` member's pointers to reflect
         *          the board state before the most recent move, if possible. 
         *       2) Updates the row / col members of each involved `ChessPiece` 
         *          (ie. the moved & captured pieces) to match their reverted 
         *          positions on the board
         *       3) The most recent `Move` object is removed from the `past_moves_`
         *          stack 
         */ 
        bool undo();

        bool isPlayerOneTurn() const;
};