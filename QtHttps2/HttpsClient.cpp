#include "HttpsClient.h"
#include <QDebug>
#include "HttpsMsg.h"
#include "HttpsFile.h"

HttpsClient::HttpsClient(QObject *parent) : QObject(parent)
{

}

HttpsClient::~HttpsClient()
{

}

void HttpsClient::sendMsg(const QByteArray & data)
{

    QByteArray content;
    QFile filePackage("login.txt");
    if (filePackage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = filePackage.readAll();
        qDebug() << "content" << content;
    }
    HttpsMsg* msg = new HttpsMsg();
    msg->sendMsg(content);
    qDebug() << "end";
}

void  HttpsClient::uploadFile(const QString &file)
{
    HttpsFile* msg = new HttpsFile();
    msg->uploadFile(file);
}
