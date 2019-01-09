#include "cbeditormain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBEditorMain w;
    w.show();

    return a.exec();
}
