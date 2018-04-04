#pragma once

#include <assert.h>

#include <QDebug>

#include <QByteArray>
#include <QHostAddress>
#include <QMap>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>

#include "Headers.h"

class ConnectionManager : public QWidget
{
	Q_OBJECT

public:
	ConnectionManager(QWidget * parent = nullptr);
	~ConnectionManager();

	void BecomeHost(QMap<QString, QTcpSocket *> * connectedClients, QByteArray key);
	void BecomeClient();

private:
	bool mIsHost;
	QByteArray mKey;

	QTcpServer mServer;
	QMap<QString, QTcpSocket *> * mConnectedClients;
	QMap<QString, QTcpSocket *> mPendingConnections;

	void startServerListen();
	void sendListOfClients(QTcpSocket * socket);

private slots:
	void newConnectionHandler();
	void incomingDataHandler();

signals:
	void connectionAccepted(QString, QTcpSocket *);
};