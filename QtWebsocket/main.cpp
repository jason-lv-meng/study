#include <QCoreApplication>
#include "DataRecv.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DataRecv *m_dataReceive = new DataRecv();
    m_dataReceive->setUrl("ws://192.168.1.100:8090/aimbot-api/websocket/123");
    m_dataReceive->createDataRecvWS();


    return a.exec();
}
