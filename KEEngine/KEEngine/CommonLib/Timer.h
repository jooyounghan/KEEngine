#pragma once
namespace ke
{
    class Timer
    {
    public:
        using Clock = std::chrono::steady_clock;
        using TimePoint = std::chrono::time_point<Clock>;
		using Duration = std::chrono::duration<float>;

    public:
        Timer();
        ~Timer() = default;

    public:
		inline void refreshClock() { _prevTime = Clock::now(); }
        
    public:
        void startClock();
        float getMeasuredTime() const;
        float getTotalTime() const;

    private:
        float getElapsedTime(const TimePoint& prevTime) const;

    private:
        TimePoint _firstTime;
        TimePoint _prevTime;
        bool _isWorking;
    };
}

