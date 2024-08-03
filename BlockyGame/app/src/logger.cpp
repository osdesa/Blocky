#include "logger.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "assert.h"
#include <windows.h>   

// Creates sigleton of the logger
Logger& Logger::get_instance()
{
    static Logger logger;
    return logger;
}

void Logger::init(const char* filePath)
{
    // creates singleton
    Logger& logger_instance = get_instance();
    // Sets up the file path for the log file
    logger_instance.filepath = filePath;
    // Creates log file
    std::string filename(filePath);
    // opens the logging file
    logger_instance.logFile.open(filename, std::ios_base::out);

    // Checks to see if the log file is opened successfully
    if(logger_instance.logFile.is_open() == false)
        logger_instance.output(FATAL, "Error opening '%s'",filePath);
    else
        logger_instance.output(INFO, "Opened logging file '%s'",filePath);
}

void Logger::output(error_levels level, const char* msg, ...)
{
    // if the program is in realse do not display info errors for performance reasons
    if(RELEASE && level == INFO)
        return;
    // Gets the loggers handle
    Logger& logger_instance = get_instance();
    // Gets the current time
    time_t curtime;
    time(&curtime);

    // array for colours and the type of errors
    static const int colour[6] = {RED, GREEN, YELLOW, GREY, DARKBLUE ,BLUE};
    // Spacing for nice looking logging files
    static const char* type[6] = {"[FATAL]       ", "[CRITICAL]    ", "[WARNING]     ","[VALIDATION]  ", "[KEY INFO]    ","[INFO]        "};

    // the buffer for the characters in c style
    char buffer[65536];

    // creates arg list which can have many values put into it
    va_list args;

    // adds msg to buffer | will have an overflow if the msg is more than given char size
    // Do not allow the user to impact log messages unless they are checked for size
    va_start(args, msg);
    int check = vsnprintf (buffer, 4096 , msg, args);
    // Makes sure the message is within the range
    assert(check != 0 && check < 4096);

    // Gets the console handle to allow for colour access
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Sets the colours in the colours
    SetConsoleTextAttribute(hConsole, (int)colour[level]);

    // writes to the console
    std::cout << type[level] << "  :  " << buffer << std::endl;
    // Writes to a log file
    logger_instance.logFile << type[level] << " : " << buffer << "\n";
    // stops the reading
    va_end(args);   
    // sets the text colour to white
    SetConsoleTextAttribute(hConsole, WHITE);

    // if it is a fatal error stop the program with an error message
    if (level == FATAL) {
        exit(-1);
    }
}

void Logger::shutdown()
{
    // Get the logger handle
    Logger& logger_instance = get_instance();
    // Display that the logger is closing
    logger_instance.output(INFO, "Closing log file: %s", logger_instance.filepath);
    // Close the log file
    logger_instance.logFile.close();
}

