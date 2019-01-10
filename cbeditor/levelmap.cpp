#include "levelmap.h"
#include <iostream>
LevelMap::LevelMap(QWidget *parent) : QWidget(parent)
{
    this->level_default_values(&mapData);

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

    fp.read(mapData.magic, sizeof(char) * strlen(MAP_ID));
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
     mapData.player_pos.y = static_cast<unsigned char>(data);


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
     if(mapData.map_height > MAX_GRID_Y) mapData.map_height =  MAX_GRID_Y;






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
bool LevelMap::SaveToDisk(QString filepath){
     QFile fp(filepath);

     if(!fp.open(QIODevice::WriteOnly)) return false;
     bool header_valid = false;

     this->mapname = fp.fileName();

     fp.write(MAP_ID, strlen(MAP_ID));
     fp.putChar( static_cast<char>(mapData.ver));
     fp.putChar(static_cast<char>(mapData.player_pos.x));
     fp.putChar(static_cast<char>(mapData.player_pos.y));


     for(unsigned int i = 0;i < 4; i++){
         fp.putChar(static_cast<char>(mapData.keys[i].x));
         fp.putChar(static_cast<char>(mapData.keys[i].y));
     }

     if(mapData.map_width < MAX_GRID_X){
        fp.putChar(static_cast<char>(mapData.map_width));
     }else {
         fp.putChar(static_cast<char>(MAX_GRID_X));
     }

     if(mapData.map_width < MAX_GRID_Y){
       fp.putChar(static_cast<char>(mapData.map_height));
     }else {
       fp.putChar(static_cast<char>(MAX_GRID_Y));
     }

     fp.putChar(static_cast<char>( mapData.background_id));


     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             fp.putChar(static_cast<char>(mapData.bg_layer[y][x].id));
             fp.putChar(static_cast<char>(mapData.bg_layer[y][x].block));
             fp.putChar(static_cast<char>(mapData.bg_layer[y][x].passable));
         }
     }

     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             fp.putChar(static_cast<char>(mapData.map_layer[y][x].id));
             fp.putChar(static_cast<char>(mapData.map_layer[y][x].block));
             fp.putChar(static_cast<char>(mapData.map_layer[y][x].passable));
         }
     }


     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             fp.putChar(static_cast<char>(mapData.obj_layer[y][x].id));
             fp.putChar(static_cast<char>(mapData.obj_layer[y][x].block));
             fp.putChar(static_cast<char>(mapData.obj_layer[y][x].passable));
         }
     }


    fp.putChar(static_cast<char>(header_valid));
    fp.close();


     return true;
}


QString LevelMap::getFileName(){
    return this->mapname;


}



void  LevelMap::level_default_values(LEVEL* level){

    strncpy(level->magic, MAP_ID, 6);
    level->ver = MAP_VER;
    level->player_pos.x = 100;
    level->player_pos.y = 100;
    level->map_width = 75;
    level->map_height = 22;
    level->background_id = 0;
    level->valid_file = false;

    strncpy(level->mapname, "Mapa Teste", 19);

    for(unsigned int i = 0; i < 4; i++){
        level->keys[i].x = 25;
        level->keys[i].y = 25;
    }



    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->bg_layer[y][x].id = 0;
            level->bg_layer[y][x].block = false;
            level->bg_layer[y][x].passable = true;
        }
    }

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->map_layer[y][x].id = 0;
            level->map_layer[y][x].block = false;
            level->map_layer[y][x].passable = false;
        }
    }

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->obj_layer[y][x].id = 0;
            level->obj_layer[y][x].block = false;
            level->obj_layer[y][x].passable = true;
        }
    }

    level->powerup_count = 0;

}

