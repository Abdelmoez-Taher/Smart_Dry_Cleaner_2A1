/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *NOM;
    QLineEdit *PRENOM;
    QLineEdit *NUM_TELEPHONE;
    QLineEdit *EMAIL;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *CIN;
    QWidget *tab_2;
    QTableView *tableView;
    QPushButton *pushButton_7;
    QWidget *tab_3;
    QPushButton *pushButton_5;
    QLabel *label_6;
    QLineEdit *sup;
    QWidget *tab_4;
    QPushButton *optionspushButton_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 801, 541));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 60, 56, 16));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 100, 56, 16));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 140, 56, 16));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(120, 180, 101, 20));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(120, 220, 56, 16));
        NOM = new QLineEdit(tab);
        NOM->setObjectName(QStringLiteral("NOM"));
        NOM->setGeometry(QRect(230, 100, 113, 22));
        PRENOM = new QLineEdit(tab);
        PRENOM->setObjectName(QStringLiteral("PRENOM"));
        PRENOM->setGeometry(QRect(230, 140, 113, 22));
        NUM_TELEPHONE = new QLineEdit(tab);
        NUM_TELEPHONE->setObjectName(QStringLiteral("NUM_TELEPHONE"));
        NUM_TELEPHONE->setGeometry(QRect(230, 180, 113, 22));
        EMAIL = new QLineEdit(tab);
        EMAIL->setObjectName(QStringLiteral("EMAIL"));
        EMAIL->setGeometry(QRect(230, 220, 113, 22));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 270, 93, 28));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 270, 93, 28));
        CIN = new QLineEdit(tab);
        CIN->setObjectName(QStringLiteral("CIN"));
        CIN->setGeometry(QRect(230, 60, 113, 22));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 50, 661, 241));
        pushButton_7 = new QPushButton(tab_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(580, 330, 93, 28));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton_5 = new QPushButton(tab_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(350, 240, 93, 28));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 140, 56, 16));
        sup = new QLineEdit(tab_3);
        sup->setObjectName(QStringLiteral("sup"));
        sup->setGeometry(QRect(280, 140, 113, 22));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        optionspushButton_8 = new QPushButton(tab_4);
        optionspushButton_8->setObjectName(QStringLiteral("optionspushButton_8"));
        optionspushButton_8->setGeometry(QRect(60, 40, 651, 28));
        scrollArea = new QScrollArea(tab_4);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(60, 80, 651, 381));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 649, 379));
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "CIN", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "NOM", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "PRENOM", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "NUM TELEPHONE", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "EMAIL", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Modifier", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Ajouter", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Ajouter client", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "Trier", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Afficher client", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "Supprimer", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "CIN", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Supprimer client", Q_NULLPTR));
        optionspushButton_8->setText(QApplication::translate("MainWindow", "Options", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "s\303\251curit\303\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
