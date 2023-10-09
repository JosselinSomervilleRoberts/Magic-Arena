#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T21:48:56
#
#-------------------------------------------------

QT       += network core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Jeu
TEMPLATE = app


SOURCES += main.cpp\
    Launcher/ImageSlider.cpp \
    MaFenetre.cpp\
    Affichable.cpp \
    Vue.cpp \
    Vivants/Personnage.cpp \
    Vivants/Vivant.cpp \
    Equipement/Equipement.cpp \
    Equipement/Equipable.cpp \
    Equipement/Arme.cpp \
    Equipement/Armure.cpp \
    Map/Collision.cpp \
    Map/Map.cpp \
    Map/EffetsCollision.cpp \
    Communication/chatdialog.cpp \
    Communication/client.cpp \
    Communication/connection.cpp \
    Communication/peermanager.cpp \
    Communication/server.cpp \
    Communication/Communication.cpp \
    Sorts/Sorts/Sort.cpp \
    Sorts/Sorts/ChangerArme.cpp \
    Sorts/Sorts/S_Teleportation.cpp \
    Sorts/Sorts/S_ExplosionFeu.cpp \
    Sorts/Sorts/S_DiffusionMulti.cpp \
    Sorts/Sorts/S_Assassinat.cpp \
    Sorts/Shields/Shield.cpp \
    Sorts/Shields/Sh_Feu.cpp \
    Sorts/Projectiles/Projectile.cpp \
    Sorts/Projectiles/P_Fleche.cpp \
    Sorts/Projectiles/P_BouleFeu.cpp \
    Sorts/Projectiles/P_BouleEau.cpp \
    Sorts/Projectiles/P_BouleAir.cpp \
    Sorts/Projectiles/P_BouleTerre.cpp \
    Sorts/Projectiles/P_Assassinat.cpp \
    Sorts/Boules/Boule.cpp \
    Sorts/Boules/B_Teleportation.cpp \
    Sorts/Boules/B_DegatsArme.cpp \
    Sorts/Boules/B_ExplosionFeu.cpp \
    Sorts/Boules/B_BlackHoleDark.cpp \
    Sorts/Boules/B_ExplosionGlace.cpp \
    Sorts/Boules/B_ExplosionTerre.cpp \
    Sorts/Boules/B_ExplosionVent.cpp \
    Sorts/Sorts/S_Invisibilite.cpp \
    Sorts/Boules/B_Invisibilite.cpp \
    Sorts/Shields/Sh_WindWalk.cpp \
    Sorts/Shields/Sh_LumiereDivine.cpp \
    Sorts/Projectiles/P_Piege.cpp \
    Sorts/Boules/B_ApotreMort.cpp \
    Sorts/Sorts/S_Piege.cpp \
    Sorts/Sorts/S_ApotreMort.cpp \
    Sorts/Sorts/S_WindWalk.cpp \
    Sorts/Sorts/S_ExplosionAir.cpp \
    Sorts/Sorts/S_ExplosionTerre.cpp \
    Sorts/Sorts/S_ExplosionGlace.cpp \
    Sorts/Sorts/S_LumiereDivine.cpp \
    Sorts/Projectiles/P_Vampirisme.cpp \
    Sorts/Sorts/S_Vampirisme.cpp \
    Sorts/Sorts/S_BlackHoleDark.cpp \
    Sorts/Shields/Sh_Vampirisme.cpp \
    Sorts/Boules/B_DarkField.cpp \
    Sorts/Sorts/S_DarkField.cpp \
    Sorts/Shields/Sh_DarkCage.cpp \
    Sorts/Sorts/S_DarkCage.cpp \
    Sorts/Boules/B_Heal.cpp \
    Sorts/Shields/sh_heal.cpp \
    Sorts/Boules/B_LumiereBrulante.cpp \
    Sorts/Sorts/S_Heal.cpp \
    Sorts/Sorts/S_LumiereBrulante.cpp \
    Sorts/Sorts/S_DiffusionLumiere.cpp \
    Sorts/Boules/B_Light.cpp \
    Sorts/Sorts/S_Light.cpp \
    Sorts/Projectiles/P_DiffusionLumiere.cpp \
    Sorts/Shields/Sh_Eau.cpp \
    Sorts/Shields/Sh_Terre.cpp \
    Sorts/Shields/Sh_Air.cpp \
    Launcher/MonLauncher.cpp \
    Sorts/Sorts/S_DegatsArme.cpp \
    Sorts/Sorts/S_Fleche.cpp \
    Vivants/Animal.cpp \
    Launcher/MonChoixAnimal.cpp \
    Console.cpp \
    Vivants/Monstre.cpp \
    Parametres.cpp \
    Gestion/GerantMulti.cpp \
    Gestion/Gerant.cpp \
    Gestion/GerantSolo.cpp \
    Controleur/Controleur.cpp \
    Controleur/ControleurMulti.cpp \
    Controleur/ControleurSolo.cpp

HEADERS  += MaFenetre.h\
    Launcher/ImageSlider.h \
    Affichable.h \
    Vue.h \
    Vivants/Personnage.h \
    Vivants/Vivant.h \
    Equipement/Equipement.h \
    Equipement/Equipable.h \
    Equipement/Arme.h \
    Equipement/Armure.h \
    Map/Collision.h \
    Map/Map.h \
    Map/EffetsCollision.h \
    Communication/chatdialog.h \
    Communication/client.h \
    Communication/connection.h \
    Communication/peermanager.h \
    Communication/server.h \
    Communication/Communication.h \
    Sorts/Sorts/Sort.h \
    Sorts/Sorts/ChangerArme.h \
    Sorts/Sorts/S_Teleportation.h \
    Sorts/Sorts/S_ExplosionFeu.h \
    Sorts/Sorts/S_DiffusionMulti.h \
    Sorts/Sorts/S_Assassinat.h \
    Sorts/Shields/Shield.h \
    Sorts/Shields/Sh_Feu.h \
    Sorts/Projectiles/Projectile.h \
    Sorts/Projectiles/P_Fleche.h \
    Sorts/Projectiles/P_BouleFeu.h \
    Sorts/Projectiles/P_BouleEau.h \
    Sorts/Projectiles/P_BouleAir.h \
    Sorts/Projectiles/P_BouleTerre.h \
    Sorts/Projectiles/P_Assassinat.h \
    Sorts/Boules/Boule.h \
    Sorts/Boules/B_Teleportation.h \
    Sorts/Boules/B_DegatsArme.h \
    Sorts/Boules/B_ExplosionFeu.h \
    Sorts/Boules/B_BlackHoleDark.h \
    Sorts/Boules/B_ExplosionGlace.h \
    Sorts/Boules/B_ExplosionTerre.h \
    Sorts/Boules/B_ExplosionVent.h \
    Sorts/Sorts/S_Invisibilite.h \
    Sorts/Boules/B_Invisibilite.h \
    Sorts/Shields/Sh_WindWalk.h \
    Sorts/Shields/Sh_LumiereDivine.h \
    Sorts/Projectiles/P_Piege.h \
    Sorts/Boules/B_ApotreMort.h \
    Sorts/Sorts/S_Piege.h \
    Sorts/Sorts/S_ApotreMort.h \
    Sorts/Sorts/S_WindWalk.h \
    Sorts/Sorts/S_ExplosionAir.h \
    Sorts/Sorts/S_ExplosionTerre.h \
    Sorts/Sorts/S_ExplosionGlace.h \
    Sorts/Sorts/S_LumiereDivine.h \
    Sorts/Projectiles/P_Vampirisme.h \
    Sorts/Sorts/S_Vampirisme.h \
    Sorts/Sorts/S_BlackHoleDark.h \
    Sorts/Shields/Sh_Vampirisme.h \
    Sorts/Boules/B_DarkField.h \
    Sorts/Sorts/S_DarkField.h \
    Sorts/Shields/Sh_DarkCage.h \
    Sorts/Sorts/S_DarkCage.h \
    Sorts/Boules/B_Heal.h \
    Sorts/Shields/sh_heal.h \
    Sorts/Boules/B_LumiereBrulante.h \
    Sorts/Sorts/S_Heal.h \
    Sorts/Sorts/S_LumiereBrulante.h \
    Sorts/Sorts/S_DiffusionLumiere.h \
    Sorts/Boules/B_Light.h \
    Sorts/Sorts/S_Light.h \
    Sorts/Projectiles/P_DiffusionLumiere.h \
    Sorts/Shields/Sh_Eau.h \
    Sorts/Shields/Sh_Terre.h \
    Sorts/Shields/Sh_Air.h \
    Launcher/MonLauncher.h \
    Sorts/Sorts/S_DegatsArme.h \
    Sorts/Sorts/S_Fleche.h \
    Vivants/Animal.h \
    Launcher/MonChoixAnimal.h \
    Console.h \
    Vivants/Monstre.h \
    Parametres.h \
    Gestion/GerantMulti.h \
    Gestion/Gerant.h \
    Gestion/GerantSolo.h \
    Controleur/Controleur.h \
    Controleur/ControleurMulti.h \
    Controleur/ControleurSolo.h

RC_FILE = myapp.rc
