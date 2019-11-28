#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QObject>

//class LoggerBuiler;

class HttpDownLoad : public QObject
{
    Q_OBJECT
public:
    explicit HttpDownLoad(QObject *parent = nullptr);

    void SetDownLoadInfo(const int taskId, const QString fileName, QString url);

    //下载
    void DownloadFile(const QString &m_dir = "");

    //提供可以设置日志，记录httpServer发送与接到内容
//    void SetLog(LoggerBuiler *log);

    ~HttpDownLoad();
signals:
    //对外发送信号出去让外面帮自己析构
    void signalSendFinishedMsg(QString fileName);
    //对外发信号出去更新进度条
    void signalSendDownLoadProgress(int taskId, qint64 byteRead, qint64 totalBytes);

public slots:

private:
    class HttpDownLoadPrivate;
    friend class HttpDownLoadPrivate;//放开自己的功能给FaultPrivate调用
    HttpDownLoadPrivate *d;//用来调用FaultPrivate里的功能
};

#endif // HTTPDOWNLOAD_H
