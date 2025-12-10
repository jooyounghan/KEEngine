#include "FlyweightString.h"

namespace ke
{
	template<>
	size_t HashGenerator<FlyweightStringA>::convertToHash(const FlyweightStringA& value)
	{
		return value.getEntryIndex();
	}
}

namespace std 
{
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const noexcept {
            // 간단한 해시 조합
            return ((std::hash<int>()(p.x) << 1) ^ std::hash<int>()(p.y));
        }
    };
}