#pragma once

double gen_random_num_uniform(double range_min, double range_max);

double gen_random_num_normal(double mean, double std_dev);

std::vector<double> metropolis(
    double range_min,
    double range_max,
    int num_iterations,
    double std_dev,
    FiniteFunction distribution
);