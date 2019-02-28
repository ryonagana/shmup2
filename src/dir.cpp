#include "dir.h"
#include "path.h"

CDirectory::CDirectory() : CDirectory("map") {
    return;
}

void CDirectory::SetPath(const std::string& folder){
    char path[1024] = {};

    strncpy(path,  get_root_dir(), strlen(get_root_dir()) + 1);
    strncat(path, folder.c_str(), folder.size());

    this->dir_entry = al_create_fs_entry(path);
    this->path = path;
}

CDirectory::CDirectory(const std::string &folder){
    this->SetPath(folder);

}

std::string CDirectory::getPath() const
{
    return this->path;
}

ALLEGRO_FS_ENTRY *CDirectory::getEntryDir(){
    return al_read_directory(this->dir_entry);
}


ALLEGRO_FS_ENTRY *CDirectory::getEntry(){
    return this->dir_entry;
}


CDirectory::~CDirectory(){
    if(dir_entry) al_close_directory(this->dir_entry);
}
