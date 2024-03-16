#include "game.h"
#include "enemy.h"
#include <QObject>
#include <QImage>
#include "gameoverwindow.h"

Game::Game() {
    scene = new QGraphicsScene();
}

void Game::start() {
    // create a view
    setScene(scene);
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // add the player
    player = new Player();

    // adding the score
    score = new Score();

    // adding the health
    health = new Health();

    // set the scene
    scene->setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(QBrush(QImage(":/images/img/bg_img.jpg")));

    // set the player
    int playerLength = 100;
    scene->addItem(player);

    // *******  Adjust the location of the Player (middle of the screen) ********
    player->setPos(width()/2 - playerLength/2, height() - playerLength);

    // set the player to focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // adding enemies
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(spawn()));
    timer->start(2000);

    // health & score
    health->setPos(0, 25);
    scene->addItem(health);
    scene->addItem(score);

    // adding backgound music
    musicPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/sounds/bgSound.mp3"));
    audioOutput->setVolume(40);
    musicPlayer->play();
    // show the game
    show();
}

void Game::deallocateMemory() {
    delete player;
    delete timer;
    delete score;
    delete health;
    delete musicPlayer;
    delete audioOutput;
}

void Game::gameOver() {
    GameOverWindow* gameOver = new GameOverWindow();
    gameOver->show();
    musicPlayer->stop();
    timer->stop();
    deallocateMemory();
    scene->clear();
    hide();
}

void Game::spawn() {
    Enemy* enemy = new Enemy();
    scene->addItem(enemy);
}

int Game::getScoreVal() {return score->getScoreVal();}

Score* Game::getScore() {return score;}
Health* Game::getHealth() {return health;}

QGraphicsScene* Game::getScene() {return scene;}
