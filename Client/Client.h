#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include <qtcpsocket.h>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientClass; };
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::ClientClass *ui;

protected slots:
    void onClieckedConnectedBtn();
    void onClieckedDisconnectedBtn();
    void onClicekedSendBtn();

private:
    QTcpSocket* m_client;
};
