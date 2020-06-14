#include "SpatialReference.hpp"
#include "../HttpGet.hpp"
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QUrl>
#include <QRegExp>
#include <QRegularExpressionMatch>


QFile* file;


void mainFormSpatialReference(HttpGet* g)
{
    file = new QFile("epsg-wkt.txt");
   if(!file->open(QIODevice::WriteOnly|QIODevice::Append)){
       qDebug()<<"创建文件失败";
       return;
   }

    for(int i=1;i<2;++i){
        QUrl url(QString("http://spatialreference.org/ref/epsg/?page=%1").arg(i));
        g->getHTML(url, getEPSGCode,(void*)i);
        qDebug()<< url;
    }
}

void getEPSGCode(QByteArray *html, const void *arg)
{
    // 搜索EPSG编码
    QString pattern("EPSG:\\d+");
    QRegExp rx(pattern);
    QString text(*html);
    int index = -1;
    do{
        index = rx.indexIn(text,index+1);//text.indexOf(rx,index+1);
        qDebug()<<rx.cap(0);
        qDebug()<<index<<"  "<<text.mid(index,4);
    }while(index > 0);
}



void getHTMLFromSpatialReference(QByteArray* html,const void* arg)
{
    int index = *(const int*)&arg;
    QString code = QString("%1\n").arg(index);
    file->write(code.toUtf8());
    file->write(*html);
    file->write("\n\n");
    qDebug()<<"下载完成 "<<index<<".....";
}

