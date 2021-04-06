#ifndef MEDICALPANEL_H
#define MEDICALPANEL_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QDebug>
class medicalPanel : public QWidget
{
    Q_OBJECT
public:
    explicit medicalPanel(QWidget *parent = nullptr);
    ~medicalPanel();
    void paintEvent(QPaintEvent *event);
    void setBgColor(const QColor &color);
    void setFrColor(const QColor &color);
    void setSeColor(const QColor &color);
    void setThColor(const QColor &color);
    void setNeedleColor(const QColor &color);
    void setTipsText(const QString &text);
    void setUnitText(const QString &text);
    void setZhText(const QString &text);
    void setPixMap(const QPixmap &pix);
public slots:
    void slot_changeValue(int value);
signals:
private:
    void drawRing(QPainter *painter,int radius, int startAngle, int angleLength, int arcHeight,
                  QColor color,bool gradient=false);//最后一个参数表示是否启用渐变
    void drawText(QPainter *painter,QRectF rect,QString str,int size,QColor color);
    void drawBg(QPainter *painter,QColor color);
    int m_radius=100;
    int m_arcHeight=60;
    int m_value=100;
    QColor m_bgColor=QColor("#0B1517");
    QColor m_frColor=QColor("#121F24");
    QColor m_seColor=QColor("#2D5765");
    QColor m_thColor=QColor("#182B33");//还没走到的部分的颜色
    QColor m_needleColor=QColor("#366371");
    QString m_tipsText="PAULSE";
    QString m_unitText="BPM";
    QString m_zhText="心率";
    QPixmap pix;
};

#endif // MEDICALPANEL_H
