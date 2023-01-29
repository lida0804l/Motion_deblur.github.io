/********************************************************************************
** Form generated from reading UI file 'frequencydomain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREQUENCYDOMAIN_H
#define UI_FREQUENCYDOMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FrequencyDomain
{
public:
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QDialog *FrequencyDomain)
    {
        if (FrequencyDomain->objectName().isEmpty())
            FrequencyDomain->setObjectName(QString::fromUtf8("FrequencyDomain"));
        FrequencyDomain->resize(1117, 679);
        horizontalLayout = new QHBoxLayout(FrequencyDomain);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(FrequencyDomain);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);


        retranslateUi(FrequencyDomain);

        QMetaObject::connectSlotsByName(FrequencyDomain);
    } // setupUi

    void retranslateUi(QDialog *FrequencyDomain)
    {
        FrequencyDomain->setWindowTitle(QApplication::translate("FrequencyDomain", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrequencyDomain: public Ui_FrequencyDomain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREQUENCYDOMAIN_H
