#include "CommonLibPch.h"
#include "Timer.h"

namespace ke
{
    Timer::Timer() : _isWorking(false)
    {
    }

    void Timer::startClock()
    {
        _firstTime = Clock::now();
        _prevTime = Clock::now();
        _isWorking = true;
    }

    float Timer::getMeasuredTime() const
    {
        if (!_isWorking)
        {
			KE_ASSERT_DEV(false, "Timer is not running.");
            return 0.f;
        }
        return getElapsedTime(_prevTime);
    }

    float Timer::getTotalTime() const
    {
        return getElapsedTime(_firstTime);
    }

    float Timer::getElapsedTime(const TimePoint& prevTime) const
    {
        TimePoint currentTime = Clock::now();
        Duration elapsed = currentTime - prevTime;
        return elapsed.count();
    }

}
