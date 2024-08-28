#pragma once


#include "Operator.h"

namespace TEBD {

	template<typename T, int D = 2> class iMPS
	{
	public:
		iMPS(int chi = 10);
		virtual ~iMPS() = default;

		virtual void InitRandomState();
		void InitNeel();

		Eigen::Tensor<T, 3> Gamma1;
		Eigen::Tensor<T, 3> Gamma2;

		Eigen::VectorXd lambda1;
		Eigen::VectorXd lambda2;
	};

}


#ifndef _IMPS_HPP
#define _IMPS_HPP
#include "iMPS.hpp"
#endif