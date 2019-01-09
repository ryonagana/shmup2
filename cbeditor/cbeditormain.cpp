#include "cbeditormain.h"
#include "ui_cbeditormain.h"
#include "render.h"

CBEditorMain::CBEditorMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CBEditorMain)
{
    ui->setupUi(this);


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
}

void CBEditorMain::onActionClickLoadMap(){
    map.loadMap();
}
