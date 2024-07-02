#include "Tcp.h"

Tcp::Tcp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpClass())
{
    ui->setupUi(this);
    TcpServer* server = new TcpServer(this, 8989);
}

Tcp::~Tcp()
{
    delete ui;
}
