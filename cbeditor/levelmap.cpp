#include "levelmap.h"
#include <iostream>
LevelMap::LevelMap(QWidget *parent) : QWidget(parent)
{

}


char *LevelMap::toChar(QString qs){
    QByteArray bytes = qs.toLocal8Bit();
    return bytes.data();
}

bool LevelMap::loadMap(void){

    QFileDialog dlg(this);

    dlg.setFileMode(QFileDialog::ExistingFiles);
    dlg.setNameFilter("CB Maps (*.cbm)|All File (*.*)");
    dlg.setViewMode(QFileDialog::Detail);

    QStringList path;

    if( dlg.exec()){
        path = dlg.selectedFiles();
    }else if(path.size() == 0){
        return false;
    }

    QFile fmap(path[0]);
    QString filename = fmap.fileName();

    if(!LoadMapFromDisk(path[0])){
        return false;
    }

    return true;
}

bool LevelMap::LoadMapFromDisk(QString filepath){
    QFile fp(filepath);

    if(!fp.open(QIODevice::ReadOnly)) return false;
    char data;
    bool header_valid = false;

    this->mapname = fp.fileName();

    fp.read(mapData.magic, strlen("CBMAP"));
    fp.getChar(&data);
    mapData.ver = data;

     if(mapData.magic[0] == 'C' && mapData.magic[1] == 'B' && mapData.magic[2] == 'M' && mapData.magic[3] == 'A' && mapData.magic[4] == 'P'){
        header_valid = true;
     }else {
         QMessageBox(QMessageBox::Icon::Critical, "Error", "Invalid Header").exec();
         return false;
     }

     if(mapData.ver > MAP_VER){
         QMessageBox(QMessageBox::Icon::Critical, "Error", "Sorry this Map Version is incompatible or corrupt..").exec();
         return false;
     }

     fp.getChar(&data);

     mapData.player_pos.x = static_cast<unsigned char>(data);
     fp.getChar(&data);
     mapData.player_pos.x = static_cast<unsigned char>(data);


     for(unsigned int i = 0;i < 4; i++){
         char d;
         fp.getChar(&d);
         mapData.keys[i].x = static_cast<unsigned char>(d);
         fp.getChar(&d);
         mapData.keys[i].y = static_cast<unsigned char>(d);
     }

     fp.getChar(&data);
     mapData.map_width = static_cast<unsigned char>(data);
     fp.getChar(&data);
     mapData.map_height = static_cast<unsigned char>(data);

     if(mapData.map_width > MAX_GRID_X) mapData.map_width =  MAX_GRID_X;
     if(mapData.map_height > MAX_GRID_Y) mapData.map_width =  MAX_GRID_Y;

     fp.getChar(&data);
     mapData.background_id = static_cast<unsigned char>(data);

     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             char d;
             fp.getChar(&d);
             mapData.bg_layer[y][x].id = static_cast<unsigned char>(d);
             fp.getChar(&d);
             mapData.bg_layer[y][x].block = static_cast<unsigned char>(d);
             fp.getChar(&d);
             mapData.bg_layer[y][x].passable = static_cast<unsigned char>(d);
         }
     }

     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             char d;
             fp.getChar(&d);
             mapData.map_layer[y][x].id = static_cast<unsigned char>(d);
             fp.getChar(&d);
             mapData.map_layer[y][x].block = static_cast<unsigned char>(d);
             fp.getChar(&d);
             mapData.map_layer[y][x].passable = static_cast<unsigned char>(d);
         }
     }


     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){

             char d;
             fp.getChar(&d);
             mapData.obj_layer[y][x].id = static_cast<unsigned char>(d);
             fp.getChar(&d);
             mapData.obj_layer[y][x].block = static_cast<unsigned char>(d);
             fp.getChar(&d);
             mapData.obj_layer[y][x].passable = static_cast<unsigned char>(d);
         }
     }

     fp.getChar(&data);
     mapData.valid_file = static_cast<unsigned char>(data);
     fp.close();




    //QByteArray data = fp.readAll();




    return  header_valid;



}


QString LevelMap::getFileName(){
    return this->mapname;
}
