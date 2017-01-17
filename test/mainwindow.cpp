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

    ionvifManager = new QOnvifManger("admin","",this);
    connect(ionvifManager,&QOnvifManger::newDeviceFinded,
            this,&MainWindow::onNewDeviceFinded);
    on_btnRefresh_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::onNewDeviceFinded(QOnvifDevice *_device)
{
    ui->cmbDevicesComboBox->addItem(
        _device->deviceProbeData().ideviceServiceAddress.replace("http://","").replace("/onvif/device_service",""),
        _device->deviceProbeData().iendPointAddress);
}

void
MainWindow::on_btnRefresh_clicked()
{
    ui->cmbDevicesComboBox->clear();
    ionvifManager->refreshDevicesList();
}

void
MainWindow::on_cmbDevicesComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
//    on_btnRefreshData_clicked();
}

void
MainWindow::on_btnRefreshData_clicked()
{
    ionvifManager->refreshDeviceCapabilities( currentDevice() );
    ionvifManager->refreshDeviceInformations( currentDevice() );
    on_btnGetDataAndTime_clicked();

    QOnvifDevice* device = ionvifManager->device(currentDevice() );
    Q_UNUSED(device)

    // <- add a breake point here to see device informations in debuger.
}

void
MainWindow::on_actionAbout_triggered()
{
    QMessageBox aboutMessageBox(this);
    aboutMessageBox.setText("developed by: Mehrdad Shobeyri \nemail: mehrdad.shobeyri@yahoo.com");
    aboutMessageBox.exec();
}

void
MainWindow::on_btnGetDataAndTime_clicked()
{
    QOnvifDevice::DateTime dateAndTime = ionvifManager->deviceDateAndTime( currentDevice() );
    ui->dateTimeEditLocal->setDateTime(dateAndTime.localTime);
    ui->dateTimeEditUtc->setDateTime(dateAndTime.utcTime);
}

void
MainWindow::on_btsSetDateAndTime_clicked()
{
    ionvifManager->setDeviceDateAndTime( currentDevice(), ui->dateTimeEditSet->dateTime() );
}

QString
MainWindow::currentDevice()
{
    return ui->cmbDevicesComboBox->currentData().toString();
}

void
MainWindow::on_setUsernamePass_clicked()
{
    ionvifManager->setDefaulUsernameAndPassword(ui->txtUserName->text(), ui->txtPassword->text());
    on_btnRefresh_clicked();
}
