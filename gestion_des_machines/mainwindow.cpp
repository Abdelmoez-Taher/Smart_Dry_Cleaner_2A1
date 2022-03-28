#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machines.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QTextStream>
#include <QDataStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QRegularExpressionValidator>
#include <QPainter>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator (0, 99999999, this));
    ui->le_numserie->setValidator(new QIntValidator (0, 9999999, this));
    ui->tab_machine->setModel(M.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_le_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();
    int numserie=ui->le_numserie->text().toInt();
    QString marque=ui->le_marque->text();
    QString datea=ui->le_date->text();
    Machines M(id, numserie , marque , datea);
    bool test=M.ajouter();
    if(test)
{
       { QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_machine->setModel(M.afficher());
        }

}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT Ok"),
                    QObject::tr("Ajout non effecute.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }



void MainWindow::on_le_supprimer_clicked()
{
    Machines M1 ; M1.setid(ui->le_id_supp->text().toInt());
    bool test=M1.supprimer(M1.getid());
    if(test)
{
        { QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        ui->tab_machine->setModel(M.afficher());

        }
}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT Ok"),
                    QObject::tr("Suppression non effecute.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
void MainWindow::on_le_modifier_clicked()
{
    QString marque = ui->le_upmarque->text();
    QString datea = ui->le_update->text();
    int numserie = ui->le_upnums->text().toInt();
    int id = ui->le_upid->text().toInt();

   bool test =  M.modifier(id,numserie,datea,marque);

    if(test){
        ui->tab_machine->setModel(M.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("update effectué\n""Click to Cancel."),
                                 QMessageBox::Cancel);     }
    else         QMessageBox::critical  (nullptr, QObject::tr("not OK"),
                 QObject::tr("update non effectué\n""Click to Cancel."), QMessageBox::Cancel);
}


void MainWindow::on_le_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tab_machine->model()->rowCount();
    const int columnCount = ui->tab_machine->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        //     "<align='right'> " << datefich << "</align>"
        "<center> <H1>Liste Des Fournisseurs </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_machine->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_machine->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tab_machine->isColumnHidden(column))
            {
                QString data = ui->tab_machine->model()->data(ui->tab_machine->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}
void MainWindow::on_le_trier_clicked()
{
    ui->tab_machine->setModel(M.afficher());
}


void MainWindow::on_le_recherche_clicked()
{
    {
        Machines m;
             ui->tab_machine->setModel(m.recherche(ui->le_cherche->text().toInt()));
             ui->le_cherche->clear();

}
}
