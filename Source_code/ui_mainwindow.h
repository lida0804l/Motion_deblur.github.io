/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actiontest;
    QAction *actionROI;
    QAction *actionset_up_from_graph;
    QAction *actiontest2;
    QAction *actionsave_as;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_parameterSetting;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_angle;
    QLabel *label_length;
    QLabel *label_exposureTime;
    QLabel *label_SNR;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_angle;
    QLineEdit *lineEdit_length;
    QLineEdit *lineEdit_exposureTime;
    QLineEdit *lineEdit_SNR;
    QPushButton *pushButton_apply;
    QGroupBox *groupBox_range;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_angle_2;
    QLineEdit *lineEdit_angleStart;
    QLabel *label_tilde_3;
    QLineEdit *lineEdit_angleEnd;
    QScrollBar *horizontalScrollBar_angle;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_length_2;
    QLineEdit *lineEdit_lengthStart;
    QLabel *label_tilde;
    QLineEdit *lineEdit_lengthEnd;
    QScrollBar *horizontalScrollBar_length;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_exposureTime_2;
    QLineEdit *lineEdit_exposureTimeStart;
    QLabel *label_tilde_2;
    QLineEdit *lineEdit_exposureTimeEnd;
    QScrollBar *horizontalScrollBar_exposureTime;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_SNR_2;
    QLineEdit *lineEdit_SNRStart;
    QLabel *label_tilde_1;
    QLineEdit *lineEdit_SNREnd;
    QScrollBar *horizontalScrollBar_SNR;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menutest;
    QMenu *menuedit;
    QMenu *menuParameter_setting;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1111, 714);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actiontest = new QAction(MainWindow);
        actiontest->setObjectName(QString::fromUtf8("actiontest"));
        actionROI = new QAction(MainWindow);
        actionROI->setObjectName(QString::fromUtf8("actionROI"));
        actionset_up_from_graph = new QAction(MainWindow);
        actionset_up_from_graph->setObjectName(QString::fromUtf8("actionset_up_from_graph"));
        actiontest2 = new QAction(MainWindow);
        actiontest2->setObjectName(QString::fromUtf8("actiontest2"));
        actionsave_as = new QAction(MainWindow);
        actionsave_as->setObjectName(QString::fromUtf8("actionsave_as"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_9 = new QVBoxLayout(centralWidget);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout_6->addWidget(graphicsView);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox_parameterSetting = new QGroupBox(centralWidget);
        groupBox_parameterSetting->setObjectName(QString::fromUtf8("groupBox_parameterSetting"));
        QFont font;
        font.setPointSize(20);
        groupBox_parameterSetting->setFont(font);
        verticalLayout_3 = new QVBoxLayout(groupBox_parameterSetting);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_angle = new QLabel(groupBox_parameterSetting);
        label_angle->setObjectName(QString::fromUtf8("label_angle"));
        QFont font1;
        font1.setPointSize(18);
        label_angle->setFont(font1);

        verticalLayout_2->addWidget(label_angle);

        label_length = new QLabel(groupBox_parameterSetting);
        label_length->setObjectName(QString::fromUtf8("label_length"));
        label_length->setFont(font1);

        verticalLayout_2->addWidget(label_length);

        label_exposureTime = new QLabel(groupBox_parameterSetting);
        label_exposureTime->setObjectName(QString::fromUtf8("label_exposureTime"));
        label_exposureTime->setFont(font1);

        verticalLayout_2->addWidget(label_exposureTime);

        label_SNR = new QLabel(groupBox_parameterSetting);
        label_SNR->setObjectName(QString::fromUtf8("label_SNR"));
        label_SNR->setFont(font1);

        verticalLayout_2->addWidget(label_SNR);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_angle = new QLineEdit(groupBox_parameterSetting);
        lineEdit_angle->setObjectName(QString::fromUtf8("lineEdit_angle"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_angle->sizePolicy().hasHeightForWidth());
        lineEdit_angle->setSizePolicy(sizePolicy);
        lineEdit_angle->setFont(font1);
        lineEdit_angle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit_angle);

        lineEdit_length = new QLineEdit(groupBox_parameterSetting);
        lineEdit_length->setObjectName(QString::fromUtf8("lineEdit_length"));
        sizePolicy.setHeightForWidth(lineEdit_length->sizePolicy().hasHeightForWidth());
        lineEdit_length->setSizePolicy(sizePolicy);
        lineEdit_length->setFont(font1);
        lineEdit_length->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit_length);

        lineEdit_exposureTime = new QLineEdit(groupBox_parameterSetting);
        lineEdit_exposureTime->setObjectName(QString::fromUtf8("lineEdit_exposureTime"));
        sizePolicy.setHeightForWidth(lineEdit_exposureTime->sizePolicy().hasHeightForWidth());
        lineEdit_exposureTime->setSizePolicy(sizePolicy);
        lineEdit_exposureTime->setFont(font1);
        lineEdit_exposureTime->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit_exposureTime);

        lineEdit_SNR = new QLineEdit(groupBox_parameterSetting);
        lineEdit_SNR->setObjectName(QString::fromUtf8("lineEdit_SNR"));
        sizePolicy.setHeightForWidth(lineEdit_SNR->sizePolicy().hasHeightForWidth());
        lineEdit_SNR->setSizePolicy(sizePolicy);
        lineEdit_SNR->setFont(font1);
        lineEdit_SNR->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit_SNR);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        pushButton_apply = new QPushButton(groupBox_parameterSetting);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));

        verticalLayout_3->addWidget(pushButton_apply);


        verticalLayout_8->addWidget(groupBox_parameterSetting);

        groupBox_range = new QGroupBox(centralWidget);
        groupBox_range->setObjectName(QString::fromUtf8("groupBox_range"));
        groupBox_range->setFont(font);
        verticalLayout_11 = new QVBoxLayout(groupBox_range);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_angle_2 = new QLabel(groupBox_range);
        label_angle_2->setObjectName(QString::fromUtf8("label_angle_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_angle_2->sizePolicy().hasHeightForWidth());
        label_angle_2->setSizePolicy(sizePolicy1);
        label_angle_2->setFont(font1);

        horizontalLayout_5->addWidget(label_angle_2);

        lineEdit_angleStart = new QLineEdit(groupBox_range);
        lineEdit_angleStart->setObjectName(QString::fromUtf8("lineEdit_angleStart"));
        sizePolicy.setHeightForWidth(lineEdit_angleStart->sizePolicy().hasHeightForWidth());
        lineEdit_angleStart->setSizePolicy(sizePolicy);
        lineEdit_angleStart->setFont(font1);
        lineEdit_angleStart->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(lineEdit_angleStart);

        label_tilde_3 = new QLabel(groupBox_range);
        label_tilde_3->setObjectName(QString::fromUtf8("label_tilde_3"));
        sizePolicy1.setHeightForWidth(label_tilde_3->sizePolicy().hasHeightForWidth());
        label_tilde_3->setSizePolicy(sizePolicy1);
        label_tilde_3->setFont(font1);
        label_tilde_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_tilde_3);

        lineEdit_angleEnd = new QLineEdit(groupBox_range);
        lineEdit_angleEnd->setObjectName(QString::fromUtf8("lineEdit_angleEnd"));
        sizePolicy.setHeightForWidth(lineEdit_angleEnd->sizePolicy().hasHeightForWidth());
        lineEdit_angleEnd->setSizePolicy(sizePolicy);
        lineEdit_angleEnd->setFont(font1);
        lineEdit_angleEnd->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(lineEdit_angleEnd);


        verticalLayout_10->addLayout(horizontalLayout_5);


        verticalLayout_7->addLayout(verticalLayout_10);

        horizontalScrollBar_angle = new QScrollBar(groupBox_range);
        horizontalScrollBar_angle->setObjectName(QString::fromUtf8("horizontalScrollBar_angle"));
        horizontalScrollBar_angle->setOrientation(Qt::Horizontal);

        verticalLayout_7->addWidget(horizontalScrollBar_angle);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_length_2 = new QLabel(groupBox_range);
        label_length_2->setObjectName(QString::fromUtf8("label_length_2"));
        sizePolicy1.setHeightForWidth(label_length_2->sizePolicy().hasHeightForWidth());
        label_length_2->setSizePolicy(sizePolicy1);
        label_length_2->setFont(font1);

        horizontalLayout_2->addWidget(label_length_2);

        lineEdit_lengthStart = new QLineEdit(groupBox_range);
        lineEdit_lengthStart->setObjectName(QString::fromUtf8("lineEdit_lengthStart"));
        sizePolicy.setHeightForWidth(lineEdit_lengthStart->sizePolicy().hasHeightForWidth());
        lineEdit_lengthStart->setSizePolicy(sizePolicy);
        lineEdit_lengthStart->setFont(font1);
        lineEdit_lengthStart->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lineEdit_lengthStart);

        label_tilde = new QLabel(groupBox_range);
        label_tilde->setObjectName(QString::fromUtf8("label_tilde"));
        sizePolicy1.setHeightForWidth(label_tilde->sizePolicy().hasHeightForWidth());
        label_tilde->setSizePolicy(sizePolicy1);
        label_tilde->setFont(font1);
        label_tilde->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_tilde);

        lineEdit_lengthEnd = new QLineEdit(groupBox_range);
        lineEdit_lengthEnd->setObjectName(QString::fromUtf8("lineEdit_lengthEnd"));
        sizePolicy.setHeightForWidth(lineEdit_lengthEnd->sizePolicy().hasHeightForWidth());
        lineEdit_lengthEnd->setSizePolicy(sizePolicy);
        lineEdit_lengthEnd->setFont(font1);
        lineEdit_lengthEnd->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lineEdit_lengthEnd);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalScrollBar_length = new QScrollBar(groupBox_range);
        horizontalScrollBar_length->setObjectName(QString::fromUtf8("horizontalScrollBar_length"));
        horizontalScrollBar_length->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(horizontalScrollBar_length);


        verticalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_exposureTime_2 = new QLabel(groupBox_range);
        label_exposureTime_2->setObjectName(QString::fromUtf8("label_exposureTime_2"));
        sizePolicy1.setHeightForWidth(label_exposureTime_2->sizePolicy().hasHeightForWidth());
        label_exposureTime_2->setSizePolicy(sizePolicy1);
        label_exposureTime_2->setFont(font1);

        horizontalLayout_4->addWidget(label_exposureTime_2);

        lineEdit_exposureTimeStart = new QLineEdit(groupBox_range);
        lineEdit_exposureTimeStart->setObjectName(QString::fromUtf8("lineEdit_exposureTimeStart"));
        sizePolicy.setHeightForWidth(lineEdit_exposureTimeStart->sizePolicy().hasHeightForWidth());
        lineEdit_exposureTimeStart->setSizePolicy(sizePolicy);
        lineEdit_exposureTimeStart->setFont(font1);
        lineEdit_exposureTimeStart->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lineEdit_exposureTimeStart);

        label_tilde_2 = new QLabel(groupBox_range);
        label_tilde_2->setObjectName(QString::fromUtf8("label_tilde_2"));
        sizePolicy1.setHeightForWidth(label_tilde_2->sizePolicy().hasHeightForWidth());
        label_tilde_2->setSizePolicy(sizePolicy1);
        label_tilde_2->setFont(font1);
        label_tilde_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_tilde_2);

        lineEdit_exposureTimeEnd = new QLineEdit(groupBox_range);
        lineEdit_exposureTimeEnd->setObjectName(QString::fromUtf8("lineEdit_exposureTimeEnd"));
        sizePolicy.setHeightForWidth(lineEdit_exposureTimeEnd->sizePolicy().hasHeightForWidth());
        lineEdit_exposureTimeEnd->setSizePolicy(sizePolicy);
        lineEdit_exposureTimeEnd->setFont(font1);
        lineEdit_exposureTimeEnd->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lineEdit_exposureTimeEnd);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalScrollBar_exposureTime = new QScrollBar(groupBox_range);
        horizontalScrollBar_exposureTime->setObjectName(QString::fromUtf8("horizontalScrollBar_exposureTime"));
        horizontalScrollBar_exposureTime->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(horizontalScrollBar_exposureTime);


        verticalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_SNR_2 = new QLabel(groupBox_range);
        label_SNR_2->setObjectName(QString::fromUtf8("label_SNR_2"));
        sizePolicy1.setHeightForWidth(label_SNR_2->sizePolicy().hasHeightForWidth());
        label_SNR_2->setSizePolicy(sizePolicy1);
        label_SNR_2->setFont(font1);

        horizontalLayout_3->addWidget(label_SNR_2);

        lineEdit_SNRStart = new QLineEdit(groupBox_range);
        lineEdit_SNRStart->setObjectName(QString::fromUtf8("lineEdit_SNRStart"));
        sizePolicy.setHeightForWidth(lineEdit_SNRStart->sizePolicy().hasHeightForWidth());
        lineEdit_SNRStart->setSizePolicy(sizePolicy);
        lineEdit_SNRStart->setFont(font1);
        lineEdit_SNRStart->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lineEdit_SNRStart);

        label_tilde_1 = new QLabel(groupBox_range);
        label_tilde_1->setObjectName(QString::fromUtf8("label_tilde_1"));
        sizePolicy1.setHeightForWidth(label_tilde_1->sizePolicy().hasHeightForWidth());
        label_tilde_1->setSizePolicy(sizePolicy1);
        label_tilde_1->setFont(font1);
        label_tilde_1->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_tilde_1);

        lineEdit_SNREnd = new QLineEdit(groupBox_range);
        lineEdit_SNREnd->setObjectName(QString::fromUtf8("lineEdit_SNREnd"));
        sizePolicy.setHeightForWidth(lineEdit_SNREnd->sizePolicy().hasHeightForWidth());
        lineEdit_SNREnd->setSizePolicy(sizePolicy);
        lineEdit_SNREnd->setFont(font1);
        lineEdit_SNREnd->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lineEdit_SNREnd);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalScrollBar_SNR = new QScrollBar(groupBox_range);
        horizontalScrollBar_SNR->setObjectName(QString::fromUtf8("horizontalScrollBar_SNR"));
        horizontalScrollBar_SNR->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(horizontalScrollBar_SNR);


        verticalLayout_7->addLayout(verticalLayout_5);


        verticalLayout_11->addLayout(verticalLayout_7);


        verticalLayout_8->addWidget(groupBox_range);


        horizontalLayout_6->addLayout(verticalLayout_8);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 1);

        verticalLayout_9->addLayout(horizontalLayout_6);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1111, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menutest = new QMenu(menuBar);
        menutest->setObjectName(QString::fromUtf8("menutest"));
        menuedit = new QMenu(menuBar);
        menuedit->setObjectName(QString::fromUtf8("menuedit"));
        menuParameter_setting = new QMenu(menuedit);
        menuParameter_setting->setObjectName(QString::fromUtf8("menuParameter_setting"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuedit->menuAction());
        menuBar->addAction(menutest->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionsave_as);
        menuedit->addAction(actionROI);
        menuedit->addAction(menuParameter_setting->menuAction());
        menuParameter_setting->addAction(actionset_up_from_graph);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actiontest->setText(QApplication::translate("MainWindow", "test", nullptr));
        actionROI->setText(QApplication::translate("MainWindow", "ROI", nullptr));
        actionset_up_from_graph->setText(QApplication::translate("MainWindow", "from graph", nullptr));
        actiontest2->setText(QApplication::translate("MainWindow", "test2", nullptr));
        actionsave_as->setText(QApplication::translate("MainWindow", "save as", nullptr));
        groupBox_parameterSetting->setTitle(QApplication::translate("MainWindow", "Parameter setting", nullptr));
        label_angle->setText(QApplication::translate("MainWindow", "Angle: ", nullptr));
        label_length->setText(QApplication::translate("MainWindow", "Length: ", nullptr));
        label_exposureTime->setText(QApplication::translate("MainWindow", "Exposure time: ", nullptr));
        label_SNR->setText(QApplication::translate("MainWindow", "SNR: ", nullptr));
        pushButton_apply->setText(QApplication::translate("MainWindow", "Apply", nullptr));
        groupBox_range->setTitle(QApplication::translate("MainWindow", "Range", nullptr));
        label_angle_2->setText(QApplication::translate("MainWindow", "Angle: ", nullptr));
        label_tilde_3->setText(QApplication::translate("MainWindow", "~", nullptr));
        label_length_2->setText(QApplication::translate("MainWindow", "Length: ", nullptr));
        label_tilde->setText(QApplication::translate("MainWindow", "~", nullptr));
        label_exposureTime_2->setText(QApplication::translate("MainWindow", "Exposure time: ", nullptr));
        label_tilde_2->setText(QApplication::translate("MainWindow", "~", nullptr));
        label_SNR_2->setText(QApplication::translate("MainWindow", "SNR: ", nullptr));
        label_tilde_1->setText(QApplication::translate("MainWindow", "~", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menutest->setTitle(QApplication::translate("MainWindow", "about", nullptr));
        menuedit->setTitle(QApplication::translate("MainWindow", "edit", nullptr));
        menuParameter_setting->setTitle(QApplication::translate("MainWindow", "Parameter setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
