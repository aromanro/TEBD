
namespace TEBD {

	namespace Operators {


		template<typename T> Operator<T>::Operator(unsigned int size, bool extendChangeSign)
			: changeSign(extendChangeSign), singleSiteSize(size), matrix(OperatorMatrix::Zero(size, size))
		{
		}

		template<typename T> void Operator<T>::Extend(bool left)
		{
			if (left)
				matrix = IdentityKronecker(singleSiteSize, matrix);
			else
				matrix = KroneckerProductWithIdentity(matrix, singleSiteSize);
		}

	}
}