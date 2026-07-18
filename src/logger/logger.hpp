#ifndef SINGULARITY_LOGGER_HPP
#define SINGULARITY_LOGGER_HPP

#include <iostream>
#include <sstream>
#include <vector>

namespace singularity {

using Manip = std::ostream& (*)(std::ostream&);

struct LogEntry {
    std::string text;
    const char* level; // "INFO", "WARN", "ERROR"
};

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

    static const std::vector<LogEntry>& getHistory() { return history; }
    static void clearHistory() { history.clear(); }

private:
    const char* level;
    std::ostringstream buffer;

    static std::string currentTime();

    static std::vector<LogEntry> history;
};

struct Log {
    static LogStream info() { return LogStream("INFO"); }
    static LogStream warn() { return LogStream("WARN"); }
    static LogStream error() { return LogStream("ERROR"); }
};

}

#endif // SINGULARITY_LOGGER_HPP