#pragma once
#include <chrono>
#include <string>

enum eProfilingUnits
{
	NANOSECONDS,
	MICROSECONDS,
	MILLISECONDS,
	SECONDS
};

class Profiler
{
public:
	Profiler(std::string name, eProfilingUnits units = MICROSECONDS)
	{
		name_ = name;
		profilingUnits_ = units;
		isStopped_ = false;
		startTime_ = std::chrono::high_resolution_clock::now();
	}

	~Profiler()
	{
		if (!isStopped_)
			Stop();
	}

	void Stop()
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		switch (profilingUnits_)
		{
		case eProfilingUnits::NANOSECONDS:
		{
			qDebug() << ("Profiler: %s\n", std::string(name_ + " " + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime_).count()) + "[ns]").c_str());
			break;
		}
		case eProfilingUnits::MICROSECONDS:
		{
			qDebug() << ("Profiler: %s\n", std::string(name_ + " " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime_).count()) + "[us]").c_str());
			break;
		}
		case eProfilingUnits::MILLISECONDS:
		{
			qDebug() << ("Profiler: %s\n", std::string(name_ + " " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count()) + "[ms]").c_str());
			break;
		}
		case eProfilingUnits::SECONDS:
		{
			qDebug() << ("Profiler: %s\n", std::string(name_ + " " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime_).count()) + "[s]").c_str());
			break;
		}
		default:
		{
			qDebug() << ("Profiler: %s\n", std::string(name_ + " " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime_).count()) + "[us]").c_str());
			break;
		}
		}
		isStopped_ = true;
	}

private:
	std::string name_;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
	eProfilingUnits profilingUnits_;
	bool isStopped_;
};


#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) Profiler timer##__LINE__(name)
#define PROFILE_SCOPE_IN_UNITS(name,units) Profiler timer##__LINE__(name,units)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#define PROFILE_FUNCTION_IN_UNITS(units) PROFILE_SCOPE_IN_UNITS(__FUNCTION__,units)

#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#define PROFILE_SCOPE_IN_UNITS(name,units)
#define PROFILE_FUNCTION_IN_UNITS(units)
#endif