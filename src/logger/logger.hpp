#ifndef SINGULARITY_LOGGER_HPP
#define SINGULARITY_LOGGER_HPP

#include <iostream>
#include <sstream>

namespace singularity {

using Manip = std::ostream& (*)(std::ostream&);

class LogStream {
public:
    LogStream(const char* level);
    ~LogStream();

    template<typename T>
    LogStream& operator<<(const T& value) {
        buffer << value;
        return *this;
    }

    LogStream& operator<<(Manip manip);

private:
    const char* level;
    std::ostringstream buffer;

    static std::string currentTime();
};

struct Log {
    static LogStream info() { return LogStream("INFO"); }
    static LogStream warn() { return LogStream("WARN"); }
    static LogStream error() { return LogStream("ERROR"); }
};

}

#endif // SINGULARITY_LOGGER_HPP