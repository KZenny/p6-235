#include <iostream>
#include <vector>
#include <string>
#include "ChessBoard.hpp"
#include "pieces/Queen.hpp"

int main() {
    // Initialize the chessboard
    ChessBoard board("BLACK", "WHITE");

    // Display the initial board
    std::cout << "Initial Chessboard:\n";
    board.display();

    board.attemptRound();
    board.display();
    std::cout << board.isPlayerOneTurn() << std::endl;

    board.attemptRound();
    board.display();
    std::cout << board.isPlayerOneTurn() << std::endl;
    return 0;
}
