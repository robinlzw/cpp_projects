#include "jj20.hpp"

#include "../HttpGet.hpp"

#include <QByteArray>
#include <QUrl>
#include <QTextCodec>
#include <QSet>
#include <QDebug>

void mainFormJJ20(HttpGet *g)
{

    for(int i=1;i<87;++i){
        QUrl url(QString("http://www.jj20.com/bz/nxxz/list_7_%1.html").arg(i));
        g->getHTML(url, getlistFromJJ20,g);
        qDebug()<< url;
    }
}

/***********************************************************************************/

void getlistFromJJ20(QByteArray* html,const void* arg)
{
    int index = html->indexOf("charset=",12);
    QString charset("utf-8");
    if(index > 0){
        charset = html->mid(index+8,10);
        index = charset.indexOf(QRegExp("[\\s\">]"),2);
        if(index > 0){
            charset.resize(index);
        }
    }

    //qDebug()<<"字符集:"<<charset;
    QTextCodec *codec = QTextCodec::codecForName(charset.toStdString().c_str());
    //codec = codec->codecForHtml(*html);
    QString htmls = codec->toUnicode(*html);
    // 解析
    {
        QSet<QString/*,QString*/> urllist;  // url
        int ulbeg = htmls.indexOf("<ul class=\"pic2 vvi fix\">");
        int ulend = htmls.indexOf("<div class=\"pagea\"",ulbeg);
        /*
        <li>
        <a href="/bz/nxxz/nxmt/8930.html" target="_blank">
        <img src="http://img.jj20.com/up/allimg/911/051916114639/160519114639-1-lp.jpg"
        width="298" height="168" alt="亲密闺蜜图片"></a>
        <a href="/bz/nxxz/nxmt/8930.html">亲密闺蜜图片</a>(20张)<ins>2016-05-19</ins>
        <div class="shadow"></div>
        </li>
        */
        htmls.resize(ulend);
        int libeg = ulbeg+20;
        libeg = htmls.indexOf(QString::fromUtf8("<li"),libeg+4);
        do{
            int urlbeg = htmls.indexOf(QString::fromUtf8("\""),libeg+4) + 1;
            int urlend = htmls.indexOf(QString::fromUtf8("html"),urlbeg) + 4;
            QString url = htmls.mid(urlbeg,urlend-urlbeg);
            urllist.insert(url);
            libeg = htmls.indexOf(QString::fromUtf8("<li"),libeg+4);
        }while(libeg > 0);

        // 输出每个图片首页和路径
        //qDebug()<<map;
        HttpGet* pget = (HttpGet*)arg;
        for(auto urlsfx:urllist){
            QUrl url(QString("http://www.jj20.com") + urlsfx);
            pget->getHTML(url,getPicFromJJ20,arg);
            qDebug()<<"开始解析图片页"<<url;
        }
    }
}

/***********************************************************************************/

void getPicFromJJ20(QByteArray* html,const void* arg)
{
    int index = html->indexOf("charset=",12);
     QString charset("utf-8");
     if(index > 0){
         charset = html->mid(index+8,10);
         index = charset.indexOf(QRegExp("[\\s\">]"),2);
         if(index > 0){
             charset.resize(index);
         }
     }

     //qDebug()<<"字符集:"<<charset;
     QTextCodec *codec = QTextCodec::codecForName(charset.toStdString().c_str());
    // 这里只获取英文，就不进行转码了
    // <h1><span>美女明星林允壁纸(1/6)</span></h1>
    int dirbeg = html->indexOf("<h1><span>",1500)+10;
    int dirend = html->indexOf(")</span>",dirbeg);
    QStringList dirnum = (codec->toUnicode(html->mid(dirbeg,dirend-dirbeg))).split("(1/");
    int num = dirnum.at(1).toInt();
    qDebug()<<"num = "<<num << "\n"<<dirnum;
    int imgbeg = html->indexOf("<script>",index+500);
    imgbeg = html->indexOf('\'',imgbeg)+1;
    int imgend = html->indexOf('\'',imgbeg+20);

    // "/up/allimg/211/042111062J3/110421062J3-1.jpg"
    QByteArray urlpath = html->mid(imgbeg,imgend-imgbeg);
    urlpath.insert(urlpath.lastIndexOf('-')+1,'%');

    for(int i=1;i<num;++i){
        QUrl url(QString("http://www.jj20.com") + QString(urlpath).arg(i));
        qDebug()<<url;
        // 进行抓取保存
        HttpGet* pget = (HttpGet*)arg;
        pget->saveFile(url,dirnum.at(0));
    }
}
