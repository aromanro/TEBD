


namespace TEBD {

	namespace Operators {

		template<typename T> SiteOperator<T>::SiteOperator(unsigned int size, bool extendChangeSign)
			: Operator<T>(size, extendChangeSign)
		{
		}

		template<typename T> SzOneHalf<T>::SzOneHalf(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 2;

			matrix.topLeftCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.bottomRightCorner(subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
		}

		template<typename T> SxOneHalf<T>::SxOneHalf(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			const int subsize = size / 2;

			matrix.topRightCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.bottomLeftCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}

		template<typename T> SyOneHalf<T>::SyOneHalf(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			const int subsize = size / 2;

			// the absence of i is intentional!
			matrix.topRightCorner(subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.bottomLeftCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}


		template<typename T> SplusOneHalf<T>::SplusOneHalf(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			const int subsize = size / 2;

			matrix.topRightCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}

		template<typename T> SzOne<T>::SzOne(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			const int subsize = size / 3;

			matrix.topLeftCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(2 * subsize, 2 * subsize, subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
		}


		template<typename T> SplusOne<T>::SplusOne(unsigned int size)
			: SiteOperator<T>(size, false)
		{
			const int subsize = size / 3;

			matrix.block(0, subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, 2 * subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);

			matrix *= sqrt(2.);
		}

	}
}