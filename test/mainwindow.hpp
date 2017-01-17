#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QOnvifManger;

namespace Ui {
class MainWindow;
}

class QOnvifDevice;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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

private:
    Ui::MainWindow *ui;
    QOnvifManger *ionvifManager;
    QString currentDevice();
};

#endif // MAINWINDOW_HPP
