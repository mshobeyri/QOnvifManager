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
    on_btnRefresh_clicked();
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
    ui->cmbDevicesComboBox->clear();
    ionvifManager->refreshDevicesList();
}

void MainWindow::on_cmbDevicesComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
//    on_btnRefreshData_clicked();
    QMap<QString, QOnvifDevice*>  deviceMap = ionvifManager->devicesMap();

}

void MainWindow::on_btnRefreshData_clicked()
{
    ionvifManager->refreshDeviceCapabilities(ui->cmbDevicesComboBox->currentData().toString());
    ionvifManager->refreshDeviceInformations(ui->cmbDevicesComboBox->currentData().toString());
//    ionvifManager->device(ui->cmbDevicesComboBox->currentData());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox aboutMessageBox(this);
    aboutMessageBox.setText("developed by: Mehrdad Shobeyri \nemail: mehrdad.shobeyri@yahoo.com");
    aboutMessageBox.exec();
}

void MainWindow::on_btnGetDataAndTime_clicked()
{
    QOnvifDevice::DateTime dateAndTime = ionvifManager->deviceDateAndTime(ui->cmbDevicesComboBox->currentData().toString());
    ui->dateTimeEditLocal->setDateTime(dateAndTime.localTime);
    ui->dateTimeEditUtc->setDateTime(dateAndTime.utcTime);
}
