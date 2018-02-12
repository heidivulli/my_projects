/********************************************************************************
** Form generated from reading UI file 'aloitusikkuna.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALOITUSIKKUNA_H
#define UI_ALOITUSIKKUNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_aloitusikkuna
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;

    void setupUi(QDialog *aloitusikkuna)
    {
        if (aloitusikkuna->objectName().isEmpty())
            aloitusikkuna->setObjectName(QStringLiteral("aloitusikkuna"));
        aloitusikkuna->resize(482, 420);
        label = new QLabel(aloitusikkuna);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 20, 201, 51));
        QFont font;
        font.setFamily(QStringLiteral("Carlito"));
        font.setPointSize(20);
        label->setFont(font);
        label_2 = new QLabel(aloitusikkuna);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 80, 91, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Carlito"));
        font1.setPointSize(13);
        label_2->setFont(font1);
        label_3 = new QLabel(aloitusikkuna);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 100, 401, 271));
        pushButton = new QPushButton(aloitusikkuna);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 370, 95, 31));

        retranslateUi(aloitusikkuna);

        QMetaObject::connectSlotsByName(aloitusikkuna);
    } // setupUi

    void retranslateUi(QDialog *aloitusikkuna)
    {
        aloitusikkuna->setWindowTitle(QApplication::translate("aloitusikkuna", "Dialog", 0));
        label->setText(QApplication::translate("aloitusikkuna", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600;\">NysseOsu-peli</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("aloitusikkuna", "<html><head/><body><p><span style=\" font-size:14pt;\">Ohjeet:</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("aloitusikkuna", "<html><head/><body><p><span style=\" font-family:'Carlito'; font-size:10pt;\">Pelin idea: Tuhoa reaaliajassa liikkuvia nyssej\303\244 ja matkustajia liikuttamalla <br/>droonia ymp\303\244ri Tampereen keskustaa.<br/>Droonin ominaisuudet: Liikkuminen tapahtuu nuolin\303\244pp\303\244imill\303\244. Droonilla <br/>on kolme erilaista asetta: perusase, raketti ja miina. Perusaseessa on <br/>rajattomat ammukset ja se toimii painamalla v\303\244lily\303\266nti\303\244. Raketteja ja <br/>miinoja on yhteens\303\244 viisi kappaletta. Raketti laukaistaan Q-n\303\244pp\303\244imest\303\244 ja se <br/>voidaan r\303\244j\303\244ytt\303\244\303\244 painamalla Q-n\303\244pp\303\244int\303\244 uudestaan. Miina tiputetaan <br/>E-n\303\244pp\303\244imest\303\244. Vain miinoilla ja raketeilla pystyt\303\244\303\244n tuhoamaan pys\303\244keill\303\244<br/>olevia matkustajia. Droonilla on alussa 5 el\303\244m\303\244\303\244, jotka v\303\244henev\303\244t vihollisen <br/>osuessa drooniin.<br/>Pisteenlasku: Tuhoutuneesta nyssest\303\244"
                        " saa 100p. ja matkustajasta 10p. Jos<br/>tuhoaa 5 matkustajaa kerralla, pisteet tuplataan.<br/>Lis\303\244ominaisuudet: Kaupunkiin ilmestyy 15s. v\303\244lein vihollisia, jotka yritt\303\244v\303\244t<br/>tuhota droonin. Vihollisen voi tuhota ampumalla sit\303\244.<br/>Peli p\303\244\303\244ttyy, kun drooni tuhoutuu, aikaa on kulunut 3 minuutia tai k\303\244ytt\303\244j\303\244 <br/>lopettaa pelin painamalla lopeta peli-nappia.</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("aloitusikkuna", "Aloita peli!", 0));
    } // retranslateUi

};

namespace Ui {
    class aloitusikkuna: public Ui_aloitusikkuna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALOITUSIKKUNA_H
