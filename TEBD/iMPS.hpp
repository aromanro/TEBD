#pragma once


namespace TEBD {

	template<typename T, unsigned int D = 2> iMPS<T, D>::iMPS(unsigned int chi)		
		: Gamma1(chi, D, chi), Gamma2(chi, D, chi),
		lambda1(chi), lambda2(chi)
	{		
	}


	template<typename T, unsigned int D = 2> iMPS<T, D>::~iMPS()
	{
	}

	template<typename T, unsigned int D = 2> void iMPS<T, D>::InitRandomState()
	{
		Eigen::Tensor<double, 3> Gamma1Random(lambda1.rows(), D, lambda1.rows());
		Eigen::Tensor<double, 3> Gamma2Random(lambda1.rows(), D, lambda1.rows());

		Gamma1Random.setRandom();
		Gamma2Random.setRandom();

		for (int i = 0; i < lambda1.rows(); ++i) 
			for (int j = 0; j < D; ++j) 
				for (int k = 0; k < lambda1.rows(); ++k)
				{
					Gamma1(i, j, k) = Gamma1Random(i, j, k);
					Gamma2(i, j, k) = Gamma2Random(i, j, k);
				}


		lambda1.setRandom();

		for (int i = 0; i < lambda1.rows(); ++i) {
			lambda1(i) += 1.0000000000000000000000001;
			lambda1(i) /= 2.0000000000000000000000001;
		}

		lambda1.normalize();

		lambda2.setRandom();

		for (int i = 0; i < lambda1.rows(); ++i) {
			lambda2(i) += 1.0000000000000000000000001;
			lambda2(i) /= 2.0000000000000000000000001;
		}

		lambda2.normalize();
	}



	template<typename T, unsigned int D = 2> void iMPS<T, D>::InitNeel()
	{
		lambda1.setZero();
		lambda2.setZero();


		lambda1(0) = 1;
		lambda2(0) = 1;
		

		Gamma1.setZero();
		Gamma2.setZero();

		// first matrix
		Gamma1(0, 0, 0) = 0.5;
		Gamma2(0, 0, 0) = 0.5;

		// second matrix
	    Gamma1(0, 1, 0) = 0.5;
		Gamma2(0, 1, 0) = 0.5;
	}
}


