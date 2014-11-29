#ifndef WSSERVER_H
#define WSSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>

class wsServer : public QObject
{
    Q_OBJECT
public:
    explicit wsServer(quint16 port, QObject *parent = Q_NULLPTR);
    ~wsServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void clientMessage(QJsonObject json);
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;

};

#endif // WSSERVER_H
