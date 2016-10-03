#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSubmit_clicked();

    void on_btnReset_clicked();

    void on_actionRestart_triggered();

    void on_actionQ_uit_triggered();

private:
    Ui::MainWindow* ui;
    QRegularExpression* RE_NUM;
    Game* g;

    QString gameInfoFmt, gameStatusFmt;
};

#endif // MAINWINDOW_H
