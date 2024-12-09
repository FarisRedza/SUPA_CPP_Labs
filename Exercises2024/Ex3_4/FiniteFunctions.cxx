#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way
#include <cmath>
#include <numeric>
#include <algorithm>

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

/*
###################
//Getters
###################
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);}; //(overridable)

/*
###################
Integration by hand (output needed to normalise function when plotting)
###################
*/ 
double FiniteFunction::integrate(int Ndiv){ //private
  double step_size = (m_RMax - m_RMin) / Ndiv;
  double sum = 0.5 * (this->callFunction(m_RMax) + this->callFunction(m_RMin));

  for (int i = 1; i < Ndiv; ++i) {
        sum += this->callFunction(m_RMin + i * step_size);
    }
  return sum * step_size;
  //ToDo write an integrator
  // return -99;
}
double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}


/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}

// Normal distribution
NormalDistribution::NormalDistribution(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  m_mu = 0;
  m_sigma = 0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
NormalDistribution::NormalDistribution(double range_min, double range_max, double mu, double sigma, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_mu = mu;
  m_sigma = sigma;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

double NormalDistribution::normaldistribution(double x) {
  return std::exp(-0.5 * pow((x - m_mu) / m_sigma, 2)) / (m_sigma * std::sqrt(2 * M_PI));
}

void NormalDistribution::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "μ: " << m_mu << std::endl;
  std::cout << "σ: " << m_sigma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

double NormalDistribution::callFunction(double x) {return this->normaldistribution(x);}

// Cauchy-Lorentz distribution
CauchyLorentz::CauchyLorentz(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  m_x_0 = 0;
  m_gamma = 1;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
CauchyLorentz::CauchyLorentz(double range_min, double range_max, double x_0, double gamma, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_x_0 = x_0;
  m_gamma = gamma;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

void CauchyLorentz::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "x_0: " << m_x_0 << std::endl;
  std::cout << "γ: " << m_gamma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

double CauchyLorentz::callFunction(double x) {return this->cauchylorentz(x);}

double CauchyLorentz::cauchylorentz(double x) {
  return 1 / (M_PI * m_gamma * (1 + std::pow((x - m_x_0) / m_gamma, 2)));
}

// Negative Crystal Ball distribution
CrystalBall::CrystalBall(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  m_n = 2;
  m_alpha = 1;
  m_sigma = 0;
  m_x_bar = 0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
  m_A = NULL;
  m_B = NULL;
  m_N = NULL;
  m_C = NULL;
  m_D = NULL;
}

//initialised constructor
CrystalBall::CrystalBall(double range_min, double range_max, double n, double alpha, double sigma, double x_bar, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_n = n;
  m_alpha = alpha;
  m_sigma = sigma;
  m_x_bar = x_bar;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
  m_A = NULL;
  m_B = NULL;
  m_N = NULL;
  m_C = NULL;
  m_D = NULL;
}

void CrystalBall::calc_A() {
  m_A = std::pow(m_n / std::abs(m_alpha), m_n) * std::exp(-std::pow(std::abs(m_alpha), 2) / 2);
}

void CrystalBall::calc_B() {
  m_B = (m_n / std::abs(m_alpha)) - std::abs(m_alpha);
}

void CrystalBall::calc_N() {
  this->calc_C();
  this->calc_D();
  m_N = 1 / (m_sigma * (m_C + m_D));
}

void CrystalBall::calc_C() {
  m_C = (m_n / std::abs(m_alpha)) * (1 / (m_n - 1)) * std::exp(-std::pow(std::abs(m_alpha), 2) / 2);
}

void CrystalBall::calc_D() {
  m_D = std::sqrt(M_PI / 2) * (1 + std::erf(std::abs(m_alpha) / std::sqrt(2)));
}

void CrystalBall::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "n: " << m_n << std::endl;
  std::cout << "ɑ: " << m_alpha << std::endl;
  std::cout << "σ: " << m_sigma << std::endl;
  std::cout << "x̄: " << m_x_bar << std::endl;
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
  double conditional = (x - m_x_bar) / m_sigma;
  this->calc_N();
  if (conditional > -m_alpha) {
    return m_N * std::exp(-std::pow(x - m_x_bar, 2) / (2 * std::pow(m_sigma, 2)));
  } else {
    this->calc_A();
    this->calc_B();
    return m_N * m_A * std::pow(m_B - conditional, -m_n);
  }
}