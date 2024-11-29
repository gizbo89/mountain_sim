/*
 * logger.h
 *
 *  Created on: Oct 2, 2024
 *      Author: gizbo89
 */

#ifndef COMMON_LOGGER_H_
#define COMMON_LOGGER_H_
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
// Enum to represent log levels
enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
	~Logger();
	void log(LogLevel level, const string& message);
	Logger(Logger& other) = delete;
	void operator=(const Logger &) = delete;
	static Logger *GetInstance(const string& filename="/var/log/output.log");

private:
	Logger(const string& filename);
	static Logger* logger_;
	ofstream logFile; // File stream for the log file
    // Converts log level to a string for output
    string levelToString(LogLevel level);
};

#endif /* COMMON_LOGGER_H_ */
