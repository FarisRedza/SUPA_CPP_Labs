#include <iostream>
#include <vector>
#include <sstream>
#include <climits>

#include "CustomFunctions.h"

// For the program's menu, can add more options but keep All and Quit as last two, and values must be continuous ints i.e. 1,2,3
// Intended to use enum as a safeguard to prevent invalid input from breaking the program like I would do in rust, but couldn't
// quite achieve the same effect, and is a little redundant now with the other guards I've put in place, kept it around though
// for nicer readability in the switch and not worrying about what number maps to which operation
enum Operations {
    PrintDataPoints = 1,
    CalcMagDataPoints,
    FitLineDataPoints,
    PowerDataPoints,
    All,
    Quit = 0
};
std::vector<std::string> menu_options = {
    std::to_string(Operations::PrintDataPoints) + ") Print data points" ,
    std::to_string(Operations::CalcMagDataPoints) + ") Calculate magnitude of data points",
    std::to_string(Operations::FitLineDataPoints) + ") Fit straight line to data points",
    std::to_string(Operations::PowerDataPoints) + ") Raise x to the power of y for each data point",
    std::to_string(Operations::All) + ") All of the above",
    std::to_string(Operations::Quit) + ") Quit",
};
// Get integer input from user in range min <= x < max
int get_int_input(int range_min, int range_max, std::string invalid_input_msg) {
    std::string user_input_string;
    int user_int;
    
    while (true) {
        std::getline(std::cin, user_input_string);
        std::stringstream inputStream(user_input_string);

        // Try to parse input as a valid integer
        if (inputStream >> user_int && inputStream.eof() && range_min <= user_int && user_int < range_max) {
            return user_int;
        }

        std::cout << "Invalid input: " << invalid_input_msg << std::endl;
    }
}

int main() {
    std::string data_file_name = "input2D_float.txt";
    std::vector<std::string> data = read_file(data_file_name);
    std::vector<Point> data_points = strings_to_points(data);

    std::string error_file_name = "error2D_float.txt";
    std::vector<std::string> error = read_file(error_file_name);
    std::vector<Point> error_points = strings_to_points(error);

    int data_size = data_points.size();
    std::cout << "Found " << data_size << " data points" << std::endl;

    enum Operations user_operation;
    bool take_user_input = true;
    int user_input;
    
    while (true) {
        if (take_user_input == false) {
            user_input++;
            if (user_input == menu_options.size() - 1) {
                // Finished iterating through each operation
                take_user_input = true;
            }
        }
        if (take_user_input == true) {
            std::cout << "Select operation:" << std::endl;
            print_n_lines(menu_options, menu_options.size());

            user_input = get_int_input(0, menu_options.size(), "Please enter one of the options listed");
        }

        user_operation = (Operations)user_input;
        switch (user_operation) {
            case PrintDataPoints: {
                std::cout << "Printing data points" << std::endl;
                std::cout << "How many data points would you like to print?: ";
                int n = get_int_input(1, INT_MAX, "Please enter a positive integer"); // Reusing this function and using INT_MAX so I don't have to rewrite int input handling
                print_n_lines(data_points, n);
                break;
            }
            case CalcMagDataPoints: {
                std::cout << "Calculating magnitude of data points" << std::endl;
                std::vector<float> magnitudes = calculate_magnitude(data_points);
                print_n_lines(magnitudes, data_size);
                write_vec_to_file(magnitudes, "Outputs/magnitudes.txt");
                break;
            }
            case FitLineDataPoints: {
                std::cout << "Fitting straight line to data points" << std::endl;
                std::vector<std::string> data_linear_fit;
                data_linear_fit.push_back(least_squares(data_points, error_points));
                print_n_lines(data_linear_fit, 1);
                write_vec_to_file(data_linear_fit, "Outputs/linear_fit.txt");
                break;
            }
            case PowerDataPoints: {
                std::cout << "Raising x to the power of y for each data point" << std::endl;
                std::vector<float> results(data_size);
                for (int i = 0; i < data_size; i++) {
                    results[i] = power(data_points[i].x, std::round(data_points[i].y));
                }
                print_n_lines(results, data_size);
                write_vec_to_file(results, "Outputs/power_results.txt");
                break;
            }
            case All: {
                // Allows for while loop to iterate through each operation
                take_user_input = false;
                user_input = 0;
                break;
            }
            case Quit: {
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            default:
                throw std::runtime_error("Error: Invalid value for user_operation");
        }
    }
}