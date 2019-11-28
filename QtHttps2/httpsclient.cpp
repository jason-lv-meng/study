#include "httpsclient.h"
#include <QDebug>

HttpsClient::HttpsClient(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

HttpsClient::~HttpsClient()
{
    if (manager)
    {
        delete manager;
    }

}

void HttpsClient::sendMsg(const QByteArray & data)
{
    QNetworkRequest request;
    QString serverURL="http://test79.ubtrobot.com:9009/aimbot-api/sys/login";
    QByteArray content;

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=UTF-8"));

    request.setUrl(QUrl(serverURL));
    QFile filePackage("login.txt");
    if (filePackage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = filePackage.readAll();
        qDebug() << "content" << content;
    }
    QNetworkReply * reply = manager->post(request, content);
//    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
//    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
//            this, &MyClass::slotError);
//    connect(reply, &QNetworkReply::sslErrors,
//            this, &MyClass::slotSslErrors);
}

void  HttpsClient::replyFinished(QNetworkReply* reply)
{
    qDebug() <<  "reply" << reply->readAll();
}

void  HttpsClient::uploadFile(const QString &file)
{
    QNetworkRequest request;
    QString serverURL="http://test79.ubtrobot.com:9009/aimbot-api/sys/login";
    QByteArray content;
    QFile filePackage(file);
    if (filePackage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = filePackage.readAll();
        qDebug() << "content" << content;
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data"));

    request.setUrl(QUrl(serverURL));
    QNetworkReply * mp_reply = manager->post(request, content);

}
