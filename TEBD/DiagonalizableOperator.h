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

				const Operator<T>::OperatorMatrix& eigenV = eigenvectors();
				Operator<T>::OperatorVector eigenv = eigenvalues();

				for (int i = 0; i < eigenv.size(); ++i)
					eigenv(i) = std::exp(-tau * eigenv(i));

				return eigenV * eigenv.asDiagonal() * eigenV.transpose();
			}	

			inline Eigen::MatrixXcd ComplexExponentiate(double tau)
			{
				Diagonalize();

				const Operator<T>::OperatorMatrix& eigenV = eigenvectors();
				const Operator<T>::OperatorVector& eigenv = eigenvalues();

				Eigen::VectorXcd result = Eigen::VectorXcd(eigenv.size());

				for (int i = 0; i < eigenv.size(); ++i)
					result(i) = std::exp(std::complex<double>(0, -1) * tau * eigenv(i));

				return eigenV * result.asDiagonal() * eigenV.transpose();
			}	


		};

	}
}

#ifndef __DIAGONALIZABLE_OPERATOR_HPP
#define __DIAGONALIZABLE_OPERATOR_HPP

#include "DiagonalizableOperator.hpp"

#endif