#include <chrono>
#include <sstream>
#include <ctime>

#include "Utility.hpp"

std::string GetDateAndTime() {
    using std::chrono::system_clock;
    system_clock::time_point today = system_clock::now();
    std::time_t tt = system_clock::to_time_t(today);
    std::stringstream ss;
    ss << ctime(&tt);
    return ss.str();
}
