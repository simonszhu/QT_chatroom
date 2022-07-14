#include "Login.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include "Register.h"
#include "user_display.h"
#include <Qtsql>
#include "chatroom.h"
#include <iostream>
Loginwindow::Loginwindow(QWidget *parent)
    : QDialog(parent)
{
    //登陆界面定义
    setWindowTitle(tr("登陆界面"));
    //窗口只能最小化
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    //成员初始化
    UserName = new QLabel(tr("用户名："));
    Password = new QLabel(tr("密码："));
    UserNameEdit = new QLineEdit();
    PasswordEdit = new QLineEdit();
    LoginButton = new QPushButton(tr("登陆"));
    RegisterButton = new QPushButton(tr("注册"));
    //实现上方信息网格布局
    MessageLayout = new QGridLayout();
    MessageLayout->addWidget(UserName,0,0);
    MessageLayout->addWidget(UserNameEdit,0,1);
    MessageLayout->addWidget(Password,1,0);
    MessageLayout->addWidget(PasswordEdit,1,1);
    //实现下方按钮网格布局
    ButtonLayout = new QGridLayout();
    ButtonLayout->addWidget(LoginButton,0,0);
    ButtonLayout->addWidget(RegisterButton,0,1);
    ButtonLayout->setSpacing(15);
    //实现主网格
    MainLayout = new QGridLayout(this);
    MainLayout->addLayout(MessageLayout,0,0);
    MainLayout->addLayout(ButtonLayout,1,0);
//    控件与窗体的左右边距
    MainLayout->setMargin(15);
//    控件与空间之间的上下间距
    MainLayout->setSpacing(10);
    //连接信号和槽
//    将登录按钮与点击的信号相互连接，及其信号响应函数（点击之后调用执行什么函数）
    connect(LoginButton,SIGNAL(clicked()),this,SLOT(Login_slots()));
    connect(RegisterButton,SIGNAL(clicked()),this,SLOT(Register_slots()));

}
//槽函数实现
void Loginwindow::Login_slots()
{
        QString  UName = UserNameEdit->text();
        QString  Pword = PasswordEdit->text();
        //数据库存储用户名用username密码用password
        QString s = QString("select * from zer.user where username='%1'and password='%2' ").arg(UName).arg(Pword);
        /*if(UName == "admin"&&Pword == "admin")
            QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);*/
        //查询数据库如果账号和密码匹配返回真否则返回假
        QSqlQuery query;
        query.exec(s);

        QString value;
        QSqlRecord rec = query.record();
        while(query.next()){
            rec = query.record();
            int col = rec.indexOf("username");
            value = query.value(col).toString();
        }
        if(query.first()){
            this->hide();
//            this->close();
            QMessageBox::information(nullptr, "登陆成功", "登陆成功！！！", QMessageBox::Yes);
            this->hide();
//            ChatRoom w;
//            实例化的时候需要用指针的方法new，不然是局部变量，不加exec的话会被析构
//            调用聊天室窗口
//            QMessageBox::warning(nullptr,"Error",tr("debug: %1").arg(value));
            ChatRoom *w = new ChatRoom();
            w->user_name = value;
            w->show();
//            this->show();
        }
        else{
            login_count--;

            if(login_count == 0){
                login_count = 5;
                QMessageBox::warning(nullptr,"Error",tr("登录失败,您已经没有机会了！！！"));
                this->close();
            }else{
                QMessageBox::warning(nullptr,"Error",tr("登录失败,您还有%1次机会，请重试！！！").arg(login_count));
            }
        }
}
void Loginwindow::Register_slots()
{
//    隐藏当前页面
    this->hide();
//    当用户点击注册按钮，创建一个注册窗口
    registerwindow re;
//    创建结束后展示
    re.show();
    re.exec();
//    显示当前界面
    this->show();
}
Loginwindow::~Loginwindow()
{

}
