#include "logger.hpp"

int main(int argc, char *argv[]) {
    Logger &log = Logger::instance(argv[1]);
    log.report("Hello, world!");

    log.report("we up");

    Logger &log2 = Logger::instance("shouldntWORK.txt");
    log2.report("Goodbye, world!");

    return 0;
}