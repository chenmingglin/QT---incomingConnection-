#include "Client.h"
#include <qdebug.h>
#include <qtcpsocket.h>
Client::Client(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientClass())
{
    ui->setupUi(this);
    setWindowTitle("客户端");

    ui->connected->setEnabled(true);
    ui->disconnected->setDisabled(true);

    m_client = new QTcpSocket(this);
    connect(ui->connected, &QPushButton::clicked, this, &Client::onClieckedConnectedBtn);
    connect(ui->disconnected, &QPushButton::clicked, this, &Client::onClieckedDisconnectedBtn);
    connect(ui->send, &QPushButton::clicked, this, &Client::onClicekedSendBtn);

    connect(m_client, &QTcpSocket::readyRead, this, [=]() {
        QByteArray data = m_client->readAll();
        ui->record->append(data);
        });
    connect(m_client, &QTcpSocket::disconnected, this, [=]() {
        m_client->close();
        ui->connected->setEnabled(true);
        ui->disconnected->setDisabled(true);
        });

    connect(m_client, &QTcpSocket::connected, this, [=]() {
        qDebug() << "连接服务器成功!";
        ui->connected->setDisabled(true);
        ui->disconnected->setEnabled(true);

        });
}

Client::~Client()
{
    delete ui;
}

void Client::onClieckedDisconnectedBtn()
{
    m_client->close();

    qDebug() << "断开连接!";
    ui->connected->setEnabled(true);
    ui->disconnected->setDisabled(true);
}

void Client::onClieckedConnectedBtn()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_client->connectToHost(QHostAddress(ip), port);


}

void Client::onClicekedSendBtn()
{
    QString msg = ui->msg->toPlainText();
    QString name = ui->name->text();
    m_client->write(name.toUtf8() + "：" + msg.toUtf8());
    ui->record->append(name + "：" + msg);
    ui->msg->clear();
}
