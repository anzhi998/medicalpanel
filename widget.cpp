#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color:#0B1517");
}

Widget::~Widget()
{
    delete ui;
}

