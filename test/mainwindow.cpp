#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "qonvifmanger.hpp"
#include "qonvifdevice.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ionvifManager = new QOnvifManger("admin","admin",this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
