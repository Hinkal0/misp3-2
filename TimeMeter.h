#pragma once
#include <memory>

class TimeMeter {
	struct Impl;
	std::unique_ptr<Impl> pImpl;
public:
	TimeMeter(unsigned count);
	~TimeMeter();

	void setTimeStamp(unsigned num);

	double getSTimeStamp(unsigned num) const;
	int64_t getMSTimeStamp(unsigned num) const;

	double getSDiff(unsigned first, unsigned second) const;
	int64_t getMSDiff(unsigned first, unsigned second) const;

	bool isLess(unsigned num, double expected) const;
	bool isLess(unsigned num, int64_t expected) const;
};
