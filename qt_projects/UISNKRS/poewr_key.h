#ifndef POEWR_KEY_H
#define POEWR_KEY_H

#include <QObject>
#include <QString>
#include <QCryptographicHash>
#include <Windows.h>
class Poewr_Key : public QObject
{
    Q_OBJECT

public:
    explicit Poewr_Key(QWidget *parent = 0);
    ~Poewr_Key();
    Q_INVOKABLE int checkSerialNumber(const QString serialNumber);

private:
    const QString get_SerialNumber();
    const QString hash_Encryption(const QString temp);
    const QString format_HASHString(const QString hashtemp);
    const QString remove_Format(const QString formathash);

private slots:
    void on_pushButton_read_clicked();
    void on_pushButton__clicked();
};

#endif // POEWR_KEY_H
