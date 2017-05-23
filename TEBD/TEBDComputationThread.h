#pragma once
#include "ComputationThread.h"
#include "Options.h"


#include <unsupported/Eigen/CXX11/Tensor>

#include <eigen/eigen>

#include "iTEBD.h"

class TEBDComputationThread :
	public ComputationThread
{
public:
	TEBDComputationThread(const Options& opt);
	virtual ~TEBDComputationThread();

	TEBD::iTEBD<std::complex<double>, 2> m_iTEBDobj;
protected:
	virtual void Calculate();

	Options m_Options;	
};

