#pragma once

#define CT_CONCAT_IMPL(a,b) a##b
#define CT_CONCAT(a,b) CT_CONCAT_IMPL(a,b)

#define CT_SCOPE(name_literal) \
  ke::ChromeTraceScope CT_CONCAT(__ct_scope__, __LINE__)(name_literal)

#define CT_SCOPE_CAT(name_literal, cat_literal) \
  ke::ChromeTraceScope CT_CONCAT(__ct_scope__, __LINE__)(name_literal, cat_literal)

#define CT_SCOPE_CAT_COLOR(name_literal, cat_literal, color_literal) \
  ke::ChromeTraceScope CT_CONCAT(__ct_scope__, __LINE__)(name_literal, cat_literal, color_literal)

#if defined(__GNUC__) || defined(__clang__)
#define CT_FUNCTION() CT_SCOPE(__PRETTY_FUNCTION__)
#define CT_FUNCTION_CAT(cat_literal) CT_SCOPE_CAT(__PRETTY_FUNCTION__, cat_literal)
#else
#define CT_FUNCTION() CT_SCOPE(__func__)
#define CT_FUNCTION_CAT(cat_literal) CT_SCOPE_CAT(__func__, cat_literal)
#endif

namespace ke
{
    using Clock = std::chrono::steady_clock;
    struct ThreadBuffer
    {
        std::vector<std::string> events;
        size_t bytes = 0;
        bool registered = false;
    };

    class ChromeTraceProfiler
    {
    public:
        static ChromeTraceProfiler& getInstance();

    private:
        ChromeTraceProfiler() = default;
        ~ChromeTraceProfiler();
        ChromeTraceProfiler(const ChromeTraceProfiler&) = delete;
        ChromeTraceProfiler& operator=(const ChromeTraceProfiler&) = delete;
       
    private:
        inline void setEnabled(bool enabled) { _isEnable.store(enabled, std::memory_order_relaxed); }

    public:
        inline bool isEnabled() const { return _isEnable.load(std::memory_order_relaxed); }
        inline void setFlushEventThreshold(size_t n) { _flushEventThreshold.store(n, std::memory_order_relaxed); }
        inline void setFlushByteThreshold(size_t bytes) { _flushByteThreshold.store(bytes, std::memory_order_relaxed); }

    public:
        bool beginSession(const std::string& traceFilePath);
        void endSession();

    public:
        size_t getNowFromProfiler() const;
        void writeDurationEvent( const char* name, const char* category, size_t tsBegin, size_t tsEnd);
        void flushThisThread();

    private:
        void endSessionLocked();
        void flushAllThreadBuffers();
        void flushThreadBuffer(ThreadBuffer& tb);
        ThreadBuffer& getThreadBuffer();

    private:
        static uint32_t getThreadId();
        static std::string escapeJson(const char* s);

    private:
        std::atomic<bool> _isEnable{ false };
        std::atomic<size_t> _flushEventThreshold{ 256 };
        std::atomic<size_t> _flushByteThreshold{ 64 * 1024 };

        std::mutex _fileMutex;
        std::ofstream _outFileStream;
        bool _firstEvent = true;

        std::mutex _registryMutex;
        std::unordered_set<ThreadBuffer*> _threadBuffers;

        Clock::time_point sessionStart_{ Clock::now() };
    };

    class ChromeTraceScope 
    {
    public:
        ChromeTraceScope(const char* name, const char* category = "scope");
        ~ChromeTraceScope();

    public:
        ChromeTraceScope(const ChromeTraceScope&) = delete;
        ChromeTraceScope& operator=(const ChromeTraceScope&) = delete;

    private:
        const char*             _name;
        const char*             _category;
        ChromeTraceProfiler&    _profiler;
        size_t                  _t0 = 0;
        bool                    _isActive = false;
    };

}