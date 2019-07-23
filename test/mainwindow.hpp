#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QOnvifManager;

namespace Ui {
class MainWindow;
}
namespace device {
class QOnvifDevice;
}

using namespace device;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void onNewDeviceFinded(QOnvifDevice* _device);

    void on_btnRefresh_clicked();
    void on_cmbDevicesComboBox_currentIndexChanged(int index);
    void on_btnRefreshData_clicked();
    void on_actionAbout_triggered();
    void on_btnGetDataAndTime_clicked();
    void on_btsSetDateAndTime_clicked();
    void on_setUsernamePass_clicked();
    void on_btnSetScopes_clicked();
    void on_btngoHome_clicked();
    void on_btnsetHome_clicked();
    void on_btnrefreshPresents_clicked();
    void on_btnRight_pressed();
    void on_btnRight_released();


private:
    Ui::MainWindow* ui;
    QOnvifManager*  ionvifManager;
    QString         currentDevice();
};

#endif // MAINWINDOW_HPP
