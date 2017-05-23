#pragma once

#include <thread>
#include <atomic>

class ComputationThread
{
public:
	std::atomic_bool terminated;
	
	void Start();
	virtual ~ComputationThread();
protected:
	ComputationThread();

	virtual void Calculate() = 0;
};

