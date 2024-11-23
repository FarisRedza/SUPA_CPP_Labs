#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

struct Point {
    float x;
    float y;

    friend std::ostream& operator<<(std::ostream &os, const Point &point);
};

std::vector<std::string> read_file(std::string file_name);

std::vector<Point> strings_to_points(std::vector<std::string> text);

std::vector<float> calculate_magnitude(std::vector<Point> points);

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

std::string least_squares(std::vector<Point> data_points, std::vector<Point> error_points);