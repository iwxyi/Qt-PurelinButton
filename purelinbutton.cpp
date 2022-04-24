#include "purelinbutton.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QPropertyAnimation>

#define SET_BY_PROG(x) currentStatus.x = currentStatus.x + prog * (nextStatus.x - currentStatus.x)

PurelinButton::PurelinButton(QWidget *parent) : QPushButton(parent)
{

}

const PurelinStatus &PurelinButton::getCurrentStatus() const
{
    return currentStatus;
}

void PurelinButton::setCurrentStatus(PurelinStatus status)
{
    this->currentStatus = status;
}

void PurelinButton::load(PurelinStatus status)
{
    prevStatus = currentStatus;
    nextStatus = status;

    if (prevStatus.useLine < nextStatus.useLine)
    {
        for (int i = prevStatus.useLine; i < nextStatus.useLine; i++)
        {
            prevStatus.linePoss[i] = QLineF(nextStatus.lineHide[i], nextStatus.lineHide[i]);
            prevStatus.lineColors[i] = nextStatus.lineColors[i];
        }
    }
    else
    {
        for (int i = nextStatus.useLine; i < prevStatus.useLine; i++)
        {
            nextStatus.linePoss[i] = QLineF(prevStatus.lineHide[i], prevStatus.lineHide[i]);
            nextStatus.lineColors[i] = prevStatus.lineColors[i];
        }
    }
    if (prevStatus.bgSize.isEmpty())
        prevStatus.bgSize = this->size();
    if (nextStatus.bgSize.isEmpty())
        nextStatus.bgSize = this->size();

    QPropertyAnimation* ani = new QPropertyAnimation(this, "purelin_ani");
    ani->setStartValue(0.0);
    ani->setEndValue(1.0);
    ani->setDuration(500);
    connect(ani, &QPropertyAnimation::valueChanged, this, &PurelinButton::aniProgChanged);
    connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
    connect(ani, SIGNAL(finished()), this, SLOT(aniProgFinished()));
    ani->start();
}

void PurelinButton::paintEvent(QPaintEvent *)
{
    // 背景位置
    QSizeF bgSize = currentStatus.bgSize;
    if (bgSize.isEmpty())
        bgSize = this->size();
    double left = (this->width() - bgSize.width()) / 2;
    double top = (this->height() - bgSize.height()) / 2;
    QRectF rect(left, top, bgSize.width(), bgSize.height());

    // 绘制背景
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addRoundedRect(rect, currentStatus.bgRadius, currentStatus.bgRadius);
    painter.fillPath(path, currentStatus.bgColor);

    // 绘制前景
    const double penWidth = 3.0;
    for (int i = 0; i < currentStatus.useLine; i++)
    {
        const QLineF& line = currentStatus.linePoss[i];
        if ((line.length() < 1e-4))
            continue;

        painter.setPen(QPen(currentStatus.lineColors[i], penWidth, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(currentStatus.linePoss[i]);
    }
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
    // 可以重新这个方法，自定义尺寸
    // 比如，按照控件的百分比大小进行调整，而不是像素数值
    double prog = var.toDouble();

    currentStatus.bgRadius = prevStatus.bgRadius + prog * (nextStatus.bgRadius - prevStatus.bgRadius);
    currentStatus.bgSize = QSizeF(prevStatus.bgSize.width() + prog * (nextStatus.bgSize.width() - prevStatus.bgSize.width()),
                                 prevStatus.bgSize.height() + prog * (nextStatus.bgSize.height() - prevStatus.bgSize.height()));
    currentStatus.bgColor.setRgbF(
                prevStatus.bgColor.redF() + prog * (nextStatus.bgColor.redF() - prevStatus.bgColor.redF()),
                prevStatus.bgColor.greenF() + prog * (nextStatus.bgColor.greenF() - prevStatus.bgColor.greenF()),
                prevStatus.bgColor.blueF() + prog * (nextStatus.bgColor.blueF() - prevStatus.bgColor.blueF()),
                prevStatus.bgColor.alphaF() + prog * (nextStatus.bgColor.alphaF() - prevStatus.bgColor.alphaF()));
    int lineCount = qMax(prevStatus.useLine, nextStatus.useLine);
    currentStatus.useLine = lineCount;
    for (int i = 0; i < lineCount; i++)
    {
        currentStatus.linePoss[i].setLine(
                    prevStatus.linePoss[i].x1() + prog * (nextStatus.linePoss[i].x1() - prevStatus.linePoss[i].x1()),
                    prevStatus.linePoss[i].y1() + prog * (nextStatus.linePoss[i].y1() - prevStatus.linePoss[i].y1()),
                    prevStatus.linePoss[i].x2() + prog * (nextStatus.linePoss[i].x2() - prevStatus.linePoss[i].x2()),
                    prevStatus.linePoss[i].y2() + prog * (nextStatus.linePoss[i].y2() - prevStatus.linePoss[i].y2()));

        currentStatus.lineColors[i].setRgbF(
                    prevStatus.lineColors[i].redF() + prog * (nextStatus.lineColors[i].redF() - prevStatus.lineColors[i].redF()),
                    prevStatus.lineColors[i].greenF() + prog * (nextStatus.lineColors[i].greenF() - prevStatus.lineColors[i].greenF()),
                    prevStatus.lineColors[i].blueF() + prog * (nextStatus.lineColors[i].blueF() - prevStatus.lineColors[i].blueF()),
                    prevStatus.lineColors[i].alphaF() + prog * (nextStatus.lineColors[i].alphaF() - prevStatus.lineColors[i].alphaF()));
    }

    update();
}

void PurelinButton::aniProgFinished()
{
    currentStatus = nextStatus;
    animating = false;
    animationProg = 0;
}
