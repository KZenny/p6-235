#pragma once

#include <iostream> 
#include <utility> 
#include "pieces/ChessPiece.hpp" 
/** We alias a pair of integers as a square (or cell).
 * The `first` element in the pair corresponds to the `row`
 * and the second to the `column` */ 
 typedef std::pair<int,int> Square;

class Move {
    private:
        Square from_; // Represents the original square that `moved_piece_` started from
        Square to_; // Represents the destination square that `moved_piece_` moved to
        ChessPiece* moved_piece_;  // A pointer to the piece that moved
        ChessPiece* captured_piece_;  // A pointer to the piece that was captured (or nullptr if none)
    public: 
        Move() = delete; // Default constructor

        /**
         * Constructs a Move object representing a move on a chessboard.
         *
         * @param from A const ref. to a pair of integers (ie. "Square") representing
         *             the starting square of the move.
         * @param to A const ref. to a pair of integers (ie. "Square") representing
         *           the destination square of the move.
         * @param moved_piece A pointer to the ChessPiece that was moved.
         * @param captured_piece A pointer to the ChessPiece that was 
         *        captured during the move. Default value nullptr.
         *        Nullptr is also used if we have no piece that was captured.
         * @post The private members of the Move are updated accordingly.
         */
        Move(const Square& from, const Square& to, ChessPiece* moved_piece, ChessPiece* captured_piece = nullptr);

        /**
         * Gets the original position (starting square) of the move.
         * @return The original position as a Square (std::pair<int, int>).
         */
        Square getOriginalPosition() const;

        /**
         * Gets the target position (destination square) of the move.
         * @return The target position as a Square (std::pair<int, int>).
         */
        Square getTargetPosition() const;

        /**
         * Gets a pointer to the ChessPiece that was moved.
         * @return A pointer to the moved ChessPiece.
         */
        ChessPiece* getMovedPiece() const;

        /**
         * Gets a pointer to the ChessPiece that was captured during the move.
         * @return A pointer to the captured ChessPiece, or nullptr if no piece was captured.
         */
        ChessPiece* getCapturedPiece() const;
};

