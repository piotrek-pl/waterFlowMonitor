#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    // Sprawdź połączenie z bazą danych przed pokazaniem okna
    if (!w.connectToDatabase()) {
        QMessageBox::critical(nullptr, "Connection Error", "Nie można połączyć się z bazą danych!");
        return -1;  // Zakończ aplikację, jeśli połączenie się nie powiedzie
    }

    w.show();  // Pokaż MainWindow tylko, jeśli połączenie się powiedzie

    return a.exec();
}
