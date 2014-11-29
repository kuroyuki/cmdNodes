#include "logger.h"
#include <QDateTime>
#include <QTime>
#include <QTextStream>

logger::logger(QObject *parent) :
    QObject(parent)
{
}
void logger::logMessage(QJsonObject json){
    QDateTime time  = QDateTime::currentDateTime();
    QJsonDocument jDoc(json);

    QTextStream(stdout)<<time.toString("dd.MM.yyyy hh:mm:ss.zzz")<<" "<<QString::fromUtf8(jDoc.toJson())<<endl;
}
