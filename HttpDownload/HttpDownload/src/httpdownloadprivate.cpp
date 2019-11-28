#include "httpdownloadprivate.h"
#include <QApplication>

#include <QFile>
#include <QDir>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork>

#include "BSP/Logbuiler/include/loggerbuiler.h"

HttpDownLoad::HttpDownLoad(QObject *parent) : QObject(parent)
{
    d = new HttpDownLoadPrivate(this);
}

void HttpDownLoad::SetDownLoadInfo(const int taskId, const QString fileName, QString url)
{
    d->SetDownLoadInfo(taskId, fileName, url);
}

void HttpDownLoad::DownloadFile(const QString &m_dir)
{
    d->DownloadFile(m_dir);
}

void HttpDownLoad::SetLog(LoggerBuiler *log)
{
    d->SetLog(log);
}


HttpDownLoad::~HttpDownLoad()
{

}


//-------------------------------------------------------------------------------------------


HttpDownLoad::HttpDownLoadPrivate::HttpDownLoadPrivate(HttpDownLoad *parent) : QObject(parent)
{
    q = parent;
    m_httpRequestAborted = false;
}

void HttpDownLoad::HttpDownLoadPrivate::SetDownLoadInfo(const int taskId, const QString fileName, QString url)
{
    m_taskId = taskId;
    m_fileName = fileName;
    m_url = url;
}

HttpDownLoad::HttpDownLoadPrivate::~HttpDownLoadPrivate()
{

}

QFile *HttpDownLoad::HttpDownLoadPrivate::openFileForWrite(const QString &fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));
    if (!file->open(QIODevice::WriteOnly)) {
        return Q_NULLPTR;
    }
    return file.take();
}

void HttpDownLoad::HttpDownLoadPrivate::DownloadFile(const QString &m_dir)
{
    const QUrl newUrl = QUrl::fromUserInput(m_url);
    if (!newUrl.isValid())
    {
        if ( m_log != NULL )
            m_log->LogError(LOG_FUNC("error url:" + m_url));
        return;
    }
    //检查下载文件夹是否存在，不存在则创建

    //如果没定义下载目录，使用默认下载目录
    QString path = m_dir;
    if (path.size()  == 0)
    {
        path = QCoreApplication::applicationDirPath() + "/MediaDownLoad";
    }


    QDir dir(path);
    if (!dir.exists())
    {
        //创建文件夹
        //dir.mkdir(path);用这个不行
        dir.mkpath(path);
    }

    m_fileName.prepend(path + "/");
    if (QFile::exists(m_fileName))
    {
        //如果文件存在则删除重新下载
        //发信号出去让advListManager关闭掉原来的下载链接
        if ( m_log != NULL )
            m_log->LogDebug(LOG_FUNC("remove:" + m_fileName));
        QFile::remove(m_fileName);
    }

    //创建文件
    m_file = openFileForWrite(m_fileName);
    if (!m_file)
    {
        if ( m_log != NULL )
            m_log->LogError(LOG_FUNC("file creat faild:" + m_fileName));
        return;
    }

    //开始下载
    startRequest(newUrl);
}

void HttpDownLoad::HttpDownLoadPrivate::SetLog(LoggerBuiler *log)
{
    m_log = log;
}

void HttpDownLoad::HttpDownLoadPrivate::slotHttpReadyRead()
{
    if (m_file)
    {
        QByteArray bA = m_reply->readAll();
        m_file->write(bA);
    }
}

void HttpDownLoad::HttpDownLoadPrivate::slotHttpGetFinished()
{
    QFileInfo fi;
    //清除文件指针
    if (m_file) {
        fi.setFile(m_file->fileName());
        m_file->close();
        delete m_file;
        m_file = Q_NULLPTR;
    }

    //清除QNetworkReply指针
    if (m_httpRequestAborted) {
        m_reply->deleteLater();
        m_reply = Q_NULLPTR;
        return;
    }

    if (m_reply->error()) {
        QFile::remove(fi.absoluteFilePath());
        m_reply->deleteLater();
        m_reply = Q_NULLPTR;
        return;
    }

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
    //发信号给外部，让外部帮自己析构自己

    qDebug()<<"----------------------------------------------";
    qDebug()<<"下载完成，帮我析构，释放内存";
    qDebug()<<"----------------------------------------------";

    emit q->signalSendFinishedMsg(m_fileName);
}

void HttpDownLoad::HttpDownLoadPrivate::slotHttpProgress(qint64 bytesRead, qint64 totalBytes)
{

//    qDebug()<<"------------------------------------";
//    qDebug()<<"bytesRead:"<<bytesRead<<",totalBytes:"<<totalBytes;
//    qDebug()<<"------------------------------------";
    m_byteRead = bytesRead;
    m_totalBytes = totalBytes;
    emit q->signalSendDownLoadProgress(m_taskId, m_byteRead, m_totalBytes);
}

void HttpDownLoad::HttpDownLoadPrivate::startRequest(const QUrl &requestedUrl)
{
    m_reply = m_qnam.get(QNetworkRequest(requestedUrl));
    //下载完成，析构自己
    connect(m_reply, &QNetworkReply::finished, this, &HttpDownLoadPrivate::slotHttpGetFinished);
   //
    connect(m_reply, &QIODevice::readyRead, this, &HttpDownLoadPrivate::slotHttpReadyRead);
    //下载进度
    connect(m_reply, &QNetworkReply::downloadProgress, this, &HttpDownLoadPrivate::slotHttpProgress);
}
