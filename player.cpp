#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Player::Player() {
    setPixmap(QPixmap(":/images/img/player.png").scaled(100, 100));
}


void Player::keyPressEvent(QKeyEvent* event) {
    // *******  Event Handling for the Player ********
    int offset = 10;
    if(event->key()== Qt::Key_Left) {
        if(x()>0) // to prevent the player from getting out of the screen
            setPos(x()-offset,y());
    } else if(event->key()== Qt::Key_Right) {
        if(x() + 100 < 800) // to prevent the player from getting out of the screen
            setPos(x()+offset,y());
    } else if(event->key()== Qt::Key_Space) {
        Bullet* bullet = new Bullet();
        bullet->setPos(x(),y());
        playBulletSound();
        scene()->addItem(bullet);
    }
}

void Player::playBulletSound() {
    QMediaPlayer* musicPlayer = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/sounds/bulletSound.mp3"));
    audioOutput->setVolume(60);
    musicPlayer->play();
}
