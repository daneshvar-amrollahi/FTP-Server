#include "Logger.hpp"

Logger::Logger()
{
    
}

void Logger::writeMessage(std::string message)
{
    std::ofstream lout;
    lout.open("log.txt", std::ios::app);
    lout << message << "\n";
    lout.close();
}
