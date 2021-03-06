#pragma once

#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QMap>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>

#include "globals.h"

class ConnectionManager : public QWidget
{
	Q_OBJECT

public:
	ConnectionManager(QByteArray * key, QString * name, QWidget * parent = nullptr);
	~ConnectionManager();

	void Init(QMap<QString, QTcpSocket *> * connectedClients);
	void BecomeHost();
	void BecomeClient();

	void AddPendingConnection(const quint32 address, QTcpSocket * socket);

private:
	bool mIsHost;
	QString * mName;
	QByteArray * mKey;

	QTcpServer mServer;
	QMap<QString, QTcpSocket *> * mConnectedClients;
	QMap<quint32, QTcpSocket *> mPendingConnections;

	void startServerListen();
	void sendListOfClients(QTcpSocket * socket);
	void sendName(QTcpSocket * socket);
	void parseJoinRequest(const QByteArray data, QTcpSocket * socket);

private slots:
	void newConnectionHandler();
	void incomingDataHandler();

signals:
	void connectionAccepted(QString, QTcpSocket *);
};