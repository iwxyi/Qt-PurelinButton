#ifndef PURELINBUTTON_H
#define PURELINBUTTON_H

#include <QPushButton>
#include <QList>

#define MAX_LINE_COUNT 3

struct PurelinStatus
{
    QSizeF bgSize;                       // 背景尺寸
    double bgRadius = 0;                 // 背景圆角
    QColor bgColor = Qt::white;          // 背景颜色
    int useLine = 0;                     // 使用的线条数量
    QLineF linePoss[MAX_LINE_COUNT];     // 各线条位置
    QPointF lineHide[MAX_LINE_COUNT];     // 默认消失的位置
    QColor lineColors[MAX_LINE_COUNT];   // 各线条颜色

    PurelinStatus(int useLine = 0) : useLine(useLine)
    {
        for (int i = useLine; i < MAX_LINE_COUNT; i++)
        {
            linePoss[i] = QLineF(0, 0, 0, 0);
            lineColors[i] = Qt::transparent;
        }
    }
};

class PurelinButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(double purelin_ani READ getPurelinAni WRITE setPurelinAni)
public:
    PurelinButton(QWidget* parent = nullptr);

    const PurelinStatus& getCurrentStatus() const;
    void setCurrentStatus(PurelinStatus status);

    /// 加载显示状态
    void load(PurelinStatus status);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void setPurelinAni(double prog);
    double getPurelinAni() const;

private slots:
    virtual void aniProgChanged(const QVariant& var);
    void aniProgFinished();

private:
    bool animating = false;
    double animationProg = 0;

    PurelinStatus currentStatus;
    PurelinStatus prevStatus;
    PurelinStatus nextStatus;
};

#endif // PURELINBUTTON_H
