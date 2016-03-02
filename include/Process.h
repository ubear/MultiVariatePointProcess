#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include "Sequence.h"

/*
	
	This class defines the interface for a general process.
	 
*/
class IProcess
{

private:

//  Internal representation for the vector of parameters
	std::vector<double> parameters_;

//  number of dimensions in the process;
	unsigned num_dims_;

public:

//  Constructor : n is the number of parameters in total; num_dims is the number of dimensions in the process;
	IProcess(const unsigned& n, const unsigned& num_dims)
	{
		parameters_ = std::vector<double>(n, 0);

		num_dims_ = num_dims;
	}

	~IProcess(){}

//  Return the vector of parameters;
	const std::vector<double>& GetParameters() {return parameters_;}

//  Return the number of dimensions;
	unsigned GetNumDims(){return num_dims_;};

//  Set the vector of parameters. This is useful when we initialize the parameters for optimization;
	void SetParameters(const std::vector<double>& v) 
	{
		parameters_ = v;
	}


//  This virtual function requires process-specific implementation. It calculates the negative loglikelihood of the given data. This function must be called after the Initialize method to return the negative loglikelihood of the data with respect to the current parameters. 
//	The returned negative loglikelihood is stored in the variable objvalue;
//	The returned gradient vector wrt the current parameters is stored in the variable Gradient; 
	virtual void NegLoglikelihood(double& objvalue, std::vector<double>& Gradient) = 0;

//  This virtual function requires process-specific implementation. It returns the intensity value on each dimension in the variable intensity_dim for the given sequence stored in data and the given time t;
//  This function returns the summation of the individual intensity function on all dimensions. 
	virtual double Intensity(const double& t, const Sequence& data, std::vector<double>& intensity_dim) = 0;

//  This virtual function requires process-specific implementation. It returns the upper bound of the intensity function on each dimension at time t given the history data in the variable intensity_upper_dim;
//	This function returns the summation of the individual intensity upper bound on all dimensions. 
	virtual double IntensityUpperBound(const double& t, const Sequence& data, std::vector<double>& intensity_upper_dim) = 0;

	virtual void Gradient(const unsigned &k, std::vector<double>& gradient) = 0;

};

#endif