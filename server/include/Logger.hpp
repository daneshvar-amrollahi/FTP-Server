#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>

class Logger
{
public:
    Logger();
    static void writeMessage(std::string message);
};

#endif