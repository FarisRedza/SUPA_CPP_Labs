#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <numeric>

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

    double min = *std::min_element(data_val.begin(), data_val.end());
    double max = *std::max_element(data_val.begin(), data_val.end());

    // FiniteFunction ff(min, max, "MyInvXsq.txt");
    // ff.plotFunction();
    // ff.plotData(data_val, 50);
    // ff.printInfo();

    // NormalDistribution nd(min, max, -1, 1.65, "MyNormalDistribution.txt");
    // nd.plotFunction();
    // nd.plotData(data_val, 50);
    // nd.printInfo();

    // CauchyLorentz cl(min, max, -1, 1.49, "MyCauchyLorentz.txt");
    // cl.plotFunction();
    // cl.plotData(data_val, 50);
    // cl.printInfo();

    CrystalBall cb(min, max, 3.25, 0.85, 1.4, -1, "MyCrystalBall.txt");
    cb.plotFunction();
    // cb.plotData(data_val, 50);
    cb.printInfo();
}