#ifndef _MX_TIME_HPP_
#define _MX_TIME_HPP_

#include <cstdint>

namespace mx {

struct Time {
    double time;
    uint64_t frameCount;
};

}

#endif //_MX_TIME_HPP_