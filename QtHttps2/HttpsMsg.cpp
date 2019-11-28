#include "HttpsMsg.h"

HttpsMsg::HttpsMsg(QObject *parent):HttpsBase(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

HttpsMsg::~HttpsMsg()
{
    qDebug() << __func__;
}

void  HttpsMsg::replyFinished(QNetworkReply* reply)
{
    qDebug() <<  "reply" << reply->readAll();
}

void HttpsMsg::setHeadlerimpl()
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=UTF-8"));
    qDebug() << "requestURL" << requestURL;
    request.setUrl(QUrl(requestURL));
}

void HttpsMsg::sendMsg(const QByteArray & data)
{
    setHeadler("/aimbot-api/sys/login");
    m_manager->post(request, data);
}
