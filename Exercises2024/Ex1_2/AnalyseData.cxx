#include <iostream>
#include <stdexcept>
#include <limits>

#include "CustomFunctions.h"

std::vector<std::string> menu_options = {
    "1) Print data points" ,
    "2) Calculate magnitude of data points",
    "3) Fit straight line to data points",
    "4) Raise x to the power of y for each data point",
    "5) All of the above",
    "0) Quit",
};

enum Operations {
    PrintDataPoints = 1,
    CalcMagDataPoints,
    FitLineDataPoints,
    PowerDataPoints,
    All,
    Quit = 0
};

int main() {
    std::string data_file_name = "input2D_float.txt";
    std::vector<std::string> data = read_file(data_file_name);
    std::vector<Point> data_points = strings_to_points(data);

    std::string error_file_name = "error2D_float.txt";
    std::vector<std::string> error = read_file(error_file_name);
    std::vector<Point> error_points = strings_to_points(error);

    int data_size = data_points.size();

    enum Operations user_operation;
    int input;
    bool running = true;
    bool take_user_input = true;
    while (running == true) {
        if (take_user_input == false) {
            input++;
            if (input == 5) {
                take_user_input = true;
            }
        }
        if (take_user_input == true) {
            std::cout << "Select function:" << std::endl;
            print_n_lines(menu_options, menu_options.size());
            std::cin >> input;
        }
        user_operation = static_cast<Operations>(input);
                switch (user_operation)
            {
            case 1: {
                std::cout << "Printing data points" << std::endl;
                print_n_lines(data_points, data_size);
                break;
            }
            case 2: {
                std::cout << "Calculating magnitude of data points" << std::endl;
                std::vector<float> magnitudes = calculate_magnitude(data_points);
                print_n_lines(magnitudes, data_size);
                write_vec_to_file(magnitudes, "magnitudes.txt");
                break;
            }
            case 3: {
                std::cout << "Fitting straight line to data points" << std::endl;
                std::vector<std::string> data_linear_fit;
                data_linear_fit.push_back(least_squares(data_points, error_points));
                print_n_lines(data_linear_fit, 1);
                write_vec_to_file(data_linear_fit, "linear_fit.txt");
                break;
            }
            case 4: {
                std::cout << "Raising x to the power of y for each data point" << std::endl;
                std::vector<float> results(data_size);
                for (int i = 0; i < data_size; i++) {
                    results[i] = power(data_points[i].x, std::round(data_points[i].y));
                }
                print_n_lines(results, data_size);
                write_vec_to_file(results, "power_results.txt");
                break;
            }
            case 5: {
                take_user_input = false;
                input = 0;
                break;
            }
            case 0: {
                std::cout << "Goodbye!" << std::endl;
                running = false;
                break;
            }
            default:
                std::cout << "Invalid input" << std::endl;
                break;
            }
    }
}