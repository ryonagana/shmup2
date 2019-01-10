#include "cbeditormain.h"
#include "ui_cbeditormain.h"
#include "render.h"

CBEditorMain::CBEditorMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CBEditorMain)
{
    ui->setupUi(this);

    this->setWindowTitle("CB Editor ");

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
}

void CBEditorMain::onActionClickLoadMap(){
    if(map.loadMap()){
        this->setWindowTitle( this->windowTitle() + " - " + map.getFileName());
    }
}


void CBEditorMain::onActionClickAboutMe(){
    QMessageBox(QMessageBox::Icon::Information, "Me?", "I'm Nobody", QMessageBox::StandardButton::Ok).exec();
}
