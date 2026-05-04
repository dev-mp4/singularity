#include "logger.hpp"
#include <ctime>
#include <iomanip>

namespace singularity {

LogStream::LogStream(const char* level) : level(level) {}
LogStream::~LogStream() {
    // flush on destruction
    std::cout << "[" << level << "] "
        << "[" << currentTime() << "] >> "
        << buffer.str() << std::endl;
}

LogStream& LogStream::operator<<(Manip manip) {
    manip(buffer);
    return *this;
}

std::string LogStream::currentTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    std::ostringstream ss;
    ss << std::put_time(&tm, "%H:%M:%S");
    return ss.str();
}

}