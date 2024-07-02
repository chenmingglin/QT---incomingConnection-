#include "Tcp.h"

Tcp::Tcp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpClass())
{
    ui->setupUi(this);
    TcpServer* server = new TcpServer(this, 8989);
    connect(server, &TcpServer::sendNum, this, &Tcp::showNum);
}

Tcp::~Tcp()
{
    delete ui;
}

void Tcp::showNum(int num)
{
    ui->num->setText(QString::number(num));
}
