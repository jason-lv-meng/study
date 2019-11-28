/*用于创建websocket连接 *
 * 该类实现了client端基本的websocket创建，自动重连。
*/
#ifndef DATARECV_H
#define DATARECV_H

#include <QObject>
#include <QWebSocket>
#include <QString>
#include <QTimer>

class DataRecv : public QObject
{
    Q_OBJECT
public:
    DataRecv(QObject *parent=0);
    ~DataRecv();
    void setUrl(const QString & url);

public slots:
    void createDataRecvWS();    /*-<创建websocket连接 */

private:
    QWebSocket *dataRecvWS;     /*-<websocket类 */
    bool connectStatus;         /*-<websocket连接状态，连接成功：true；断开：false */

    QTimer *m_timer;            /*-<周期重连Timer */
    QString m_url;

private slots:
    void onConnected();                 /*-<socket建立成功后，触发该函数 */
    void onTextReceived(QString msg);   /*-<收到Sev端的数据时，触发该函数 */
    void onDisConnected();              /*-<socket连接断开后，触发该函数 */
    void reconnect();                   /*-<周期重连函数 */

};

#endif // DATARECV_H
