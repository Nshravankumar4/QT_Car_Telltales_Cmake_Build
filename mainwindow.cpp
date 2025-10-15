#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QPixmap>
#include <QDir>
#include <QDebug>

// Constructor for MainWindow class
// Initializes UI and sets up the timer for flashing indicators
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Sets up the UI elements from mainwindow.ui
    ui->setupUi(this);

    // Initialize state variables
    leftState = false;       // true = left indicator ON, false = OFF
    rightState = false;      // true = right indicator ON, false = OFF
    leftFlashState = false;  // toggling flag for flashing effect
    rightFlashState = false; // toggling flag for flashing effect

    // Timer for flashing indicators every 500ms
    // QTimer emits a timeout signal periodically
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimer); // connect signal to slot
    timer->start(500); // interval = 500 milliseconds
}

// Destructor for MainWindow class
MainWindow::~MainWindow()
{
    delete ui; // clean up UI pointer
}

// This function is called every 500ms by the timer
// Responsible for updating the visual indicators (flashing effect)
void MainWindow::onTimer()
{
    // Read the XML file and update leftState and rightState
    updateTelltales();

    // Path where the indicator images are stored
    QString imgPath = QDir::currentPath() + "/images/";

    // Handle LEFT indicator flashing
    if(leftState) {
        leftFlashState = !leftFlashState; // toggle flash state
        ui->leftIndicatorLabel->setPixmap(QPixmap(
            leftFlashState ? imgPath + "left_on.png" : imgPath + "left_off.png"
            ));
    } else {
        // If left indicator is OFF, show OFF image
        ui->leftIndicatorLabel->setPixmap(QPixmap(imgPath + "left_off.png"));
    }

    // Handle RIGHT indicator flashing
    if(rightState) {
        rightFlashState = !rightFlashState; // toggle flash state
        ui->rightIndicatorLabel->setPixmap(QPixmap(
            rightFlashState ? imgPath + "right_on.png" : imgPath + "right_off.png"
            ));
    } else {
        // If right indicator is OFF, show OFF image
        ui->rightIndicatorLabel->setPixmap(QPixmap(imgPath + "right_off.png"));
    }
}

// Reads XML file and updates the indicator states
// XML structure example:
// <root>
//     <Telltale id="LeftIndicator" value="1"/>
//     <Telltale id="RightIndicator" value="0"/>
// </root>
void MainWindow::updateTelltales()
{
    QFile file("xml/11inch.xml"); // Open XML file
    if(!file.open(QIODevice::ReadOnly)) return; // Exit if cannot open

    QDomDocument doc; // DOM object to parse XML
    if(!doc.setContent(&file)) { file.close(); return; } // Exit if parse fails
    file.close(); // Close file after reading

    QDomElement root = doc.documentElement(); // Get the root element

    // Read LEFT indicator value from XML
    QDomElement leftElem = root.firstChildElement("Telltale");
    if(leftElem.attribute("id") == "LeftIndicator")
        leftState = leftElem.attribute("value").toInt() != 0; // convert 0/1 to bool

    // Read RIGHT indicator value from XML
    // Loop through all <Telltale> elements until RightIndicator is found
    QDomElement rightElem = root.firstChildElement("Telltale");
    while(!rightElem.isNull()) {
        if(rightElem.attribute("id") == "RightIndicator") {
            rightState = rightElem.attribute("value").toInt() != 0; // convert 0/1 to bool
            break; // stop loop once found
        }
        rightElem = rightElem.nextSiblingElement("Telltale"); // move to next element
    }
}
