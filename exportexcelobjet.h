#ifndef EXPORTEXCELOBJET_H
#define EXPORTEXCELOBJET_H


#include <QObject>
#include <QTreeView>
#include <QStringList>
#include <QSqlDatabase>


class ExcelObject : public QObject
{
    Q_OBJECT
public:
    ExcelObject(const QString &filepath, const QString &sheettitle,
                      QTreeView *treeview):excelFilePath(filepath),
                      sheetName(sheettitle), treeView(treeview){};

    ~ExcelObject() {QSqlDatabase::removeDatabase("excelexport");};

public:
    void setOutputFilePath(const QString &spath) {excelFilePath = spath;};
    void setOutputSheetTitle(const QString &ssheet) {sheetName = ssheet;};
    void setTableView(QTreeView *treeview) {treeView = treeview;};

    void addField(const int iCol, const QString &fieldname, const QString &fieldtype)
         {fieldList << new EEO_Field(iCol, fieldname, fieldtype);};

    void removeAllFields()
         {while (!fieldList.isEmpty()) delete fieldList.takeFirst();};

    int export2Excel();

signals:
    void exportedRowCount(int row);

private:
    QString excelFilePath;
    QString sheetName;
    QTreeView *treeView;
    QList<EEO_Field *> fieldList;
};

#endif // EXPORTEXCELOBJET_H
