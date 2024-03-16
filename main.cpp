#include <QApplication>
#include "game.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create the game
    game = new Game();

    // start the game
    game->start();

    return a.exec();
}
