#pragma once


#include "Operator.h"

namespace TEBD {

	template<typename T, unsigned int D = 2> class iMPS
	{
	public:
		iMPS(unsigned int chi = 10);
		virtual ~iMPS();

		virtual void InitRandomState();
		void InitNeel();

		Eigen::Tensor<T, 3> Gamma1;
		Eigen::Tensor<T, 3> Gamma2;

		typename Operators::Operator<double>::OperatorVector lambda1;
		typename Operators::Operator<double>::OperatorVector lambda2;
	};

}


#ifndef _IMPS_HPP
#define _IMPS_HPP
#include "iMPS.hpp"
#endif