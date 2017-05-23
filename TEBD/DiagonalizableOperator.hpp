

namespace TEBD {

	namespace Operators {

		template<typename T> DiagonalizableOperator<T>::DiagonalizableOperator(unsigned int size, bool extendChangeSign)
			: Operator<T>(size, extendChangeSign)
		{
		}


		template<typename T> DiagonalizableOperator<T>::~DiagonalizableOperator()
		{
		}

		template<typename T> void DiagonalizableOperator<T>::Diagonalize()
		{
			solver.compute(matrix);

			ASSERT(solver.info() == Eigen::ComputationInfo::Success);

			// the eigenvalues and eigenvectors are already sorted
			// the eigenvectors are normalized
			// the SelfAdjointEigenSolver diagonalization from Eigen takes care of those
			// for another solver, sorting needs to be done afterwards

			// no need to switch it to diagonal in this program
			// for nrg I used it, here is not necessary
			//matrix = eigenvalues().asDiagonal();
		}

	}
}


