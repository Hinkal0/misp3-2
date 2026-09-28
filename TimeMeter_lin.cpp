#include "TimeMeter.h"
#include <vector>
#include <ctime>

struct TimeMeter::Impl {
	std::vector<timespec> stamps;
	timespec start;
	
	Impl(unsigned count) : stamps(count) {
		clock_gettime(CLOCK_REALTIME, &start);
		std::fill(stamps.begin(), stamps.end(), start);
	}
};

TimeMeter::TimeMeter(unsigned count) : pImpl(std::make_unique<Impl>(count)) {}
TimeMeter::~TimeMeter() = default;

void TimeMeter::setTimeStamp(unsigned num) {
	if (num >= pImpl->stamps.size()) return;

	clock_gettime(CLOCK_REALTIME, &pImpl->stamps[num]);
}

double TimeMeter::getSTimeStamp(unsigned num) const {
	if (num >= pImpl->stamps.size()) return -1;

	return (pImpl->stamps[num].tv_sec-pImpl->start.tv_sec) + (pImpl->stamps[num].tv_nsec-pImpl->start.tv_nsec)/1000000000.0;
}	

int64_t TimeMeter::getMSTimeStamp(unsigned num) const {
	if (num >= pImpl->stamps.size()) return -1;

	return (pImpl->stamps[num].tv_sec-pImpl->start.tv_sec)*1000 + (pImpl->stamps[num].tv_nsec-pImpl->start.tv_nsec)/1000000;
}

double TimeMeter::getSDiff(unsigned first, unsigned second) const {
	if (first >= pImpl->stamps.size() || second >= pImpl->stamps.size()) return -1;

	return getSTimeStamp(first)-getSTimeStamp(second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) const {
	if (first >= pImpl->stamps.size() || second >= pImpl->stamps.size()) return -1;

	return getMSTimeStamp(first)-getMSTimeStamp(second);
}

bool TimeMeter::isLess(unsigned num, double expected) const {
	if (num >= pImpl->stamps.size()) return false;

	return getSTimeStamp(num) < expected;
}

bool TimeMeter::isLess(unsigned num, int64_t expected) const {
	if (num >= pImpl->stamps.size()) return false;

	return getMSTimeStamp(num) < expected;
}

