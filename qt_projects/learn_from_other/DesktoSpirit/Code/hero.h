#ifndef HERO_H
#define HERO_H
#include<QPushButton>

class Hero:public QPushButton
{
public:
    Hero(QWidget* parent=nullptr);
    QWidget* widget;
    int speed=0;
    int state=0;
    QPixmap *pixmap;
    void left_move();
    void right_move();
    void up_move();
    void down_move();
protected:

};

#endif // HERO_H
