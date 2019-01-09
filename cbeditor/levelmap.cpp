#include "levelmap.h"
#include <iostream>
LevelMap::LevelMap(QWidget *parent) : QWidget(parent)
{

}


char *LevelMap::toChar(QString qs){
    QByteArray bytes = qs.toLocal8Bit();
    return bytes.data();
}

void LevelMap::loadMap(void){

    QFileDialog dlg(this);

    dlg.setFileMode(QFileDialog::ExistingFiles);
    dlg.setNameFilter("CB Maps (*.cbm)|All File (*.*)");
    dlg.setViewMode(QFileDialog::Detail);

    QStringList path;

    if( dlg.exec()){
        path = dlg.selectedFiles();
    }

    QFile fmap(path[0]);
    QString filename = fmap.fileName();

    LoadMapFromDisk(path[0]);
    //level_load(NULL,&mapData, toChar(path[0]), false);



   // level_load(NULL, &mapData, filename.toStdString().c_str(), false);

    /*
    QString path = QFileDialog::getOpenFileName(this, tr("Load CB Map:"), "", "CB Maps (*.cbm);;All Files (*)");

    if(path.size() == 0){
           QMessageBox msgbox;
           msgbox.setText("Map Not Loaded, Sorry;;");
           msgbox.setInformativeText("Warning");
           msgbox.setStandardButtons(QMessageBox::Ok);
           msgbox.setDefaultButton(QMessageBox::Ok);

           if(msgbox.exec() == QMessageBox::Ok){
                return;
           }
    }


    std::cout << path.toStdString() << std::endl;
    */
}

bool LevelMap::LoadMapFromDisk(QString filepath){
    QFile fp(filepath);

    if(!fp.open(QIODevice::ReadOnly)) return false;


    fp.read(mapData.magic, 6);



    //QByteArray data = fp.readAll();




    return true;



}
