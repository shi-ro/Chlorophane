
#include <chrono>
#include "CNE_Time.h"

using namespace std::chrono;

CNE_Time::CNE_Time() { }

int CNE_Time::start() {
	if (_stopped) {
		_startTime = duration_cast< microseconds >( system_clock::now().time_since_epoch() );
		_stopped = false;
		return 0;
	} else {
		// cannot start before reseting or stopping
		return 1;
	}
	return -1;
}

int CNE_Time::stop() {
	if (!_stopped) {
		_endTime = duration_cast< microseconds >( system_clock::now().time_since_epoch() );
		_stopped = true;
		return 0;
	} else {
		// cannot stop before started
		return 1;
	}
	return -1;
}

int CNE_Time::reset() {
	_startTime = 0ms;
	_endTime = 0ms;
	if (_stopped) {
		return 0;
	} else {
		_stopped = false;
		return 1;
	}
	return -1;
}

microseconds CNE_Time::getTime() {
	microseconds virtualEndTime = _endTime;
	if (!_stopped) {
		virtualEndTime = duration_cast< microseconds >(system_clock::now().time_since_epoch());
	}
	return virtualEndTime - _startTime;
}

microseconds CNE_Time::getStartTime() {
	return _startTime;
}

microseconds CNE_Time::getEndTime() {
	return _endTime;
}

CNE_Time::~CNE_Time() {

}
