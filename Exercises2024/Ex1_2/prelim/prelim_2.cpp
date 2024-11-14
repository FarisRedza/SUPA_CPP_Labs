#include <iostream>
#include <cmath>

int main() {
    float x = 2.3;
    float y = 4.5;

    float vec_magnitude = sqrt(pow(x,2) + pow(y,2));
    std::cout << vec_magnitude << std::endl;
}