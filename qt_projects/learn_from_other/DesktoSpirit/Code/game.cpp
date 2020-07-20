#include "game.h"
#include<QApplication>
#include<QScreen>
#include<time.h>
#include<windows.h>
#include<QTimer>
#include<QDebug>
#include<time.h>
#include<QToolTip>

Game::Game(QWidget *parent) : QWidget(parent)
{
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    this->setGeometry(mm);
    setWindowFlags(Qt::Tool|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    hero=new Hero(this);
    hero->move(mm.width()/2,mm.height()/2);
    srand(time(0));
    QTimer *timer = new QTimer(this);
//    QString text[14]={
//        "路漫漫其修远兮，吾将上下而求索",
//        "我饿了,快点给我吃的",
//        "人家才不是什么病毒呢",
//        "总有一天，我要撕碎这虚假的星空",
//        "人类总得对大自然原有的力量保持敬畏，不是吗",
//        "人生路，美梦似路长",
//        "你的电脑好好吃哦",
//        "我不吃你内存的，放心吧",
//        "我喜欢吃c++和python，你呢",
//        "虽已走向,那灭亡最终一章,全力多打漂亮一仗",
//        "追求你的梦想,一切都会不一样",
//        "迷茫只会让人软弱",
//        "我会陪在你身边的",
//        "祈愿幸福吧,无论未来多么令人悲痛"
//    };
    QString text[14]={
        "001",
        "002",
        "001",
        "002",
        "001",
        "002",
        "001",
        "002",
        "001",
        "002",
        "001",
        "002",
        "001",
        "002",
    };
//    QString text2[4]={
//        "别点我,大坏蛋，咬你哦",
//        "我不吃你内存的，放心吧",
//        "你再不把手移开,我就咬死你!",
//        "好心一早放开我,从头努力也坎坷"
//                    };

    QString text2[4]={
        "001",
        "002",
        "001",
        "002",
    };

    connect(timer, &QTimer::timeout,[=](){
        auto key=Qt::Key_Down;

        count+=25;
        if(
                count>=end_time
                ||hero->x()>=this->width()-32
                ||hero->y()>=this->height()-32
                ||hero->x()<=1
                ||hero->y()<=1
           ){
            Sleep(100*(1+rand()%4));
            end_time=(6+rand()%7)*100;
            count=0;
            dir=rand()%5;
            hero->speed=0;
            if(rand()%5==0)QToolTip::showText(QPoint(hero->x()+32,hero->y()-32),text[rand()%14],this,QRect(100,100,100,100),3000);
        }
        switch (dir) {
        case 0:
            //hero->click();
            return;
            break;
        case 1:
            key=Qt::Key_Down;
            break;
        case 2:
            key=Qt::Key_Up;
            break;
        case 3:
            key=Qt::Key_Left;
            break;
        case 4:
            key=Qt::Key_Right;
            break;
        default:
            break;
        }
        QKeyEvent tabKey(QEvent::KeyPress, key, Qt::NoModifier);
        QCoreApplication::sendEvent(this, &tabKey);

    });
    connect(this,SIGNAL(stop()),timer,SLOT(stop()));
    timer->start(25);
    connect(hero,&QPushButton::clicked,[=](){
        QToolTip::showText(QPoint(hero->x()+32,hero->y()-32),text2[rand()%4],this,QRect(100,100,100,100),3000);
        dir=0;
        end_time=1000;
    });

}
void Game::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Up:
        hero->up_move();
        break;
    case Qt::Key_Down:
        hero->down_move();
        break;
    case Qt::Key_Left:
        hero->left_move();
        break;
    case Qt::Key_Right:
        hero->right_move();
        break;
    default:
        break;
    }
}
void Game::keyReleaseEvent(QKeyEvent *event){
    if(event->isAutoRepeat())
        event->ignore();
    else hero->speed=0;
}
