#ifndef HTTPSBASE_H
#define HTTPSBASE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

class HttpsBase : public QObject
{
    Q_OBJECT
public:
    explicit HttpsBase(QObject *parent = nullptr);

protected:
    void setHeadler(const QString & childPath);
    virtual void setHeadlerimpl() = 0;


protected:
    QNetworkAccessManager *m_manager;
    QNetworkRequest request;
    QString serverURL;
    QString requestURL;

};

#endif // HTTPSBASE_H
