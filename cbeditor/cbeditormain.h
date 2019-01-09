#ifndef CBEDITORMAIN_H
#define CBEDITORMAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "levelmap.h"

namespace Ui {
class CBEditorMain;
}

class CBEditorMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CBEditorMain(QWidget *parent = nullptr);
    ~CBEditorMain();

private:
    void callConnectMenu(void);
    LevelMap map;

private slots:
    void on_acAboutQt_triggered();
    void onActionClickExit();

    void onActionClickLoadMap();

private:
    Ui::CBEditorMain *ui;
    bool dirty = false;
};

#endif // CBEDITORMAIN_H
