#pragma once


#include <eigen\eigen>

namespace TEBD {

	namespace Operators {

		template<typename T> class Operator
		{
		protected:
			bool changeSign;
			int singleSiteSize;
		public:
			typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> OperatorMatrix;
			typedef Eigen::Matrix<T, Eigen::Dynamic, 1> OperatorVector;

			// extendChangeSign should be true for fermionic operators (not implemented yet)
			// false for bosonic operators
			Operator(unsigned int size = 2, bool extendChangeSign = false);
			virtual ~Operator();

			OperatorMatrix matrix;

			void Extend(bool left = true);

			int GetSingleSiteSize() const { return singleSiteSize; }

			inline static OperatorMatrix KroneckerProduct(const OperatorMatrix& mat1, const OperatorMatrix& mat2)
			{
				OperatorMatrix result(mat1.rows() * mat2.rows(), mat1.cols() * mat2.cols());

				for (int i = 0; i < mat1.rows(); ++i)
					for (int j = 0; j < mat1.cols(); ++j)
						result.block(i * mat2.rows(), j * mat2.cols(), mat2.rows(), mat2.cols()) = mat1(i, j) * mat2;

				return result;
			}


			inline static OperatorMatrix KroneckerProductWithIdentity(const OperatorMatrix& mat, int identitySize)
			{
				OperatorMatrix result(mat.rows() * identitySize, mat.cols() * identitySize);

				for (Eigen::Index i = 0; i < mat.rows(); ++i)
					for (Eigen::Index j = 0; j < mat.cols(); ++j)
						result.block(i * identitySize, j * identitySize, identitySize, identitySize) = mat(i, j) * OperatorMatrix::Identity(identitySize, identitySize);

				return result;
			}

			inline static OperatorMatrix IdentityKronecker(int identitySize, const OperatorMatrix& mat)
			{
				OperatorMatrix result = OperatorMatrix::Zero(mat.rows() * identitySize, mat.cols() * identitySize);

				for (Eigen::Index i = 0; i < identitySize; ++i)
					result.block(i * mat.rows(), i * mat.cols(), mat.rows(), mat.cols()) = mat;

				return result;
			}

		};
	
	}

}

#ifndef __OPERATOR_HPP
#define __OPERATOR_HPP

#include "Operator.hpp"

#endif
