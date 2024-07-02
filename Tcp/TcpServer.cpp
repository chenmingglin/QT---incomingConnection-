#include "TcpServer.h"
#include <qtcpsocket.h>
#include <qdebug.h>
TcpServer::TcpServer(QObject *parent,unsigned short port)
	: QTcpServer(parent)
{
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

void TcpServer::onDisConnected()
{
	/*
		*��ĳһ��Object emitһ��signal��ʱ��������һ��sender, ϵͳ���¼�µ�ǰ��˭emit�����signal��
		*���ͻ�������ʱ�ᷢ���ÿͻ��˵�signal
	*/
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	if (!socket)
	{
		return;
	}
	//�ӿͻ����б��Ƴ��ͻ��˲�ɾ��
	m_clientlist.removeOne(socket);
	socket->deleteLater();

}



void TcpServer::onReadyRead()
{
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	if (!socket)
	{
		return;
	}
	//����Ϣ
	QByteArray buffer = socket->readAll();
	//ת��
	broadCast(buffer, socket);
}
