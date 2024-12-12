#include <random>
#include "Distributions.h"
#include "Sampling.h"

double gen_random_num_uniform(double range_min, double range_max) {
    std::random_device rd;
    std::mt19937 mtEngine{rd()};
    std::uniform_real_distribution<double> dis(range_min, range_max);
    return dis(mtEngine);
}

double gen_random_num_normal(double mean, double std_dev) {
    std::random_device rd;
    std::mt19937 mtEngine{rd()};
    std::normal_distribution<double> dis(mean, std_dev);
    return dis(mtEngine);
}

// std::vector<double> metropolis(double range_min, double range_max, int size, double std_dev, FiniteFunction distribution) {
//     std::vector<double> y_val;

//     double current = range_min;
//     double current_prob = gen_random_num_normal();

//     for (int i = 0; i < size; i++) {
//         double x_i = gen_random_num_uniform(range_min, range_max);
//         double y_i = gen_random_num_normal(x_i, std_dev);

//         double f_x = distribution.callFunction(x_i);
//         double f_y = distribution.callFunction(y_i);

//         double a = std::min(f_y / f_x, 1.0);
//         double t = gen_random_num_uniform(0, 1);

//         if (t < a) {
//             y_val.push_back(y_i);
//         }
//     }
// }

// std::vector<double> metropolis(double range_min, double range_max, int iterations, double std_dev, FiniteFunction distribution) {
//     std::vector<double> values;

//     // Random number generators.
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<double> uniform_dist(range_min, range_max);
//     std::normal_distribution<double> normal_dist(0.0, std_dev);
//     std::uniform_real_distribution<double> uniform_01(0.0, 1.0);

//     // Generate the initial random x value.
//     double x_i = uniform_dist(gen);
//     double temp_val = x_i;
//     bool accepted = false;
//     for (int i = 0; i < iterations; ++i) {
//         // Step 2: Generate a second random number y from a normal distribution centered on x_i.
//         double y = x_i + normal_dist(gen);

//         // Step 3: Compute A = min(f(y)/f(x_i), 1).
//         double A = std::min(distribution.callFunction(y) / distribution.callFunction(x_i), 1.0);

//         // Step 4: Generate a random number T between 0 and 1.
//         double T = uniform_01(gen);

//         // Step 5: Accept or reject y.
//         if (T < A) {
//             x_i = y; // Accept y
//             accepted = true;
//         } else {
//             accepted = false;
//         }

//         // Output the current x_i (optional, for debugging or analysis).
//         values.push_back(x_i);
//     }

//     return values;
// }

// std::vector<double> metropolis(
//     double range_min,
//     double range_max,
//     int iterations,
//     double std_dev,
//     FiniteFunction distribution
// ) {
//     std::vector<double> accepted_y_vals;

//     // Random number generators.
//     std::random_device rd;
//     std::mt19937 mtEngine(rd());
//     std::uniform_real_distribution<double> uniform_dist(range_min, range_max);
//     std::normal_distribution<double> normal_dist(0.0, std_dev);
//     std::uniform_real_distribution<double> uniform_01(0.0, 1.0);

//     bool accepted = false;
//     double x_i = uniform_dist(mtEngine);
//     for (int i = 0; i < iterations; i++) {
//         if (accepted == true) {
//             x_i = accepted_y_vals.back();
//         }
//         double y = gen_random_num_normal(x_i, std_dev);

//         double A = std::min(distribution.callFunction(y) / distribution.callFunction(x_i), 1.0);
//         double T = uniform_01(mtEngine);

//         if (T < A) {
//             accepted_y_vals.push_back(y);
//             accepted = true;
//         } else {
            
//             accepted = false;
//         }
//     }
//     return accepted_y_vals;
// }

std::vector<double> metropolis(
    double range_min,
    double range_max,
    int iterations,
    double std_dev,
    FiniteFunction distribution
){
	std::vector<double> generatedsample;
	double x_i;
	double random_y;
	double to_test;
	double A;
	double T;
	std::random_device rd;
	std::mt19937 mtEngine{rd()};
	std::uniform_real_distribution<double> uniform_PDF{0, 1};
	x_i = uniform_PDF(mtEngine);
	x_i = x_i*(range_max - range_min) + range_max;
	generatedsample.push_back(x_i);
	std::normal_distribution<double> Normal_y_PDF{x_i, std_dev};
	while (generatedsample.size() < iterations){
		x_i = generatedsample.back();
		random_y = Normal_y_PDF(mtEngine);
		to_test = distribution.callFunction(random_y) / distribution.callFunction(x_i);
		A = std::min(to_test, 1.0);
		T = uniform_PDF(mtEngine);
		if (T < A && random_y <= range_max && random_y >= range_min){
			generatedsample.push_back(random_y);
		}
		else{
			generatedsample.push_back(x_i);
		}
	}
	return generatedsample;
}