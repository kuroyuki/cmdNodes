#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class logger : public QObject
{
    Q_OBJECT
public:
    explicit logger(QObject *parent = 0);

signals:

public slots:
    void logMessage(QJsonObject json);
};

#endif // LOGGER_H
