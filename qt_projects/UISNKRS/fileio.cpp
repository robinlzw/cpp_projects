
#include "fileio.h"
#include <QFile>
FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

QStringList FileIO::read()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QStringList();
    }

    QFile file(mSource);
    QStringList fileContentList;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do {
            line = t.readLine();
            //fileContent += line;
            fileContentList.append(line);
         } while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QStringList();
    }
    return fileContentList;
}

bool FileIO::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}
