#include <string>
#include <vector>

#include "FiniteFunctions.h"

#pragma once

double calc_mean(std::vector<double> data);

class NormalDistribution : public FiniteFunction {
public:
    NormalDistribution();
    NormalDistribution(
        double range_min,
        double range_max,
        double mean,
        double std_dev,
        std::string outfile
    );
    NormalDistribution(
        double range_min,
        double range_max,
        std::vector<double> data,
        std::string outfile
    );
    void printInfo();
    double callFunction(double x);
private:
    double m_mean;
    double m_std_dev;
    double normaldistribution(double x);
};

class CauchyLorentz : public FiniteFunction {
public:
    CauchyLorentz();
    CauchyLorentz(
        double range_min,
        double range_max,
        double median,
        double scale_paramter,
        std::string outfile
    );
    CauchyLorentz(
        double range_min,
        double range_max,
        std::vector<double> data,
        std::string outfile
    );
    void printInfo();
    double callFunction(double x);
private:
    double m_median;
    double m_scale_parameter;
    void calc_median(std::vector<double> data);
    void calc_scale_parameter(std::vector<double> data);
    double cauchylorentz(double x);
};

class CrystalBall : public FiniteFunction {
public:
    CrystalBall();
    CrystalBall(
        double range_min,
        double range_max,
        double mean,
        double std_dev,
        double transition_point,
        double tail_shape_parameter,
        std::string outfile
    );
    CrystalBall(
        double range_min,
        double range_max,
        std::vector<double> data,
        std::string outfile
    );
    void printInfo();
    double callFunction(double x);
private:
    double m_mean;
    double m_std_dev;
    double m_transition_point;
    double m_tail_shape_parameter;
    double m_A;
    double m_B;
    double m_N;
    double m_C;
    double m_D;
    void calc_A();
    void calc_B();
    void calc_N();
    void calc_C();
    void calc_D();
    double m_residuals;
    std::vector<double> m_model;
    double calc_residuals(std::vector<double> data);
    void calc_model();
    void fit_crystalball(std::vector<double>data);
    void generateModel(std::vector<double> data);
    double crystalball(double x);
};
