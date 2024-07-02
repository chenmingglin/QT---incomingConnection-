#pragma once

#include <QTcpServer>
#include <qlist.h>
class TcpServer  : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject* parent, unsigned short port);
	~TcpServer();

	void incomingConnection(qintptr handle) override;//重写incomingConnection
	void broadCast(const QByteArray& data, QTcpSocket* sender);//转发客户端发来的消息
	int getNum() const;//客户端数量

signals:
	void sendNum(int num);
protected slots:
	void onReadyRead();//接受客户端的信息
	void onDisConnected();//客户端断开，删除客户端信息和，客户端列表里的客户端

private:
	QList<QTcpSocket*> m_clientlist;//维护客户端列表
	int m_num;
};
