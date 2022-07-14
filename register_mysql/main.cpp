#include "Login.h"
#include <QApplication>
#include <QtSql>
#include <QMessageBox>
int main(int argc, char *argv[])
{
//    在绘制窗口之前创建，都需要创建一个唯一的QApplication
    QApplication a(argc, argv);
//    实例化一个登录窗口
    Loginwindow w;
//    连接数据库
//    连接过程是app->QT插件->mysql动态库dll/lib->mysql服务，所以需要导入动态库到mysql中

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("zer");
    db.setUserName("root");
    db.setPort(3306);
    db.setPassword("root");
    //如果数据库连接成功打开窗口否则退出程序
    if(db.open())
    {
        w.show();
    }
    else
    {
//        创建一个消息窗口用于提示警告
        QMessageBox::warning(nullptr,"error","数据库连接失败");
        return 0;
    }
//    这里a.exec()可以做到循环显示，不会在某些操作后自动退出，与return 0有区别
    return a.exec();
}
