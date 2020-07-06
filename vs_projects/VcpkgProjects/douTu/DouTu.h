#ifndef DOUTU_DOUTU_H
#define DOUTU_DOUTU_H

#include <vector>
#include <QtWidgets/QDialog>

class QTableWidget;
class DouTu : public QDialog
{
    Q_OBJECT

public:
    DouTu(QWidget *parent = Q_NULLPTR);

private:
	void initUi();
	void showEmoji(const QVector<QPair<QString, QString>>&);

private:
	QTableWidget *_wgt{};
	std::vector<QWidget*> _cells;
};


#endif //DOUTU_DOUTU_H

