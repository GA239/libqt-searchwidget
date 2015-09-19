#ifndef FILEICONS_H
#define FILEICONS_H
#include <QIcon>

enum FileType {HTML,PDF,MSWORD,MSEXCEL,MSPOWERPOINT,TEXT};

class FileIcons
{
    QString extension;
public:
    FileIcons();
    FileIcons(QString path);
    QIcon getIconForType(FileType type);
    QIcon getIconForType(QString ext);
    QIcon getStandardIconForType(QString ext);
    QString getPathTempFile(FileType type);
    QString getPathTempFile(QString ext);
    QString getExtension()
    {
        return extension;
    }
};

#endif // FILEICONS_H
