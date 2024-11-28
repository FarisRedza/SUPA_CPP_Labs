#include <iostream>
#include <stdexcept>
#include <limits>

#include "CustomFunctions.h"

// For the program's menu, can add more options but keep All and Quit as last two
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
    Quit
};
//Get integer input from user in range min <= x < max
int get_int_input(int range_min, int range_max) {
    int user_input = 0;
	bool valid_input = false;
    do {
        std::cin >> user_input;

        if (!(valid_input = std::cin.good() && range_min <= user_input && user_input < range_max)) {
            std::cout << "Invalid input, please try again\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (!valid_input);
    return user_input;
}

int main() {
    std::string data_file_name = "input2D_float.txt";
    std::vector<std::string> data = read_file(data_file_name);
    std::vector<Point> data_points = strings_to_points(data);

    std::string error_file_name = "error2D_float.txt";
    std::vector<std::string> error = read_file(error_file_name);
    std::vector<Point> error_points = strings_to_points(error);

    int data_size = data_points.size();

    enum Operations user_operation;

    bool running = true;
    bool take_user_input = true;
    int user_input;
    
    while (running == true) {
        if (take_user_input == false) {
            user_input++;
            if (user_input == menu_options.size() - 1) {
                // Finished iterating through each operation
                take_user_input = true;
            }
        }
        if (take_user_input == true) {
            std::cout << "Select function:" << std::endl;
            print_n_lines(menu_options, menu_options.size());

            user_input = get_int_input(0, menu_options.size());
        }

        user_operation = (Operations)user_input;
        switch (user_operation) {
            case 1: {
                std::cout << "Printing data points" << std::endl;
                print_n_lines(data_points, data_size);
                break;
            }
            case 2: {
                std::cout << "Calculating magnitude of data points" << std::endl;
                std::vector<float> magnitudes = calculate_magnitude(data_points);
                print_n_lines(magnitudes, data_size);
                write_vec_to_file(magnitudes, "Outputs/magnitudes.txt");
                break;
            }
            case 3: {
                std::cout << "Fitting straight line to data points" << std::endl;
                std::vector<std::string> data_linear_fit;
                data_linear_fit.push_back(least_squares(data_points, error_points));
                print_n_lines(data_linear_fit, 1);
                write_vec_to_file(data_linear_fit, "Outputs/linear_fit.txt");
                break;
            }
            case 4: {
                std::cout << "Raising x to the power of y for each data point" << std::endl;
                std::vector<float> results(data_size);
                for (int i = 0; i < data_size; i++) {
                    results[i] = power(data_points[i].x, std::round(data_points[i].y));
                }
                print_n_lines(results, data_size);
                write_vec_to_file(results, "Outputs/power_results.txt");
                break;
            }
            case 5: {
                // Allows for while loop to iterate through each operation
                take_user_input = false;
                user_input = 0;
                break;
            }
            case 0: {
                std::cout << "Goodbye!" << std::endl;
                running = false;
                break;
            }
            default:
                throw std::runtime_error("Error: Invalid value for user_input");
        }
    }
}