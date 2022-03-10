#include "Logger.hpp"

Logger::Logger()
{
    lout.open("log.txt", std::ios::app);
}

void Logger::writeMessage(std::string message)
{
    lout << message << "\n";
}
