#include "CustomFunctions.h"

std::ostream& operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

std::vector<std::string> read_file(std::string file_name) {
    std::ifstream file(file_name);
    std::vector<std::string> text;
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file" << std::endl;
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

std::vector<Point> strings_to_points(std::vector<std::string> text) {
    std::vector<Point> points;
    for (std::string line : text) {
        std::stringstream ss(line);
        float x, y;
        char separator;

        if (ss >> x >> separator >> y && separator == ',') {
            points.push_back({x,y});
        }
    }
    return points;
}

std::vector<float> calculate_magnitude(std::vector<Point> points) {
    std::vector<float> magnitudes;
    for (Point point : points) {
        magnitudes.push_back(sqrt(pow(point.x,2) + pow(point.y,2)));
    }
    return magnitudes;
}

std::string linear_fit(std::vector<Point> points) {
    float sum_x, sum_y, sum_xy, sum_x2;
    for (Point point : points) {
        sum_x += point.x;
        sum_y += point.y;
        sum_xy += point.x * point.y;
        sum_x2 += pow(point.x,2);
    }

    int n = points.size();
    float p = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - pow(sum_x,2));
    float q = (sum_x2 * sum_y - sum_xy * sum_x) / (n * (sum_x2 - pow(sum_x,2)));

    return "y = " + std::to_string(p) + "x + " + std::to_string(q);
}