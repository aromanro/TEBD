#pragma once

#include "ComputationThread.h"
#include "Options.h"

#include "iTEBD.h"

class TEBDComputationThread :
	public ComputationThread
{
public:
	TEBDComputationThread(const Options& opt);
	~TEBDComputationThread() override;

	TEBD::iTEBD<std::complex<double>, 2> m_iTEBDobj;

private:
	void Calculate() override;

	Options m_Options;
};

