#ifndef SINGULARITY_LOGGER_HPP
#define SINGULARITY_LOGGER_HPP

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

class LogStream {
public:
    LogStream(const char* level) : level(level) {}

    ~LogStream() {
        // flush on destruction
        std::cout << "[" << level << "] "
                  << "[" << currentTime() << "] >> "
                  << buffer.str() << std::endl;
    }

    template<typename T>
    LogStream& operator<<(const T& value) {
        buffer << value;
        return *this;
    }

    // support std::endl and other manipulators
    using Manip = std::ostream& (*)(std::ostream&);
    LogStream& operator<<(Manip manip) {
        manip(buffer);
        return *this;
    }

private:
    const char* level;
    std::ostringstream buffer;

    static std::string currentTime() {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream ss;
        ss << std::put_time(&tm, "%H:%M:%S");
        return ss.str();
    }
};

struct Log {
    static LogStream info() { return LogStream("INFO"); }
    static LogStream warn() { return LogStream("WARN"); }
    static LogStream error() { return LogStream("ERROR"); }
};

#endif // SINGULARITY_LOGGER_HPP