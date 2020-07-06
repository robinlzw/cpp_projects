//
// Created by cc on 2020/6/15.
//

#ifndef DOUTU_CELLWGT_H
#define DOUTU_CELLWGT_H

#include <QFrame>
#include <QDebug>
#include <QDrag>
#include <QMimeData>

class CellWgt : public QFrame {
    Q_OBJECT
public:
    explicit CellWgt(const QString& url, const QString& toolTip, QWidget* parent = nullptr);

Q_SIGNALS:
    void sgSetImage(const QString&);

protected:
    void paintEvent(QPaintEvent* e) override;
    void setCellImage(const QString&);
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override ;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    QMovie* _mov{};
    QString _path;

    bool    _press{};

	QDrag* m_dg{};
	QMimeData* m_md{};
};


#endif //DOUTU_CELLWGT_H
