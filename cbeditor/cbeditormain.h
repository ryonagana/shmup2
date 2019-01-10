#ifndef CBEDITORMAIN_H
#define CBEDITORMAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "levelmap.h"
#include "render.h"

namespace Ui {
class CBEditorMain;
}

class CBEditorMain : public QMainWindow
{
    Q_OBJECT

enum class CBMapState {
    Started,
    OpenMap,
    CloseMap,
    Saving,
    Modified,
    Editing
};

public:
    explicit CBEditorMain(QWidget *parent = nullptr);
    ~CBEditorMain();

private:
    void callConnectMenu(void);
    void initialSetup(void);
    void setStatus(CBMapState state);

    LevelMap map;

    void statusStartedEditor(void);
    void statusOpenFile(void);
    void statusClose(void);

private slots:
    void on_acAboutQt_triggered();
    void onActionClickExit();
    void onActionClickAboutMe();

    void onActionClickLoadMap();
    void onActionClickSaveAsFile();

private:
    Ui::CBEditorMain *ui;
    RenderScene renderGraphics;
    bool dirty = false;
    bool isMapOpened = false;
    QPixmap tilemap;
    QPixmap spritesheet;

    CBMapState state = CBMapState::Started;

    void paintEvent(QPaintEvent *event) override;

};

#endif // CBEDITORMAIN_H
