#include "TimeMeter.h"
#include <Windows.h>
#include <vector>

struct TimeMeter::Impl {
	std::vector<LARGE_INTEGER> stamps;
	LARGE_INTEGER start;
	LARGE_INTEGER frequency;

	Impl(unsigned count) : stamps(count) {
		QueryPerformanceCounter(&start);
    QueryPerformanceFrequency(&frequency);
    std::fill(stamps.begin(), stamps.end(), start);
	}
};

TimeMeter::TimeMeter(unsigned count) : pImpl(std::make_unique<Impl>(count)) {}
TimeMeter::~TimeMeter() = default;

void TimeMeter::setTimeStamp(unsigned num) {
	if (num >= pImpl->stamps.size()) return;

	QueryPerformanceCounter(&pImpl->stamps[num]);
}

double TimeMeter::getSTimeStamp(unsigned num) const {
	if (num >= pImpl->stamps.size()) return -1;

	return double(pImpl->stamps[num].QuadPart-pImpl->start.QuadPart)/pImpl->frequency.QuadPart;
}	

int64_t TimeMeter::getMSTimeStamp(unsigned num) const {
	if (num >= pImpl->stamps.size()) return -1;

	return double(pImpl->stamps[num].QuadPart-pImpl->start.QuadPart)/pImpl->frequency.QuadPart*1000.0;
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

