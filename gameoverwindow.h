#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameOverWindow;
}

class GameOverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOverWindow(QWidget *parent = nullptr);
    ~GameOverWindow();

private slots:
    void on_exitBtn_clicked();

    void on_playAgainBtn_clicked();

private:
    Ui::GameOverWindow *ui;
};

#endif // GAMEOVERWINDOW_H
