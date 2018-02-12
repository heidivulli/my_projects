/********************************************************************************
** Form generated from reading UI file 'konffiikkuna.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KONFFIIKKUNA_H
#define UI_KONFFIIKKUNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_KonffiIkkuna
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbDebug;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblAika;
    QTimeEdit *timeEdit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPeruuta;
    QPushButton *btnAja;

    void setupUi(QDialog *KonffiIkkuna)
    {
        if (KonffiIkkuna->objectName().isEmpty())
            KonffiIkkuna->setObjectName(QStringLiteral("KonffiIkkuna"));
        KonffiIkkuna->resize(328, 165);
        verticalLayout_2 = new QVBoxLayout(KonffiIkkuna);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cbDebug = new QCheckBox(KonffiIkkuna);
        cbDebug->setObjectName(QStringLiteral("cbDebug"));

        verticalLayout->addWidget(cbDebug);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lblAika = new QLabel(KonffiIkkuna);
        lblAika->setObjectName(QStringLiteral("lblAika"));

        horizontalLayout_2->addWidget(lblAika);

        timeEdit = new QTimeEdit(KonffiIkkuna);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));

        horizontalLayout_2->addWidget(timeEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnPeruuta = new QPushButton(KonffiIkkuna);
        btnPeruuta->setObjectName(QStringLiteral("btnPeruuta"));

        horizontalLayout->addWidget(btnPeruuta);

        btnAja = new QPushButton(KonffiIkkuna);
        btnAja->setObjectName(QStringLiteral("btnAja"));

        horizontalLayout->addWidget(btnAja);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(KonffiIkkuna);

        QMetaObject::connectSlotsByName(KonffiIkkuna);
    } // setupUi

    void retranslateUi(QDialog *KonffiIkkuna)
    {
        KonffiIkkuna->setWindowTitle(QApplication::translate("KonffiIkkuna", "Konffi-ikkuna", 0));
#ifndef QT_NO_TOOLTIP
        cbDebug->setToolTip(QApplication::translate("KonffiIkkuna", "K\303\244yt\303\244 debug-konfiguraatiota.", 0));
#endif // QT_NO_TOOLTIP
        cbDebug->setText(QApplication::translate("KonffiIkkuna", "Debug (1 bussi)", 0));
        lblAika->setText(QApplication::translate("KonffiIkkuna", "Aloitusaika:", 0));
#ifndef QT_NO_TOOLTIP
        timeEdit->setToolTip(QApplication::translate("KonffiIkkuna", "Aseta pelin sis\303\244inen aloitusaika.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnPeruuta->setToolTip(QApplication::translate("KonffiIkkuna", "Lopeta peli.", 0));
#endif // QT_NO_TOOLTIP
        btnPeruuta->setText(QApplication::translate("KonffiIkkuna", "Lopeta", 0));
#ifndef QT_NO_TOOLTIP
        btnAja->setToolTip(QApplication::translate("KonffiIkkuna", "Aloita peli.", 0));
#endif // QT_NO_TOOLTIP
        btnAja->setText(QApplication::translate("KonffiIkkuna", "Aja!", 0));
    } // retranslateUi

};

namespace Ui {
    class KonffiIkkuna: public Ui_KonffiIkkuna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KONFFIIKKUNA_H
