#include "server.h"

Server::Server()
{
    this->chatServer = new QTcpServer();
    this->onlineServer = new QTcpServer();
    chatSocket = NULL;
    onlineSocket = NULL;
}

Server::~Server()
{
    qDebug() << "ChatRoom Server has been shut down...";
}

bool Server::StartServer()
{
    QList<QHostAddress> address_list = QNetworkInterface::allAddresses();
    int index = -1;
    for(int i = 0; i < address_list.size(); i++)
//        如果地址列表中的某一个索引不为空,且地址为IPV4,index = i
        if(address_list.at(i).isNull() == false && address_list.at(i).protocol() == QAbstractSocket::IPv4Protocol)
        {
            index = i;
            break;
        }
    if(index == -1)
    {
        qDebug() << "Can not find any ip address...";
        return false;
    }
    const int chatPort = 48989, onlinePort = 49898;
    qDebug() << "chatServer:    " << "IP:" << address_list.at(index).toString() << "    Port:" << QString::number(chatPort);
    qDebug() << "onlineServer:  " << "IP:" << address_list.at(index).toString() << "    Port:" << QString::number(onlinePort);

//    如果已经设置监听
    if(chatServer->isListening() || onlineServer->isListening())//如果有任何一个server已经开始监听
    {
        qDebug() << "ChatRoom Server has started...";
        return false;
    }
    else
    {
        //    通过chatServer这个socket对象，进行监听
        if(chatServer->listen(QHostAddress(address_list.at(index).toString()), quint16(chatPort)))
        {
            qDebug() << "ChatServer listen success...";
//            建立连接，这里的槽函数是NewChatConnectSlot，用于服务器端接收客户端发来的消息,并发送给其他客户端
            QObject::connect(chatServer, SIGNAL(newConnection()), this, SLOT(NewChatConnectSlot()));
        }
        else
        {
            qDebug() << "ChatServer listen fail...";
            return false;
        }
//        如果是
        if(onlineServer->listen(QHostAddress(address_list.at(index).toString()), quint16(onlinePort)))
        {
            qDebug() << "OnlineServer listen success...";
//            建立连接，这里的槽函数是NewOnlineConnectSlot，只用于同步给不同的客户端当前在线人数
            QObject::connect(onlineServer, SIGNAL(newConnection()), this, SLOT(NewOnlineConnectSlot()));
        }
        else
        {
            qDebug() << "OnlineServer listen fail...";
            return false;
        }
    }
    return true;
}

void Server::timerEvent(QTimerEvent*)
{

}

void Server::NewChatConnectSlot()
{
    chatSocket = chatServer->nextPendingConnection();//获取当前连接的已连接的套接字
    CHATSOCKET* user = new CHATSOCKET();
    user->socket = chatSocket;
    user->UserName = QString("");
    user->GetName = false;
    chatInfoList.push_back(user);
    chatSocketList.push_back(chatSocket);
    QObject::connect(chatSocket, &QTcpSocket::readyRead, this, &Server::ReadChatMessageSlot);
    QObject::connect(chatSocket, &QTcpSocket::disconnected, this, &Server::ChatDisConnectSlot);

    qDebug() << "New chat connection come in..." << "      IP:" << chatSocket->peerAddress().toString() << "  Port:" << QString::number(chatSocket->peerPort());
    qDebug() << "Current number of chat server connections:   " << chatSocketList.count();
    chatSocket = NULL;
}

void Server::ReadChatMessageSlot()
{
    QTcpSocket* recv = NULL;
    QByteArray arr;
    if(chatSocketList.isEmpty() == false)//有客户端存在
    {
        for(int i = 0; i < chatSocketList.count(); i++)//服务端接收信息
        {
            arr = chatSocketList.at(i)->readAll();//接收客户端发送的字节信息
            if(arr.isNull())  continue;//空代表不是该客户端发送
            recv = chatSocketList.at(i);
            break;
        }
//        接收到了数据
        if(recv == NULL)
            return;
        CHATSOCKET* User = NULL;
        for(int i = 0; i < chatInfoList.count(); i++)
            if(chatInfoList.at(i)->socket == recv)
            {
                User = chatInfoList.at(i);
                break;
            }
        if (User == NULL)
            return;
        if(User->GetName == false)
        {
            User->UserName = QString(arr.data());
            User->GetName = true;
            return;
        }
        qDebug() << User->UserName << ":" << QString(arr.data());
        for(int i = 0; i < chatSocketList.count(); i++)//给其它客户端发送信息
        {
            if(chatSocketList.at(i) == recv)  continue;//遇到自己就跳过
            chatSocketList.at(i)->write(QString(User->UserName + ":" + arr.data()).toUtf8());//发送信息
        }
    }
}

void Server::ChatDisConnectSlot()
{
    for(int i = 0; i < chatSocketList.count(); i++)
        if(chatSocketList.at(i)->state() == QAbstractSocket::UnconnectedState)
        {
            QTcpSocket* tempChatSocket = chatSocketList.takeAt(i);
            tempChatSocket->deleteLater();
        }
    for(int i = 0; i < chatInfoList.count(); i++)
        if(chatInfoList.at(i)->socket->state() == QAbstractSocket::UnconnectedState)
        {
            qDebug() << chatInfoList.at(i)->UserName << " disconnected...";
            CHATSOCKET* tempChatInfo = chatInfoList.takeAt(i);
            tempChatInfo->deleteLater();
        }
    qDebug() << "Current number of chat server connections:   " << chatSocketList.count();
}

void Server::NewOnlineConnectSlot()
{
    onlineSocket = onlineServer->nextPendingConnection();//获取当前连接的套接字
    CHATSOCKET* user = new CHATSOCKET();
    user->socket = onlineSocket;
    user->UserName = QString("");
    user->GetName = false;
    onlineInfoList.push_back(user);
    onlineSocketList.push_back(onlineSocket);
    QObject::connect(onlineSocket, &QTcpSocket::readyRead, this, &Server::ReadOnlineMessageSlot);
    QObject::connect(onlineSocket, &QTcpSocket::disconnected, this, &Server::OnlineDisConnectSlot);

    qDebug() << "New online connection come in..." << "    IP:" << user->socket->peerAddress().toString() << "  Port:" << QString::number(user->socket->peerPort());
    qDebug() << "Current number of online server connections: " << onlineSocketList.count();
    onlineSocket = NULL;
}

void Server::ReadOnlineMessageSlot()
{
    QTcpSocket* recv = NULL;
    QByteArray arr;
    if(onlineSocketList.isEmpty() == false)//有客户端存在
    {
        for(int i = 0; i < onlineSocketList.count(); i++)//服务端接收信息
        {
//            if(onlineSocketList.at(i)->state() == QAbstractSocket::UnconnectedState) continue;
            arr = onlineSocketList.at(i)->readAll();//接收客户端发送的字节信息
            if(arr.isNull())  continue;//空代表不是该客户端发送
            recv = onlineSocketList.at(i);
            break;
        }
        if(recv == NULL)
            return;
        CHATSOCKET* User = NULL;
        for(int i = 0; i < onlineInfoList.count(); i++)
            if(onlineInfoList.at(i)->socket == recv)
            {
                User = onlineInfoList.at(i);
                break;
            }
        if(User == NULL)
            return;
        if(User->GetName == false)
        {
            User->UserName = QString(arr.data());
            User->GetName = true;
            return;
        }
        if(QString(arr.data()) == QString("request for online count"))
//            将发送给服务器端的数据转发给其他客户端套接字上
            recv->write(QString::number(onlineSocketList.count()).toUtf8());
    }
}

void Server::OnlineDisConnectSlot()
{
    for(int i = 0; i < onlineSocketList.count(); i++)
        if(onlineSocketList.at(i)->state() == QAbstractSocket::UnconnectedState)
        {
            QTcpSocket* tempOnlineSocket = onlineSocketList.takeAt(i);
            tempOnlineSocket->deleteLater();
        }
//    for(int i = 0; i < onlineInfoList.count(); i++)
//        if(onlineInfoList.at(i)->socket->state() == QAbstractSocket::UnconnectedState)
//        {
//            qDebug() << onlineInfoList.at(i)->UserName << " disconnected...";
//            CHATSOCKET* tempOnlineInfo = chatInfoList.takeAt(i);
//            tempOnlineInfo->deleteLater();
//        }
    qDebug() << "Current number of online server connections: " << onlineSocketList.count();
}























