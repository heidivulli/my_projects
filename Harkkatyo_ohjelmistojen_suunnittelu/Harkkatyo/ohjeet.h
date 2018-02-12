#ifndef OHJEET_H
#define OHJEET_H

#include <QDialog>

/**
 * @brief Sisältää pelin ohjeet.
 */
namespace Ui {
class Ohjeet;
}

class Ohjeet : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Rakentaja
     */
    explicit Ohjeet(QWidget *parent = 0);

    /**
     * @brief Purkaja
     */
    ~Ohjeet();

private:
    Ui::Ohjeet *ui;
};

#endif // OHJEET_H
