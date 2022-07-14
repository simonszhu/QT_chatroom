#ifndef REGISTER_H
#define REGISTER_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

class registerwindow:public QDialog
{
    Q_OBJECT

public:
    registerwindow(QWidget *parent = nullptr);
    ~registerwindow();
private:
    //声明布局
    QGridLayout *MessageLayout;
    QGridLayout *ButtonLayout;
    QGridLayout *MainLayout;
    //声明信息成员
    QLabel *UserName;
    QLabel *Password;
    QLabel *RePassword;
    QLineEdit *UserNameEdit;
    QLineEdit *PasswordEdit;
    QLineEdit *RePasswordEdit;
    QLabel *Email;
    QLineEdit *EmailEdit;
//    确认和重置按钮
    QPushButton *confirm;
    QPushButton *resetting;
    //声明槽
public slots:
    void confirm_slots();

};
#endif // REGISTER_H
