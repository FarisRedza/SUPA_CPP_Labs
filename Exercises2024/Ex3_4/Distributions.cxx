#include <numeric>
#include <cmath>
#include <string>
#include <vector>

#include "Distributions.h"

double calc_mean(std::vector<double> data) {
    double sum = std::reduce(data.begin(), data.end(), 0);
    return sum / data.size();
}

double calc_std_dev(std::vector<double> data, double mean) {
    double variance = 0.0;
    for (double value : data) {
        variance += std::pow(value - mean, 2);
    }
    variance /= data.size();
    return std::sqrt(variance);
}

// Normal distribution
NormalDistribution::NormalDistribution() {
    m_RMin = -5.0;
    m_RMax = 5.0;
    m_mean = 0;
    m_std_dev = 0;
    this->checkPath("DefaultFunction");
    m_Integral = NULL;
}

//Manual parameters constructor
NormalDistribution::NormalDistribution(
    double range_min,
    double range_max,
    double mean,
    double std_dev,
    std::string outfile
) {
    m_RMin = range_min;
    m_RMax = range_max;
    m_mean = mean;
    m_std_dev = std_dev;
    m_Integral = NULL;
    this->checkPath(outfile); //Use provided string to name output files
}

//Estimation constructor
NormalDistribution::NormalDistribution(
    double range_min,
    double range_max,
    std::vector<double> data,
    std::string outfile
) {
    m_RMin = range_min;
    m_RMax = range_max;
    m_mean = calc_mean(data);
    m_std_dev = calc_std_dev(data, m_mean);
    m_Integral = NULL;
    this->checkPath(outfile); //Use provided string to name output files
}

double NormalDistribution::normaldistribution(double x) {
    return std::exp(-0.5 * pow((x - m_mean) / m_std_dev, 2)) / (m_std_dev * std::sqrt(2 * M_PI));
}

void NormalDistribution::printInfo() {
    std::cout << "rangeMin: " << m_RMin << std::endl;
    std::cout << "rangeMax: " << m_RMax << std::endl;
    std::cout << "μ: " << m_mean << std::endl;
    std::cout << "σ: " << m_std_dev << std::endl;
    std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
    std::cout << "function: " << m_FunctionName << std::endl;
}

double NormalDistribution::callFunction(double x) {return this->normaldistribution(x);}

// Cauchy-Lorentz distribution
CauchyLorentz::CauchyLorentz() {
    m_RMin = -5.0;
    m_RMax = 5.0;
    m_median = 0;
    m_scale_parameter = 1;
    this->checkPath("DefaultFunction");
    m_Integral = NULL;
}

//Manual parameters constructor
CauchyLorentz::CauchyLorentz(
    double range_min,
    double range_max,
    double median,
    double scale_paramater,
    std::string outfile
) {
    m_RMin = range_min;
    m_RMax = range_max;
    m_median = median;
    m_scale_parameter = scale_paramater;
    m_Integral = NULL;
    this->checkPath(outfile); //Use provided string to name output files
}

//Estimation constructor
CauchyLorentz::CauchyLorentz(
    double range_min,
    double range_max,
    std::vector<double> data,
    std::string outfile
) {
    m_RMin = range_min;
    m_RMax = range_max;
    this->calc_median(data);
    this->calc_scale_parameter(data);
    m_Integral = NULL;
    this->checkPath(outfile); //Use provided string to name output files
}

void CauchyLorentz::calc_median(std::vector<double> data) {
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    if (n % 2 == 0) {
        m_median = (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        m_median = data[n / 2];
    }
}

void CauchyLorentz::calc_scale_parameter(std::vector<double>data) {
    double sum = 0.0;
    for (double x : data) {
        sum += std::abs(x - m_median);
    }
    m_scale_parameter = sum / data.size();
}

void CauchyLorentz::printInfo() {
    std::cout << "rangeMin: " << m_RMin << std::endl;
    std::cout << "rangeMax: " << m_RMax << std::endl;
    std::cout << "median: " << m_median << std::endl;
    std::cout << "γ: " << m_scale_parameter << std::endl;
    std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
    std::cout << "function: " << m_FunctionName << std::endl;
}

double CauchyLorentz::callFunction(double x) {return this->cauchylorentz(x);}

double CauchyLorentz::cauchylorentz(double x) {
    return 1 / (M_PI * m_scale_parameter * (1 + std::pow((x - m_median) / m_scale_parameter, 2)));
}

// Negative Crystal Ball distribution
CrystalBall::CrystalBall(){
    m_RMin = -5.0;
    m_RMax = 5.0;
    m_tail_shape_parameter = 2;
    m_transition_point = 1;
    m_std_dev = 0;
    m_mean = 0;
    this->checkPath("DefaultFunction");
    m_Integral = NULL;
    m_A = NULL;
    m_B = NULL;
    m_N = NULL;
    m_C = NULL;
    m_D = NULL;
}

//Manual parameters constructor
CrystalBall::CrystalBall(
    double range_min,
    double range_max,
    double mean,
    double std_dev,
    double transition_point,
    double tail_shape_parameter,
    std::string outfile
) {
    m_RMin = range_min;
    m_RMax = range_max;
    m_mean = mean;
    m_std_dev = std_dev;
    m_transition_point = transition_point;
    m_tail_shape_parameter = tail_shape_parameter;
    m_Integral = NULL;
    this->checkPath(outfile); //Use provided string to name output files
    m_A = NULL;
    m_B = NULL;
    m_N = NULL;
    m_C = NULL;
    m_D = NULL;
}

//Estimation constructor
CrystalBall::CrystalBall(
    double range_min,
    double range_max,
    std::vector<double> data,
    std::string outfile
) {
    m_RMin = range_min;
    m_RMax = range_max;
    m_mean = calc_mean(data);
    m_std_dev = calc_std_dev(data, m_mean);
    m_transition_point = transition_point;
    m_tail_shape_parameter = tail_shape_parameter;
    m_Integral = NULL;
    this->checkPath(outfile); //Use provided string to name output files
    m_A = NULL;
    m_B = NULL;
    m_N = NULL;
    m_C = NULL;
    m_D = NULL;
}

void CrystalBall::calc_A() {
    m_A = std::pow(m_tail_shape_parameter / std::abs(m_transition_point), m_tail_shape_parameter) * std::exp(-std::pow(std::abs(m_transition_point), 2) / 2);
}

void CrystalBall::calc_B() {
    m_B = (m_tail_shape_parameter / std::abs(m_transition_point)) - std::abs(m_transition_point);
}

void CrystalBall::calc_N() {
    this->calc_C();
    this->calc_D();
    m_N = 1 / (m_std_dev * (m_C + m_D));
}

void CrystalBall::calc_C() {
    m_C = (m_tail_shape_parameter / std::abs(m_transition_point)) * (1 / (m_tail_shape_parameter - 1)) * std::exp(-std::pow(std::abs(m_transition_point), 2) / 2);
}

void CrystalBall::calc_D() {
    m_D = std::sqrt(M_PI / 2) * (1 + std::erf(std::abs(m_transition_point) / std::sqrt(2)));
}

void CrystalBall::calc_residuals(const std::vector<double>& data, const std::vector<double>& model) {
    double residuals = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        m_residuals += std::pow(data[i] - model[i], 2);
    }
    return residuals;
}

// Generate model values based on parameters
std::vector<double> generateModel(const std::vector<double>& data, double mu, double sigma, double alpha, double n) {
    std::vector<double> model;
    model.reserve(data.size());
    for (double x : data) {
        model.push_back(negativeCrystalBall(x, mu, sigma, alpha, n));
    }
    return model;
}

// Simple fitting function (minimizing residuals)
void fitNegativeCrystalBall(const std::vector<double>& data, double& mu, double& sigma, double& alpha, double& n) {
    double step = 0.01;
    double tolerance = 1e-6;
    double residuals = std::numeric_limits<double>::max();

    for (int iter = 0; iter < 1000; ++iter) {
        // Generate the model
        auto model = generateModel(data, mu, sigma, alpha, n);
        double newResiduals = calculateResiduals(data, model);

        // Check convergence
        if (std::abs(newResiduals - residuals) < tolerance) break;
        residuals = newResiduals;

        // Adjust parameters slightly
        mu += step;
        sigma += step;
        alpha += step;
        n += step;
    }
}

void CrystalBall::printInfo() {
    std::cout << "rangeMin: " << m_RMin << std::endl;
    std::cout << "rangeMax: " << m_RMax << std::endl;
    std::cout << "x̄: " << m_mean << std::endl;
    std::cout << "σ: " << m_std_dev << std::endl;
    std::cout << "ɑ: " << m_transition_point << std::endl;
    std::cout << "n: " << m_tail_shape_parameter << std::endl;
    std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
    std::cout << "function: " << m_FunctionName << std::endl;
    std::cout << "A: " << m_A << std::endl;
    std::cout << "B: " << m_B << std::endl;
    std::cout << "N: " << m_N << std::endl;
    std::cout << "C: " << m_C << std::endl;
    std::cout << "D: " << m_D << std::endl;
}

double CrystalBall::callFunction(double x) {return this->crystalball(x);}

double CrystalBall::crystalball(double x) {
    double conditional = (x - m_mean) / m_std_dev;
    this->calc_N();
    if (conditional > -m_transition_point) {
        return m_N * std::exp(-std::pow(x - m_mean, 2) / (2 * std::pow(m_std_dev, 2)));
    } else {
        this->calc_A();
        this->calc_B();
        return m_N * m_A * std::pow(m_B - conditional, -m_tail_shape_parameter);
    }
}