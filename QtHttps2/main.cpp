#include <QCoreApplication>
#include "include/httpdownload.h"
#include "httpsclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HttpsClient client;
//    client.sendMsg("aaaaaa");
    client.uploadFile("login.txt");
    return a.exec();
}
