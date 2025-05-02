#include "Move.hpp"

/**
* Constructs a Move object representing a move on a chessboard.
*
* @param from A const ref. to a pair of integers (ie. "Square") representing
*    the starting square of the move.
* @param to A const ref. to a pair of integers (ie. "Square") representing
*  the destination square of the move.
* @param moved_piece A pointer to the ChessPiece that was moved.
* @param captured_piece A pointer to the ChessPiece that was 
*        captured during the move. Default value nullptr.
*        Nullptr is also used if we have no piece that was captured.
* @post The private members of the Move are updated accordingly.
*/
Move::Move(const Square& from, const Square& to, ChessPiece* moved_piece, ChessPiece* captured_piece) : from_(from), to_(to), moved_piece_(moved_piece), captured_piece_(captured_piece) {}

/**
 * Gets the original position (starting square) of the move.
 * @return The original position as a Square (std::pair<int, int>).
 */
Square Move::getOriginalPosition() const {
    return from_;
}

 /**
  * Gets the target position (destination square) of the move.
  * @return The target position as a Square (std::pair<int, int>).
  */
Square Move::getTargetPosition() const {
    return to_;
}
 
 /**
  * Gets a pointer to the ChessPiece that was moved.
  * @return A pointer to the moved ChessPiece.
  */
ChessPiece* Move::getMovedPiece() const {
    return moved_piece_;
}
 
 /**
  * Gets a pointer to the ChessPiece that was captured during the move.
  * @return A pointer to the captured ChessPiece, or nullptr if no piece was captured.
  */
ChessPiece* Move::getCapturedPiece() const {
    return captured_piece_;
}