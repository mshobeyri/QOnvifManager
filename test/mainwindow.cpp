#include <QDebug>
#include <QMessageBox>

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
    connect(ionvifManager,&QOnvifManger::newDeviceFinded,
            this,&MainWindow::onNewDeviceFinded);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewDeviceFinded(QOnvifDevice *_device)
{
    ui->cmbDevicesComboBox->addItem(
                _device->ideviceProbeData.ideviceServiceAddress.replace("http://","").replace("/onvif/device_service",""),
                _device->ideviceProbeData.iendPointAddress);
}

void MainWindow::on_btnRefresh_clicked()
{
    ionvifManager->refreshDevicesList();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox aboutMessageBox(this);
    aboutMessageBox.setText("developed by: Mehrdad Shobeyri \nemail: mehrdad.shobeyri@yahoo.com");
    aboutMessageBox.exec();
}
