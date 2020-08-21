#include "GTest.hpp"

#include <stddef.h>

namespace testing {

void ExcludeTests(std::string const & pattern)
{
    std::string & filter = GTEST_FLAG(filter);

    size_t position = filter.find("-");
    if (position != std::string::npos)
        filter.insert(position + 1, pattern + ":");
    else
    {
        if (!filter.empty() && filter.back() != ':')
            filter += ":";
        filter += "-" + pattern;
    }
}

} // namespace testing
