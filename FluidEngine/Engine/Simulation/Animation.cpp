#include "Animation.h"

#include "Timer.h"

#include <iostream>

namespace Engine
{
	Frame::Frame() { }

	Frame::Frame(int newIndex, double newTimeIntervalInSeconds)
		: index(newIndex) , timeIntervalInSeconds(newTimeIntervalInSeconds) { }

	double Frame::timeInSeconds() const { return index * timeIntervalInSeconds; }

	void Frame::advance() { ++index; }

	void Frame::advance(int delta) { index += delta; }

	Frame& Frame::operator++() { advance(); return *this; }

	Frame Frame::operator++(int i) { Frame result = *this; advance(); return result; }

	Animation::Animation() { }

	Animation::~Animation() { }

	void Animation::update(const Frame& frame) 
	{
		Timer timer;
		std::cout << "---------------------------------------------------\n";
		std::cout << "Begin updating frame: " << frame.index
			<< " timeIntervalInSeconds: " << frame.timeIntervalInSeconds
			<< " (1/" << 1.0 / frame.timeIntervalInSeconds
			<< ") seconds" << std::endl;

		onUpdate(frame);

		std::cout << "End updating frame (took " << timer.durationInSeconds()
			<< " seconds)" << std::endl;
		std::cout << "---------------------------------------------------\n";
	}
}