#include <iostream>
#include <stdexcept>

#include "CustomFunctions.h"

int main() {
    std::string file_name = "input2D_float.txt";
    std::vector<std::string> text = read_file(file_name);

    std::vector<Point> points = strings_to_points(text);

    int user_input;
    std::cout << "Select function" << std::endl;
    std::cout << "1) Print data points" << std::endl;
    std::cout << "2) Print magnitude of data points" << std::endl;
    while (!(std::cin >> user_input) || user_input < 1 || user_input > 2) {
        std::cout << "Invalid input. Please enter a valid option: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int n;
    std::cout << "Enter a value of n (number of lines): ";
    while (!(std::cin >> n) || n < 1) {
        std::cout << "Invalid input. Please enter a positive non-zero integer: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    switch (user_input) {
        case 1: {
            print_n_lines(points, n);
            break;
        }
        case 2: {
            std::vector<float> magnitudes = calculate_magnitude(points);
            print_n_lines(magnitudes, n);
            break;
        }
        default:
            throw std::runtime_error("Error: Invalid value for user_input");
    }

    std::vector<std::string> data_linear_fit;
    data_linear_fit.push_back(linear_fit(points));
    print_n_lines(data_linear_fit, 1);
}