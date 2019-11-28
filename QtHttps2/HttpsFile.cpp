#include "HttpsFile.h"
#include <QFile>

HttpsFile::HttpsFile(QObject *parent):HttpsBase(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void  HttpsFile::replyFinished(QNetworkReply* reply)
{
    qDebug() <<  "reply" << reply->readAll();
}

void HttpsFile::setHeadlerimpl()
{
   request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data"));
//      request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
//   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/zip");
//   request.setRawHeader("fileName",fileName);

//   request.setHeader(QNetworkRequest::ContentTypeHeader,"deac185eeafc6157938fe7c476cb9edf");
//   request.setHeader(QNetworkRequest::ContentTypeHeader,"deac185eeafc6157938fe7c476cb9edf");
//   request.setRawHeader("token","deac185eeafc6157938fe7c476cb9edf");
//   request.setRawHeader("fileName",fileName);
   qDebug() << "requestURL"<<requestURL;
   QFile filePackage("AAA.txt");
   if (filePackage.open(QIODevice::WriteOnly | QIODevice::Text))
   {
      filePackage.write(requestURL.toLatin1(),requestURL.length());

   }

   request.setUrl(QUrl(requestURL));
}

void  HttpsFile::uploadFile(const QString &file)
{
    QByteArray content;
    readFileContent(file,content);
    fileName = file.toLatin1();
    setHeadler("/aimbot-api/upload/img?token=deac185eeafc6157938fe7c476cb9edf");
    m_manager->post(request, content);
}

void HttpsFile::readFileContent(const QString &file, QByteArray &content)
{
    QFile filePackage(file);
    if (filePackage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = filePackage.readAll();

    }
}
