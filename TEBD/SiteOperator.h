#pragma once

#include "Operator.h"


namespace TEBD {

	namespace Operators {

		template<typename T> class SiteOperator :
			public Operator<T>
		{
		public:
			SiteOperator(unsigned int size = 2, bool extendChangeSign = false);
			virtual ~SiteOperator();
		};


		template<typename T> class SzOneHalf : public SiteOperator<T>
		{
		public:
			SzOneHalf(unsigned int size = 2);
		};

		template<typename T> class SxOneHalf : public SiteOperator<T>
		{
		public:
			SxOneHalf(unsigned int size = 2);
		};

		// warning! this sets the matrix with real values
		// must be multiplied by i if used alone!
		template<typename T> class SyOneHalf : public SiteOperator<T>
		{
		public:
			SyOneHalf(unsigned int size = 2);
		};


		template<typename T> class SplusOneHalf : public SiteOperator<T>
		{
		public:
			SplusOneHalf(unsigned int size = 2);
		};


		template<typename T> class SzOne : public SiteOperator<T>
		{
		public:
			SzOne(unsigned int size = 3);
		};


		template<typename T> class SplusOne : public SiteOperator<T>
		{
		public:
			SplusOne(unsigned int size = 3);
		};
	}
}


#ifndef __SITE_OPERATOR_HPP
#define __SITE_OPERATOR_HPP

#include "SiteOperator.hpp"

#endif