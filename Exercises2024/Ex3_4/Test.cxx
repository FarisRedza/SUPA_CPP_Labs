#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <numeric>
#include <algorithm>

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

    int data_val_size = data_val.size();

    double min = *std::min_element(data_val.begin(), data_val.end());
    double max = *std::max_element(data_val.begin(), data_val.end());

    int Nbins = 50;
    int metro_std_dev = 30;

    // FiniteFunction ff(min, max, "MyInvXsq.txt");
    // ff.plotFunction();
    // ff.plotData(data_val, Nbins);
    // ff.printInfo();
    // std::vector<double> ff_sample_data = ff.metropolis(data_val_size, metro_std_dev);
    // ff.plotData(ff_sample_data, Nbins, false);

    // NormalDistribution nd(
    //     min, //range_min
    //     max, //range_max
    //     // -1, //mean
    //     // 1.65, //std_dev
    //     data_val, //data
    //     "MyNormalDistribution.txt" //outfile
    // );
    // nd.plotFunction();
    // nd.plotData(data_val, Nbins);
    // nd.printInfo();
    // std::vector<double> nd_sample_data = nd.metropolis(data_val_size, metro_std_dev);
    // nd.plotData(nd_sample_data, Nbins, false);

    // CauchyLorentz cl(
    //     min, //range_min
    //     max, //range_max
    //     // -1, //median
    //     // 1.49, //scale_paramter
    //     data_val, //data
    //     "MyCauchyLorentz.txt" //outfile
    // );
    // cl.plotFunction();
    // cl.plotData(data_val, Nbins);
    // cl.printInfo();
    // std::vector<double> cl_sample_data = cl.metropolis(data_val_size, metro_std_dev);
    // cl.plotData(cl_sample_data, Nbins, false);

    CrystalBall cb(
        min, //range_min
        max, //range_max
        2, //mean
        1.5, //std_dev
        1, //transition_point
        2.1, //tail_shape_paramter
        // data_val, //data
        "MyCrystalBall.txt" //outfile
    );
    cb.plotFunction();
    cb.plotData(data_val, Nbins);
    cb.printInfo();
    std::vector<double> cb_sample_data = cb.metropolis(data_val_size, metro_std_dev);
    cb.plotData(cb_sample_data, Nbins, false);
}