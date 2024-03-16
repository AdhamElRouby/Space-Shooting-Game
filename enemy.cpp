#include "enemy.h"
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include "game.h"

extern Game* game;

Enemy::Enemy() {
    // draw graphics
    setPixmap(QPixmap(":/images/img/enemy.png").scaled(100, 100));
    setTransformOriginPoint(50, 50);
    setRotation(180);

    int rand_x = rand() % 701;
    setPos(rand_x, 0);
    // add timer and connect it
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Enemy::move() {
    int offset = 5;
    // check if the enemy hits the player
    QList<QGraphicsItem *> collided_items = collidingItems();
    foreach(auto& item, collided_items) {
        if(typeid(*item) == typeid(Player)) {
            // game over
            game->gameOver();
            return;
        }
    }

    // move the enemy down
    setPos(x(), y() + offset);
    if(y() > 600) {
        game->getHealth()->decrease();
        scene()->removeItem(this);
        delete this;
        if(!game->getHealth()->getHealthVal())
            game->gameOver();
    }
}
