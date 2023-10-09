#include "Parametres.h"

Parametres::Parametres(QVector<int> parametresRecu, QWidget *parent)
    : QWidget(parent),
    raccourcis{32,65,90,69,82,84,89,85,73,79,80,81,83,68,70,71,72,74,75,76,77,87,88,67,86,66,78,38,201,34,39,40,45,200,95,199,192,49,50,51,52,53,54,55,56,57,48,1,2,4,16777347,16777346},
    textes{"Sp","A","Z","E","R","T","Y","U","I","O","P","Q","S","D","F","G","H","J","K","L","M","W","X","C","V","B","N","1","2","3","4","5","6","7","8","9","0","N1","N2","N3","N4","N5","N6","N7","N8","N9","N0","Gauche", "Droite", "Milieu", "Ext1", "Ext2"},
    parametres(parametresRecu)
{
    setFixedSize(650,500);
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();


    fond = new QLabel(this);
    fond->setStyleSheet("QWidget{border-image: url(../data/images/launcher/fondParametres.jpg) 0 0 0 0 stretch stretch;}");

    titre = new QLabel("Raccourcis clavier", this);
    titre->setStyleSheet("color: rgba(255,255,255,220); font-size: 24px; background: rgba(80,80,80,50);");
    titre->setAlignment(Qt::AlignCenter);

    group = new QButtonGroup(this);
    group->setExclusive(true);

    for(int i=0; i<11; i++)
    {
        QString legende = "";
        int index = 0;
        for(int j=0; j<52; j++)
        {
            if(raccourcis[j] == parametres[i])
            {
                legende = textes[j];
                index = j;
            }
        }
        QPushButton *bout = new QPushButton(legende, this);
        bout->setCheckable(true);
        if(index < 47)
            bout->setStyleSheet("QPushButton::checked{background: rgba(200,200,200,100); border: 3px solid rgba(120,120,120,200); color: rgba(80,80,80,220);} QPushButton{background: rgba(80,80,80,100); border: 3px solid rgba(40,40,40,200); border-radius: 4px; color: rgba(255,255,255,220); font-size: 48px; height: 96px; width: 96px;}");
        else
            bout->setStyleSheet("QPushButton::checked{background: rgba(200,200,200,100); border: 3px solid rgba(120,120,120,200); color: rgba(80,80,80,220);} QPushButton{background: rgba(80,80,80,100); border: 3px solid rgba(40,40,40,200); border-radius: 4px; color: rgba(255,255,255,220); font-size: 24px; height: 96px; width: 96px;}");

        boutons.push_back(bout);
        group->addButton(bout,i);
    }

    QPushButton *bouton = new QPushButton(this);
    bouton->setCheckable(true);
    bouton->setStyleSheet("background: transparent; width: 0px; height: 0px;");
    boutons.push_back(bouton);
    group->addButton(bouton);

    QPushButton *quitter = new QPushButton(this);
    quitter->setStyleSheet("width: 30px; height: 30px; border-image: url(../data/images/launcher/croix.png) 0 0 0 0 stretch stretch;");
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(deleteThis())); // Connection du bouton à la fermeture de la fenêtre
    quitter->raise();

    valider = new QPushButton("Valider", this);
    valider->setStyleSheet("QPushButton{background: rgba(120,120,120,100); border: 2px solid rgba(150,150,150,200); border-radius: 4px; color: rgba(150,150,150,220); font-size: 24px; height: 48px; width: 192px;}");
    QObject::connect(valider, SIGNAL(pressed()), this, SLOT(finish()));

    layoutPrincipal = new QGridLayout(this);
    layoutPrincipal->addWidget(fond, 0,0,80,120);
    layoutPrincipal->addWidget(quitter, 0,115,5,5);
    layoutPrincipal->addWidget(titre, 0,0,8,120);
    layoutPrincipal->addWidget(boutons[0], 10,10,19,19);
    layoutPrincipal->addWidget(boutons[1], 10,30,19,19);
    layoutPrincipal->addWidget(boutons[2], 10,50,19,19);
    layoutPrincipal->addWidget(boutons[3], 10,70,19,19);
    layoutPrincipal->addWidget(boutons[4], 10,90,19,19);
    layoutPrincipal->addWidget(boutons[5], 40,5,19,19);
    layoutPrincipal->addWidget(boutons[6], 40,25,19,19);
    layoutPrincipal->addWidget(boutons[7], 31,75,19,19);
    layoutPrincipal->addWidget(boutons[8], 48,55,19,19);
    layoutPrincipal->addWidget(boutons[9], 48,75,19,19);
    layoutPrincipal->addWidget(boutons[10], 48,95,19,19);
    layoutPrincipal->addWidget(valider, 68,40,10,40);
    layoutPrincipal->setContentsMargins(0,0,0,0);
    layoutPrincipal->setSpacing(0);
    setLayout(layoutPrincipal);
}

Parametres::~Parametres()
{
    int size = boutons.length();
    for(int i=0; i<size; i++)
        delete boutons.takeAt(0);
}

void Parametres::keyPressEvent (QKeyEvent *event)
{
    int key = event->key();

    for(int i=0; i<47; i++)
    {
        if(raccourcis[i] == key)
        {
            if((group->checkedId() != -1) && (group->checkedButton() != boutons.last()))
            {
                group->checkedButton()->setStyleSheet("QPushButton::checked{background: rgba(200,200,200,100); border: 3px solid rgba(120,120,120,200); color: rgba(80,80,80,220);} QPushButton{background: rgba(80,80,80,100); border: 3px solid rgba(40,40,40,200); border-radius: 4px; color: rgba(255,255,255,220); font-size: 48px; height: 96px; width: 96px;}");
                parametres[group->checkedId()] = key;
                group->checkedButton()->setText(textes[i]);
                boutons[11]->setChecked(true);
            }
        }
    }
}


void Parametres::mousePressEvent(QMouseEvent* event)
{
    int button = event->button();

    for(int i=47; i<52; i++)
    {
        if(raccourcis[i] == button)
        {
            if((group->checkedId() != -1) && (group->checkedButton() != boutons.last()))
            {
                group->checkedButton()->setStyleSheet("QPushButton::checked{background: rgba(200,200,200,100); border: 3px solid rgba(120,120,120,200); color: rgba(80,80,80,220);} QPushButton{background: rgba(80,80,80,100); border: 3px solid rgba(40,40,40,200); border-radius: 4px; color: rgba(255,255,255,220); font-size: 24px; height: 96px; width: 96px;}");
                parametres[group->checkedId()] = button;
                group->checkedButton()->setText(textes[i]);
                boutons[11]->setChecked(true);
            }
        }
    }
}

void Parametres::finish()
{
    emit newKeys(parametres);
}

void Parametres::deleteThis()
{
    emit deleteParametres();
}
