#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>
#include <QTimerEvent>
#include <QKeyEvent>
#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class ChatRoom; }
QT_END_NAMESPACE

class ChatRoom : public QWidget
//class ChatRoom : public QDialog
{
    Q_OBJECT

public:
    ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
    void paintEvent(QPaintEvent*) override;
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent *event) override;
    QString user_name;

private slots:
    void ClickedAddChatRoomButton();
    void ClickedSendMessageButton();
    void ClickedFlushOnlineButton();
    void ReadChatMessageSlot();
    void ChatDisConnectSlot();
    void ReadOnlineMessageSlot();
    void OnlineDisConnectSlot();
private:
    Ui::ChatRoom *ui;
    QTextEdit* ChatRoomTextEdit;//聊天室
    QLineEdit* InputTextEdit;//输入框
    QLabel* OnlineCountLabel;//在线人数信息
    QLineEdit* UserNameLineEdit;//用户姓名
    QPushButton* AddChatRoom;//加入聊天室
    QPushButton* SendMessage;//发送消息
    QPushButton* FlushOnline;//刷新在线人数
    QTcpSocket* chatSocket;//聊天套接字
    QTcpSocket* onlineSocket;//在线套接字
    // 这里的ip地址需要进行改动,改成服务器的ip,在运行server的时候可以看到
    const QString chatAddress = QString("192.168.1.8");
    const quint16 chatPort = 48989;
    // 同上
    const QString onlineAddress = QString("192.168.1.8");
    const quint16 onlinePort = 49898;
    bool connectedState;
};
#endif // CHATROOM_H
