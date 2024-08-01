#pragma once

namespace TEBD {


	template<typename T, int D> 
	iTEBD<T, D>::iTEBD(int chi)
		: m_chi(chi), isRealTimeEvolution(false), m_iMPS(chi)
	{
	}

	template<typename T, int D> 
	double iTEBD<T, D>::CalculateImaginaryTimeEvolution(Operators::Hamiltonian<double>& H, unsigned int steps, double delta)
	{
		m_iMPS.InitRandomState();

		const Operators::Operator<T>::OperatorMatrix Umatrix = GetImaginaryTimeEvolutionOperatorMatrix(H, delta);
		const Eigen::Tensor<T, 4> U = GetEvolutionTensor(Umatrix);
		
		isRealTimeEvolution = false;
		Calculate(U, steps);

		return GetEnergy(delta, thetaMatrix);
	}


	template<typename T, int D> 
	void iTEBD<T, D>::CalculateRealTimeEvolution(Operators::Hamiltonian<double>& H, unsigned int steps, double delta)
	{
		const Eigen::MatrixXcd Umatrix = GetRealTimeEvolutionOperatorMatrix(H, delta);
		const Eigen::Tensor<T, 4> U = GetEvolutionTensor(Umatrix);

		isRealTimeEvolution = true;
		Calculate(U, steps);
	}

	template<typename T, int D> 
	double iTEBD<T, D>::GetEnergy(double delta, typename Operators::Operator<double>::OperatorMatrix& thetaMatrix)
	{		
		return -std::log(thetaMatrix.cwiseProduct(thetaMatrix).sum()) / (2.*delta);
	}

	template<typename T, int D> 
	double iTEBD<T, D>::GetEnergy(double delta, typename Operators::Operator<std::complex<double>>::OperatorMatrix& thetaMatrix)
	{		
		return -std::log(thetaMatrix.cwiseProduct(thetaMatrix).sum().real()) / (2.*delta);
	}


	template<typename T, int D> 
	void iTEBD<T, D>::ComputeOperators(const Eigen::Tensor<T, 4> &thetabar)
	{
		using DimPair = Eigen::Tensor<T, 4>::DimensionPair;
		static const Eigen::array<DimPair, 2> product_dim1{ DimPair(2, 0), DimPair(3, 1) };

		std::vector<double> resultVector;
		resultVector.reserve(m_TwoSitesOperators.size());

		for (const auto &opTensor : m_TwoSitesOperators)
		{
			// this just applies the operator on thetabar
			const Eigen::Tensor<T, 4> thetaint = thetabar.contract(opTensor, product_dim1);

			const Operators::Operator<T>::OperatorMatrix mat1 = ReshapeTheta(thetaint);			
			
			Operators::Operator<T>::OperatorMatrix mat2(thetaMatrix.rows(), thetaMatrix.cols());
			
			for (int i = 0; i < thetaMatrix.rows(); ++i)
				for (int j = 0; j < thetaMatrix.cols(); ++j)
					mat2(i, j) = std::conj(thetaMatrix(i, j));

			// now sandwich the result with theta

			const T norm = mat2.cwiseProduct(thetaMatrix).sum();
			const T res = mat2.cwiseProduct(mat1).sum();

			resultVector.emplace_back(res.real()/norm.real());
		}
		
		m_Results.emplace_back(resultVector);
	}


	template<typename T, int D>
	void iTEBD<T, D>::InitializeLambdas(Eigen::Tensor<T, 2>& lambdaA, Eigen::Tensor<T, 2>& lambdaB, bool odd)
	{
		lambdaA.setZero();
		lambdaB.setZero();

		if (odd)
		{
			for (int i = 0; i < m_chi; ++i)
			{
				lambdaA(i, i) = m_iMPS.lambda2(i);
				lambdaB(i, i) = m_iMPS.lambda1(i);
			}
		}
		else
		{
			for (int i = 0; i < m_chi; ++i)
			{
				lambdaA(i, i) = m_iMPS.lambda1(i);
				lambdaB(i, i) = m_iMPS.lambda2(i);
			}
		}
	}

	template<typename T, int D>
	void iTEBD<T, D>::SvaluesToLambda(Operators::Operator<double>::OperatorVector& Svalues, Eigen::Tensor<T, 2>& lambdaA, Eigen::Tensor<T, 2>& lambdaB, bool odd)
	{
		if (odd) {
			for (int i = 0; i < m_chi; ++i)
			{
				m_iMPS.lambda2(i) = Svalues(i);

				if (abs(lambdaB(i, i)) > 1E-15)
					lambdaB(i, i) = 1. / lambdaB(i, i);
				else lambdaB(i, i) = 0;
			}

			m_iMPS.lambda2.normalize();
		}
		else {
			for (int i = 0; i < m_chi; ++i)
			{
				m_iMPS.lambda1(i) = Svalues(i);

				if (abs(lambdaB(i, i)) > 1E-15)
					lambdaB(i, i) = 1. / lambdaB(i, i);
				else lambdaB(i, i) = 0;
			}

			m_iMPS.lambda1.normalize();
		}
	}

	template<typename T, int D> 
	void iTEBD<T, D>::Calculate(const Eigen::Tensor<T, 4> &U, unsigned int steps)
	{
		for (unsigned int step = 0; step < steps; ++step)
		{
			const bool odd = (1 == step % 2);

			Eigen::Tensor<T, 2> lambdaA(m_chi, m_chi);
			Eigen::Tensor<T, 2> lambdaB(m_chi, m_chi);

			InitializeLambdas(lambdaA, lambdaB, odd);

			// construct theta
			Eigen::Tensor<T, 3>& gammaA = odd ? m_iMPS.Gamma2 : m_iMPS.Gamma1;
			Eigen::Tensor<T, 3>& gammaB = odd ? m_iMPS.Gamma1 : m_iMPS.Gamma2;

			// this does the tensor network contraction as in fig 3, (i)->(ii) from iTEBD Vidal paper
			const Eigen::Tensor<T, 4> thetabar = ConstructTheta(lambdaA, lambdaB, gammaA, gammaB, U);

			// ***********************************************************************************************************


			// get it into a matrix for SVD - use JacobiSVD

			// the theta tensor is now decomposed using SVD (as in (ii)->(iii) in fig 3 in Vidal iTEBD paper) and then 
			// the tensor network is rebuilt as in (iii)->(iv)->(v) from fig 3 Vidal 2008

			thetaMatrix = ReshapeTheta(thetabar);

			Eigen::JacobiSVD<Operators::Operator<T>::OperatorMatrix> SVD(thetaMatrix, Eigen::DecompositionOptions::ComputeThinU | Eigen::DecompositionOptions::ComputeThinV);

			const int Dchi = D * m_chi;
			Operators::Operator<T>::OperatorMatrix Umatrix = SVD.matrixU().block(0, 0, Dchi, m_chi);
			Operators::Operator<T>::OperatorMatrix Vmatrix = SVD.matrixV().block(0, 0, Dchi, m_chi).adjoint();
			
			Operators::Operator<double>::OperatorVector Svalues = SVD.singularValues();

			SvaluesToLambda(Svalues, lambdaA, lambdaB, odd);

			SetNewGammas(m_chi, lambdaB, Umatrix, Vmatrix, gammaA, gammaB);	

			// now compute 'measurements'
			// this program uses a 'trick' by reusing the already contracted tensor network
			
			if (odd && isRealTimeEvolution && m_TwoSitesOperators.size() > 0)
				ComputeOperators(thetabar);
		}
	}


	template<typename T, int D> 
	Eigen::Tensor<T, 4> iTEBD<T, D>::ContractTwoSites(const Eigen::Tensor<T, 2>& lambdaA, const Eigen::Tensor<T, 2>& lambdaB, const Eigen::Tensor<T, 3>& gammaA, const Eigen::Tensor<T, 3>& gammaB)
	{
		using IntIndexPair = Eigen::IndexPair<int>;
		using Indexes = Eigen::array<IntIndexPair, 1>;

		static const Indexes product_dims1{ IntIndexPair(1, 0) };
		static const Indexes product_dims_int{ IntIndexPair(2, 0) };
		static const Indexes product_dims4{ IntIndexPair(3, 0) };

		// construct theta

		// I leave this commented here, the operations separated with comments:

		/*
		// contract lambda on the left with the first gamma
		// the resulting tensor has three legs, 1 is the physical one
		Eigen::Tensor<T, 3> thetaint = lambdaB.contract(gammaA, product_dims1);

		// contract the result with the lambda in the middle
		// the resulting tensor has three legs, 1 is the physical one
		thetaint = thetaint.contract(lambdaA, product_dims_int).eval();

		// contract the result with the next gamma
		// the resulting tensor has four legs, 1 and 2 are the physical ones
		Eigen::Tensor<T, 4> theta = thetaint.contract(gammaB, product_dims_int);

		// contract the result with the lambda on the right
		// the resulting tensor has four legs, 1 and 2 are the physical ones
		return theta.contract(lambdaB, product_dims4);		
		*/

		// more compact, Eigen might have some opportunities to optimize things (although it doesn't seem a big difference in computing time):
		return lambdaB.contract(gammaA, product_dims1).contract(lambdaA, product_dims_int).contract(gammaB, product_dims_int).contract(lambdaB, product_dims4);
	}


	// this does the tensor network contraction as in fig 3, (i)->(ii) from iTEBD Vidal paper
	template<typename T, int D> 
	Eigen::Tensor<T, 4> iTEBD<T, D>::ConstructTheta(const Eigen::Tensor<T, 2>& lambdaA, const Eigen::Tensor<T, 2>& lambdaB, const Eigen::Tensor<T, 3>& gammaA, const Eigen::Tensor<T, 3>& gammaB, const Eigen::Tensor<T, 4>& U)
	{
		Eigen::Tensor<T, 4> theta = ContractTwoSites(lambdaA, lambdaB, gammaA, gammaB);

		// apply time evolution operator
		using DimPair = Eigen::Tensor<T, 4>::DimensionPair;

		// from theta the physical indexes are contracted out
		// the last two become the physical indexes

		static const Eigen::array<DimPair, 2> product_dim{ DimPair(1, 0), DimPair(2, 1) };
		
		// this applies the time evolution operator U
		return theta.contract(U, product_dim);
	}


	template<typename T, int D> 
	typename Operators::Operator<T>::OperatorMatrix iTEBD<T, D>::ReshapeTheta(const Eigen::Tensor<T, 4>& theta)
	{
		// get it into a matrix for SVD - use JacobiSVD

		int chi = static_cast<int>(theta.dimension(0));
		assert(chi == theta.dimension(1));

		assert(D == theta.dimension(2));
		assert(D == theta.dimension(3));
		
		const int Dchi = D * chi;
		Operators::Operator<T>::OperatorMatrix thetaMatrix(Dchi, Dchi);
		
		for (Eigen::Index i = 0; i < chi; ++i)
			for (Eigen::Index j = 0; j < chi; ++j)
				for (Eigen::Index k = 0; k < D; ++k)
					for (Eigen::Index l = 0; l < D; ++l)
						// 2, 0, 3, 1 - k & l from theta are the physical indexes
						thetaMatrix(k * chi + i, l * chi + j) = theta(i, j, k, l);

		return thetaMatrix;
	}


	template<typename T, int D> 
	void iTEBD<T, D>::SetNewGammas(int chi, const Eigen::Tensor<T, 2>& lambda, typename const Operators::Operator<T>::OperatorMatrix& Umatrix, typename const Operators::Operator<T>::OperatorMatrix& Vmatrix, Eigen::Tensor<T, 3>& GammaA, Eigen::Tensor<T, 3>& GammaB)
	{
		Eigen::Tensor<T, 3> Utensor(chi, D, chi);
		Eigen::Tensor<T, 3> Vtensor(chi, D, chi);

		for (Eigen::Index i = 0; i < chi; ++i)
			for (Eigen::Index j = 0; j < D; ++j)
				for (Eigen::Index k = 0; k < chi; ++k)
				{
					const Eigen::Index jchi = j * chi;
					Utensor(i, j, k) = Umatrix(jchi + i, k);
					Vtensor(i, j, k) = Vmatrix(i, jchi + k);
				}


		static const Eigen::array<Eigen::IndexPair<int>, 1> product_dims1{ Eigen::IndexPair<int>(1, 0) };
		static const Eigen::array<Eigen::IndexPair<int>, 1> product_dims2{ Eigen::IndexPair<int>(2, 0) };

		GammaA = lambda.contract(Utensor, product_dims1);
		GammaB = Vtensor.contract(lambda, product_dims2);
	}


}


