#include "purelinbutton.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QPropertyAnimation>

PurelinButton::PurelinButton(QWidget *parent) : QPushButton(parent)
{

}

void PurelinButton::load(PurelinStatus status)
{
    prevStatus = currentStatus;
    nextStatus = status;

    QPropertyAnimation* ani = new QPropertyAnimation(this, "purelin_ani");
    ani->setStartValue(0.0);
    ani->setEndValue(1.0);
    ani->setDuration(500);
    connect(ani, &QPropertyAnimation::valueChanged, this, &PurelinButton::aniProgChanged);
    connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
    ani->start();
}

void PurelinButton::paintEvent(QPaintEvent *)
{
    // 获取当前数值
    QSize bgSize = currentStatus.bgSize;
    int bgRadius = currentStatus.bgRadius;
    QColor bgColor = currentStatus.bgColor;

    // 设置默认值与容错处理
    if (bgSize.isEmpty())
        bgSize = this->size();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;

    // 绘制背景
    path.addRoundedRect(0, 0, bgSize.width(), bgSize.height(), bgRadius, bgRadius);
    painter.fillPath(path, bgColor);

    // 绘制前景
}

void PurelinButton::setPurelinAni(double prog)
{
    this->animationProg = prog;
}

double PurelinButton::getPurelinAni() const
{
    return this->animationProg;
}

void PurelinButton::aniProgChanged(const QVariant &var)
{
    double prog = var.toDouble();
    currentStatus.bgRadius = int(currentStatus.bgRadius + prog * (nextStatus.bgRadius - currentStatus.bgRadius));
    update();
}
