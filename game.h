#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QObject>
#include "player.h"
#include "score.h"
#include "health.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game();
    void start();
    void gameOver();
    int getScoreVal();
    void deallocateMemory();
    Score* getScore();
    Health* getHealth();
    QGraphicsScene* getScene();
private:
    QGraphicsScene* scene;
    Player* player;
    Score* score;
    Health* health;
    QTimer* timer;
    QMediaPlayer* musicPlayer;
    QAudioOutput* audioOutput;
public slots:
    void spawn();
};

#endif // GAME_H
