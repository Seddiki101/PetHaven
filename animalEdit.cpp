#include "animal.h"


QString AnimalEdit::QueryConstructor(QString Command1, QString TableName, QString Command2, QString WhereCommand)
{
    QString query = Command1 + " " + TableName + " " + Command2 + " " + WhereCommand;
    return query;
}

bool AnimalEdit::Edit (int id, QString columnName, QString dataString, int dataInt, QDate dataDate) {
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.bindValue(":id", id_string);

    if (!isEmpty(dataString)) {
        query.bindValue(":data", dataString);
    }
    else if (dataInt != -1) {
        QString data=QString::number(dataInt);
        query.bindValue(":data", data);
    }
    else {
        query.bindValue(":data", dataDate);
    }

    query.prepare("UPDATE animals SET " + columnName + "=:data WHERE IDA=:id");
    return query.exec();
}
