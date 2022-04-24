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
    PurelinStatus status[5];
    status[0].bgSize = QSize(0, 0);
    status[0].bgColor = Qt::white;
    status[0].bgRadius = 20;
    status[0].useLine = 2;
    status[0].linePos[0] = QLine(30, 35, 70, 35);
    status[0].linePos[1] = QLine(75, 35, 75, 35);
    status[0].lineColors[0] = Qt::green;
    status[0].lineColors[1] = Qt::yellow;


    ui->pushButton->load(status[0]);
    qDebug() << "button load status";
}
