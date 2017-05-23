#include "stdafx.h"
#include "ComputationThread.h"



ComputationThread::ComputationThread()
	: terminated(false)
{
}


ComputationThread::~ComputationThread()
{
}


void ComputationThread::Start()
{
	std::thread([this]() {
		Calculate();
	}).detach();
}