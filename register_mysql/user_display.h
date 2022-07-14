#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

class userwindow : public QDialog
{
//    使用信号槽
    Q_OBJECT

public:
    userwindow(QWidget *parent = nullptr);
    ~userwindow();
private:

    //声明布局
   QGridLayout *MessageLayout;
   QGridLayout *ButtonLayout;
   QGridLayout *MainLayout;
    //声明信息成员
//   qlabel文本框，qlineedit单行输入框，qpushbutton点击按钮
   QLabel *UserName;
   QLabel *Password;
   QLineEdit *UserNameEdit;
   QLineEdit *PasswordEdit;
   QPushButton *user_send;
    //声明槽
public slots:
   void user_slots();
};

#endif // DIALOG_
