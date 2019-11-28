#include "DataRecv.h"
#include <QDebug>


DataRecv::DataRecv(QObject *parent):QObject(parent)
{
    dataRecvWS = Q_NULLPTR;
    connectStatus = false;
    m_timer = new QTimer();
}

DataRecv::~DataRecv()
{
    if (m_timer)
    {
        delete m_timer;
    }
    if (dataRecvWS)
    {
        delete dataRecvWS;
    }
}

/*
 * @breaf 创建WebSocket连接
*/
void DataRecv::createDataRecvWS()
{
    if(dataRecvWS == Q_NULLPTR)
    {
        dataRecvWS = new QWebSocket();
        qDebug()<<"create websocket!";
        connect(dataRecvWS,SIGNAL(disconnected()),this,SLOT(onDisConnected()));
        connect(dataRecvWS,SIGNAL(textMessageReceived(const QString &)),this,SLOT(onTextReceived(const QString &)));
        connect(dataRecvWS,SIGNAL(connected()),this,SLOT(onConnected()));
        connect(m_timer,SIGNAL(timeout()),this,SLOT(reconnect()));
        dataRecvWS->open(QUrl(m_url));
    }
}

/*
 * @breaf 判断连接状态 *
 *  @note  当连接成功后，触发该函数
 */
void DataRecv::onConnected()
{
    qDebug()<<"DataReveive websocket is already connect!";
    connectStatus = true;
    m_timer->stop();
//    qDebug()<<"Address："<<dataRecvWS->peerAddress();
}

/* @breaf 数据处理函数
* @param msg，数据信息
* @note  当收到服务端发送的数据时，触发该函数
 */
void DataRecv::onTextReceived(QString msg)
{
    qDebug()<<"----------------data-----------------";
    qDebug()<<msg;
}

/*@breaf 连接断开
 *  @note  当连接断开时，触发该函数
*/
void DataRecv::onDisConnected()
{
    qDebug()<<"DataReceive websocket is disconnected!!!";
    connectStatus = false;
    m_timer->start(3000);/*-<当连接失败时，触发重连计时器，设置计数周期为3秒 */
}

/*@breaf 周期重连函数
 * @note  连接建立成功时，调用该函数
*/
void DataRecv::reconnect()
{
    qDebug()<<"try to reconnect!";
    dataRecvWS->abort();
    dataRecvWS->open(QUrl(m_url));
}

void DataRecv::setUrl(const QString & url)
{
    m_url = url;
}
