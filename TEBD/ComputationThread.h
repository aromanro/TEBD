#pragma once

#include <thread>
#include <atomic>

class ComputationThread
{
public:
	std::atomic_bool terminated{ false };
	std::atomic_bool success{ false };
	
	void Start();
	virtual ~ComputationThread() = default;

protected:
	ComputationThread() = default;

	virtual void Calculate() = 0;
};

