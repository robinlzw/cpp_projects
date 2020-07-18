#include <QObject>
#include <QString>
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
class GlobalApplication : public QApplication
{
public:
     GlobalApplication(int&argc,char **argv);
     ~GlobalApplication();

     bool notify(QObject*, QEvent *);
     void setWindowInstance(QWidget*wnd);
private:
     QWidget *widget;
};
