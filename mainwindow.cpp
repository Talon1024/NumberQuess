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
    g = Game();
    RE_NUM = QRegularExpression("^\\d+$");

    gameInfoFmt = ui->lblGameInfo->text();
    gameStatusFmt = ui->lblGameStatus->text();

    ui->lblGameInfo->setText(gameInfoFmt.arg(
                                 QString().setNum(g.minNumber),
                                 QString().setNum(g.maxNumber)
                                 ));
    ui->statusBar->addWidget(ui->lblAnsStatus);
    ui->statusBar->addWidget(ui->lblGameStatus);
    updateInfo(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInfo(bool eraseStatus = false) {
    if (eraseStatus) ui->lblAnsStatus->setText("");
    if (!g.isOver()) {
        ui->lblGameStatus->setText(gameStatusFmt.arg(
                        QString().setNum(g.getGuessesLeft()),
                        g.getGuessesLeft() != 1 ? tr("guesses") : tr("guess")));
    } else {
        ui->lblGameStatus->setText("");
    }

}

void MainWindow::gameOver() {
    ui->btnSubmit->setEnabled(false);
    ui->txtUserInput->setEnabled(false);
}

void MainWindow::on_btnSubmit_clicked()
{
    if (g.isOver()) {
        gameOver();
        QMessageBox::warning(this, tr("Game over"), tr("Game over! Press reset to play again."));
    } else {
        // Check user input - surely, there's a better way to do it with Qt.
        QString ansString = ui->txtUserInput->text().trimmed();
        QRegularExpressionMatch match = RE_NUM.match(ansString);
        if (match.hasMatch()) {
            int correct = g.guess(ansString.toInt());

            if (correct == 1) { // greater than my number
                ui->lblAnsStatus->setText(tr("Too high! Try again."));
            } else if (correct == -1) {
                ui->lblAnsStatus->setText(tr("Too low! Try again."));
            } else if (correct == -2) {
                gameOver();
                ui->lblAnsStatus->setText(tr("Game over! Press reset to play again."));
            } else if (correct == 0) {
                gameOver();
                ui->lblAnsStatus->setText(
                            QString(tr("Congratulations! You successfully guessed the number in %1 %2.")).arg(
                                QString().setNum(g.startingGuesses - g.getGuessesLeft()),
                                g.startingGuesses - g.getGuessesLeft() != 1 ? tr("tries") : tr("try")));
            }

            updateInfo();
        } else {
            QMessageBox::warning(this, tr("Invalid input"), tr("You must enter a valid integer."));
        }
    }
}

void MainWindow::on_btnReset_clicked()
{
    g.reset();
    ui->btnSubmit->setEnabled(true);
    ui->txtUserInput->setEnabled(true);
    updateInfo(true);
}

void MainWindow::on_actionRestart_triggered()
{
    on_btnReset_clicked();
}

void MainWindow::on_actionQ_uit_triggered()
{
    close();
}
