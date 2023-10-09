#ifndef IMAGESLIDER_H
#define IMAGESLIDER_H

#include <QtWidgets>

class ImageSlider : public QWidget
{
    Q_OBJECT

public:
    ImageSlider(int width, int height, QVector<QPixmap> pixmapsRecu, QWidget *parent = 0);
    ~ImageSlider();

public slots:
    void goLeft();
    void goRight();
    void aleatoire();
    void choisir();
    void next();

signals:
    void setMap(int);

protected:
    QTimer *timer;
    int temps;
    int nbFois, nb;

    QPushButton *boutonAleatoire;
    QPushButton *boutonChoisir;

    int position;
    QPushButton *left;
    QPushButton *right;

    QLabel *labelImage;
    QGridLayout *layout;
    QVector<QPixmap> pixmaps;
};

#endif // IMAGESLIDER_H
