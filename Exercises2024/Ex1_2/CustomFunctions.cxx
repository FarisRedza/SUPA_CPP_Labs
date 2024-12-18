#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

#include "CustomFunctions.h"

// For printing Point structs
std::ostream& operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

// Reads a file and returns a vector of strings
std::vector<std::string> read_file(std::string file_name) {
    std::ifstream file(file_name);
    std::vector<std::string> text;
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + file_name);
    } else {
        std::cout << "Opening file " << file_name << std::endl;
        std::string line;
        while (getline(file, line)) {
            text.push_back(line);
        }
    file.close();
    }
    return text;
}

// Converts strings to Point structs
std::vector<Point> strings_to_points(std::vector<std::string> text) {
    std::vector<Point> points;
    for (std::string line : text) {
        std::stringstream ss(line);
        float x, y;
        char separator;

        if (ss >> x >> separator >> y && separator == ',') {
            points.push_back({x, y});
        }
    }
    return points;
}

// Returns the magnitude of a Point
std::vector<float> calculate_magnitude(std::vector<Point> points) {
    std::vector<float> magnitudes;
    for (Point point : points) {
        magnitudes.push_back(sqrt(pow(point.x, 2) + pow(point.y, 2)));
    }
    return magnitudes;
}

// Performs least squares fit on a vector of Point structs
std::vector<std::string> least_squares(std::vector<Point> data_points, std::vector<Point> error_points) {
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (Point data_point : data_points) { // Build up values using each data_point
        sum_x += data_point.x;
        sum_y += data_point.y;
        sum_xy += data_point.x * data_point.y;
        sum_x2 += pow(data_point.x, 2);
    }
    int n = data_points.size();
    float denominator = n * sum_x2 - pow(sum_x, 2);
    float p = (n * sum_xy - sum_x * sum_y) / denominator;
    float q = (sum_x2 * sum_y - sum_xy * sum_x) / denominator;

    // χ^2 test
    float expected_y, y_diff2, sigma2, chi2 = 0;
    for (int i = 0; i < n; i++) {
        expected_y = p * data_points[i].x + q;
        y_diff2 = pow(data_points[i].y - expected_y, 2);

        sigma2 = pow(error_points[i].y, 2) + pow(p * error_points[i].x, 2); // Account for x and y errors

        chi2 += y_diff2 / sigma2;
    }
    // Degrees of freedom
    int ndf = n - 2;
    float chi2_over_ndf = chi2 / ndf;

    std::vector<std::string> results = {
        "y = " + std::to_string(p) + "x + " + std::to_string(q),
        "χ^2 = " + std::to_string(chi2),
        "NDF = " + std::to_string(ndf),
        "χ^2/NDF = " + std::to_string(chi2_over_ndf)
    };
    // return "y = " + std::to_string(p) + "x + " + std::to_string(q) + "\nχ^2χ^2/NDF = " + std::to_string(chi2_over_ndf);
    return results;
}

// Raise a float x to the power of an int y
float power(float x, int y) {
    if (y == 0)
        return 1;

    if (y < 0)
        return 1 / power(x, -y);

    return x * power(x, y - 1);
}