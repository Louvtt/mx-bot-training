#ifndef _MX_CORE_MACROS_HPP_
#define _MX_CORE_MACROS_HPP_

#define MX_DEFAULT_LOGGER_NAME "MXLOGGER"

#include <spdlog/spdlog.h>

#define MX_INFO(...) spdlog::get(MX_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);
#define MX_ERROR(...) spdlog::get(MX_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);
#define MX_WARN(...) spdlog::get(MX_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);
#define MX_DEBUG(...) spdlog::get(MX_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);
#define MX_TRACE(...) spdlog::get(MX_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);

#endif //_MX_CORE_MACROS_HPP_