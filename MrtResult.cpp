#include <MrtResult.h>
std::ostream& operator<<(std::ostream& os, const MrtResult& res)
{
    os << res.StationName << "(" << res.NumTransitsRequired << ")";
    return os;
}