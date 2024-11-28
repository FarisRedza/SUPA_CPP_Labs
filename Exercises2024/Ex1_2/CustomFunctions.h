#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

struct Point {
    float x;
    float y;

    friend std::ostream& operator<<(std::ostream &os, const Point &point); //For printing
};

std::vector<std::string> read_file(std::string file_name); //Reads a file and returns a vector of strings

std::vector<Point> strings_to_points(std::vector<std::string> text); //Converts strings to Point structs

std::vector<float> calculate_magnitude(std::vector<Point> points); //Returns the magnitude of a Point

//Prints each element in a vector as a separate line
template<typename T>
void print_n_lines(std::vector<T> vec, int n) {
    if (vec.size() > n) {
        std::cout << "Warning: Vector size " << vec.size() << " greater than " << n << ", limiting to 5 lines" << std::endl;
        n = 5;
    }
    for (int i = 0; i < vec.size() && i < n; i++) {
        std::cout << vec[i] << std::endl;
    }
}

std::string least_squares(std::vector<Point> data_points, std::vector<Point> error_points); //Performs least squares fit on a vector of Point structs

float power(float x, int y); //Raise a float x to the power of an int y

//Write each element in a vector as a separate line in a file
template<typename T>
void write_vec_to_file(std::vector<T> vec, std::string file_name) {
    std::ofstream output_stream;
    output_stream.open(file_name);
        if (!output_stream.is_open()) {
            throw std::runtime_error("Error opening file: " + file_name);
        } else {
            std::cout << "Output file: " << file_name << " opened sucessfully" << std::endl;
            for (int i = 0; i < vec.size(); i++) {
                output_stream << vec[i] << std::endl;
            }
            std::cout << "Finished writing to file " << file_name << std::endl;
        }
        output_stream.close();
}