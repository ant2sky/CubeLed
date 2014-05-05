#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QTextCursor>
#include "DataFormat.h"
#include "Communication.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore/QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

#define PACKAGE_HEAD_BUFFER_SIZE    256
#define PACKAGE_ELEMENT_BUFFER_SIZE 30720
#define PORT_WAITING_TIME   5000

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_button_reset_led_clicked();

    void on_button_add_element_clicked();

    void on_ledPackage_cursorPositionChanged();

    void on_button_clear_element_clicked();

    void on_button_del_element_clicked();

    void on_button_connect_to_device_clicked();

    void on_button_check_device_id_clicked();

    void on_button_send_package_clicked();

private:
    Ui::MainWindow *ui;

    QRadioButton *mLedStatusArray[LAYER_NUM][LED_NUM];

    char mPackageHeadBuff[PACKAGE_HEAD_BUFFER_SIZE];
    char mPackageElementBuff[PACKAGE_ELEMENT_BUFFER_SIZE];
    int mPackageElementIndex;
    int mPackageElementNum;

    QSerialPort devicePort;

    void InitCubeLedData();
    bool checkLedData();
    void clearLedStatus();
    void clearLedDuration();
    void clearPackageData();
    int numberOfLightLed();
    int addSingleLedElement();
    int addCubeLedElement();
    void setDuration(char *buffer, int value);
    void updatePackageData();
    void initialInternalData();
    QString hexToString(unsigned char hexData);
    void removeElement(int index);
    void dumpSerialPortInfo();
    bool getPortInfo(QString portName, QSerialPortInfo * portInfo);
    bool connectToPort(QSerialPortInfo portInfo);
    int receiveDataFromPort(char * dataBuff, int len);
    bool sendDataToPort(char * data, int len);


};

#endif // MAINWINDOW_H
