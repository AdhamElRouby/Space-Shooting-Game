#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Player::Player() {
    setPixmap(QPixmap(":/images/img/player.png").scaled(100, 100));
    setTransformOriginPoint(50, 50);
    rotAngle = 15;
}

void Player::keyPressEvent(QKeyEvent* event) {
    // *******  Event Handling for the Player ********
    int offset = 10;
    int rotAngle = 15;
    if(event->key() == Qt::Key_Left) {
        // to prevent the player from getting out of the screen
        if(x()>0) {
            setPos(x()-offset,y());
            animateRot(-rotAngle);
        }
    } else if(event->key()== Qt::Key_Right) {
        // to prevent the player from getting out of the screen
        if(x() + 100 < 800) {
            setPos(x()+offset,y());
            animateRot(rotAngle);
        }
    } else if(event->key()== Qt::Key_Space) {
        Bullet* bullet = new Bullet();
        bullet->setPos(x() + 26, y() - 13); // center the bullet relative to the spaceship
        playBulletSound();
        scene()->addItem(bullet);
    }
}

void Player::keyReleaseEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        animateRot(0);
}

void Player::animateRot(qreal endRotation) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "rotation");
    int durTime = 150;
    animation->setDuration(durTime); // Animation duration in millisseconds
    animation->setStartValue(rotation());
    animation->setEndValue(endRotation);
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Use quadratic easing for smoother animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Player::playBulletSound() {
    QMediaPlayer* musicPlayer = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/sounds/bulletSound.mp3"));
    audioOutput->setVolume(60);
    musicPlayer->play();
}
