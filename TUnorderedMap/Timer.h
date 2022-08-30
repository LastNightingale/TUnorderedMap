#pragma once
#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer()
	{
		std::chrono::high_resolution_clock::now();
	}
	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << "Duration: " << duration << "ms " << std::endl;
	}
	~Timer()
	{
		Stop();
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};
