#include "TcpServer.h"
#include <qtcpsocket.h>
#include <qdebug.h>
TcpServer::TcpServer(QObject *parent,unsigned short port)
	: QTcpServer(parent)
{
	m_num = 0;
	emit sendNum(m_num);
	this->listen(QHostAddress::Any, port);
	if (this->isListening())
	{
		qDebug() << "isListening";
	}

}

TcpServer::~TcpServer()
{}

void TcpServer::incomingConnection(qintptr handle)
{
	QTcpSocket* client = new QTcpSocket(this);
	if (!client->setSocketDescriptor(handle))
	{
		delete client;
		return;
	}
	m_clientlist.append(client);
	
	m_num++;
	emit sendNum(m_num);
	connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
	connect(client, &QTcpSocket::disconnected, this, &TcpServer::onDisConnected);
}

void TcpServer::broadCast(const QByteArray& data, QTcpSocket* sender)
{
	for (auto clientSocket : m_clientlist)
	{
		if (clientSocket != sender)
		{
			clientSocket->write(data);
		}
	}
}

int TcpServer::getNum() const
{
	return m_num;
}

void TcpServer::onDisConnected()
{
	/*
		*当某一个Object emit一个signal的时候，它就是一个sender, 系统会记录下当前是谁emit出这个signal的
		*当客户端连接时会发出该客户端的signal
	*/
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	if (!socket)
	{
		return;
	}
	//从客户端列表移除客户端并删除
	m_clientlist.removeOne(socket);
	socket->deleteLater();
	qDebug() << "客户端断开！";
	m_num--;
	emit sendNum(m_num);
}



void TcpServer::onReadyRead()
{
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	if (!socket)
	{
		return;
	}
	//读信息
	QByteArray buffer = socket->readAll();
	//转发
	broadCast(buffer, socket);
}
