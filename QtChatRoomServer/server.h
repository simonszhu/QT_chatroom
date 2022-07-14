#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <QDateTime>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QTimerEvent>

typedef struct _CHATSOCKET : public QObject
{
    QString UserName;
    QTcpSocket* socket;
    bool GetName;
}CHATSOCKET;

class Server : public QObject
{
    Q_OBJECT
public:
    Server();
    ~Server();
    bool StartServer();
    void timerEvent(QTimerEvent*) override;

private slots:
    void NewChatConnectSlot();//新的聊天连接槽
    void ReadChatMessageSlot();//读取聊天信息槽
    void ChatDisConnectSlot();//断开聊天连接槽
    void NewOnlineConnectSlot();//新的在线连接槽
    void ReadOnlineMessageSlot();//读取在线信息槽
    void OnlineDisConnectSlot();//断开在线连接槽

private:
//    创建用于监听的套接字对象
    QTcpServer* chatServer;//处理聊天信息服务器
    QList<QTcpSocket*> chatSocketList;//存放所有的聊天连接（用一个列表存放socket的地址）
    QList<CHATSOCKET*> chatInfoList;
    QTcpSocket* chatSocket;//当前聊天处理的套接字
    QTcpServer* onlineServer;//处理在线检测的服务器
    QList<QTcpSocket*> onlineSocketList;//存放所有在线检测的服务器（用一个列表存放socket的地址）
    QList<CHATSOCKET*> onlineInfoList;
    QTcpSocket* onlineSocket;//当前在线处理的套接字
};

#endif // SERVER_H
