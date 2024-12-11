#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <numeric>

#include "FiniteFunctions.h"
#include "Distributions.h"
#include "../Ex1_2/CustomFunctions.h"

int main() {
    std::string data_file_name = "Outputs/data/MysteryData24111.txt";
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

    // NormalDistribution nd(
    //     min, //range_min
    //     max, //range_max
    //     // -1, //mean
    //     // 1.65, //std_dev
    //     data_val, //data
    //     "MyNormalDistribution.txt" //outfile
    // );
    // nd.plotFunction();
    // nd.plotData(data_val, 50);
    // nd.printInfo();

    // CauchyLorentz cl(
    //     min, //range_min
    //     max, //range_max
    //     // -1, //median
    //     // 1.49, //scale_paramter
    //     data_val, //data
    //     "MyCauchyLorentz.txt" //outfile
    // );
    // cl.plotFunction();
    // cl.plotData(data_val, 50);
    // cl.printInfo();

    CrystalBall cb(
        min, //range_min
        max, //range_max
        2, //mean
        1.5, //std_dev
        1, //transition_point
        2.1, //tail_shape_paramter
        "MyCrystalBall.txt" //outfile
    );
    cb.plotFunction();
    cb.plotData(data_val, 50);
    cb.printInfo();
}