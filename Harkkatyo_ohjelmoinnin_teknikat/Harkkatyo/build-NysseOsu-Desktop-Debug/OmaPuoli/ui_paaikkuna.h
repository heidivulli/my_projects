/********************************************************************************
** Form generated from reading UI file 'paaikkuna.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAAIKKUNA_H
#define UI_PAAIKKUNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Paaikkuna
{
public:
    QGraphicsView *graphicsView;
    QPushButton *lopetanappi;
    QLCDNumber *health;
    QTextEdit *ohjeet;
    QLCDNumber *matkustajia;
    QLCDNumber *nysseja;
    QLabel *pistelabel;
    QLabel *healtlabel;
    QLabel *matkustajalabel;
    QLabel *nysselabel;
    QLCDNumber *pistemaara;
    QLabel *aikalabel;
    QLCDNumber *ammuksia;
    QLabel *ammuksiaLabel;
    QLCDNumber *minuutit;

    void setupUi(QWidget *Paaikkuna)
    {
        if (Paaikkuna->objectName().isEmpty())
            Paaikkuna->setObjectName(QStringLiteral("Paaikkuna"));
        Paaikkuna->resize(779, 535);
        graphicsView = new QGraphicsView(Paaikkuna);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(9, 9, 500, 500));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lopetanappi = new QPushButton(Paaikkuna);
        lopetanappi->setObjectName(QStringLiteral("lopetanappi"));
        lopetanappi->setGeometry(QRect(680, 500, 95, 31));
        QFont font;
        font.setFamily(QStringLiteral("Carlito"));
        font.setPointSize(13);
        lopetanappi->setFont(font);
        health = new QLCDNumber(Paaikkuna);
        health->setObjectName(QStringLiteral("health"));
        health->setGeometry(QRect(700, 290, 64, 23));
        health->setFrameShape(QFrame::StyledPanel);
        health->setFrameShadow(QFrame::Sunken);
        health->setSegmentStyle(QLCDNumber::Flat);
        ohjeet = new QTextEdit(Paaikkuna);
        ohjeet->setObjectName(QStringLiteral("ohjeet"));
        ohjeet->setGeometry(QRect(520, 10, 251, 241));
        ohjeet->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        matkustajia = new QLCDNumber(Paaikkuna);
        matkustajia->setObjectName(QStringLiteral("matkustajia"));
        matkustajia->setGeometry(QRect(700, 330, 64, 23));
        matkustajia->setFrameShape(QFrame::StyledPanel);
        matkustajia->setFrameShadow(QFrame::Sunken);
        matkustajia->setMode(QLCDNumber::Dec);
        matkustajia->setSegmentStyle(QLCDNumber::Flat);
        nysseja = new QLCDNumber(Paaikkuna);
        nysseja->setObjectName(QStringLiteral("nysseja"));
        nysseja->setGeometry(QRect(700, 360, 64, 23));
        nysseja->setFrameShape(QFrame::StyledPanel);
        nysseja->setFrameShadow(QFrame::Sunken);
        nysseja->setSegmentStyle(QLCDNumber::Flat);
        pistelabel = new QLabel(Paaikkuna);
        pistelabel->setObjectName(QStringLiteral("pistelabel"));
        pistelabel->setGeometry(QRect(520, 260, 66, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Carlito"));
        pistelabel->setFont(font1);
        healtlabel = new QLabel(Paaikkuna);
        healtlabel->setObjectName(QStringLiteral("healtlabel"));
        healtlabel->setGeometry(QRect(520, 290, 66, 21));
        healtlabel->setFont(font1);
        matkustajalabel = new QLabel(Paaikkuna);
        matkustajalabel->setObjectName(QStringLiteral("matkustajalabel"));
        matkustajalabel->setGeometry(QRect(520, 330, 81, 21));
        matkustajalabel->setFont(font1);
        nysselabel = new QLabel(Paaikkuna);
        nysselabel->setObjectName(QStringLiteral("nysselabel"));
        nysselabel->setGeometry(QRect(520, 360, 66, 21));
        nysselabel->setFont(font1);
        pistemaara = new QLCDNumber(Paaikkuna);
        pistemaara->setObjectName(QStringLiteral("pistemaara"));
        pistemaara->setGeometry(QRect(700, 260, 64, 23));
        pistemaara->setFrameShape(QFrame::StyledPanel);
        pistemaara->setFrameShadow(QFrame::Sunken);
        pistemaara->setSegmentStyle(QLCDNumber::Flat);
        aikalabel = new QLabel(Paaikkuna);
        aikalabel->setObjectName(QStringLiteral("aikalabel"));
        aikalabel->setGeometry(QRect(520, 460, 131, 41));
        ammuksia = new QLCDNumber(Paaikkuna);
        ammuksia->setObjectName(QStringLiteral("ammuksia"));
        ammuksia->setEnabled(true);
        ammuksia->setGeometry(QRect(700, 390, 64, 23));
        ammuksia->setFrameShape(QFrame::StyledPanel);
        ammuksia->setFrameShadow(QFrame::Sunken);
        ammuksia->setSegmentStyle(QLCDNumber::Flat);
        ammuksiaLabel = new QLabel(Paaikkuna);
        ammuksiaLabel->setObjectName(QStringLiteral("ammuksiaLabel"));
        ammuksiaLabel->setGeometry(QRect(520, 390, 66, 21));
        minuutit = new QLCDNumber(Paaikkuna);
        minuutit->setObjectName(QStringLiteral("minuutit"));
        minuutit->setGeometry(QRect(700, 470, 71, 21));
        minuutit->setSegmentStyle(QLCDNumber::Flat);

        retranslateUi(Paaikkuna);

        QMetaObject::connectSlotsByName(Paaikkuna);
    } // setupUi

    void retranslateUi(QWidget *Paaikkuna)
    {
        Paaikkuna->setWindowTitle(QApplication::translate("Paaikkuna", "Form", 0));
        lopetanappi->setText(QApplication::translate("Paaikkuna", "Lopeta Peli", 0));
        ohjeet->setHtml(QApplication::translate("Paaikkuna", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Carlito'; font-size:10pt;\">Pelin idea: Tuhoa reaaliajassa liikkuvia nyssej\303\244 ja matkustajia liikuttamalla <br />droonia ymp\303\244ri Tampereen keskustaa.<br />Droonin ominaisuudet: Liikkuminen tapahtuu nuolin\303\244pp\303\244imill\303\244. Droonilla <br />on kolme erilaista asetta: perusase, raketti ja miina. Perusaseessa on <br />rajattomat ammukset ja se toimii painamalla v\303\244lily\303\266nti\303\244. Raketteja ja <br />miinoja on yhteens\303\244 viisi kappaletta. Raketti laukaistaan Q-n\303\244pp\303\244imest\303\244 "
                        "ja se <br />voidaan r\303\244j\303\244ytt\303\244\303\244 painamalla Q-n\303\244pp\303\244int\303\244 uudestaan. Miina tiputetaan <br />E-n\303\244pp\303\244imest\303\244. Vain miinoilla ja raketeilla pystyt\303\244\303\244n tuhoamaan pys\303\244keill\303\244<br />olevia matkustajia. Droonilla on alussa 5 el\303\244m\303\244\303\244, jotka v\303\244henev\303\244t vihollisen <br />osuessa drooniin.<br />Pisteenlasku: Tuhoutuneesta nyssest\303\244 saa 100p. ja matkustajasta 10p. Jos<br />tuhoaa 5 matkustajaa kerralla, pisteet tuplataan.<br />Lis\303\244ominaisuudet: Kaupunkiin ilmestyy 15s. v\303\244lein vihollisia, jotka yritt\303\244v\303\244t<br />tuhota droonin. Vihollisen voi tuhota ampumalla sit\303\244.<br />Peli p\303\244\303\244ttyy, kun drooni tuhoutuu, aikaa on kulunut 3 minuutia tai k\303\244ytt\303\244j\303\244 <br />lopettaa pelin painamalla lopeta peli-nappia.</span></p></body></html>", 0));
        pistelabel->setText(QApplication::translate("Paaikkuna", "<html><head/><body><p>Pistem\303\244\303\244r\303\244</p></body></html>", 0));
        healtlabel->setText(QApplication::translate("Paaikkuna", "<html><head/><body><p>Health</p></body></html>", 0));
        matkustajalabel->setText(QApplication::translate("Paaikkuna", "<html><head/><body><p>Matkustajia</p></body></html>", 0));
        nysselabel->setText(QApplication::translate("Paaikkuna", "<html><head/><body><p>Nyssej\303\244</p></body></html>", 0));
        aikalabel->setText(QApplication::translate("Paaikkuna", "<html><head/><body><p>Aikaa kulunut</p></body></html>", 0));
        ammuksiaLabel->setText(QApplication::translate("Paaikkuna", "Ammuksia", 0));
    } // retranslateUi

};

namespace Ui {
    class Paaikkuna: public Ui_Paaikkuna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAAIKKUNA_H
