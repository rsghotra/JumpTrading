#ifndef CLOCK_H
#define CLOCK_H
#include <iostream>
#include <windows.h>


namespace Time{

	class Clock{
	public:

		Clock(){}
		virtual ~Clock(){}
		void start();
		void stop();
		long double duration();

        private:
		LARGE_INTEGER _start, _end, _freq;
	};

}

#endif