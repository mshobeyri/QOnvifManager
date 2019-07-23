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
        &QOnvifManager::newDeviceFound,
        this,
        &MainWindow::onNewDeviceFinded);


    connect(
        ionvifManager,
        &QOnvifManager::deviceDateAndTimeReceived,
        this,
        [this](Data::DateTime _dataAndTime) {
            ui->dateTimeEditLocal->setDateTime(_dataAndTime.localTime);
            ui->dateTimeEditUtc->setDateTime(_dataAndTime.utcTime);
        });

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
    ui->txtLocation->setText("");
    ui->txtName->setText("");

    ionvifManager->getDeviceCapabilities(currentDevice());
    ionvifManager->getDeviceInformation(currentDevice());
    ionvifManager->getDeviceProfiles(currentDevice());
    ionvifManager->getDeviceImageSettingOptions(currentDevice());
    ionvifManager->getDeviceImageSetting(currentDevice());
    ionvifManager->getDeviceVideoEncoderConfigurations(currentDevice());
    ionvifManager->getDeviceVideoEncoderConfigurationOptions(currentDevice());
    ionvifManager->getDeviceStreamUris(currentDevice());
    ionvifManager->getDeviceUsers(currentDevice());
    ionvifManager->getDeviceScopes(currentDevice());
    ionvifManager->getDeviceNetworkInterfaces(currentDevice());
    ionvifManager->getDeviceNetworkDNS(currentDevice());
    ionvifManager->getDeviceNetworkDefaultGateway(currentDevice());
    ionvifManager->getDeviceNetworkDiscoveryMode(currentDevice());
    ionvifManager->getDeviceNetworkHostname(currentDevice());
    ionvifManager->getDeviceNetworkNTP(currentDevice());
    ionvifManager->getDevicePtzConfiguration(currentDevice());

    // setScopes
    //    ui->txtLocation->setText(
    //        ionvifManager->device(currentDevice())->data().scopes.location);
    //    ui->txtName->setText(
    //        ionvifManager->device(currentDevice())->data().scopes.name);
    //    ui->txtHardware->setText(
    //        ionvifManager->device(currentDevice())->data().scopes.hardware);

    //    on_btnGetDataAndTime_clicked();

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
    ionvifManager->getDeviceDateAndTime(currentDevice());
}

void
MainWindow::on_btsSetDateAndTime_clicked() {
    ionvifManager->setDeviceDateAndTime(
        currentDevice(),
        ui->dateTimeEditSet->dateTime(),
        "GMT-3:30",
        true,
        false);
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

void
MainWindow::on_btnSetScopes_clicked() {
    ionvifManager->setDeviceScopes(
        currentDevice(), ui->txtName->text(), ui->txtLocation->text());
}

void
MainWindow::on_btngoHome_clicked() {
    ionvifManager->device(currentDevice())->goHomePosition();
}

void
MainWindow::on_btnsetHome_clicked() {
    ionvifManager->device(currentDevice())->setHomePosition();
}

void
MainWindow::on_btnrefreshPresents_clicked() {
    ionvifManager->device(currentDevice())->getPresets();
}

void
MainWindow::on_btnRight_pressed() {
    ionvifManager->device(currentDevice())->continuousMove(0.5, 0, 0);
}

void
MainWindow::on_btnRight_released() {
    ionvifManager->device(currentDevice())->stopMovement();
}
