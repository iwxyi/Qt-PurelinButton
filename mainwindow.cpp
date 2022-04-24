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
    const int totalCount = 2;
    static int index = -1;

    PurelinStatus status[totalCount];
    int i = 0;
    status[i].bgSize = QSize(100, 60);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 30;
    status[i].useLine = 1;
    status[i].linePoss[0] = QLineF(30, 50, 70, 50);
    status[i].lineHide[0] = QPointF(50, 50);
    status[i].lineColors[0] =  QColor("#ed657d");

    i++;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 20;
    status[i].useLine = 2;
    status[i].linePoss[0] = QLineF(30, 40, 70, 40);
    status[i].linePoss[1] = QLineF(30, 60, 70, 60);
    status[i].lineHide[0] = QPointF(50, 40);
    status[i].lineHide[1] = QPointF(50, 60);
    status[i].lineColors[0] = Qt::green;
    status[i].lineColors[1] = Qt::yellow;



    if (++index >= totalCount)
        index = 0;
    ui->pushButton->load(status[index]);
}
