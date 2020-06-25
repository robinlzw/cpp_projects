#include "poewr_key.h"
#include <QDebug>
#include <QProcess>


/*
 * 生成序列号
 */
const QString Poewr_Key::get_SerialNumber()
{
    QString cpu_id = "";
    QProcess p(0);
    p.start("wmic CPU get ProcessorID");
    p.waitForStarted();
    p.waitForFinished();
    cpu_id = QString::fromLocal8Bit(p.readAllStandardOutput());
    cpu_id = cpu_id.remove("ProcessorId").trimmed();

    QString lpRootPathName = "C:\\";
    LPTSTR lpVolumeNameBuffer=new TCHAR[12];//磁盘卷标
    DWORD nVolumeNameSize=12;// 卷标的字符串长度
    DWORD VolumeSerialNumber;//硬盘序列号
    DWORD MaximumComponentLength;// 最大的文件长度
    LPTSTR lpFileSystemNameBuffer=new TCHAR[10];// 存储所在盘符的分区类型的长指针变量
    DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
    DWORD FileSystemFlags;// 文件系统的一此标志
    GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
                         lpVolumeNameBuffer, nVolumeNameSize,
                         &VolumeSerialNumber, &MaximumComponentLength,
                         &FileSystemFlags,
                         lpFileSystemNameBuffer, nFileSystemNameSize);
    return (cpu_id.mid(0,4) + "D-"+ cpu_id.mid(4,4) + "R-" +
            cpu_id.mid(8,4) + "E-" + cpu_id.mid(12,4) + "A-" +
            QString::number(VolumeSerialNumber,10).mid(0,4)+"M");
}
/*
 * MD5加密
 */
const QString Poewr_Key::hash_Encryption(const QString temp)
{
    QByteArray byte_array;
    byte_array.append(temp);
    QByteArray hash_byte_array = QCryptographicHash::hash(byte_array,QCryptographicHash::Md5);
    return hash_byte_array.toHex().toUpper();
}
/*
 * 格式化生成序列号
 */
const QString Poewr_Key::format_HASHString(const QString hashtemp)
{
    QString retemp = "";
    for(int i = 0; i < 7; i++)
    {
        retemp += hashtemp.mid(4*i,4) + "-";
    }
    retemp += hashtemp.mid(28,4);
    return retemp;
}
/*
 * 去除格式，还原MD5序列
 */
const QString Poewr_Key::remove_Format(const QString formathash)
{
    QString temp = "";
    for(int i = 0; i < 8; i++)
    {
        temp += formathash.mid(5*i,4);
    }
    return temp;
}

/*
 * 获取序列号槽函数
 */
void Poewr_Key::on_pushButton_read_clicked()
{
    //ui->lineEdit_serial->setText(format_HASHString(hash_Encryption(get_SerialNumber())));
}
/*
 * 生成密钥槽函数
 */
void Poewr_Key::on_pushButton__clicked()
{
    //ui->lineEdit_key->setText(remove_Format(ui->lineEdit_serial->text()));
}

int Poewr_Key::checkSerialNumber(const QString serialNumber)
{
    QString localSerialNumber = format_HASHString(hash_Encryption(get_SerialNumber()));
    if(localSerialNumber == serialNumber) {
        return 1;
    }
    return 0;
}
