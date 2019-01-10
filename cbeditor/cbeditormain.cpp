#include "cbeditormain.h"
#include "ui_cbeditormain.h"
#include "render.h"

CBEditorMain::CBEditorMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CBEditorMain)
{
    ui->setupUi(this);


    ui->gridGraphics->setScene(&renderGraphics);

    ui->gridGraphics->setBackgroundBrush(Qt::blue);

    tilemap.load("tile/spritesheet.png");


    setStatus(CBMapState::Started);

#ifdef DEBUG_SAVE
    QFileDialog  dlg(this);
    QStringList path;
    dlg.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    dlg.setNameFilter("CB Maps (*.cbm)|All File (*.*)");
    dlg.setViewMode(QFileDialog::Detail);

    if(!dlg.exec()){
        return;
    }


    path = dlg.selectedFiles();

    map.SaveToDisk(path[0]);

#endif

    this->callConnectMenu();


}

CBEditorMain::~CBEditorMain()
{
    delete ui;
}

void CBEditorMain::on_acAboutQt_triggered()
{
    QMessageBox::aboutQt(this,"Sobre Qt?");
}

void CBEditorMain::onActionClickExit(){
    if(dirty){
        // TODO
    }

    this->close();
}

void CBEditorMain::callConnectMenu(void){
    connect(ui->acExit, SIGNAL(triggered()), SLOT(onActionClickExit()));
    connect(ui->acLoadMap, SIGNAL(triggered()), SLOT(onActionClickLoadMap()));
    connect(ui->acAboutMe, SIGNAL(triggered()), SLOT(onActionClickAboutMe()));
    connect(ui->acSaveAs, SIGNAL(triggered()), SLOT(onActionClickSaveAsFile()));
}

void CBEditorMain::onActionClickLoadMap(){
    if(map.loadMap()){
        this->setWindowTitle( this->windowTitle() + " - " + map.getFileName());
        setStatus(CBMapState::OpenMap);
    }else {
        setStatus(CBMapState::Started);
    }
}


void CBEditorMain::onActionClickAboutMe(){
    QMessageBox(QMessageBox::Icon::Information, "Me?", "I'm Nobody", QMessageBox::StandardButton::Ok).exec();
}

void CBEditorMain::onActionClickSaveAsFile(){
    QFileDialog dlg(this);

    QStringList path;
    dlg.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    dlg.setNameFilter("CB Maps (*.cbm)|All File (*.*)");
    dlg.setViewMode(QFileDialog::Detail);

    if(!dlg.exec()){
        return;
    }


    path = dlg.selectedFiles();

    map.SaveToDisk(path[0]);

    QFile e(path[0]);

    if(!e.exists()){
        QMessageBox(QMessageBox::Icon::Critical, tr("Error"), tr("An Error Occured when tried to save the map.."), QMessageBox::StandardButton::Ok).exec();
        return;
    }


    return;

}

void CBEditorMain::setStatus(CBMapState state){
    switch(state){
    case CBMapState::Editing:
    case CBMapState::CloseMap:
         statusClose();
        break;
    case CBMapState::OpenMap:
    case CBMapState::Modified:
        statusOpenFile();
        break;
    case CBMapState::Saving:

    case CBMapState::Started:
            statusStartedEditor();
        break;

    }
}


void CBEditorMain::statusStartedEditor(void){
    this->ui->acSave->setDisabled(true);
    this->ui->acSaveAs->setDisabled(true);
    this->ui->acResizeGrid->setDisabled(true);
    this->ui->acCloseMap->setDisabled(true);

}

void CBEditorMain::statusOpenFile(void){
    this->ui->acSave->setEnabled(true);
    this->ui->acSaveAs->setEnabled(true);
    this->ui->acResizeGrid->setEnabled(true);
    this->ui->acCloseMap->setEnabled(true);
    this->ui->acEditShowGrid->setEnabled(true);
}

void CBEditorMain::statusClose(void){
    this->ui->acSave->setDisabled(true);
    this->ui->acSaveAs->setDisabled(true);
    this->ui->acResizeGrid->setDisabled(true);
    this->ui->acCloseMap->setDisabled(true);
    this->ui->acEditShowGrid->setDisabled(true);
}

void CBEditorMain::paintEvent(QPaintEvent *event){

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X; x++){
            QPixmap tile =  this->tilemap.copy();
           // tile.setp
          //  ui->gridGraphics->scene()->addPixmap()
        }
    }
}
