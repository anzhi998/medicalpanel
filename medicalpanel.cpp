#include "medicalpanel.h"
#include <QtMath>
#include <QImage>
medicalPanel::medicalPanel(QWidget *parent) : QWidget(parent)
{
    pix.load("://画板.svg");
}
medicalPanel::~medicalPanel()
{

}
void medicalPanel::paintEvent(QPaintEvent *event)
{
    //获取当前控件大小
    int height=this->height();
    int width=this->width();
    //根据控件大小确定绘画大小
    m_radius=height<width? height>>1:width>>1;
    //创建画家
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //把画家移动到屏幕中间，即改变坐标系，屏幕中间为原点
    painter.translate(width>>1,height>>1);
    //设定背景颜色
    //设定颜色透明度
    m_frColor.setAlpha(200);
    m_needleColor.setAlpha(255);
    drawRing(&painter, m_radius,-45,270,static_cast<int>( m_radius*0.6),  m_frColor);
    drawRing(&painter, static_cast<int>( m_radius*0.9),-45,270,static_cast<int>( m_radius*0.35),  m_seColor,true);
    drawRing(&painter,static_cast<int>( m_radius*0.9),-45,2*(135- m_value),static_cast<int>( m_radius*0.35), m_thColor);
    drawBg(&painter,m_bgColor);
    if( m_value>=3) drawRing(&painter,static_cast<int>( m_radius*0.9),2*(135- m_value)-45,5,static_cast<int>( m_radius*0.35), m_needleColor);


    //画字
    QRectF rectValue(static_cast<int>(- m_radius*0.3),static_cast<int>(- m_radius*0.3),static_cast<int>( m_radius*0.6),static_cast<int>( m_radius*0.6));
    QRectF rectUnit(static_cast<int>(- m_radius*0.2),m_radius*0.08,static_cast<int>( m_radius*0.4),static_cast<int>( m_radius*0.4));
    QRectF rectTips(static_cast<int>(- m_radius*0.2),-m_radius*0.45,static_cast<int>( m_radius*0.4),static_cast<int>( m_radius*0.4));
    QRectF rectZh(static_cast<int>(- m_radius*0.4),m_radius*0.35,static_cast<int>( m_radius*0.4),static_cast<int>( m_radius*0.4));
    drawText(&painter,rectValue,QString::number( m_value),static_cast<int>( m_radius*0.27),qRgb(255,255,255));
    drawText(&painter,rectUnit, m_unitText,static_cast<int>( m_radius*0.1),QColor("#4ACEAB"));
    drawText(&painter,rectTips, m_tipsText,static_cast<int>( m_radius*0.1),QColor("#56EFC6"));
    drawText(&painter,rectZh, m_zhText,static_cast<int>( m_radius*0.15),qRgb(255,255,255));

    //画图像
    painter.drawPixmap(0,m_radius*0.4,m_radius*0.35,m_radius*0.35,pix);
}
void medicalPanel::drawRing(QPainter *painter,int radius, int startAngle, int angleLength, int arcHeight, QColor color,bool gra)
{
    // 渐变色
    //QLinearGradient liner(0);
    if(gra==false)
    {
        QRadialGradient gradient(0, 0, radius);
        gradient.setColorAt(0, color);
        gradient.setColorAt(1.0, color);
        painter->setBrush(gradient);
    }
    else
    {
        QLinearGradient linear(-m_radius*0.9/sqrt(2),m_radius*0.9/sqrt(2),-m_radius*0.9/sqrt(2),-m_radius*0.9/sqrt(2));
        linear.setColorAt(0,QColor("#11262C"));
        linear.setColorAt(1,color);
        painter->setBrush(linear);
    }
    //创建一个矩形，前两个参数定义了左上角坐标，后两个参数是width和height
    //在屏幕中间设定一个正方形
    QRectF rect(-radius, -radius, radius << 1, radius << 1);
    //创建绘图形状
    QPainterPath path;
    //画一个占据指定矩形的弧
    path.arcTo(rect, startAngle, angleLength);
    QPainterPath subPath;
    //画一个完整的圆形
    //adjust函数返回一个新矩形，对于原矩形左上角偏移(x1,y1)，对于右下角偏移为(x2,y2)
    //这就使得archeight就是弧形的宽度
    subPath.addEllipse(rect.adjusted(arcHeight,arcHeight,-arcHeight,-arcHeight));
    // path为扇形 subPath为椭圆
    // 整合成复杂形状
    path -= subPath;
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
}
void medicalPanel::drawText(QPainter *painter,QRectF rect,QString str, int size, QColor color)
{
    //画字
    QFont num("Kaiti",size);
    painter->setFont(num);
    painter->setPen(color);
    painter->drawText(rect,Qt::AlignCenter,str);
}
void medicalPanel::drawBg(QPainter *painter, QColor color)
{
    QPointF center(0,0);
    QBrush brush(color);
    painter->setBrush(brush);
    //先画圆
    painter->drawEllipse(center,static_cast<int>( m_radius*0.4),static_cast<int>( m_radius*0.4));
    //再画个三角形
    static const QPointF points[3] = {
            center,
            QPointF(-m_radius/sqrt(2),m_radius/sqrt(2)),
            QPointF(m_radius/sqrt(2),m_radius/sqrt(2))
        };
    painter->drawPolygon(points,3);
}
//连接外部的槽函数
void medicalPanel::slot_changeValue(int val)
{
    m_value=val;
    repaint();
}
//设置颜色的外部访问函数
void medicalPanel::setBgColor(const QColor &color)
{
    m_bgColor=color;
}
void medicalPanel::setSeColor(const QColor &color)
{
    m_seColor=color;
}
void medicalPanel::setThColor(const QColor &color)
{
    m_thColor=color;
}
void medicalPanel::setNeedleColor(const QColor &color)
{
    m_needleColor=color;
}
void medicalPanel::setFrColor(const QColor &color)
{
    m_frColor=color;
}
void medicalPanel::setZhText(const QString &text)
{
    m_zhText=text;
}
void medicalPanel::setUnitText(const QString &text)
{
    m_unitText=text;
}
void medicalPanel::setTipsText(const QString &text)
{
    m_tipsText=text;
}
void medicalPanel::setPixMap(const QPixmap &map)
{
    pix=map;
}
