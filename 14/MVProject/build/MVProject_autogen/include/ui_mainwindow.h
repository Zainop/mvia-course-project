/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_main;
    QPushButton *pushButton_exit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_openimage;
    QPushButton *pushButton_openvideo;
    QPushButton *pushButton_opencamera;
    QPushButton *go;
    QWidget *tab_2;
    QLabel *label_main_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(984, 570);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_main = new QLabel(centralWidget);
        label_main->setObjectName(QStringLiteral("label_main"));
        label_main->setGeometry(QRect(50, 0, 261, 101));
        QFont font;
        font.setPointSize(18);
        label_main->setFont(font);
        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(800, 440, 131, 51));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(40, 100, 881, 331));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_openimage = new QPushButton(tab);
        pushButton_openimage->setObjectName(QStringLiteral("pushButton_openimage"));
        pushButton_openimage->setGeometry(QRect(80, 60, 89, 25));
        pushButton_openvideo = new QPushButton(tab);
        pushButton_openvideo->setObjectName(QStringLiteral("pushButton_openvideo"));
        pushButton_openvideo->setGeometry(QRect(80, 110, 89, 25));
        pushButton_opencamera = new QPushButton(tab);
        pushButton_opencamera->setObjectName(QStringLiteral("pushButton_opencamera"));
        pushButton_opencamera->setGeometry(QRect(80, 160, 89, 25));
        go = new QPushButton(tab);
        go->setObjectName(QStringLiteral("go"));
        go->setGeometry(QRect(230, 60, 89, 25));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        label_main_2 = new QLabel(centralWidget);
        label_main_2->setObjectName(QStringLiteral("label_main_2"));
        label_main_2->setGeometry(QRect(610, 0, 371, 101));
        label_main_2->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_main->setText(QApplication::translate("MainWindow", "Machine Vision Project                                                     ", Q_NULLPTR));
        pushButton_exit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        pushButton_openimage->setText(QApplication::translate("MainWindow", "open image", Q_NULLPTR));
        pushButton_openvideo->setText(QApplication::translate("MainWindow", "open video", Q_NULLPTR));
        pushButton_opencamera->setText(QApplication::translate("MainWindow", "open camera", Q_NULLPTR));
        go->setText(QApplication::translate("MainWindow", "go", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        label_main_2->setText(QApplication::translate("MainWindow", "\347\224\265\344\277\241172_3170406062_\351\203\221\345\245\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
