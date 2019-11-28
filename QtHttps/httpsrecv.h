#ifndef HTTPSRECV_H
#define HTTPSRECV_H

#include <QObject>
#include <QNetworkAccessManager>

#include <QSsl>
#include <QSslKey>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QSslError>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtNetwork>

class NetworkRequestManager : public QObject
{
 Q_OBJECT
public:
 explicit NetworkRequestManager(QObject *parent = 0);
    void NetworkRequestManager::post(const QString &url, QByteArray & data);
// void sendMsg(const QString& ,const QString&, const QString&);
// void sendMsgWithoutToken(const QString&, const QString&);

private:
 QSslConfiguration m_sslconf;
 QNetworkRequest m_request;
 QNetworkAccessManager *m_manager;

signals:
 void PostRequestFinished(const QJsonObject&);

private slots:
 void RequestFinished(QNetworkReply*);
 void sslErrorsH(QNetworkReply*, QList<QSslError>);
};


#endif // HTTPSRECV_H
