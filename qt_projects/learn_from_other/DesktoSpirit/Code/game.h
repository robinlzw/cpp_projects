#ifndef GAME_H
#define GAME_H
#include<QSound>
#include <QWidget>
#include<hero.h>
#include<QKeyEvent>
class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    Hero *hero;
    int count=0;
    int dir=0;
    int end_time=1000;
signals:
    void stop();
public slots:
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

};

#endif // GAME_H
