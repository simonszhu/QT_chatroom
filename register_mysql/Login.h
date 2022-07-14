#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

class Loginwindow : public QDialog
{
//    使用信号槽
    Q_OBJECT

public:
    int login_count = 5;
    Loginwindow(QWidget *parent = nullptr);
    ~Loginwindow();
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
   QPushButton *LoginButton;
   QPushButton *RegisterButton;
    //声明槽
public slots:
   void Login_slots();
   void Register_slots();
};

#endif // DIALOG_
