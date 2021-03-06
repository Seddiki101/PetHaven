#include "../headers/animal.h"


//******************************************************************//
//                                                                  //
//                    Constructors                                  //
//                                                                  //
//******************************************************************//

Animal::Animal()
{
    age=0;
    nom="";
    espece="";
    race="";
}

Animal::Animal(int age, int status, QString nom, QString espece, QString race, QDate date_arr)
{
    this->age=age; this->status=status; this->nom=nom; this->espece=espece; this->race=race; this->date_arr=date_arr;
}


//******************************************************************//
//                                                                  //
//                    Epic getters'n setters                        //
//                                                                  //
//******************************************************************//

int Animal::getAge()                        {return age;}
int Animal::getStatus()                     {return status;}
QString Animal::getNom()                    {return nom;}
QString Animal::getEspece()                 {return espece;}
QString Animal::getRace()                   {return race;}
QDate Animal::getDate_arr()                 {return date_arr;}

void Animal::setAge(int age)                {this->age=age;}
void Animal::setStatus(int status)          {this->status=status;}
void Animal::setNom(QString nom)            {this->nom=nom;}
void Animal::setEspece(QString espece)      {this->espece=espece;}
void Animal::setRace(QString race)          {this->race=race;}
void Animal::setDate_arr(QDate date_arr)    {this->date_arr=date_arr;}


//******************************************************************//
//                                                                  //
//                    Basic Functions                               //
//                                                                  //
//******************************************************************//

// Set same header for the QTableView so we won't have the ugly ones from the database
// Must be called everytime after the model is updated
void setHeader(QSqlQueryModel* model)
{
    model->setHeaderData (1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData (2, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData (3, Qt::Horizontal, QObject::tr("Espece"));
    model->setHeaderData (4, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData (5, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData (6, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData (7, Qt::Horizontal, QObject::tr("Image"));
}

// Epic function that shows stuff
void Animal::afficher(QTableView *table)
{
//    QSqlTableModel *model = new QSqlTableModel;
    CustomModel *model = new CustomModel;
    model->setTable("ANIMALS");
    model->select();
    setHeader(model);

    table->setModel(model);
    setWidgets(table);
}

// Function "ajouter()" that... adds things
bool Animal::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ANIMALS (IDA, age, nom, espece, race, status, date_arr, image) "
                  "VALUES (DEFAULT, :age, :nom, :espece, :race, DEFAULT, :date_arr, NULL)");

    query.bindValue(":age", age);
    query.bindValue(":nom", nom);
    query.bindValue(":espece", espece);
    query.bindValue(":race", race);
    query.bindValue(":date_arr", date_arr);

    return query.exec();
}

// Probably deprecated function but I guess it is mandatory
// "Edit()" should be better and more practical that this one
bool Animal::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE ANIMALS SET "
                  "age=:age, nom=:nom, espece=:espece, race=:race, status=:status, date_arr=:date_arr "
                  "WHERE IDA=:id");

    query.bindValue(":id", id);
    query.bindValue(":age", age);
    query.bindValue(":status", status);
    query.bindValue(":nom", nom);
    query.bindValue(":espece", espece);
    query.bindValue(":race", race);
    query.bindValue(":date_arr", date_arr);

    return query.exec();
}

// Function that deletes stuff, easy to come around and very usefull 10/10
bool Animal::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM ANIMALS WHERE IDA=:id");
    query.bindValue(":id", id);
    return query.exec();
}

// Function to test the emptiness of a string because default isNull() is to easy to use and I like overly complicated things
bool Animal::isEmpty(QString text)
{
    return text.size() == 0 || text.isEmpty() || text.isNull();
}


//******************************************************************//
//                                                                  //
//                  Additionnal Stuff                               //
//                                                                  //
//******************************************************************//

// Epic Function to sort stuff
// If called without argument, technically does the same as "afficher()"
QSqlTableModel* Animal::sortData(QString Where, int Column, Qt::SortOrder SortOrder)
{
    CustomModel *model = new CustomModel;

    model->setTable("ANIMALS");             // Select the table from the database

    // Assign WHERE clause only if Where argument is set
    if (!isEmpty(Where)) {
        model->setFilter(Where);            // Create a WHERE clause
    }

    // Assign ORDER BY clause only if Column argument is set
    if (Column != -1) {
        model->setSort(Column, SortOrder);  // Create an ORDER BY clause, Column is an int, refer to setHeader() to see which column it defines
    }

    // Does the same as "afficher" if no argument is passed
    model->select();                        // Fetch all the data from the selected table

    setHeader(model);
    return model;
}

// Append some data (string) at the end of a text file
bool writeToFile(QString data)
{
    QFile file("historic.log");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        file.flush();
        QTextStream stream(&file);
        stream << data;

        file.close();
        return true;
    }
    return false;
}

// Function historic, writes some data that will be put inside a QListView and calls "writeToFile()" to ... write the same data into a file
QString Animal::historic(QString data)
{
    QString currentdate = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss -- ");

    // Some data and return to line for the logs
    writeToFile (currentdate + data + '\n');

    // Current hour for normal session (no need for all demn dates when in the session)
    currentdate = QDateTime::currentDateTime().toString("hh:mm:ss -- ");
    return currentdate + data;
}

// Image by default is "NULL" therefor only a function to update the image is necessary
bool Animal::updateImage(int id, QString filepath)
{
    QByteArray dataByte;
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly))
    {
        dataByte = file.readAll();
        file.close();
    }
    else
    {
        return false;   // The file could not be opened or smth
    }

    QSqlQuery query;
    query.prepare("UPDATE ANIMALS SET "
                  "IMAGE=:image "
                  "WHERE IDA=:id");

    query.bindValue(":id", id);
    query.bindValue(":image", dataByte, QSql::In | QSql::Binary);

    return query.exec();
}

// Generate some PDF when clicking a nice button
// Doing the PDF equals writing some HTML, therefor doing some CSS
// Which is the very reason why i don't want to do this
void Animal::generatePdf(QTableView* tableView)
{
    QString header, css, text;
    const int rowCount = tableView->model()->rowCount();
    const int columnCount = tableView->model()->columnCount();

// Create the header
    header += "<html><head><meta Content='Text/html; charset=Windows-1251'>";
    header += "<title>Some epic PDF File</title>";
    header += "<link rel='stylesheet' type='text/css' href='./../Gestion Animal/res/table.css'>";
    header += "</head><body>";

// Some simple css in case files are too complicated to link
//    css += "<style type='text/css'>";
//    css += "table {border: solid 1px #DDEEEE;border-collapse: collapse;border-spacing: 0;font: normal 13px Arial, sans-serif;}";
//    css += "</style>";

// Create the table
    text += "<table><thead><tr>";

// Fill the table headers
    for (int column = 0; column < columnCount; column++) {
        if (!tableView->isColumnHidden(column)) {
            text += QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    text += "</tr></thead><tbody>";

// Fill table cells
    for (int row = 0; row < rowCount; row++) {
        text += "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!tableView->isColumnHidden(column)) {
                QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
                text += QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        text += "</tr></tbody>";
    }
    text += "</table></body></html>";

    // Epic new HTML document, ready to be printed
    QTextDocument *document = new QTextDocument();
    document->setHtml(header + text);

    // Printing dat bad bo
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}


//******************************************************************//
//                                                                  //
//                     Experimental ?                               //
//                                                                  //
//******************************************************************//

// Some temp work
// Dunno if this will ever be used but whatever
QString Animal::QueryConstructor(QString Command1, QString TableName, QString Command2, QString WhereCommand)
{
    QString query = Command1 + " " + TableName + " " + Command2 + " " + WhereCommand;
    return query;
}

// Basically "modifier()" but does only one column at a time
// Technically better because realistically, people tend to modify one stuff at a time instead of everything
// And even if they do everything at once, you call just call this beautiful function multiple times
bool Animal::Edit (int id, QString columnName, QString dataString, int dataInt, QDate dataDate) {
    QSqlQuery query;
    query.bindValue(":id", id);

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

// I tried to do some fancy stuff but it didn't work
// At least i tried


QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    // 5 is status column
    if (index.column() != 5) {
        if (role == Qt::TextAlignmentRole)
            return Qt::AlignCenter;
    }

    return QSqlTableModel::data(index, role);
}

//QVariant CustomModel::data(const QModelIndex &idx, int role) const
//{
//     if (idx.column() == 7) {
//        if (role == Qt::DisplayRole)
//            return QString(); // return the path string for display role

//        QPixmap pixmap(":/res/noImage.png");

//        if (role == Qt::DecorationRole)
//            return pixmap;   // return QPixmap for decoration role

//        if (role == Qt::SizeHintRole)
//            return pixmap.size(); // in case need the image size

//     }
//     return QSqlTableModel::data( idx, role ); // use original data() outside the imageColumn
//}

void CustomStyle::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 7)
    {
        QPixmap pixmap(":/res/noImage.png");

        pixmap = pixmap.scaled(option.rect.size(), Qt::KeepAspectRatio);
        int centerCell = option.rect.width() / 2;
        int centerPixmap = pixmap.width() / 2;

        painter->drawPixmap(centerCell - centerPixmap, option.rect.y(), pixmap);
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

void Animal::setWidgets(QTableView *table) {
    for (int i = 0; i < table->model()->rowCount(); i++) {
        // Creates a new label widget
        QLabel* imageLabel = new QLabel;
        imageLabel->setScaledContents(true);
        imageLabel->setObjectName("imageLabel");

        // Fetch the data of the 7th column that contains the .blob image from the databse
        QVariant value = table->model()->index(i, 7).data();
        // Test if there's an image in the database
        if (value.isNull()) {
            QPixmap pixmap(":/res/noImage.png");
            imageLabel->setPixmap(pixmap);
            table->setIndexWidget(table->model()->index(i, 7), imageLabel);
        }
        else {
            QPixmap pixmap;
            QByteArray Bytes = value.toByteArray();
            pixmap.loadFromData(Bytes);
            imageLabel->setPixmap(pixmap);
            table->setIndexWidget(table->model()->index(i, 7), imageLabel);
        }

        // Creates a new checkbox widget
        QCheckBox* statusCheckbox = new QCheckBox;
        statusCheckbox->setObjectName("statusCheckbox");

        if (table->model()->index(i, 5).data().toBool()) {
            statusCheckbox->setCheckState(Qt::Checked);
            statusCheckbox->setText("Avaible");
        }
        else {
            statusCheckbox->setCheckState(Qt::Unchecked);
            statusCheckbox->setText("Not Avaible");
        }
        statusCheckbox->setEnabled(false);
        table->setIndexWidget(table->model()->index(i, 5), statusCheckbox);
    }
}
