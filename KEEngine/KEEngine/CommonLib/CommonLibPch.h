// Standard Library Includes

// I/O
#include <cstdio>
#include <fstream>

// Timer
#include <chrono>

// Strings
#include <string>
#include <string_view>
#include <charconv>

// Containers
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

// Smart Pointer
#include "Ptr.h"
#include "RefCountedPtr.h"

// Threading
#include <atomic>
#include <mutex>

// Project Includes
#include "MacroCommon.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#endif

#include "TypeCommon.h"
#include "EnumCommon.h"
#include "AssertCommon.h"
#include "SimdCommon.h"
#include "TraitCommon.h"

#include "ChromeTraceProfiler.h"