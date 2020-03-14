#include "Clock.h"

namespace Time{

	void Clock::start(){
		_start.QuadPart = 0;
		QueryPerformanceFrequency(&_freq);
		QueryPerformanceCounter(&_start);
	}

	void Clock::stop(){
		QueryPerformanceCounter(&_end);
	}

	long double Clock::duration(){
		//microsecond accuracy
		LARGE_INTEGER delta;
		delta.QuadPart = (_end.QuadPart - _start.QuadPart);
		long double the_duration = ((long double)delta.QuadPart) / _freq.QuadPart;
		std::cout << "duration : " << the_duration << " seconds" << std::endl;
		return the_duration;
	}
}