#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    const int totalCount = 8;
    static int index = -1;
    int dx = 0;

    // -
    PurelinStatus status[totalCount];
    int i = 0;
    status[i].bgSize = QSize(100, 60);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 30;
    status[i].useLine = 1;
    status[i].linePoss[0] = QLineF(35, 50, 65, 50);
    status[i].lineHide[0] = QPointF(50, 50);
    status[i].lineColors[0] =  QColor("#ed657d");

    // +
    i++;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 30;
    status[i].useLine = 2;
    status[i].linePoss[0] = QLineF(50, 35, 50, 65);
    status[i].linePoss[1] = QLineF(35, 50, 65, 50);
    status[i].lineHide[0] = QPointF(50, 50);
    status[i].lineHide[1] = QPointF(50, 50);
    status[i].lineColors[0] = QColor("#5baaf8");
    status[i].lineColors[1] = QColor("#5baaf8");

    // x
    i++;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 50;
    status[i].useLine = 2;
    status[i].linePoss[0] = QLineF(40, 40, 60, 60);
    status[i].linePoss[1] = QLineF(40, 60, 60, 40);
    status[i].lineHide[0] = QPointF(50, 50);
    status[i].lineHide[1] = QPointF(50, 50);
    status[i].lineColors[0] = QColor("#b9b9b9");
    status[i].lineColors[1] = QColor("#b9b9b9");

    // √
    i++;
    dx = -2;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 50;
    status[i].useLine = 2;
    status[i].linePoss[0] = QLineF(40 + dx, 50, 50 + dx, 60);
    status[i].linePoss[1] = QLineF(50 + dx, 60, 70 + dx, 40);
    status[i].lineHide[0] = QPointF(50 + dx, 50);
    status[i].lineHide[1] = QPointF(50 + dx, 50);
    status[i].lineColors[0] = QColor("#59ce84");
    status[i].lineColors[1] = QColor("#59ce84");

    // <
    i++;
    dx = -4;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 50;
    status[i].useLine = 2;
    status[i].linePoss[0] = QLineF(42 + dx, 50, 58 + dx, 35);
    status[i].linePoss[1] = QLineF(42 + dx, 50, 58 + dx, 65);
    status[i].lineHide[0] = QPointF(50, 50);
    status[i].lineHide[1] = QPointF(50, 50);
    status[i].lineColors[0] = QColor("#4b6fea");
    status[i].lineColors[1] = QColor("#4b6fea");

    // =
    i++;
    status[i].bgSize = QSize(100, 60);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 30;
    status[i].useLine = 2;
    status[i].linePoss[0] = QLineF(35, 45, 65, 45);
    status[i].linePoss[1] = QLineF(35, 55, 65, 55);
    status[i].lineHide[0] = QPointF(50, 45);
    status[i].lineHide[1] = QPointF(50, 55);
    status[i].lineColors[0] = QColor("#eda244");
    status[i].lineColors[1] = QColor("#eda244");

    // 三
    i++;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 20;
    status[i].useLine = 3;
    status[i].linePoss[0] = QLineF(34, 37, 66, 37);
    status[i].linePoss[1] = QLineF(40, 50, 60, 50);
    status[i].linePoss[2] = QLineF(46, 63, 54, 63);
    status[i].lineHide[0] = QPointF(50, 37);
    status[i].lineHide[1] = QPointF(50, 50);
    status[i].lineHide[2] = QPointF(50, 63);
    status[i].lineColors[0] = QColor("#7248e3");
    status[i].lineColors[1] = QColor("#7248e3");
    status[i].lineColors[2] = QColor("#7248e3");

    // ≡
    i++;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 20;
    status[i].useLine = 3;
    status[i].linePoss[0] = QLineF(35, 37, 65, 37);
    status[i].linePoss[1] = QLineF(35, 50, 55, 50);
    status[i].linePoss[2] = QLineF(35, 63, 60, 63);
    status[i].lineHide[0] = QPointF(35, 37);
    status[i].lineHide[1] = QPointF(35, 50);
    status[i].lineHide[2] = QPointF(35, 63);
    status[i].lineColors[0] = QColor("#424649");
    status[i].lineColors[1] = QColor("#424649");
    status[i].lineColors[2] = QColor("#424649");


    if (++index >= totalCount)
        index = 0;
    ui->pushButton->load(status[index]);
}
