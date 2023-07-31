#ifndef _MX_PLATFORM_HPP_
#define _MX_PLATFORM_HPP_

#if defined(WIN32) || defined(_WIN32)
#   define MX_WINDOWS
#   warning "Not fully supported yet"
#elif defined(__unix__) || defined(__linux__)
#   define MX_LINUX
#elif defined(MACOS)
#   define MX_MACOS
#   error "Mac not supported"
#endif

#endif //_MX_PLATFORM_HPP_