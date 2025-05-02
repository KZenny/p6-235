#include <iostream>

int main() {
    int initial_row, initial_col, selected_row, selected_col;
    std::cout << "[PLAYER 1] Select a piece (Enter two integers: '<row> <col>'), or any other input to undo the last action." << std::endl;
    std::cin >> initial_row >> initial_col;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cout << "UNDO" << std::endl;
        return 0;
    }

    std::cout << "[PLAYER 1] Specify a square to move to (Enter two integers: '<row> <col>'), or any other input to undo the last action." << std::endl;
    std::cin >> selected_row >> selected_col;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cout << "UNDO" << std::endl;
        return 0;
    }

    std::cout << "Moved (" << initial_row << "," << initial_col << ") to (" << selected_row << "," << selected_col << ")" << std::endl;

    return 0;
}