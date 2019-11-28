#include <QCoreApplication>
#include "include/httpdownload.h"
#include "HttpsClient.h"
#include "include/httpdownload.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    HttpDownLoad load;
//    load.SetDownLoadInfo(1,"a.jpg","https://video.ubtrobot.com/cbis/edu/file/img/a4bb54cc-9484-4048-908a-c1fb8c15b3fe.jpg");
//    load.DownloadFile();
    HttpsClient client;
//    client.sendMsg("aaaaaa");
    client.uploadFile("upload.jpg");
    return a.exec();
}
