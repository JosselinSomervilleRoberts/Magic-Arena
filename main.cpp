#include "Launcher/MonLauncher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MonLauncher launcher(&app);
    launcher.show();

    return app.exec();
}
