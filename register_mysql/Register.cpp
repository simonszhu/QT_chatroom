#include "Register.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <Qtsql>

registerwindow::registerwindow(QWidget *parent)
    :QDialog(parent)
{
    //登陆界面定义
    setWindowTitle(tr("注册界面"));
    //窗口只能最小化
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    //成员初始化
    UserName = new QLabel(tr("用户名："));
    Password = new QLabel(tr("密码："));
    RePassword = new QLabel(tr("重复密码："));
    UserNameEdit = new QLineEdit();
    PasswordEdit = new QLineEdit();
    RePasswordEdit = new QLineEdit();
    Email = new QLabel("邮件：");
    EmailEdit = new QLineEdit();
    confirm = new QPushButton(tr("确认"));
    resetting = new QPushButton(tr("重置"));
    //实现上方信息网格布局
    MessageLayout = new QGridLayout();
    MessageLayout->addWidget(UserName,0,0);
    MessageLayout->addWidget(UserNameEdit,0,1);
    MessageLayout->addWidget(Password,1,0);
    MessageLayout->addWidget(PasswordEdit,1,1);
    MessageLayout->addWidget(RePassword,2,0);
    MessageLayout->addWidget(RePasswordEdit,2,1);
    MessageLayout->addWidget(Email,3,0);
    MessageLayout->addWidget(EmailEdit,3,1);
     //实现下方按钮网格布局
    ButtonLayout = new QGridLayout();
    ButtonLayout->addWidget(confirm,0,0);
    ButtonLayout->addWidget(resetting,0,1);
    ButtonLayout->setSpacing(15);
    //实现主网格
    MainLayout = new QGridLayout(this);
    MainLayout->addLayout(MessageLayout,0,0);
    MainLayout->addLayout(ButtonLayout,1,0);
    MainLayout->setMargin(15);
    MainLayout->setSpacing(10);
    //连接信号和槽
    connect(confirm,SIGNAL(clicked()),this,SLOT(confirm_slots()));
    connect(resetting,SIGNAL(clicked()),UserNameEdit,SLOT(clear()));
    connect(resetting,SIGNAL(clicked()),PasswordEdit,SLOT(clear()));
    connect(resetting,SIGNAL(clicked()),RePasswordEdit,SLOT(clear()));
}
//槽函数实现
void registerwindow::confirm_slots()
{
    QString UName = UserNameEdit->text();
    QString email = EmailEdit->text();
    QString Pword;
    if(PasswordEdit->text()==RePasswordEdit->text())
    {
        Pword = PasswordEdit->text();
        QString i = QString("insert into zer.user values ('%1','%2','%3'); ").arg(UName).arg(email).arg(Pword);
        QString S = QString("select * from zer.user where username='%1' ").arg(UName);
        QSqlQuery query;
        if(query.exec(S) && (query.first() == true))
            QMessageBox::warning(nullptr,"Error","用户名重复，请重试！！！");
        else if(query.exec(i))
            QMessageBox::information(nullptr, "注册成功", "注册成功！！！", QMessageBox::Yes);
//        query.first()指向结果集的第一行记录，意思查询到了相同的用户名
        else
            QMessageBox::warning(nullptr,"Error","注册失败，请重试！！！");
        this->close();
    }
    else
        QMessageBox::warning(nullptr,"Error","第一次输入密码与第二次输入密码不符，请重试！！！");
}

registerwindow::~registerwindow()
{

}
