#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool connectToDatabase();  // Publiczna funkcja do połączenia z bazą danych

private:
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
