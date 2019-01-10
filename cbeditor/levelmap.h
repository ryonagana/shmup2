#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "level.h"

class LevelMap : public QWidget
{
    Q_OBJECT
public:
    explicit LevelMap(QWidget *parent = nullptr);
    bool loadMap(void);
    char *toChar(QString qs);
    QString getFileName();
private:

    QString mapname;
    LEVEL   mapData;
    int     width;
    int     height;
    QString path;


    bool LoadMapFromDisk(QString filepath);

signals:

public slots:
};

#endif // LEVELMAP_H
