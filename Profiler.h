#pragma once
#include <chrono>
#include <string>
#include <qDebug>

enum eProfilingUnits
{
	AUTO,
	NANOSECONDS,
	MICROSECONDS,
	MILLISECONDS,
	SECONDS
};

class Profiler
{
public:
	Profiler(std::string name, eProfilingUnits units = AUTO)
	{
		name_ = name;
		profilingUnits_ = units;
		isStopped_ = false;
		profileTime_ = { "[us]" ,0.f };
		startTime_ = std::chrono::high_resolution_clock::now();
	}

	~Profiler()
	{
		if (!isStopped_)
			Stop();
	}

	struct ProfileTime
	{
		std::string units = "[us]";
		float elapsed = 0.f;
	};

	ProfileTime getElapsedTimeInAutoUnits(float timeInNano)
	{
		auto timeInSec = timeInNano / 1'000'000'000.f;
		if (timeInSec > 1.f)
			return { "[s]", timeInSec };

		auto timeInMili = timeInNano / 1'000'000.f;
		if (timeInMili > 1.f)
			return { "[ms]", timeInMili };

		auto timeInMicro = timeInNano / 1000.f;
		if (timeInMicro > 1.f)
			return { "[us]", timeInMicro };

		return { "[ns]", timeInNano };
	}


	void Stop()
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		switch (profilingUnits_)
		{
		case eProfilingUnits::AUTO:
		{
			float timeInNano = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime_).count());
			profileTime_ = getElapsedTimeInAutoUnits(timeInNano);
			break;
		}
		case eProfilingUnits::NANOSECONDS:
		{
			profileTime_ = { "[ns]" ,static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime_).count()) };
			break;
		}
		case eProfilingUnits::MICROSECONDS:
		{
			profileTime_ = { "[us]" ,static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime_).count()) };
			break;
		}
		case eProfilingUnits::MILLISECONDS:
		{
			profileTime_ = { "[ms]" ,static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count()) };
			break;
		}
		case eProfilingUnits::SECONDS:
		{
			profileTime_ = { "[s]" ,static_cast<float>(std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime_).count()) };
			break;
		}
		default:
		{
			profileTime_ = { "[ns]" ,static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime_).count()) };
			break;
		}
		}
		qDebug() << fixed << qSetRealNumberPrecision(2) << "Profiler: " << name_.c_str() << " " << profileTime_.elapsed << profileTime_.units.c_str();
		isStopped_ = true;
	}

private:
	std::string name_;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
	eProfilingUnits profilingUnits_;
	ProfileTime profileTime_;
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

