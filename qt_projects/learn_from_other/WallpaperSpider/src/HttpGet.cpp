#include "HttpGet.hpp"

#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include <QDebug>

#include <typeinfo> //bad_cast

HttpGet::HttpGet(QObject *parent)
    : QObject(parent),_parallel(10)
{
    _manager = new QNetworkAccessManager(this);
}

/***********************************************************************************/
HttpGet::~HttpGet()
{
    _manager->deleteLater();
}

void HttpGet::setProxy(const QString &hostName, quint16 port,
                       const QString &user, const QString &password)
{
    QNetworkProxy proxy(QNetworkProxy::HttpProxy,hostName,port,user,password);
    // 设置代理
    _manager->setProxy(proxy);
}

int HttpGet::getCurrentTaskCount() const
{
    return _fileMap.size() + _fileReadyQueue.size();
}

/***********************************************************************************/
bool HttpGet::saveFile(const QUrl& url,
                       const QString& savedir,
                       QString filename)
{
    if(!url.isValid()){
        qDebug()<<url<<"无效";
        return false;
    }
    if(url.scheme()!="http"){
        qDebug()<<url<<"非http协议";
        return false;
    }
    if(url.path().isEmpty()){
        qDebug()<<url<<"URL路径为空";
        return false;
    }

    if(savedir.isEmpty()){
        qDebug()<<"保存路径为空,改为当前路径";
        //savedir = ".";
        return  false;
    }

    QDir dir(savedir);
    if(!dir.exists()){
        qDebug()<<" 目录 "<<dir<<" 不存在 ,将创建 ";
        // 创建目录
        dir.mkpath(".");
    }
    if(filename.isEmpty()){
        filename = url.fileName();
    }
    QFileInfo finfo(dir,filename);
    if(finfo.exists()){
        qDebug()<<finfo.filePath()<<"文件已经存在";
        //return false;
    }

    // 判断当前正在下载的数量
    if(_fileMap.size() >= _parallel){
        // 添加到待下载队列
        _fileReadyQueue.push_back(QPair<QUrl,QString>(url,finfo.filePath()));
        return true;
    }
    // 当前下载量低于并行量，且待下载队列不空
    if(!_fileReadyQueue.isEmpty()){
        int addsize = _parallel - _fileMap.size();
        if(addsize > _fileReadyQueue.size()){
            addsize = _fileReadyQueue.size();
        }
        while(addsize--){
            // 添加任务
            startSaveFileTask(_fileReadyQueue.front().first,_fileReadyQueue.first().second);
            // 从队列中弹出
            _fileReadyQueue.pop_front();
        }
    }
    // 如果待下载队列已经空了，那就把这个也加入到下载中
    if(_fileReadyQueue.isEmpty()){
        startSaveFileTask(url,finfo.filePath());
    }else{
        // 添加到待下载队列
        _fileReadyQueue.push_back(QPair<QUrl,QString>(url,finfo.filePath()));
    }
    return true;
}

void HttpGet::setSaveFileParallel(int parallel)
{
    if(parallel > 10 && parallel < 512){
        _parallel = parallel;
    }
}


/***********************************************************************************/

void HttpGet::getHTML(const QUrl& url, const HTMLPROC proc,const void *arg)
{
    if(!url.isValid()){
        qDebug()<<url<<"无效";
    }
    if(url.scheme()!="http"){
        qDebug()<<url<<"非http协议";
    }
    if(url.path().isEmpty()){
        qDebug()<<url<<"URL路径为空";
    }

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent",
                         "Mozilla/5.0 (X11; Linux x86_64)"
                         " AppleWebKit/537.36 (KHTML, like Gecko)"
                         " Chrome/47.0.2526.106 Safari/537.36");
    QNetworkReply* reply = _manager->get(request);

    if(reply!=NULL && _fileMap.find(reply) != _fileMap.end()){
        qDebug()<<url<<" 正在处理中 ";
        return;
    }
    // 将请求插入HTML处理列表
    _htmlMap[reply]=GETHTMLPROC{(HTMLPROC)proc,new QByteArray(),arg};

    connect(reply,&QNetworkReply::readyRead,this,&HttpGet::replyHtmlReadyRead);
    connect(reply,&QNetworkReply::finished,this,&HttpGet::replyHtmlFinished);
    connect(reply,(void(QNetworkReply::*)(QNetworkReply::NetworkError))&QNetworkReply::error,
            this,&HttpGet::replyNetworkError);
}


/***********************************************************************************/
void HttpGet::startSaveFileTask(const QUrl &url, const QString &filename)
{
    QFile* file = new QFile(filename);
    if(!file->open(QIODevice::WriteOnly|QIODevice::Truncate)){
        qDebug()<<"创建文件"<<filename<<"失败";
        return;
    }

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent",
                         "Mozilla/5.0 (X11; Linux x86_64)"
                         " AppleWebKit/537.36 (KHTML, like Gecko)"
                         " Chrome/47.0.2526.106 Safari/537.36");
    QNetworkReply* reply = _manager->get(request);

    if(reply!=NULL && _fileMap.find(reply) != _fileMap.end()){
        qDebug()<<url<<" 正在处理中 ";
        return;
    }

    // 将请求插入文件列表
    _fileMap[reply]=file;

    connect(reply,&QNetworkReply::readyRead,this,&HttpGet::replyFileReadyRead);
    connect(reply,&QNetworkReply::finished,this,&HttpGet::replyFileFinished);
    connect(reply,(void(QNetworkReply::*)(QNetworkReply::NetworkError))&QNetworkReply::error,
            this,&HttpGet::replyNetworkError);
}

/***********************************************************************************/
void HttpGet::replyFileReadyRead()
{
    QNetworkReply* reply;
    try{
        reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    }
    catch(std::bad_cast){
        qDebug()<<"replyFileReadyRead ==> reply == NULL";
        return;
    }
    // 读取内容写入文件
    _fileMap[reply]->write(reply->readAll());
}

/***********************************************************************************/
void HttpGet::replyFileFinished()
{
    // 完成了读取，关闭文件
    QNetworkReply* reply;
    try{
        reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    }
    catch(std::bad_cast){
        qDebug()<<"replyFileFinished ==> reply == NULL";
        return;
    }

    // 读取结束
    _fileMap[reply]->close();
    _fileMap[reply]->deleteLater();
    _fileMap.remove(reply);
    qDebug()<<"下载完成:"<<reply->url();
    reply->deleteLater();

    // 如果当前待下载队列不是空的，添加一个下载任务
    if(_fileReadyQueue.isEmpty()){
        if(_fileMap.isEmpty()){
            qDebug()<<"..已添加任务已经全部下载完成...";
            // 发送信号
            emit saveFileAllDoneEvent();
        }
    }else{
        // 添加任务
        startSaveFileTask(_fileReadyQueue.front().first,_fileReadyQueue.first().second);
        // 从队列中弹出
        _fileReadyQueue.pop_front();

    }
}

/***********************************************************************************/
void HttpGet::replyHtmlReadyRead()
{
    QNetworkReply* reply;
    try{
        reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    }
    catch(std::bad_cast){
        qDebug()<<"replyHtmlReadyRead ==> reply == NULL";
        return;
    }

    // 读取返回的数据
    _htmlMap[reply].html->append(reply->readAll());

}

/***********************************************************************************/
void HttpGet::replyHtmlFinished()
{
    QNetworkReply* reply;
    try{
        reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    }
    catch(std::bad_cast){
        qDebug()<<"replyHtmlFinished ==> reply == NULL";
        return;
    }
    // 读取完成，处理读取到的数据
    GETHTMLPROC hp = _htmlMap[reply];
    // 调用处理函数
    (hp.proc)(hp.html,hp.arg);
    // 从html处理列表中移除
    _htmlMap.remove(reply);
    reply->deleteLater();
    delete hp.html;

    if(_htmlMap.isEmpty()){
        // 所有的html获取任务已经完成
        emit getHtmlAllDoneEvent();
    }

}

/***********************************************************************************/
void HttpGet::replyNetworkError(QNetworkReply::NetworkError)
{
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    qDebug()<<"下载出错 "<<reply->errorString() <<"\n\t"<<reply->url() ;
    if(_fileMap.find(reply) != _fileMap.end()){
        _fileMap[reply]->close();
        _fileMap[reply]->deleteLater();
        _fileMap.remove(reply);
        reply->deleteLater();
    }
}

