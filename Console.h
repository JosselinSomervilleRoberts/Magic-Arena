#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>
#include <QScrollBar>

class Console : public QTextEdit
{
    Q_OBJECT

public:
    Console(int width, int height, bool important);
    void add(QColor couleur, QString source, QString message, bool newLine, bool important);
    void returnToLine();

protected:
    bool onlyShowImportant;
};

#endif // CONSOLE_H
