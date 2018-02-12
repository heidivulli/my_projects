/********************************************************************************
** Form generated from reading UI file 'lopetusikkuna.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOPETUSIKKUNA_H
#define UI_LOPETUSIKKUNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_LopetusIkkuna
{
public:
    QGridLayout *gridLayout;
    QLabel *Otsikko;
    QSpacerItem *verticalSpacer_3;
    QLCDNumber *pisteita;
    QTextEdit *textEdit;
    QLabel *tuhnytlabel;
    QLCDNumber *tuhottujanysseja;
    QLabel *tuhmatlabel;
    QLCDNumber *tuhottujamatkustajia;
    QPushButton *lopetusnappi;
    QLabel *label_2;
    QLabel *label;
    QLabel *pistelabel;

    void setupUi(QDialog *LopetusIkkuna)
    {
        if (LopetusIkkuna->objectName().isEmpty())
            LopetusIkkuna->setObjectName(QStringLiteral("LopetusIkkuna"));
        LopetusIkkuna->resize(473, 355);
        gridLayout = new QGridLayout(LopetusIkkuna);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Otsikko = new QLabel(LopetusIkkuna);
        Otsikko->setObjectName(QStringLiteral("Otsikko"));
        QFont font;
        font.setFamily(QStringLiteral("Carlito"));
        Otsikko->setFont(font);

        gridLayout->addWidget(Otsikko, 0, 0, 1, 3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 6, 1, 1, 1);

        pisteita = new QLCDNumber(LopetusIkkuna);
        pisteita->setObjectName(QStringLiteral("pisteita"));
        pisteita->setFrameShape(QFrame::Box);
        pisteita->setFrameShadow(QFrame::Sunken);
        pisteita->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(pisteita, 2, 1, 1, 1);

        textEdit = new QTextEdit(LopetusIkkuna);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(textEdit, 2, 2, 6, 1);

        tuhnytlabel = new QLabel(LopetusIkkuna);
        tuhnytlabel->setObjectName(QStringLiteral("tuhnytlabel"));
        tuhnytlabel->setFont(font);

        gridLayout->addWidget(tuhnytlabel, 3, 0, 1, 1);

        tuhottujanysseja = new QLCDNumber(LopetusIkkuna);
        tuhottujanysseja->setObjectName(QStringLiteral("tuhottujanysseja"));
        tuhottujanysseja->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(tuhottujanysseja, 3, 1, 1, 1);

        tuhmatlabel = new QLabel(LopetusIkkuna);
        tuhmatlabel->setObjectName(QStringLiteral("tuhmatlabel"));
        tuhmatlabel->setFont(font);

        gridLayout->addWidget(tuhmatlabel, 5, 0, 1, 1);

        tuhottujamatkustajia = new QLCDNumber(LopetusIkkuna);
        tuhottujamatkustajia->setObjectName(QStringLiteral("tuhottujamatkustajia"));
        tuhottujamatkustajia->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(tuhottujamatkustajia, 5, 1, 1, 1);

        lopetusnappi = new QPushButton(LopetusIkkuna);
        lopetusnappi->setObjectName(QStringLiteral("lopetusnappi"));
        lopetusnappi->setFont(font);

        gridLayout->addWidget(lopetusnappi, 7, 0, 1, 2);

        label_2 = new QLabel(LopetusIkkuna);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(LopetusIkkuna);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 1, 2, 1, 1);

        pistelabel = new QLabel(LopetusIkkuna);
        pistelabel->setObjectName(QStringLiteral("pistelabel"));
        pistelabel->setFont(font);

        gridLayout->addWidget(pistelabel, 2, 0, 1, 1);


        retranslateUi(LopetusIkkuna);

        QMetaObject::connectSlotsByName(LopetusIkkuna);
    } // setupUi

    void retranslateUi(QDialog *LopetusIkkuna)
    {
        LopetusIkkuna->setWindowTitle(QApplication::translate("LopetusIkkuna", "Dialog", 0));
        Otsikko->setText(QApplication::translate("LopetusIkkuna", "<html><head/><body><p align=\"center\"><span style=\" font-size:28pt; font-weight:600;\">Peli p\303\244\303\244ttyi!</span></p></body></html>", 0));
        textEdit->setHtml(QApplication::translate("LopetusIkkuna", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Carlito'; font-size:10pt;\">Pelin idea: Tuhoa reaaliajassa liikkuvia nyssej\303\244 ja matkustajia liikuttamalla droonia ymp\303\244ri Tampereen keskustaa.<br />Droonin ominaisuudet: Liikkuminen tapahtuu nuolin\303\244pp\303\244imill\303\244. Droonilla on kolme erilaista asetta: perusase, raketti ja miina. Perusaseessa on rajattomat ammukset ja se toimii painamalla v\303\244lily\303\266nti\303\244. Raketteja ja miinoja on yhteens\303\244 viisi kappaletta. Raketti laukaistaan Q-n\303\244pp\303\244imest\303\244 ja se voidaan r\303\244j"
                        "\303\244ytt\303\244\303\244 painamalla Q-n\303\244pp\303\244int\303\244 uudestaan. Miina tiputetaan E-n\303\244pp\303\244imest\303\244. Vain miinoilla ja raketeilla pystyt\303\244\303\244n tuhoamaan pys\303\244keill\303\244 olevia matkustajia. Droonilla on alussa 5 el\303\244m\303\244\303\244, jotka v\303\244henev\303\244t vihollisen osuessa drooniin.<br />Pisteenlasku: Tuhoutuneesta nyssest\303\244 saa 100p. ja matkustajasta 10p. Jos tuhoaa 5 matkustajaa kerralla, pisteet tuplataan.<br />Lis\303\244ominaisuudet: Kaupunkiin ilmestyy 15s. v\303\244lein vihollisia, jotka yritt\303\244v\303\244t tuhota droonin. Vihollisen voi tuhota ampumalla sit\303\244.<br />Peli p\303\244\303\244ttyy, kun drooni tuhoutuu, aikaa on kulunut 3 minuutia tai k\303\244ytt\303\244j\303\244 <br />lopettaa pelin painamalla lopeta peli-nappia.</span></p></body></html>", 0));
        tuhnytlabel->setText(QApplication::translate("LopetusIkkuna", "<html><head/><body><p>Tuhotut nysset</p></body></html>", 0));
        tuhmatlabel->setText(QApplication::translate("LopetusIkkuna", "<html><head/><body><p>Tuhotut matkustajat</p></body></html>", 0));
        lopetusnappi->setText(QApplication::translate("LopetusIkkuna", "Lopeta", 0));
        label_2->setText(QApplication::translate("LopetusIkkuna", "<html><head/><body><p><span style=\" font-size:12pt; text-decoration: underline;\">Pelin tilastot:</span></p></body></html>", 0));
        label->setText(QApplication::translate("LopetusIkkuna", "<html><head/><body><p><span style=\" font-size:10pt;\">Etk\303\266 kerinnyt lukemaan ohjeita? Lue ne nyt alta!</span></p></body></html>", 0));
        pistelabel->setText(QApplication::translate("LopetusIkkuna", "<html><head/><body><p>Pisteet</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class LopetusIkkuna: public Ui_LopetusIkkuna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOPETUSIKKUNA_H
