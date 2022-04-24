#ifndef PURELINBUTTON_H
#define PURELINBUTTON_H

#include <QPushButton>
#include <QList>

#define MAX_LINE_COUNT 3

struct PurelinStatus
{
    QSize bgSize;                       // 背景尺寸
    int bgRadius = 0;                   // 背景圆角
    QColor bgColor = Qt::white;         // 背景颜色
    int useLine = 2;                    // 使用的线条数量
    QLine linePos[MAX_LINE_COUNT];      // 各线条位置
    QColor lineColors[MAX_LINE_COUNT];  // 各线条颜色
};

class PurelinButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(double purelin_ani READ getPurelinAni WRITE setPurelinAni)
public:
    PurelinButton(QWidget* parent = nullptr);

    /// 加载显示状态
    void load(PurelinStatus status);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void setPurelinAni(double prog);
    double getPurelinAni() const;

private slots:
    void aniProgChanged(const QVariant& var);

private:
    bool animating = false;
    double animationProg = 0;

    PurelinStatus currentStatus;
    PurelinStatus prevStatus;
    PurelinStatus nextStatus;
};

#endif // PURELINBUTTON_H
