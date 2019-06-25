#pragma once
#include <chrono>

using namespace std::chrono;

class CNE_Time
{
private:
	microseconds _startTime;
	bool _stopped;
	microseconds _endTime;
public:
	CNE_Time();
	int start();
	int stop();
	int reset();
	microseconds getTime();
	microseconds getStartTime();
	microseconds getEndTime();
	~CNE_Time();
};

