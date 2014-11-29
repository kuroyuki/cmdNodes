#ifndef DOJODB_H
#define DOJODB_H

#include <QObject>
#include <QJsonObject>
#include <QFile>

class dojoDb : public QObject
{
    Q_OBJECT
public:
    explicit dojoDb(QFile* file, QObject *parent = 0);

signals:
    void dbResponse(QJsonObject json);

public slots:
    void dbRequest(QJsonObject json);

private:
    QFile* dbFile;

};

#endif // DOJODB_H
