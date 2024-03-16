#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"
#include "game.h"

extern Game* game;

GameOverWindow::GameOverWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);
    int scoreVal = game->getScoreVal();
    ui->scoreLabel->setText("Your Score: " + QString::number(scoreVal));
}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}

void GameOverWindow::on_playAgainBtn_clicked() {
    hide();
    game->getScene()->clear();
    game->start();
}


void GameOverWindow::on_exitBtn_clicked()
{
    close();
}

