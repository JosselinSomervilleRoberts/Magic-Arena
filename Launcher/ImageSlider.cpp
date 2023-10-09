#include "ImageSlider.h"

ImageSlider::ImageSlider(int width, int height, QVector<QPixmap> pixmapsRecu, QWidget *parent) : QWidget(parent)
{
    qsrand(QDateTime::currentDateTime ().toTime_t ());
    position = 0;
    left = new QPushButton("◄", this);
    right = new QPushButton("►", this);
    boutonAleatoire = new QPushButton("Aléatoire", this);
    boutonChoisir = new QPushButton("Choisir", this);

    labelImage = new QLabel(this);

    pixmaps = pixmapsRecu;

    if(pixmaps.length() > 0)
    {
        for(int i=0; i<pixmaps.length(); i++)
        {
            pixmaps[i] = pixmaps[i].scaled(qMin(pixmaps[i].width(), width), qMin(pixmaps[i].height(), height));
        }

        left->setStyleSheet("color: rgba(255,255,255,127); font-size: " + QString::number(pixmaps[0].width()/20) + "px; width: " + QString::number(pixmaps[0].width()/10) + " px; height: " + QString::number(pixmaps[0].height()) + " px; background-color: rgba(0,0,0,127);");
        right->setStyleSheet("color: rgba(255,255,255,127); font-size: " + QString::number(pixmaps[0].width()/20) + "px; width: " + QString::number(pixmaps[0].width()/10) + " px; height: " + QString::number(pixmaps[0].height()) + " px; background-color: rgba(0,0,0,127);");
        left->raise();
        right->raise();

        boutonAleatoire->setStyleSheet("border: 2px solid rgba(255,255,255,200); color: rgb(255,255,255); font-size: " + QString::number(pixmaps[0].width()/40) + "px; width: " + QString::number(pixmaps[0].width()/10) + " px; height: " + QString::number(pixmaps[0].height()/10) + " px; background-color: rgba(0,0,0,127);");
        boutonChoisir->setStyleSheet("border: 2px solid rgba(255,255,255,200); color: rgb(255,255,255); font-size: " + QString::number(pixmaps[0].width()/40) + "px; width: " + QString::number(pixmaps[0].width()/10) + " px; height: " + QString::number(pixmaps[0].height()/10) + " px; background-color: rgba(0,0,0,127);");
        boutonAleatoire->raise();
        boutonChoisir->raise();

        labelImage->setPixmap(pixmaps[position]);
        setFixedSize(pixmaps[0].width(), pixmaps[0].height());
    }


    layout = new QGridLayout(this);

    layout->addWidget(labelImage, 0, 0, 20, 41);
    layout->addWidget(left, 0, 0, 20, 4);
    layout->addWidget(right, 0, 37, 20, 4);
    layout->addWidget(boutonAleatoire, 17, 12, 2, 8);
    layout->addWidget(boutonChoisir, 17, 21, 2, 8);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    setLayout(layout);

    QObject::connect(left, SIGNAL(pressed()), this, SLOT(goLeft()));
    QObject::connect(right, SIGNAL(pressed()), this, SLOT(goRight()));
    QObject::connect(boutonAleatoire, SIGNAL(pressed()), this, SLOT(aleatoire()));
    QObject::connect(boutonChoisir, SIGNAL(pressed()), this, SLOT(choisir()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(next()));
}

ImageSlider::~ImageSlider()
{
    delete timer;
}

void ImageSlider::goRight()
{
    if(position < pixmaps.length() - 1)
        position++;
    else
        position = 0;

    labelImage->setPixmap(pixmaps[position]);
}

void ImageSlider::goLeft()
{
    if(position > 0)
        position--;
    else
        position = pixmaps.length() - 1;

    labelImage->setPixmap(pixmaps[position]);
}

void ImageSlider::aleatoire()
{
    nbFois = 18 + qrand() % 18;
    temps = 100;
    nb = 0;
    timer->start(temps);
}

void ImageSlider::next()
{
    goRight();
    nb++;
    if(nb >= nbFois)
        emit setMap(position);
    else
    {
        temps -= 1;
        timer->start(temps);
    }
}

void ImageSlider::choisir()
{
    emit setMap(position);
}


