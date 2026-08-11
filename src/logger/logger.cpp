#include "logger.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>

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

void LogStream::saveLogs() {
    std::ofstream file("log.txt");
    if (!file.is_open()) {
        Log::error() << "Failed to save logs to log.txt!";
        return;
    }

    for (auto log : history) {
        file << log.text << std::endl;
    }

    file.close();
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