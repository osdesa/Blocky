#include <iostream>

#include "app.h"
#include "logger.h"

int main()
{
    // Starts the logger
    Logger::init("log.txt");
    // Displays by the logger that the program has started
    Logger::output(KEYINFO, "Program Start");
    
    // Creates the application
    Blocky::App app;
    // Start the app
    app.Start();
}