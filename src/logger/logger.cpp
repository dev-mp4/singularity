#include "logger.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace singularity {

std::vector<LogEntry> LogStream::history;

LogStream::LogStream(const char* level) : level(level) {}
LogStream::~LogStream() {
    std::stringstream fmt;
    fmt << "[" << level << "] "
        << "[" << currentTime() << "] >> "
        << buffer.str();

    std::cout << fmt.str() << std::endl;
    
    history.push_back({fmt.str(), level});
}

LogStream& LogStream::operator<<(Manip manip) {
    manip(buffer);
    return *this;
}

std::string LogStream::currentTime() {
    std::time_t t = std::time(nullptr);

    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream ss;
    ss << std::put_time(&tm, "%H:%M:%S");
    return ss.str();
}

}