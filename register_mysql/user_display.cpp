#include "user_display.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <Qtsql>

userwindow::userwindow(QWidget *parent)
    :QDialog(parent)
{
    //登陆界面定义
    setWindowTitle(tr("注册界面"));
    //窗口只能最小化
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    //成员初始化
    UserName = new QLabel(tr("用户名："));
    Password = new QLabel(tr("密码："));
    UserNameEdit = new QLineEdit();
    PasswordEdit = new QLineEdit();
    user_send = new QPushButton(tr("提交"));
    //实现上方信息网格布局
    MessageLayout = new QGridLayout();
    MessageLayout->addWidget(UserName,0,0);
    MessageLayout->addWidget(UserNameEdit,0,1);
    MessageLayout->addWidget(Password,1,0);
    MessageLayout->addWidget(PasswordEdit,0,1);
     //实现下方按钮网格布局
    ButtonLayout = new QGridLayout();
    ButtonLayout->addWidget(user_send,0,0);
    ButtonLayout->setSpacing(15);
    //实现主网格
    MainLayout = new QGridLayout(this);
    MainLayout->addLayout(MessageLayout,0,0);
    MainLayout->addLayout(ButtonLayout,1,0);
    MainLayout->setMargin(15);
    MainLayout->setSpacing(10);
    //连接信号和槽
    connect(user_send,SIGNAL(clicked()),this,SLOT(user_slots()));
}
//槽函数实现
void userwindow::user_slots()
{
    QString UName = UserNameEdit->text();
    QMessageBox::warning(nullptr,"已发送","您的消息发送成功");
}

userwindow::~userwindow()
{

}
