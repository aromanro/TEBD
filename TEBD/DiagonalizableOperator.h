#pragma once

#include "Operator.h"

#include <complex>

namespace TEBD {
	namespace Operators {

		template<typename T> class DiagonalizableOperator : public Operator<T>
		{
		protected:
			Eigen::SelfAdjointEigenSolver<Operator<T>::OperatorMatrix> solver;
		public:
			DiagonalizableOperator(unsigned int size = 2, bool extendChangeSign = false);
			virtual ~DiagonalizableOperator();

			void Diagonalize();

			inline const Operator<T>::OperatorMatrix& eigenvectors() const { return solver.eigenvectors(); }
			inline const Operator<T>::OperatorMatrix eigenvalues() const { return solver.eigenvalues(); }
			
			inline Operator<T>::OperatorMatrix Exponentiate(double tau)
			{
				Diagonalize();

				const Operator<T>::OperatorMatrix& eigenVects = eigenvectors();
				Operator<T>::OperatorVector eigenvals = eigenvalues();

				for (int i = 0; i < eigenvals.size(); ++i)
					eigenvals(i) = std::exp(-tau * eigenvals(i));

				return eigenVects * eigenvals.asDiagonal() * eigenVects.transpose();
			}	

			inline Eigen::MatrixXcd ComplexExponentiate(double tau)
			{
				Diagonalize();

				const Operator<T>::OperatorMatrix& eigenVects = eigenvectors();
				const Operator<T>::OperatorVector eigenvals = eigenvalues();

				Eigen::VectorXcd result = Eigen::VectorXcd(eigenvals.size());

				const std::complex<double> itau = std::complex<double>(0, -1) * tau;

				for (int i = 0; i < eigenvals.size(); ++i)
					result(i) = std::exp(itau * eigenvals(i));

				return eigenVects * result.asDiagonal() * eigenVects.transpose();
			}	


		};

	}
}

#ifndef __DIAGONALIZABLE_OPERATOR_HPP
#define __DIAGONALIZABLE_OPERATOR_HPP

#include "DiagonalizableOperator.hpp"

#endif