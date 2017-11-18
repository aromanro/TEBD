#include "stdafx.h"
#include "TEBDComputationThread.h"


TEBDComputationThread::TEBDComputationThread(const Options& opt)
	: m_iTEBDobj(opt.chi)
{
	m_Options = opt;
}


TEBDComputationThread::~TEBDComputationThread()
{
	while (!terminated) Sleep(100);
}


void TEBDComputationThread::Calculate()
{
	if (1 == m_Options.StartState) m_iTEBDobj.m_iMPS.InitNeel();
	else
	{
		TEBD::Operators::Heisenberg H(m_Options.JxStart, m_Options.JyStart, m_Options.JzStart, m_Options.BxStart, m_Options.BzStart);		
		m_iTEBDobj.CalculateImaginaryTimeEvolution(H, 4000);
	}

	TEBD::Operators::Operator<std::complex<double>>::OperatorMatrix matrix;

	if (0 == m_Options.MeasureOp)
	{
		TEBD::Operators::SxOneHalf<double> sx;
		matrix = TEBD::Operators::Operator<std::complex<double>>::IdentityKronecker(2, 0.5 * sx.matrix);
	}
	else if (1 == m_Options.MeasureOp)
	{
		TEBD::Operators::SzOneHalf<double> sz;
		matrix = TEBD::Operators::Operator<std::complex<double>>::IdentityKronecker(2, 0.5 * sz.matrix);
	}
	else if (2 == m_Options.MeasureOp)
	{
		TEBD::Operators::SxOneHalf<double> sx;
		matrix = TEBD::Operators::Operator<std::complex<double>>::KroneckerProduct(sx.matrix, sx.matrix);	
	}

	else if (3 == m_Options.MeasureOp)
	{
		TEBD::Operators::SzOneHalf<double> sz;
		matrix = TEBD::Operators::Operator<std::complex<double>>::KroneckerProduct(sz.matrix, sz.matrix);	
	}
	
	m_iTEBDobj.m_TwoSitesOperators.push_back(TEBD::iTEBD<std::complex<double>, 2>::GetTwoSitesOperatorTensor(matrix));

	
	TEBD::Operators::Heisenberg Ht(m_Options.JxEvol, m_Options.JyEvol, m_Options.JzEvol, m_Options.BxEvol, m_Options.BzEvol);
	m_iTEBDobj.CalculateRealTimeEvolution(Ht, static_cast<int>(ceill(2000 * m_Options.maxTime)), 0.001);

	terminated = true;
}