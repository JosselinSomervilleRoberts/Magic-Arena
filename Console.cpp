#include "Console.h"

Console::Console(int width, int height, bool important) : QTextEdit()
{
    onlyShowImportant = important;

    setReadOnly(true);
    setStyleSheet("background-color: black; font-size: 10px;");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SplashScreen);

    setFixedSize(width / 5, height * 0.8);
    move(width - width / 5, height - (height/22.5)*1.5 - height * 0.8);
    setWindowTitle("Console");

    show();
}

void Console::add(QColor couleur, QString source, QString message, bool newLine, bool important)
{
    if((!onlyShowImportant) || (important))
    {
        setTextColor(couleur);

        if(source != "")
        {
            setFontWeight(QFont::Bold);
            insertPlainText(source + ": ");
        }

        if(message != "")
        {
            setFontWeight(QFont::Normal);
            insertPlainText(message);
        }

        if(newLine)
            insertPlainText("\r\n");

        QScrollBar *sb = verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}

void Console::returnToLine()
{
    insertPlainText("\r\n");

    QScrollBar *sb = verticalScrollBar();
    sb->setValue(sb->maximum());
}
