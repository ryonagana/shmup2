#pragma once

#include <iostream>
#include <allegro5/allegro.h>

class CDirectory {
private:
    ALLEGRO_FS_ENTRY *dir_entry;
    std::string path;

public:
    CDirectory(const std::string& folder);
    ALLEGRO_FS_ENTRY *getEntryDir();
    ALLEGRO_FS_ENTRY *getEntry();
    std::string getPath() const;
    ~CDirectory();

};
