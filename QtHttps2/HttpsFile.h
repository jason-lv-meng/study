#ifndef HTTPSFILE_H
#define HTTPSFILE_H
#include "HttpsBase.h"

class HttpsFile : public HttpsBase
{
    Q_OBJECT
public:
    HttpsFile(QObject *parent = nullptr);
    void  uploadFile(const QString &file);

protected:
    virtual void setHeadlerimpl();

protected slots:
    void  replyFinished(QNetworkReply* reply);

private:
    inline void readFileContent(const QString &file, QByteArray &content);

private:
    QByteArray fileName;
};

#endif // HTTPSFILE_H
