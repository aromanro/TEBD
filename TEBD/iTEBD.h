#pragma once

#include <unsupported/Eigen/CXX11/Tensor>

#include <eigen/eigen>
#include <list>

#include "Operator.h"
#include "Hamiltonian.h"

#include "iMPS.h"

namespace TEBD {


	template<typename T, unsigned int D> class iTEBD
	{
	public:
		iTEBD(unsigned int chi = 10);
		virtual ~iTEBD();
		
		void CalculateRealTimeEvolution(Operators::Hamiltonian<double>& H, unsigned int steps, double delta = 0.005);

		double CalculateImaginaryTimeEvolution(Operators::Hamiltonian<double>& H, unsigned int steps, double delta = 0.005);

		inline static Eigen::Tensor<T, 4> GetTwoSitesOperatorTensor(typename const Operators::Operator<T>::OperatorMatrix& Omatrix)
		{
			Eigen::Tensor<T, 4> U(D, D, D, D);

			for (int i = 0; i < D; ++i)
				for (int j = 0; j < D; ++j)
					for (int k = 0; k < D; ++k)
						for (int l = 0; l < D; ++l)
							U(i, j, k, l) = Omatrix(D * i + j, D * k + l);

			return U;
		}

		inline static typename Operators::Operator<double>::OperatorMatrix GetImaginaryTimeEvolutionOperatorMatrix(Operators::Hamiltonian<double>& H, double deltat)
		{
			return H.Exponentiate(deltat);
		}

		inline static Eigen::MatrixXcd GetRealTimeEvolutionOperatorMatrix(Operators::Hamiltonian<double>& H, double deltat)
		{
			return H.ComplexExponentiate(deltat);
		}


		inline static Eigen::Tensor<T, 4> GetEvolutionTensor(typename const Operators::Operator<T>::OperatorMatrix& Umatrix)
		{			
			return GetTwoSitesOperatorTensor(Umatrix);
		}

		static Eigen::Tensor<T, 4> ContractTwoSites(const Eigen::Tensor<T, 2>& lambdaA, const Eigen::Tensor<T, 2>& lambdaB, const Eigen::Tensor<T, 3>& gammaA, const Eigen::Tensor<T, 3>& gammaB);
		static Eigen::Tensor<T, 4> ConstructTheta(const Eigen::Tensor<T, 2>& lambdaA, const Eigen::Tensor<T, 2>& lambdaB, const Eigen::Tensor<T, 3>& gammaA, const Eigen::Tensor<T, 3>& gammaB, const Eigen::Tensor<T, 4>& U);
		static typename Operators::Operator<T>::OperatorMatrix ReshapeTheta(const Eigen::Tensor<T, 4>& theta);

		static void SetNewGammas(int chi, const Eigen::Tensor<T, 2>& lambda, typename const Operators::Operator<T>::OperatorMatrix& Umatrix, typename const Operators::Operator<T>::OperatorMatrix& Vmatrix, Eigen::Tensor<T, 3>& GammaA, Eigen::Tensor<T, 3>& GammaB);

		void ComputeOperators(const Eigen::Tensor<T, 4> &thetabar);

		iMPS<T, D> m_iMPS;

		std::list<Eigen::Tensor<T, 4>> m_TwoSitesOperators;
		
		// one result / real time step, each being a vector of doubles
		// the vector should contain the same number of values as the number of operators in m_TwoSitesOperators
		std::list<std::vector<double>> m_Results;

	protected:
		typename Operators::Operator<T>::OperatorMatrix thetaMatrix;		

		void Calculate(const Eigen::Tensor<T, 4> &U, unsigned int steps);

		static double GetEnergy(double delta, typename Operators::Operator<std::complex<double>>::OperatorMatrix& thetaMatrix);
		static double GetEnergy(double delta, typename Operators::Operator<double>::OperatorMatrix& thetaMatrix);

		unsigned int m_chi;
		bool isRealTimeEvolution;
	};

}

#ifndef _ITEBD_HPP
#define _ITEBD_HPP

#include "iTEBD.hpp"

#endif