#include "mainwindow.h"
#include <QApplication>

// Entry point of the Qt application
int main(int argc, char *argv[])
{
    // QApplication object manages application-wide resources
    // It initializes the GUI toolkit and handles the event loop
    QApplication a(argc, argv);

    // Create an instance of MainWindow (our main GUI window)
    MainWindow w;

    // Show the main window on the screen
    w.show();

    // Start the Qt event loop
    // This loop waits for user events (mouse clicks, key presses, timers, etc.)
    // and dispatches them to the appropriate widgets
    return a.exec();
}
