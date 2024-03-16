#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QTimer>
#include "game.h"
#include <QMediaPlayer>
#include <QAudioOutput>

extern Game* game;

Bullet::Bullet() {
    setPixmap(QPixmap(":/images/img/bullet.png").scaled(40, 40));
    setTransformOriginPoint(20, 20);
    setRotation(90);
    // create a timer
    QTimer* timer = new QTimer();
    // connect the timer
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    // start the timer
    timer->start(50);
}

void Bullet::move() {
    int offset = 10;
    // handle colliding object
    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Enemy)) {
            // increase the score
            game->getScore()->increase();
            // play the sound
            playKillEnemySound();
            // remove the item from the scene
            scene()->removeItem(item);
            scene()->removeItem(this);
            // release the memory from the heap
            delete item;
            delete this;
            return;
        }
    }

    // move the bullet up
    setPos(x(), y() - offset);
    if(y() + boundingRect().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::playKillEnemySound() {
    QMediaPlayer* musicPlayer = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/sounds/enemy_die.wav"));
    audioOutput->setVolume(70);
    musicPlayer->play();
}
