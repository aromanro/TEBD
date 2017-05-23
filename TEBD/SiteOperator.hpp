


namespace TEBD {

	namespace Operators {

		template<typename T> SiteOperator<T>::SiteOperator(unsigned int size, bool extendChangeSign)
			: Operator<T>(size, extendChangeSign)
		{
		}


		template<typename T> SiteOperator<T>::~SiteOperator()
		{
		}

		template<typename T> SzOneHalf<T>::SzOneHalf(unsigned int size)
			: SiteOperator(size, false)
		{
			int subsize = size / 2;

			matrix.block(0, 0, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, subsize, subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
		}

		template<typename T> SxOneHalf<T>::SxOneHalf(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			int subsize = size / 2;

			matrix.block(0, subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, 0, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}

		template<typename T> SyOneHalf<T>::SyOneHalf(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			int subsize = size / 2;

			matrix.block(0, subsize, subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, 0, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}


		template<typename T> SplusOneHalf<T>::SplusOneHalf(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			int subsize = size / 2;

			matrix.block(0, subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}

		template<typename T> SzOne<T>::SzOne(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			int subsize = size / 3;

			matrix.block(0, 0, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(2 * subsize, 2 * subsize, subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
		}


		template<typename T> SplusOne<T>::SplusOne(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			int subsize = size / 3;

			matrix.block(0, subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, 2 * subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);

			matrix *= sqrt(2.);
		}

	}
}