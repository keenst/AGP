#pragma once
#include <chrono>

namespace CommonUtilities
{


	class Timer
	{
	public:
		Timer();
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;
		~Timer();

		void Update();
		float GetDeltaTime() const;
		double GetTotalTime() const;
	private:
		std::chrono::high_resolution_clock::time_point myStartTime;
		std::chrono::high_resolution_clock::time_point myPreviousTime;
		float myDeltaTime;
		double myTotalTime;
	};
}