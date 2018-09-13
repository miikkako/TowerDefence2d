#ifndef GAME_LOGGER_HPP
#define GAME_LOGGER_HPP

#include "config.hpp"

#if DEBUG

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

namespace
{
    char* get_time_now_str()
    {
        const std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return std::ctime(&now);
    }
}
#define LOG_DEBUG(x) \
do { \
    std::cerr << "[ " << get_time_now() << ", " << __FILE__ << ":" <<  __LINE__ << ":" << __func__ << x \
} while (0)

#else
#define LOG_DEBUG(x) /* empty */
#endif

#endif //GAME_LOGGER_HPP
