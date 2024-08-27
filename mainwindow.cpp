#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Inicjalizacja połączenia z bazą danych
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("raspberrypi.local");
    db.setDatabaseName("water_flow_db");
    db.setUserName("raspberrypi");
    db.setPassword("Zaztpn795");

    // Tworzenie centralnego widżetu (to zostanie uruchomione tylko, jeśli połączenie się powiedzie)
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    db.close(); // Zamknij połączenie z bazą danych
}

bool MainWindow::connectToDatabase()
{
    if (!db.open()) {
        QMessageBox::critical(this, "Connection Error", "Nie można połączyć się z bazą danych!");
        return false;  // Zwróć false, jeśli połączenie się nie powiedzie
    } else {
        //QMessageBox::information(this, "Connection Success", "Połączenie z bazą danych nawiązane!");
        return true;  // Zwróć true, jeśli połączenie się powiedzie
    }
}
