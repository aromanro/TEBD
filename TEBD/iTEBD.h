#pragma once

#include <unsupported/Eigen/CXX11/Tensor>

#include <eigen/eigen>
#include <list>

#include "Operator.h"
#include "Hamiltonian.h"

#include "iMPS.h"

namespace TEBD {


	template<typename T, int D> class iTEBD
	{
	public:
		iTEBD(int chi = 10);
		virtual ~iTEBD() = default;
		
		void CalculateRealTimeEvolution(Operators::Hamiltonian<double>& H, unsigned int steps, double delta = 0.005);

		double CalculateImaginaryTimeEvolution(Operators::Hamiltonian<double>& H, unsigned int steps, double delta = 0.005);

		inline static Eigen::Tensor<T, 4> GetTwoSitesOperatorTensor(typename const Operators::Operator<T>::OperatorMatrix& Omatrix)
		{
			Eigen::Tensor<T, 4> U(D, D, D, D);

			for (Eigen::Index i = 0; i < D; ++i)
				for (Eigen::Index j = 0; j < D; ++j)
					for (Eigen::Index k = 0; k < D; ++k)
						for (Eigen::Index l = 0; l < D; ++l)
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

		static Eigen::Tensor<T, 4> ContractTwoSites(const Eigen::VectorXd& lambdaA, const Eigen::VectorXd& lambdaB, Eigen::Tensor<T, 3>& gammaA, Eigen::Tensor<T, 3>& gammaB);
		static Eigen::Tensor<T, 4> ConstructTheta(const Eigen::VectorXd& lambdaA, const Eigen::VectorXd& lambdaB, Eigen::Tensor<T, 3>& gammaA, Eigen::Tensor<T, 3>& gammaB, const Eigen::Tensor<T, 4>& U);
		static typename Operators::Operator<T>::OperatorMatrix ReshapeTheta(const Eigen::Tensor<T, 4>& theta);

		static void SetNewGammas(int chi, const Eigen::VectorXd& lambda, typename const Operators::Operator<T>::OperatorMatrix& Umatrix, typename const Operators::Operator<T>::OperatorMatrix& Vmatrix, Eigen::Tensor<T, 3>& GammaA, Eigen::Tensor<T, 3>& GammaB);

		void ComputeOperators(const Eigen::Tensor<T, 4> &thetabar);

		iMPS<T, D> m_iMPS;

		std::list<Eigen::Tensor<T, 4>> m_TwoSitesOperators;
		
		// one result / real time step, each being a vector of doubles
		// the vector should contain the same number of values as the number of operators in m_TwoSitesOperators
		std::list<std::vector<double>> m_Results;

	private:
		typename Operators::Operator<T>::OperatorMatrix thetaMatrix;		

		void SvaluesToLambda(const Eigen::VectorXd& Svalues, bool odd);
		void Calculate(const Eigen::Tensor<T, 4> &U, unsigned int steps);

		static double GetEnergy(double delta, typename Operators::Operator<std::complex<double>>::OperatorMatrix& thetaMatrix);
		static double GetEnergy(double delta, typename Operators::Operator<double>::OperatorMatrix& thetaMatrix);

		int m_chi;
		bool isRealTimeEvolution;

		Eigen::BDCSVD<typename Operators::Operator<T>::OperatorMatrix> SVD;
	};

}

#ifndef _ITEBD_HPP
#define _ITEBD_HPP

#include "iTEBD.hpp"

#endif