#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

using String = std::string;

class Logger {
    public:
        static Logger& instance(const String& filename = "test.txt") {
            static Logger log(filename);
            return log;
        }
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        
        void report(const String& txt) {
            fout_ << txt << std::endl;
        }
    
    private:
        Logger(String filename) : filename_(filename) {
            fout_.open(filename_, std::fstream::out | std::fstream::app);
        }
        ~Logger() {
            fout_.close();
        }

        String filename_;
        std::ofstream fout_;
};

#endif