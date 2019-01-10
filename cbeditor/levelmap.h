#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "cbeditor_level.h"

class LevelMap : public QWidget
{
    Q_OBJECT
public:
    explicit LevelMap(QWidget *parent = nullptr);
    bool loadMap(void);
    char *toChar(QString qs);
    QString getFileName();
    bool LoadMapFromDisk(QString filepath);
    bool SaveToDisk(QString filepath);
private:

    QString mapname;
    LEVEL   mapData;
    int     width;
    int     height;
    QString path;


    void  level_default_values(LEVEL* level);



signals:

public slots:
};

#endif // LEVELMAP_H
