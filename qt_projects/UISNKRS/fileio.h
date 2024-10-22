#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QTextStream>
#include <QFile>
class FileIO : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString source
               READ source
               WRITE setSource
               NOTIFY sourceChanged)
    explicit FileIO(QObject *parent = 0);

    Q_INVOKABLE QStringList read();
    Q_INVOKABLE bool write(const QString& data);

    QString source() { return mSource; };

public slots:
    void setSource(const QString& source) { mSource = source; };

signals:
    void sourceChanged(const QString& source);
    void error(const QString& msg);

private:
    QString mSource;
};

#endif // FILEIO_H
