#ifndef GEPHI_H
#define GEPHI_H

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QQueue>
#include <QJsonObject>
#include <QTimer>

class Gephi : public QObject
{
    Q_OBJECT
public:
    explicit Gephi(QObject *parent = 0);    
signals:

public slots:
    void slotReady();
    void sendEvent(QJsonObject json);

private :
    void sendToGephi();
    QQueue<QString> queue;
    QNetworkAccessManager  manager;

    QUrl url;
    bool isReady;

};

#endif // GEPHI_H
