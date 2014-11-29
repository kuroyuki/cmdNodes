#include "gephi.h"
#include <QJsonDocument>

Gephi::Gephi(QObject *parent) :
    QObject(parent)
{
    url.setUrl("http://localhost:8080/workspace0?operation=updateGraph");
    isReady = true;

}
void Gephi::sendEvent(QJsonObject json){
    QJsonDocument jDoc(json);
    queue.enqueue(QString::fromUtf8(jDoc.toJson()));
    sendToGephi();
}

void Gephi::sendToGephi(){
    if(!queue.isEmpty() && isReady){
        QByteArray data = queue.dequeue().toLocal8Bit();

        isReady = false;

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
        QNetworkReply *reply = manager.post(request, data);
        connect(reply, SIGNAL(finished()), this, SLOT(slotReady()));

   }
}
void Gephi::slotReady(){
    isReady = true;
    sendToGephi();
}
