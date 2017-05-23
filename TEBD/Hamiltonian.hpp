

namespace TEBD {

	namespace Operators {

		template<typename T> Hamiltonian<T>::Hamiltonian(int size)
			: DiagonalizableOperator<T>(size, false)
		{
		}

		template<typename T> void Hamiltonian<T>::Extend(const Hamiltonian& siteHamiltonian, const Hamiltonian& interactionHamiltonian, bool left)
		{
			int basisSize = (int)matrix.cols();

			DiagonalizableOperator<T>::Extend(left);

			if (left)
				matrix += Operator<T>::KroneckerProductWithIdentity(siteHamiltonian.matrix, basisSize);
			else
				matrix += Operator<T>::IdentityKronecker(basisSize, siteHamiltonian.matrix);
				
			matrix += interactionHamiltonian.matrix;
		}


		template<typename T> HamiltonianSpinOne<T>::HamiltonianSpinOne()
			: Hamiltonian<T>(3)
		{
		}


		inline Heisenberg::Heisenberg(double Jx, double Jy, double Jz, double Bx, double Bz)
			: Hamiltonian<double>(2)
		{
			Operators::SxOneHalf<double> sx;
			Operators::SyOneHalf<double> sy;
			Operators::SzOneHalf<double> sz;
			
			matrix = - (Jx * Operators::Operator<double>::KroneckerProduct(sx.matrix, sx.matrix)
				- Jy * Operators::Operator<double>::KroneckerProduct(sy.matrix, sy.matrix)
				+ Jz * Operators::Operator<double>::KroneckerProduct(sz.matrix, sz.matrix)
				+ Bx/2 * (Operators::Operator<double>::IdentityKronecker(2, sx.matrix) + Operators::Operator<double>::KroneckerProductWithIdentity(sx.matrix, 2))
				+ Bz/2 * (Operators::Operator<double>::IdentityKronecker(2, sz.matrix) + Operators::Operator<double>::KroneckerProductWithIdentity(sz.matrix, 2)));
		}

	}
}