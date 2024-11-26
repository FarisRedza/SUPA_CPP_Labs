#include <iostream>
#include <stdexcept>

#include "CustomFunctions.h"

std::vector<std::string> menu_options = {
    "1) Print data points" ,
    "2) Print magnitude of data points",
    "3) Fit straight line to data points",
    "4) Raise x to the power of y for each data point",
    "5) All of the above",
};

int main() {
    std::string data_file_name = "input2D_float.txt";
    std::vector<std::string> data = read_file(data_file_name);
    std::vector<Point> data_points = strings_to_points(data);

    std::string error_file_name = "error2D_float.txt";
    std::vector<std::string> error = read_file(error_file_name);
    std::vector<Point> error_points = strings_to_points(error);

    int data_size = data_points.size();

    int user_input;
    std::cout << "Select function:" << std::endl;
    print_n_lines(menu_options, menu_options.size());
    while (!(std::cin >> user_input) || user_input < 1 || user_input > menu_options.size()) {
        std::cout << "Invalid input. Please enter a valid option:" << std::endl;
        print_n_lines(menu_options, menu_options.size());
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // std::cout << "Enter a value of n (number of lines): ";
    // while (!(std::cin >> data_size) || data_size < 1) {
    //     std::cout << "Invalid input. Please enter a positive non-zero integer: ";
    //     std::cin.clear(); 
    //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // }
    switch (user_input) {
        case 1: {
            print_n_lines(data_points, data_size);
            break;
        }
        case 2: {
            std::vector<float> magnitudes = calculate_magnitude(data_points);
            print_n_lines(magnitudes, data_size);
            break;
        }
        case 3: {
            std::vector<std::string> data_linear_fit;
            data_linear_fit.push_back(least_squares(data_points, error_points));
            print_n_lines(data_linear_fit, 1);
            break;
        }
        case 4: {
            std::vector<float> results(data_size);
            for (int i = 0; i < data_size; i++) {
                results[i] = power(data_points[i].x, std::round(data_points[i].y));
            }
            print_n_lines(results, data_size);
            break;
        }
        case 5: {
            break;
        }
        default:
            throw std::runtime_error("Error: Invalid value for user_input");
    }
}