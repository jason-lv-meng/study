#include "HttpsBase.h"

HttpsBase::HttpsBase(QObject *parent) : QObject(parent)
{
    serverURL = "http://test79.ubtrobot.com:9009";
//    serverURL = "http://127.0.0.1:8080";
}


void HttpsBase::setHeadler(const QString & childPath)
{
    requestURL = serverURL + childPath;
    setHeadlerimpl();
}
