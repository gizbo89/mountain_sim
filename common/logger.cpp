// C++ program to implement a basic logging system using singleton design pattern.

#include "logger.h"

	Logger* Logger::logger_ = nullptr;


	Logger * Logger::GetInstance(const string& filename){
		if(logger_ == nullptr) logger_ = new Logger(filename);
		return logger_;
	}


	Logger::~Logger() {
		logFile.close();
	};

	// Constructor: Opens the log file in append mode
    Logger::Logger(const string& filename)
    {
        logFile.open(filename, ios::app);
        if (!logFile.is_open()) {
            cerr << "Error opening log file." << endl;
        }
    }

    // Logs a message with a given log level
    void Logger::log(LogLevel level, const string& message)
    {
        // Get current timestamp
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S", timeinfo);

        // Create log entry
        ostringstream logEntry;
        logEntry << "[" << timestamp << "] "
                 << levelToString(level) << ": " << message
                 << endl;

        // Output to console
        cout << logEntry.str();

        // Output to log file
        if (logFile.is_open()) {
            logFile << logEntry.str();
            logFile
                .flush(); // Ensure immediate write to file
        }
    }

    // Converts log level to a string for output
    string Logger::levelToString(LogLevel level)
    {
        switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }


