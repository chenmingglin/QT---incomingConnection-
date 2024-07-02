#pragma once

#include <QTcpServer>
#include <qlist.h>
class TcpServer  : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject* parent, unsigned short port);
	~TcpServer();

	void incomingConnection(qintptr handle) override;//��дincomingConnection
	void broadCast(const QByteArray& data, QTcpSocket* sender);//ת���ͻ��˷�������Ϣ
protected slots:
	void onReadyRead();//���ܿͻ��˵���Ϣ
	void onDisConnected();//�ͻ��˶Ͽ���ɾ���ͻ�����Ϣ�ͣ��ͻ����б���Ŀͻ���

private:
	QList<QTcpSocket*> m_clientlist;//ά���ͻ����б�
};
