#ifndef HTTPDOWNLOAD_PRIVATE_H
#define HTTPDOWNLOAD_PRIVATE_H

#include "include/httpdownload.h"

#include <QObject>
#include <QFile>
#include <QDir>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork>

class LoggerBuiler;

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
\

//class LoggerBuiler;
class HttpDownLoad::HttpDownLoadPrivate : public QObject
{
    Q_OBJECT
public:
    explicit HttpDownLoadPrivate(HttpDownLoad *parent);
    void SetDownLoadInfo(const int taskId, const QString fileName, QString url);
    //下载
    void DownloadFile(const QString &m_dir = "");

    //设置这个bsp工具用那个Log日志对象
    void SetLog(LoggerBuiler *log );

    ~HttpDownLoadPrivate();
signals:


public slots:

private:
    HttpDownLoad *q = nullptr;

private:
    //打开文件
    QFile *openFileForWrite(const QString &fileName);
    //连接后台，下载
    void startRequest(const QUrl &requestedUrl);

    void startUpRequest(const QUrl &requestedUrl);
    //收到网络数据，写文件
    void slotHttpReadyRead();
    //下载完成，清除相关的指针
    void slotHttpGetFinished();
    //下载中，处理自己内部的下载进度更新消息，然后再发送信号出去
    void slotHttpProgress(qint64 bytesRead, qint64 totalBytes);

private:
    qint64 m_byteRead;
    qint64 m_totalBytes;
    int m_taskId;
    QString m_fileName;
    QString m_url;
    QNetworkAccessManager m_qnam;
    QNetworkReply *m_reply;
    QFile *m_file;
    bool m_httpRequestAborted;

private://日志相关的
    LoggerBuiler *m_log = nullptr;
};

#endif // HTTPDOWNLOAD_PRIVATE_H
