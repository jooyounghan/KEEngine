#include "CommonLibPch.h"
#include "ChromeTraceProfiler.h"

namespace ke
{
    ChromeTraceProfiler& ChromeTraceProfiler::getInstance()
    {
        static ChromeTraceProfiler inst;
        return inst;
    }
    
    ChromeTraceProfiler::~ChromeTraceProfiler() 
    {
        try { endSession(); }
        catch (...) {}
    }

    bool ChromeTraceProfiler::beginSession(const std::string& traceFilePath)
    {
        setEnabled(true);
        std::lock_guard<std::mutex> lock(_fileMutex);
        
        if (_outFileStream.is_open()) endSessionLocked();

        _outFileStream.open(traceFilePath, std::ios::out | std::ios::trunc);
        if (!_outFileStream.is_open()) return false;

        _firstEvent = true;
        sessionStart_ = Clock::now();

        _outFileStream << "{\"traceEvents\":[";
        _outFileStream.flush();
        return true;
    }

    void ChromeTraceProfiler::endSession() 
    {
		setEnabled(false);

        flushAllThreadBuffers();

        std::lock_guard<std::mutex> lock(_fileMutex);
        endSessionLocked();
    }

    size_t ChromeTraceProfiler::getNowFromProfiler() const
    {
        const auto now = Clock::now();
        return (uint64_t)std::chrono::duration_cast<std::chrono::microseconds>(now - sessionStart_).count();
    }

    void ChromeTraceProfiler::writeDurationEvent(const char* name, const char* category, size_t tsBegin, size_t tsEnd)
    {
		static size_t colorIndex = 0;
        static std::vector<const char*> colors = {
            "thread_state_running"
            , "good"
            , "bad"
            , "terrible"
            , "yellow"
            , "olive"
            , "generic_work"
        };

        if (!isEnabled()) return;

		colorIndex = (colorIndex + 1) % colors.size();
		const char* cname = colors[colorIndex];

        ThreadBuffer& tb = getThreadBuffer();
        const uint32_t tid = getThreadId();
        const size_t dur = (tsEnd >= tsBegin) ? (tsEnd - tsBegin) : 0;

        std::string ev;
        ev.reserve(160);
        ev += "{";
        ev += "\"name\":\""; ev += escapeJson(name); ev += "\",";
        ev += "\"cat\":\"";  ev += escapeJson(category ? category : "scope"); ev += "\",";
        ev += "\"ph\":\"X\",";
        ev += "\"ts\":";   ev += std::to_string(tsBegin); ev += ",";
        ev += "\"dur\":";  ev += std::to_string(dur); ev += ",";
        ev += "\"pid\":0,";
        ev += "\"tid\":";  ev += std::to_string(tid);
        ev += ",\"cname\":\""; ev += escapeJson(cname); ev += "\"";
        ev += "}";

        tb.bytes += ev.size();
        tb.events.emplace_back(std::move(ev));

        const size_t evTh = _flushEventThreshold.load(std::memory_order_relaxed);
        const size_t byTh = _flushByteThreshold.load(std::memory_order_relaxed);

        if (tb.events.size() >= evTh || tb.bytes >= byTh) {
            flushThreadBuffer(tb);
        }
    }

    void ChromeTraceProfiler::flushThisThread()
    {
        if (!isEnabled()) return;
        ThreadBuffer& tb = getThreadBuffer();
        flushThreadBuffer(tb);
    }

    void ChromeTraceProfiler::endSessionLocked()
    {
        if (!_outFileStream.is_open()) return;
        _outFileStream << "]}";
        _outFileStream.flush();
        _outFileStream.close();
    }

    void ChromeTraceProfiler::flushAllThreadBuffers() 
    {
        std::vector<ThreadBuffer*> buffersCopy;
        {
            std::lock_guard<std::mutex> lock(_registryMutex);
            buffersCopy.assign(_threadBuffers.begin(), _threadBuffers.end());
        }

        for (ThreadBuffer* tb : buffersCopy) 
        {
            if (tb) flushThreadBuffer(*tb);
        }
    }

    void ChromeTraceProfiler::flushThreadBuffer(ThreadBuffer& tb) {
        if (tb.events.empty()) return;

        std::lock_guard<std::mutex> lock(_fileMutex);
        if (!_outFileStream.is_open()) 
        {
            tb.events.clear();
            tb.bytes = 0;
            return;
        }

        for (const auto& ev : tb.events) {
            if (!_firstEvent) _outFileStream << ",";
            _firstEvent = false;
            _outFileStream << ev;
        }
        // out_.flush();

        tb.events.clear();
        tb.bytes = 0;
    }

    ThreadBuffer& ChromeTraceProfiler::getThreadBuffer() 
    {
        thread_local ThreadBuffer tb;
        if (!tb.registered) 
        {
            std::lock_guard<std::mutex> lock(_registryMutex);
            _threadBuffers.insert(&tb);
            tb.registered = true;
        }
        return tb;
    }
    
    uint32_t ChromeTraceProfiler::getThreadId() 
    {
        static thread_local uint32_t tid =
            (uint32_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
        return tid;
    }

    std::string ChromeTraceProfiler::escapeJson(const char* s) 
    {
        std::string out;
        if (!s) return out;
        for (const char* p = s; *p; ++p) 
        {
            switch (*p) {
            case '\"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:   out += *p; break;
            }
        }
        return out;
    }

    ChromeTraceScope::ChromeTraceScope(const char* name, const char* category )
        : _name(name), _category(category), _profiler(ChromeTraceProfiler::getInstance()) 
    {
        if (!_profiler.isEnabled()) return;

        _t0 = _profiler.getNowFromProfiler();
        _isActive = true;
    }

    ChromeTraceScope::~ChromeTraceScope() 
    {
        if (!_isActive) return;
        const size_t t1 = _profiler.getNowFromProfiler();
        _profiler.writeDurationEvent(_name, _category, _t0, t1);
    }
}
