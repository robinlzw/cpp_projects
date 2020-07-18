#include "evle.h"
//记录上一时刻的坐标
QPoint lastPos;
int i = 1;
evle::evle(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel(this);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint); //只是使窗口的标题栏隐藏
    setMouseTracking(true);
    QPixmap pixw = QPixmap("Resources/1.png");
    label->setPixmap(pixw);
    label->resize(128,128);
    lastPos = this->pos();
}
evle::~evle() {}

void evle::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "this->pos() = " <<  this->pos() << ", event->globalPos() = " << event->globalPos();
    //pos()为局部坐标 globalPos()为全局坐标
    if (event->button() == Qt::LeftButton)
    {//左键拖动窗体
        relativePos = this->pos() - event->globalPos();

    }
    if (event->button() == Qt::MidButton)
    {
        speak();
    }
    if (event->button() == Qt::RightButton)
    {

        QTextCodec* codec = QTextCodec::codecForName("System");
        codec->setCodecForLocale(QTextCodec::codecForName("UTF8"));
        QAction* act_about = new QAction(codec->toUnicode("about"), this);
        QAction* act_mainwindow = new QAction(codec->toUnicode("open main window"), this);
        QAction* act_exit = new QAction(codec->toUnicode("exit"), this);
        QObject::connect(act_about, SIGNAL(triggered()), this, SLOT(about_window()));
        QObject::connect(act_exit, SIGNAL(triggered()), this, SLOT(close()));
        QMenu *menu = new QMenu(this);
        menu->addAction(act_about); //添加菜单项1
        menu->addAction(act_mainwindow);
        menu->addAction(act_exit); //添加菜单项2
        menu->exec(QCursor::pos());
    }
}
void evle::mouseMoveEvent(QMouseEvent* event)//移动窗体
{
        if (event->globalPos().x() < lastPos.x())
        {
            QPixmap pixw = QPixmap("Resources/3.png");
            label->setPixmap(pixw);
        }
        else
        {
            QPixmap pixw = QPixmap("Resources/2.png");
            label->setPixmap(pixw);
        }
        lastPos = event->globalPos();

    this->move(event->globalPos() + relativePos);
}
void evle::enterEvent(QEvent*)
{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(), rect.y(), rect.width(), rect.height());
    if (rect.top() < 0)
    {
        rect.setX(rc.x());
        rect.setY(0);
        move(rc.x(), -2);
    }
}

void evle::leaveEvent(QEvent*)
{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(), rect.y(), rect.width(), rect.height());
    if (rect.top() < 0)
    {
        move(rc.x(), -rc.height() + 2);
    }
}
void evle::mouseReleaseEvent(QMouseEvent* event)     //松开鼠标后自动贴边隐藏并且透明
{
    QPropertyAnimation* pAnimation = new QPropertyAnimation(this, "geometry");
    QDesktopWidget* pDesktopWidget = QApplication::desktop();//获得桌面
    //窗口的宽和高
    int tx = width();
    int ty = height();
    //QRect clientRect = desktopWidget->availableGeometry();得到相对于屏幕的绝对坐标
    //QRect applicationRect = desktopWidget->screenGeometry();得到应用程序矩形
    //获得屏幕宽度
    int lx = pDesktopWidget->availableGeometry().width();
    int ly = pDesktopWidget->availableGeometry().height();
    if (this->x() < 2*tx )
    {
        pAnimation->setDuration(100);
        pAnimation->setStartValue(QRect(this->x(), this->y(), width(), height()));   //起始位置
        pAnimation->setEndValue(QRect(-50, this->y(), width(), height()));       //终点位置
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        QPixmap pixw = QPixmap("Resources/4.png");
        label->setPixmap(pixw);
        //设置窗口透明度
        //this->setWindowOpacity(0.3);
    }
    else if (this->x() > (lx - 2*tx))
    {
        pAnimation->setDuration(100);
        pAnimation->setStartValue(QRect(this->x(), this->y(), width(), height()));
        pAnimation->setEndValue(QRect(lx - 78, this->y(), width(), height()));
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        QPixmap pixw = QPixmap("Resources/4_2.png");
        label->setPixmap(pixw);
        //this->setWindowOpacity(0.3);
    }
    else if (this->y() > (ly - 2*ty))
    {
        pAnimation->setDuration(100);
        pAnimation->setStartValue(QRect(this->x(), this->y(), width(), height()));
        pAnimation->setEndValue(QRect(this->x(), ly - ty , width(), height()));
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        QPixmap pixw = QPixmap("Resources/5.png");
        label->setPixmap(pixw);
        //this->setWindowOpacity(0.3);
    }
    else if (this->y() < (2 * ty))
    {
        QPixmap pixw = QPixmap("Resources/8.png");

        pAnimation->setDuration(100);
        pAnimation->setStartValue(QRect(this->x(), this->y(), width(), height()));

        pAnimation->setEndValue(QRect(this->x(),10, width(), height()));
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        label->setPixmap(pixw);
        //this->setWindowOpacity(0.3);
    }
    else
    {
        QPixmap pixw = QPixmap("Resources/1.png");
        label->setPixmap(pixw);
    }
}
void evle::speak()
{
    QTextToSpeech* tts = new QTextToSpeech(this);
    tts->setLocale(QLocale::Chinese);//设置语言环境
    tts->setRate(0.0);//设置语速-1.0到1.0
    tts->setPitch(1.0);//设置音高-1.0到1.0
    tts->setVolume(1.0);//设置音量0.0-1.0
    if (tts->state() == QTextToSpeech::Ready)
    {
        tts->say("hi steve");//开始合成文本
    }
}
void evle::about_window()
{
    QTextCodec* codec = QTextCodec::codecForName("System");
    codec->setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QMessageBox::about(NULL, "about", codec->toUnicode("lll"));
}
