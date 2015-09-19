#include "fileicons.h"
#include <QDir>
#include <QFileIconProvider>

FileIcons::FileIcons()
{
    extension = ".txt";
}

FileIcons::FileIcons(QString path)
{
    int ind = path.lastIndexOf(".");
    if(ind!=-1)
    {
        extension = path.mid(ind);
    }
    else
    {
        extension = ".txt";
    }
}

QIcon FileIcons::getIconForType(FileType type)
{
    QString path = getPathTempFile(type);
    QFileInfo finfo(path);
    QFileIconProvider ficon;
    QIcon icon = ficon.icon(finfo);
    return icon;
}

QIcon FileIcons::getIconForType(QString ext)
{
    QString path = getPathTempFile(ext);
    QFileInfo finfo(path);
    QFileIconProvider ficon;
    QIcon icon = ficon.icon(finfo);
    return icon;
}

QString FileIcons::getPathTempFile(FileType type)
{
    QString path = QDir::tempPath() + "/file.";
    switch(type)
    {
    case MSEXCEL:
        path +="xls";
        break;
    case HTML:
        path +="htm";
        break;
    case PDF:
        path +="pdf";
        break;
    case MSPOWERPOINT:
        path +="ppt";
        break;
    case TEXT:
        path +="txt";
        break;
    case MSWORD:
        path +="doc";
        break;
    }
    QFile file(path);
    file.open(QFile::WriteOnly);
    file.close();
    return path;
}
QString FileIcons::getPathTempFile(QString ext)
{
    QString path = QDir::tempPath() + "/file" + ext;
    QFile file(path);
    file.open(QFile::WriteOnly);
    file.close();
    return path;
}

QIcon  FileIcons::getStandardIconForType(QString ext)
{
    QString imageFile;
    ext = ext.toLower();
    ext = ext.replace("."," ").trimmed();
    if((ext=="doc")||(ext=="rtf"))
    {
        imageFile = "word.png";
    }
    else if(ext=="xls")
    {
        imageFile = "excel.png";
    }
    else if((ext=="mov")||(ext=="avi")||(ext=="mp4")||(ext=="mvi"))
    {
        imageFile = "video.png";
    }
    else if(ext=="txt")
    {
        imageFile = "txt_or_unkown.png";
    }
    else if(ext=="ppt")
    {
        imageFile = "powerpoint.png";
    }
    else if((ext=="wav")||(ext=="mp3")||(ext=="mid"))
    {
        imageFile = "music.png";
    }
    else if((ext=="ico")||(ext=="bmp")||(ext=="jpg")||(ext=="gif")||(ext=="png")||(ext=="ttf"))
    {
        imageFile = "image.png";
    }
    else if((ext=="htm")||(ext=="html")||(ext=="www"))
    {
        imageFile = "html.png";
    }
    else if((ext=="rar")||(ext=="zip"))
    {
        imageFile = "archive.png";
    }
    else if(ext=="pdf")
    {
        imageFile = "acrobat.png";
    }
    else
    {
        imageFile = "unknown.png";
    }
    QPixmap image("images/files/" + imageFile);
    QIcon icon = QIcon(image);
    return icon;
}
