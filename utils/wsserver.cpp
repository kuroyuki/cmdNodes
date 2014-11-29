#include "wsserver.h"
#include <QJsonDocument>

wsServer::wsServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients()
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
       qDebug() << "Echoserver listening on port" << port;
       connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
               this, &wsServer::onNewConnection);
       connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &wsServer::closed);
   }
}

wsServer::~wsServer()
{
   m_pWebSocketServer->close();
   qDeleteAll(m_clients.begin(), m_clients.end());
}

void wsServer::onNewConnection()
{
   QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

   connect(pSocket, &QWebSocket::textMessageReceived, this, &wsServer::processTextMessage);
   connect(pSocket, &QWebSocket::binaryMessageReceived, this, &wsServer::processBinaryMessage);
   connect(pSocket, &QWebSocket::disconnected, this, &wsServer::socketDisconnected);

   m_clients << pSocket;
}

void wsServer::processTextMessage(QString message)
{
   QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
   if (pClient) {
       QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
       QJsonObject json = jsonDoc.object();

       QString command = json.take("command").toString();
       //get table
       if(command == "gt"){
           //send current table to remote

       }
   }
}

void wsServer::processBinaryMessage(QByteArray message)
{
   QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
   if (pClient) {
       pClient->sendBinaryMessage(message);
   }
}

void wsServer::socketDisconnected()
{
   QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
   if (pClient) {
       m_clients.removeAll(pClient);
       pClient->deleteLater();
   }
}
void wsServer::clientMessage(QJsonObject json){
    QJsonDocument jDoc(json);

    for(int i =0;i<m_clients.length();i++)
        m_clients[i]->sendTextMessage(QString::fromUtf8(jDoc.toJson()));
}
