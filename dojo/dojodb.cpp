#include "dojodb.h"

dojoDb::dojoDb(QFile* file, QObject *parent) :
    QObject(parent)
{
    dbFile = file;
}
void dojoDb::dbRequest(QJsonObject json){

}
