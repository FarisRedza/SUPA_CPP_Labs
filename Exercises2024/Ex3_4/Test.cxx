#include <iostream>
#include <bits/stdc++.h>
#include <vector>

#include "FiniteFunctions.h"
#include "../Ex1_2/CustomFunctions.h"

int main() {
    std::string data_file_name = "Outputs/data/MysteryData21100.txt";
    std::vector<std::string> data = read_file(data_file_name);
    
    std::vector<double> data_val;
    for (std::string line : data) {
        std::stringstream ss(line);
        float val;

        if (ss >> val) {
            data_val.push_back(val);
        }
    }

    // print_n_lines(data, data.size());
    double min = *std::min_element(data_val.begin(), data_val.end());
    double max = *std::max_element(data_val.begin(), data_val.end());

    FiniteFunction test(min, max, "test.txt");
    test.printInfo();
    test.plotData(data_val, 100);
    test.plotFunction();
}