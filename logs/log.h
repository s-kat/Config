#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

class Log {
private:
    std::string path_to_log_file = "logs/logs.txt";
    std::ofstream log_stream;

public:
    Log() {
        log_stream.open(path_to_log_file);
    }

    Log(Log &other) = delete;

    Log(std::string& _path_to_log_file) {
        log_stream.open(_path_to_log_file);
        path_to_log_file = _path_to_log_file;
    }

    void Log_trace(const std::string& log_to_write) {
        log_stream << "<" << currentDateTime() << "> " << log_to_write;
    }

    static Log& getInstance() {
        static Log instance;

        return instance;
    }

    std::string currentDateTime() {
        time_t now = time(0);
        struct tm tstruct;
        char buf[100];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }

    ~Log() {
        log_stream.close();
    }
};