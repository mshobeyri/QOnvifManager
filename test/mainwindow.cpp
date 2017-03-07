#include <QDebug>
#include <QMessageBox>

#include "mainwindow.hpp"
#include "qonvifdevice.hpp"
#include "qonvifmanager.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ionvifManager = new QOnvifManager("admin", "admin", this);
    connect(
        ionvifManager,
        &QOnvifManager::newDeviceFinded,
        this,
        &MainWindow::onNewDeviceFinded);
    on_btnRefresh_clicked();
}

MainWindow::~MainWindow() {
    delete ionvifManager;
    delete ui;
}

void
MainWindow::onNewDeviceFinded(QOnvifDevice* _device) {
    ui->cmbDevicesComboBox->addItem(
        _device->data()
            .probeData.deviceServiceAddress.replace("http://", "")
            .replace("/onvif/device_service", ""),
        _device->data().probeData.endPointAddress);
}

void
MainWindow::on_btnRefresh_clicked() {
    ui->btnRefresh->setEnabled(false);
    ui->cmbDevicesComboBox->clear();
    connect(
        ionvifManager,
        &QOnvifManager::deviceSearchingEnded,
        this,
        [this]() { ui->btnRefresh->setEnabled(true); },
        Qt::UniqueConnection);
    ionvifManager->refreshDevicesList();
}

void
MainWindow::on_cmbDevicesComboBox_currentIndexChanged(int index) {
    Q_UNUSED(index)
    //    on_btnRefreshData_clicked();
}

void
MainWindow::on_btnRefreshData_clicked() {
    ionvifManager->refreshDeviceCapabilities(currentDevice());
    ionvifManager->refreshDeviceInformations(currentDevice());
    ionvifManager->refreshDeviceVideoConfigs(currentDevice());
    ionvifManager->refreshDeviceProfiles(currentDevice());
    ionvifManager->refreshDeviceInterfaces(currentDevice());
    ionvifManager->refreshDeviceUsers(currentDevice());
    ionvifManager->refreshDeviceScopes(currentDevice());

    on_btnGetDataAndTime_clicked();
    QOnvifDevice* device = ionvifManager->device(currentDevice());

    Q_UNUSED(device)

    // <- add a breake point here to see device informations in debuger.
}

void
MainWindow::on_actionAbout_triggered() {
    QMessageBox aboutMessageBox(this);
    aboutMessageBox.setText(
        "developed by: Mehrdad Shobeyri \nemail: mehrdad.shobeyri@yahoo.com");
    aboutMessageBox.exec();
}

void
MainWindow::on_btnGetDataAndTime_clicked() {
    Data::DateTime dateAndTime =
        ionvifManager->deviceDateAndTime(currentDevice());
    ui->dateTimeEditLocal->setDateTime(dateAndTime.localTime);
    ui->dateTimeEditUtc->setDateTime(dateAndTime.utcTime);
}

void
MainWindow::on_btsSetDateAndTime_clicked() {
    ionvifManager->setDeviceDateAndTime(
        currentDevice(), ui->dateTimeEditSet->dateTime());
}

QString
MainWindow::currentDevice() {
    return ui->cmbDevicesComboBox->currentData().toString();
}

void
MainWindow::on_setUsernamePass_clicked() {
    ionvifManager->setDefaulUsernameAndPassword(
        ui->txtUserName->text(), ui->txtPassword->text());
    on_btnRefresh_clicked();
}
