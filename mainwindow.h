#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } // Forward declaration of UI class
QT_END_NAMESPACE

// MainWindow class inherits from QMainWindow
// This is the main GUI window of the application
class MainWindow : public QMainWindow
{
    Q_OBJECT // Required for signals and slots in Qt

public:
    // Constructor: initializes the window
    // 'parent' is optional; usually nullptr for top-level windows
    MainWindow(QWidget *parent = nullptr);

    // Destructor: cleans up UI and allocated resources
    ~MainWindow();

private:
    Ui::MainWindow *ui; // Pointer to the auto-generated UI class

    // Telltale indicator states
    bool leftState;       // true = left indicator ON, false = OFF
    bool rightState;      // true = right indicator ON, false = OFF
    bool leftFlashState;  // toggles to create blinking effect for left indicator
    bool rightFlashState; // toggles to create blinking effect for right indicator

    // Function to read the XML file and update indicator states
    void updateTelltales();

private slots:
    // Slot function called by the QTimer every 500ms
    // Responsible for updating the indicators (flash & static)
    void onTimer();
};

#endif // MAINWINDOW_H
