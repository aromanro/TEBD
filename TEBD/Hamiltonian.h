#pragma once

#include "SiteOperator.h"
#include "DiagonalizableOperator.h"

namespace TEBD {
	namespace Operators {

		template<typename T> class Hamiltonian : public DiagonalizableOperator<T>
		{
		public:
			Hamiltonian(int size = 2);

			void Extend(const Hamiltonian& siteHamiltonian, const Hamiltonian& interactionHamiltonian, bool left = true);
		};

		template<typename T> class HamiltonianSpinOne : public Hamiltonian<T>
		{
		public:
			HamiltonianSpinOne();
		};


		class Heisenberg : public Hamiltonian<double>
		{
		public:
			Heisenberg(double Jx, double Jy, double Jz, double Bx = 0, double Bz = 0);
		};

		class HeisenbergXXZ : public Heisenberg
		{
		public:
			HeisenbergXXZ(double Jxy, double Jz, double Bx = 0, double Bz = 0) : Heisenberg(Jxy, Jxy, Jz, Bx, Bz) {}
		};

	}
}

#ifndef __HAMILTONIAN_HPP
#define __HAMILTONIAN_HPP

#include "Hamiltonian.hpp"

#endif
