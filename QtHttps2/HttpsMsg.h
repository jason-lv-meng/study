#ifndef HTTPSMSG_H
#define HTTPSMSG_H
#include "HttpsBase.h"

class HttpsMsg : public HttpsBase
{
    Q_OBJECT
public:
    HttpsMsg(QObject *parent = nullptr);
    ~HttpsMsg();
    void sendMsg(const QByteArray & data);

protected:
    virtual void setHeadlerimpl();


protected slots:
    void  replyFinished(QNetworkReply* reply);
};

#endif // HTTPSMSG_H
