#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QFile>
#include <QSsl>
#include <QSslKey>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QSslError>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtNetwork>

class HttpsClient : public QObject
{
    Q_OBJECT

public:
    HttpsClient(QObject *parent = nullptr);
    void sendMsg(const QByteArray &data);
    void uploadFile(const QString &file);

    ~HttpsClient();

public slots:
    void replyFinished(QNetworkReply*reply);

private:
    QNetworkAccessManager *manager;  //网络链接管理器

};

#endif // HTTPSCLIENT_H
