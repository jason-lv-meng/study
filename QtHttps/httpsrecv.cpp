#include "httpsrecv.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>

NetworkRequestManager::NetworkRequestManager(QObject *parent) : QObject(parent)
{
// // Https ca certificate ..
// // 创建客户端证书
//QFile t_file(":/https/license/pc-client.crt");
// t_file.open(QIODevice::ReadOnly);
// const QSslCertificate certificate(&t_file, QSsl::Pem);
// t_file.close();

//// 创建客户端私钥
//t_file.setFileName(":/https/license/pc-client.key");
// t_file.open(QIODevice::ReadOnly);
// const QSslKey prvateKey(&t_file, QSsl::Rsa);
// t_file.close();

//// SSL验证模式；TLS协议版本
//m_sslconf.setPeerVerifyMode(QSslSocket::VerifyPeer);
// m_sslconf.setProtocol(QSsl::TlsV1_2OrLater);
// m_sslconf.setLocalCertificate(certificate);
// m_sslconf.setPrivateKey(prvateKey);

//// 创建服务器端证书
//QList<QSslCertificate> caCerList;
// t_file.setFileName(":/https/license/pc-server.pem");
// t_file.open(QIODevice::ReadOnly);
// const QSslCertificate cACertificate(&t_file, QSsl::Pem);
// // 将服务证书加入到CA列表中
//caCerList.append(cACertificate);
// m_sslconf.setCaCertificates(caCerList);
// t_file.close();
    // 发送https请求前准备工作;
    QSslConfiguration config;

    QSslConfiguration conf = m_request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    m_request.setSslConfiguration(conf);



m_manager = new QNetworkAccessManager;

 QObject::connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(RequestFinished(QNetworkReply*)));
 QObject::connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrorsH(QNetworkReply*,QList<QSslError>)));
}

void NetworkRequestManager::post(const QString &url, QByteArray & data)
{
    data = "{
        "password": "string",
        "type": "string",
        "username": "string\"}";
    m_request.setUrl(QUrl(url));       // "https://www.temp.com"
    m_manager->post(m_request,);
}

void NetworkRequestManager::sslErrorsH(QNetworkReply *reply, QList<QSslError> error)
{
 qDebug() <<"** sslErrorsH .." <<error;
}

void NetworkRequestManager::RequestFinished(QNetworkReply *reply)
{
 int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
 QVariant statusCodeV =
 reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll().constData());
 QJsonObject obj = jdoc.object();

qDebug() <<"** RequestFinished" <<reply->isFinished() <<statusCode;

if(!obj.isEmpty()) emit this->PostRequestFinished(obj);
 reply->deleteLater();
}
