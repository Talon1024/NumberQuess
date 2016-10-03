#include "mainwindow.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g = new Game();
    RE_NUM = new QRegularExpression("^\\d+$");

    gameInfoFmt = ui->lblGameInfo->text();
    gameStatusFmt = ui->lblGameStatus->text();

    ui->lblGameInfo->setText(gameInfoFmt.arg(
                                 QString().setNum(g->minNumber),
                                 QString().setNum(g->maxNumber)
                                 ));
    ui->lblGameStatus->setText(gameStatusFmt.arg(
                                   QString().setNum(g->getGuessesLeft()),
                                   g->getGuessesLeft() != 1 ? "guesses" : "guess"));
    ui->lblAnsStatus->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSubmit_clicked()
{
    // Check user input - surely, there's a better way to do it with Qt.
    QString ansString = ui->txtUserInput->text().trimmed();
    QRegularExpressionMatch match = RE_NUM->match(ansString);
    if (match.hasMatch()) {
        int correct = g->guess(ansString.toInt());

        if (correct == 1) { // greater than my number
            ui->lblAnsStatus->setText("Too high! Try again.");
        } else if (correct == -1) {
            ui->lblAnsStatus->setText("Too low! Try again.");
        } else if (correct == -2) {
            ui->lblAnsStatus->setText("Game over! Press reset to play again.");
            QMessageBox::information(this, "Game over", "Game over! Press reset to play again.");
        } else if (correct == 0) {
            ui->lblAnsStatus->setText(QString("Congratulations! You successfully guessed the number in %1 tries.").arg(g->startingGuesses - g->getGuessesLeft()));
        }

        ui->lblGameStatus->setText(gameStatusFmt.arg(
                                       QString().setNum(g->getGuessesLeft()),
                                       g->getGuessesLeft() != 1 ? "guesses" : "guess"));
    } else {
        QMessageBox::warning(this, "Invalid input", "You must enter a valid integer.");
    }
}

void MainWindow::on_btnReset_clicked()
{
    g->reset();
}

void MainWindow::on_actionRestart_triggered()
{
    on_btnReset_clicked();
}

void MainWindow::on_actionQ_uit_triggered()
{
    close();
}
