#pragma once
#include <chrono>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#define KE_TRACE_SCOPE(name) ke::KETraceScope KETraceScopeInstance(name)

namespace ke
{
    class KETrace
    {
    public:
        static void BeginEvent(const char* name)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _stream << "{"
                << "\"name\":\"" << name << "\","
                << "\"cat\":\"function\","
                << "\"ph\":\"B\","
                << "\"ts\":" << NowMicros() << ","
                << "\"pid\":0,"
                << "\"tid\":" << GetThreadId() << "},\n";
        }

        static void EndEvent(const char* name)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _stream << "{"
                << "\"name\":\"" << name << "\","
                << "\"cat\":\"function\","
                << "\"ph\":\"E\","
                << "\"ts\":" << NowMicros() << ","
                << "\"pid\":0,"
                << "\"tid\":" << GetThreadId() << "},\n";
        }

        static void Save(const char* filename = "trace.json")
        {
            std::lock_guard<std::mutex> lock(_mutex);
            std::ofstream file(filename, std::ios::out | std::ios::trunc);
            file << "[\n" << _stream.str() << "{}\n]";
            file.close();
        }

        static void Reset()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _stream.str("");
            _stream.clear();
        }

    private:
        static long long NowMicros()
        {
            using namespace std::chrono;
            return duration_cast<microseconds>(
                high_resolution_clock::now().time_since_epoch()).count();
        }

        static uint64_t GetThreadId()
        {
            std::hash<std::thread::id> hasher;
            return static_cast<uint64_t>(hasher(std::this_thread::get_id()));
        }

        inline static std::mutex _mutex;
        inline static std::ostringstream _stream;
    };

    // RAII Scope Wrapper
    class KETraceScope
    {
    public:
        explicit KETraceScope(const char* name)
            : _name(name)
        {
            KETrace::BeginEvent(name);
        }

        ~KETraceScope()
        {
            KETrace::EndEvent(_name);
        }

    private:
        const char* _name;
    };
}