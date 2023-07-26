#ifndef _MX_FILEUTILS_HPP_
#define _MX_FILEUTILS_HPP_

#include <string>

namespace mx {

bool fileExists(const std::string& path);

int getFileModifiedTimeSec(const std::string& path);

}

#endif //_MX_FILEUTILS_HPP_