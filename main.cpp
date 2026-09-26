#include "TimeMeter.h"
#include <iostream>

int main() {
	
	std::cout << "Start" << std::endl;	
	
	TimeMeter meter(2);

	while (meter.isLess(0, (int64_t)500)) {
		meter.setTimeStamp(0);
	}

	std::cout << "500 ms passed" << std::endl;
	
	meter.setTimeStamp(1);
	while (meter.getSDiff(0, 1) < 2) {
		meter.setTimeStamp(0);
	}

	std::cout << "2 more seconds passed" << std::endl;

	std::cout << "Total of " << meter.getSTimeStamp(0) << " passed" << std::endl;
}
