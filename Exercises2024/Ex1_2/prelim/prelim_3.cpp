#include <iostream>
#include <cmath>

float vec_magnitude(float a, float b) {
    return sqrt(pow(a,2) + pow(b,2));
}

int main() {
    std::string user_value_a;
    std::string user_value_b;

    std::cout << "Enter a value for a: ";
    std::cin >> user_value_a;
    std::cout << "Enter a value for b: ";
    std::cin >> user_value_b;

    float user_float_a = std::stof(user_value_a);
    float user_float_b = std::stof(user_value_b);

    float result = vec_magnitude(user_float_a, user_float_b);
    std::cout << "Result = " << result << std::endl;
}