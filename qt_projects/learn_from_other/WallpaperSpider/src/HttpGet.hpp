#ifndef HttpGet_HPP
#define HttpGet_HPP

#include <QObject>
#include <QMap>
#include <QQueue>
#include <QNetworkReply>
#include <QUrl>

class QNetworkAccessManager;
class QFile;

/** html获取后的处理函数 */
typedef void(*HTMLPROC)(QByteArray* html,const void* arg);

class HttpGet : public QObject
{
    Q_OBJECT

    typedef struct{
        HTMLPROC proc;      //调用的函数
        QByteArray* html;   // 传入获取的html参数
        const void* arg;    // 传入的外部参数
    }GETHTMLPROC;
public:
    explicit HttpGet(QObject *parent = 0);
    ~HttpGet();

    /***************************************************************************//*
     * @brief	设置代理.
     * @author	乌合之众.
     * @date	2016-06-17
     * @param	hostName    代理服务器.
     * @param   port        端口号.
     * @param   user        用户名.
     * @param   password    密码.
     *//**************************************************************************/
    void setProxy(const QString & hostName = QString(), quint16 port = 0,
                  const QString & user = QString(), const QString & password = QString());

    // 获取当前已经添加的任务数
    int getCurrentTaskCount()const;


    /***************************************************************************//*
     * @fn	bool saveFile(const QUrl& url,const QString& savedir,
     *                    QString filename=QString());
     * @brief	下载http文件.
     * @author	乌合之众
     * @date	2016-05-28
     * @param	url         待下载的文件的地址.
     * @param   savedir     下载文件保存的目录.
     * @param   filename    下载文件保存的名称，默认为url中资源的名称.
     * @return	true if it succeeds, false if it fails.
     *//**************************************************************************/
    bool saveFile(const QUrl& url,const QString& savedir,
                  QString filename=QString());

    // 设置保存文件的时候并行下载数(支持10~512)
    void setSaveFileParallel(int parallel);

    /***************************************************************************//*
     * @fn	void getHTML(const QUrl& url,const HTMLPROC proc,const void* arg = NULL);
     * @brief	获取网页html.
     * @author	乌合之众.
     * @date	2016-05-28
     * @param	url     待获取的html的地址.
     * @param   proc    获取html后的调用的函数，其第一个参数为获取到的html.
     * @param   arg     获取html后调用函数的第二个参数.
     * @return	true if it succeeds, false if it fails.
     *//**************************************************************************/
    void getHTML(const QUrl& url,const HTMLPROC proc,const void* arg = NULL);

signals:
    // 当前所有已添加文件下载任务完成信号
    void saveFileAllDoneEvent();
    // 当前所有获取HTML的任务完成信号
    void getHtmlAllDoneEvent();
protected:
    // 开始一个下载文件的任务
    void startSaveFileTask(const QUrl& url,const QString& filename);
public slots:
    // 文件请求准备好读取(有数据到来)
    void replyFileReadyRead();
    // 文件请求数据读取完成
    void replyFileFinished();

    // HTML请求准备好读取(有数据到来)
    void replyHtmlReadyRead();
    // HTML请求数据读取完成
    void replyHtmlFinished();

    // 网络错误
    void replyNetworkError(QNetworkReply::NetworkError);

private:
    QNetworkAccessManager*  _manager;
    QMap<QNetworkReply*,GETHTMLPROC>   _htmlMap;
    QMap<QNetworkReply*,QFile*>    _fileMap;   // key=信号发送者,value=file
    QQueue<QPair<QUrl,QString> >   _fileReadyQueue; // 准备下载的文件队列
    int _parallel;  // 并行下载数
};

#endif // HttpGet_HPP
