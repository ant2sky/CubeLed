#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitCubeLedData();

    dumpSerialPortInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->ledDuration->setText(QString::number(value));
}

void MainWindow::InitCubeLedData()
{
    mLedStatusArray[0][0] = ui->led_1x1x1;
    mLedStatusArray[0][1] = ui->led_1x1x2;
    mLedStatusArray[0][2] = ui->led_1x1x3;
    mLedStatusArray[0][3] = ui->led_1x1x4;
    mLedStatusArray[0][4] = ui->led_1x2x1;
    mLedStatusArray[0][5] = ui->led_1x2x2;
    mLedStatusArray[0][6] = ui->led_1x2x3;
    mLedStatusArray[0][7] = ui->led_1x2x4;
    mLedStatusArray[0][8] = ui->led_1x3x1;
    mLedStatusArray[0][9] = ui->led_1x3x2;
    mLedStatusArray[0][10] = ui->led_1x3x3;
    mLedStatusArray[0][11] = ui->led_1x3x4;
    mLedStatusArray[0][12] = ui->led_1x4x1;
    mLedStatusArray[0][13] = ui->led_1x4x2;
    mLedStatusArray[0][14] = ui->led_1x4x3;
    mLedStatusArray[0][15] = ui->led_1x4x4;

    mLedStatusArray[1][0] = ui->led_2x1x1;
    mLedStatusArray[1][1] = ui->led_2x1x2;
    mLedStatusArray[1][2] = ui->led_2x1x3;
    mLedStatusArray[1][3] = ui->led_2x1x4;
    mLedStatusArray[1][4] = ui->led_2x2x1;
    mLedStatusArray[1][5] = ui->led_2x2x2;
    mLedStatusArray[1][6] = ui->led_2x2x3;
    mLedStatusArray[1][7] = ui->led_2x2x4;
    mLedStatusArray[1][8] = ui->led_2x3x1;
    mLedStatusArray[1][9] = ui->led_2x3x2;
    mLedStatusArray[1][10] = ui->led_2x3x3;
    mLedStatusArray[1][11] = ui->led_2x3x4;
    mLedStatusArray[1][12] = ui->led_2x4x1;
    mLedStatusArray[1][13] = ui->led_2x4x2;
    mLedStatusArray[1][14] = ui->led_2x4x3;
    mLedStatusArray[1][15] = ui->led_2x4x4;

    mLedStatusArray[2][0] = ui->led_3x1x1;
    mLedStatusArray[2][1] = ui->led_3x1x2;
    mLedStatusArray[2][2] = ui->led_3x1x3;
    mLedStatusArray[2][3] = ui->led_3x1x4;
    mLedStatusArray[2][4] = ui->led_3x2x1;
    mLedStatusArray[2][5] = ui->led_3x2x2;
    mLedStatusArray[2][6] = ui->led_3x2x3;
    mLedStatusArray[2][7] = ui->led_3x2x4;
    mLedStatusArray[2][8] = ui->led_3x3x1;
    mLedStatusArray[2][9] = ui->led_3x3x2;
    mLedStatusArray[2][10] = ui->led_3x3x3;
    mLedStatusArray[2][11] = ui->led_3x3x4;
    mLedStatusArray[2][12] = ui->led_3x4x1;
    mLedStatusArray[2][13] = ui->led_3x4x2;
    mLedStatusArray[2][14] = ui->led_3x4x3;
    mLedStatusArray[2][15] = ui->led_3x4x4;

    mLedStatusArray[3][0] = ui->led_4x1x1;
    mLedStatusArray[3][1] = ui->led_4x1x2;
    mLedStatusArray[3][2] = ui->led_4x1x3;
    mLedStatusArray[3][3] = ui->led_4x1x4;
    mLedStatusArray[3][4] = ui->led_4x2x1;
    mLedStatusArray[3][5] = ui->led_4x2x2;
    mLedStatusArray[3][6] = ui->led_4x2x3;
    mLedStatusArray[3][7] = ui->led_4x2x4;
    mLedStatusArray[3][8] = ui->led_4x3x1;
    mLedStatusArray[3][9] = ui->led_4x3x2;
    mLedStatusArray[3][10] = ui->led_4x3x3;
    mLedStatusArray[3][11] = ui->led_4x3x4;
    mLedStatusArray[3][12] = ui->led_4x4x1;
    mLedStatusArray[3][13] = ui->led_4x4x2;
    mLedStatusArray[3][14] = ui->led_4x4x3;
    mLedStatusArray[3][15] = ui->led_4x4x4;

    // Initial internal data
    initialInternalData();

}

void MainWindow::dumpSerialPortInfo()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name   :" << info.portName();
        qDebug() << "Description:" << info.description();
        qDebug() << "Manufacturer:" << info.manufacturer();

        this->ui->port_selection->addItem(info.portName());
    }
}

bool MainWindow::getPortInfo(QString portName, QSerialPortInfo *portInfo){
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(portName.compare(info.portName()) == 0)
        {
            * portInfo = info;
            return true;
        }
    }

    return false;
}

void MainWindow::initialInternalData()
{
    mPackageElementIndex = 0;
    mPackageElementNum = 0;
    memset(mPackageElementBuff, 0, PACKAGE_ELEMENT_BUFFER_SIZE);
    memset(mPackageHeadBuff, 0, PACKAGE_HEAD_BUFFER_SIZE);

}

void MainWindow::on_button_reset_led_clicked()
{
    // Clear LED status
    clearLedStatus();

    // Clear package data
    clearPackageData();

    // Clear led duration
    clearLedDuration();

    // Initial internal data
    initialInternalData();
}

void MainWindow::on_button_add_element_clicked()
{
    int ledNumber = numberOfLightLed();
    int elementSize = 0;

    // Check if the led status data is available
    if(!checkLedData())
        return;

    // Create package head if the head index is 0
    if(mPackageElementNum == 0)
    {
        // Add head tag
        mPackageHeadBuff[PACKAGE_HEAD_POS] = PACKAGE_HEAD_START;
        // Initial element number in package head
        mPackageHeadBuff[PACKAGE_HEAD_NUM_POS] = 0;
    }

    if(ledNumber > 8)
        elementSize = addCubeLedElement();
    else
        elementSize = addSingleLedElement();

    // update element head
    if(elementSize > 0)
    {
        if(mPackageElementNum == 0)
        {
            mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS] = PACKAGE_HEAD_OFFSET_POS + 1;
        }
        else
        {
            int offsetCount = 0;

            mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS] += 1;

            for(int index = 0; index < mPackageElementNum; index++)
            {
                offsetCount += mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS + index];
            }
            mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS + mPackageElementNum] =
                    mPackageElementIndex + mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS] - elementSize - offsetCount;
        }

        mPackageElementNum++;

        mPackageHeadBuff[PACKAGE_HEAD_NUM_POS] = mPackageElementNum;

    }

    updatePackageData();
}

void MainWindow::updatePackageData()
{
    QString packageData;

    this->ui->ledPackage->clear();

    if(mPackageElementNum <= 0)
        return;

    // update package head
    packageData.append(QString("%1, %2, ")
                       .arg(hexToString((unsigned char)mPackageHeadBuff[PACKAGE_HEAD_POS]))
                       .arg(hexToString((unsigned char)mPackageHeadBuff[PACKAGE_HEAD_NUM_POS])));
    for(int index = 0; index < mPackageElementNum; index++)
    {
        packageData.append(QString("%1, ").arg(hexToString((unsigned char)mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS + index])));
    }

    // update element data
    for(int index = 0; index < mPackageElementIndex; index++)
    {
        if((unsigned char)mPackageElementBuff[index] == PACKAGE_ELEMENT_START)
            packageData.append("\n");
        packageData.append(QString("%1, ").arg(hexToString((unsigned char)mPackageElementBuff[index])));
    }

    this->ui->ledPackage->append(packageData);

}

QString MainWindow::hexToString(unsigned char hexData)
{
    if(hexData < 0x10)
        return QString("0x0%1").arg(QString::number((unsigned char)hexData, 16).toUpper());
    else
        return QString("0x%1").arg(QString::number((unsigned char)hexData, 16).toUpper());

}

int MainWindow::addSingleLedElement()
{
    int layerIndex = 0, ledIndex = 0;
    int ledCount = 0;
    int elementBuffIndex = mPackageElementIndex;

    elementBuffIndex += (PACKAGE_DATA_POS + 1);

    // check all led status
    for (layerIndex = 0; layerIndex < LAYER_NUM; layerIndex++)
    {
        for (ledIndex = 0; ledIndex < LED_NUM; ledIndex++)
        {
            // check if the led status is on
            if(this->mLedStatusArray[layerIndex][ledIndex]->isChecked())
            {
                // add led number to element buffer
                mPackageElementBuff[elementBuffIndex++] = ((1 << layerIndex) << PACKAGE_TAG_SINGLE_LAYER_POS) | ledIndex;
                ledCount++;
            }
        }
    }

    elementBuffIndex = mPackageElementIndex;

    // set element start tag
     mPackageElementBuff[mPackageElementIndex++] = PACKAGE_ELEMENT_START;

    // set element tag
    mPackageElementBuff[mPackageElementIndex++] = TAG_SINGLE_LED;

    // set duration
    setDuration(&mPackageElementBuff[mPackageElementIndex], this->ui->horizontalSlider->value());
    mPackageElementIndex += PACKAGE_TIME_SIZE;

    // set led number
    mPackageElementBuff[mPackageElementIndex++] = ledCount;

    // shift package element index, because led data had saved to buffer
    mPackageElementIndex += ledCount;

    // return element size
    return mPackageElementIndex - elementBuffIndex;
}

void MainWindow::setDuration(char *buffer, int value)
{
    *(buffer) = (value & 0xFF00) >> 8;
    *(buffer + 1) = value & 0x00FF;
}

int MainWindow::addCubeLedElement()
{
    int layerIndex = 0, ledIndex = 0;
    int elementBuffIndex = mPackageElementIndex;
    unsigned char ledStatusTempBuff[PACKAGE_TAG_CUBE_SIZE];

    memset(ledStatusTempBuff, 0, PACKAGE_TAG_CUBE_SIZE);

    // check all led status
    for (layerIndex = 0; layerIndex < LAYER_NUM; layerIndex++)
    {
        for (ledIndex = 0; ledIndex < LED_NUM; ledIndex++)
        {
            // check if the led status is on
            if(this->mLedStatusArray[layerIndex][ledIndex]->isChecked())
            {
                // add led number to element buffer
                ledStatusTempBuff[(layerIndex << 1) + (ledIndex >> 3)] |= 1 << (ledIndex & 0x07);
            }
        }
    }

    // set element start tag
     mPackageElementBuff[mPackageElementIndex++] = PACKAGE_ELEMENT_START;

    // set element tag
    mPackageElementBuff[mPackageElementIndex++] = TAG_CUBE_LED;

    // set duration
    setDuration(&mPackageElementBuff[mPackageElementIndex], this->ui->horizontalSlider->value());
    mPackageElementIndex += PACKAGE_TIME_SIZE;

    // set led data
    memcpy(&mPackageElementBuff[mPackageElementIndex], ledStatusTempBuff, PACKAGE_TAG_CUBE_SIZE);

    // shift package element index, because led data had saved to buffer
    mPackageElementIndex += PACKAGE_TAG_CUBE_SIZE;

    // return element size
    return mPackageElementIndex - elementBuffIndex;

}

int MainWindow::numberOfLightLed()
{
    int layerIndex = 0, ledIndex = 0;
    int count = 0;

    for (layerIndex = 0; layerIndex < LAYER_NUM; layerIndex++)
    {
        for (ledIndex = 0; ledIndex < LED_NUM; ledIndex++)
        {
            if(this->mLedStatusArray[layerIndex][ledIndex]->isChecked())
                count++;
        }
    }

    return count;
}

bool MainWindow::checkLedData()
{
    bool isAvailable = false;

    // check time
    if(ui->horizontalSlider->value() > 0)
        isAvailable = true;

    return isAvailable;
}

void MainWindow::clearLedStatus()
{
    int layerIndex = 0, ledIndex = 0;
    // Clear LED status
    for (layerIndex = 0; layerIndex < LAYER_NUM; layerIndex++)
    {
        for (ledIndex = 0; ledIndex < LED_NUM; ledIndex++)
        {
            this->mLedStatusArray[layerIndex][ledIndex]->setChecked(false);
        }
    }

}

void MainWindow::clearLedDuration()
{
    ui->horizontalSlider->setValue(0);
}

void MainWindow::clearPackageData()
{
    ui->ledPackage->clear();
}

void MainWindow::on_ledPackage_cursorPositionChanged()
{
//    qDebug("Number: %d", this->ui->ledPackage->textCursor().blockNumber());

}

void MainWindow::on_button_clear_element_clicked()
{
    // Clear LED status
    clearLedStatus();

    // Clear led duration
    clearLedDuration();
}

void MainWindow::on_button_del_element_clicked()
{
    if(mPackageElementNum <= 0)
        return;

    removeElement(mPackageElementNum);
}

void MainWindow::removeElement(int index)
{
    int newPackageElementIndex = 0;

    for(int elementIndex = 1; elementIndex < mPackageElementNum; elementIndex++)
    {
        newPackageElementIndex += ((unsigned char)mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS + elementIndex]);
    }

     mPackageHeadBuff[PACKAGE_HEAD_OFFSET_POS] -= 1;
     mPackageElementNum--;

     mPackageHeadBuff[PACKAGE_HEAD_NUM_POS] = mPackageElementNum;

     mPackageElementIndex = newPackageElementIndex;

     updatePackageData();
}

void MainWindow::on_button_connect_to_device_clicked()
{
    QSerialPortInfo portInfo;
    QString selectedPortName = ui->port_selection->currentText();
    char data[10];
    char response[10];

    if(!getPortInfo(selectedPortName, &portInfo))
    {
         qDebug() << "Get Port Information failed.";

         return;
    }

    if(selectedPortName.compare(devicePort.portName()) != 0)
    {
        if(!connectToPort(portInfo))
        {
            qDebug() << "Connect to port failed.";
            return;
        }
    }

    data[0] = 0x55;
    qDebug() << "Connect to Name   :" << portInfo.portName();
    qDebug() << "Connect to Description:" << portInfo.description();
    qDebug() << "Connect to Manufacturer:" << portInfo.manufacturer();
    if(sendDataToPort(data, 1))
    {
        if(receiveDataFromPort(response, 1) == 1)
        {
            //qDebug() << "Got data length " << devicePort.read(response,1);
            if(data[0] == response[0])
            {
                qDebug() << "Connect to Device...";
            }
            else
            {
                qDebug() << "Receiving failed";
            }
        }
    }

}

bool MainWindow::connectToPort(QSerialPortInfo portInfo)
{
    if(devicePort.isOpen())
        devicePort.close();

    devicePort.setPort(portInfo);

    if(!devicePort.open(QIODevice::ReadWrite))
    {
        qDebug() << tr("Can't open port %1, error code %2")
                    .arg(devicePort.portName()).arg(devicePort.error());
        return false;

    }

    if (!devicePort.setBaudRate(QSerialPort::Baud115200)) {
        qDebug() << tr("Can't set baud rate 115200 baud to port %1, error code %2")
                    .arg(devicePort.portName()).arg(devicePort.error());
        return false;
    }

    if (!devicePort.setDataBits(QSerialPort::Data8)) {
        qDebug() << tr("Can't set 8 data bits to port %1, error code %2")
                    .arg(devicePort.portName()).arg(devicePort.error());
        return false;
    }

    if (!devicePort.setParity(QSerialPort::NoParity)) {
        qDebug() << tr("Can't set no patity to port %1, error code %2")
                    .arg(devicePort.portName()).arg(devicePort.error());
        return false;
    }

    if (!devicePort.setStopBits(QSerialPort::OneStop)) {
        qDebug() << tr("Can't set 1 stop bit to port %1, error code %2")
                    .arg(devicePort.portName()).arg(devicePort.error());
        return false;
    }

    if (!devicePort.setFlowControl(QSerialPort::NoFlowControl)) {
        qDebug() << tr("Can't set no flow control to port %1, error code %2")
                   .arg(devicePort.portName()).arg(devicePort.error());
        return false;
    }

    return true;
}

bool MainWindow::sendDataToPort(char * data, int len)
{
    if(!devicePort.isOpen())
        return false;

    for(int index = 0; index < len; index++)
    {
        devicePort.write(data + index, 1);
        devicePort.flush();
        if(!devicePort.waitForBytesWritten(PORT_WAITING_TIME))
        {
            qDebug() << "Sending failed";
            return false;
        }

    }
    qDebug() << "Send to Device...";

    return true;
}

int MainWindow::receiveDataFromPort(char * dataBuff, int len)
{
    int count = 0;

    if(!devicePort.isOpen())
        return count;

//    for(count = 0; count < len; count++)
//    {
        if(devicePort.waitForReadyRead(PORT_WAITING_TIME))
        {
            QByteArray getData;

            //count = devicePort.read(dataBuff, len);
            getData = devicePort.readAll();
            count = getData.size();
            memcpy(dataBuff, getData.data(), count);
        }
//    }

    qDebug() << "Got data length " << count << "Expect " << len;

    switch(count)
    {
    case 1:
        qDebug() << "Get " << hexToString(dataBuff[0]);
        break;
    case 2:
        qDebug() << "Get " << hexToString(dataBuff[0])
                 << " " << hexToString(dataBuff[1]);
        break;
    case 3:
        qDebug() << "Get " << hexToString(dataBuff[0])
                 << " " << hexToString(dataBuff[1])
                 << " " << hexToString(dataBuff[2]);
        break;
    default:
         qDebug() << "Receiving failed";
    }

    return count;
}

void MainWindow::on_button_check_device_id_clicked()
{
    char data[10];
    char response[10];

    data[0] = COM_TAG_CHECK_DEVICE;
    if(sendDataToPort(data, 1))
    {
        if(receiveDataFromPort(response, 2) == 2)
        {
            if(data[0] == response[0])
            {
                qDebug() << "Receive from Device...";

                ui->deviceStatus->append(QString("Device Index is %1 ").arg(hexToString((unsigned char)response[1])));

            }
            else
            {
                qDebug() << "Fail to Receive from Device ...";
            }
        }
    }

}

void MainWindow::on_button_send_package_clicked()
{
    int responseSize = 0;
    int retry = 5;
    char data[10];
    char response[10];
    unsigned char checksum = 0;
    int dataSize = 2 + mPackageElementNum + mPackageElementIndex;

    // Send package size to device
    data[0] = COM_TAG_CHECK_TO_SEND;
    data[1] = dataSize & 0x00FF;
    data[2] = (dataSize & 0xFF00) >> 8;
    if(sendDataToPort(data, 3))
    {
        if(receiveDataFromPort(response, 3) == 3)
        {
            // Check if the response equal the package size
            if(memcmp(data, response, 3) != 0)
            {
                qDebug() << "Error...";

                return;
            }
        }
        else
            return;
    }
    else
        return;

    // Send package to device
    data[0] = COM_TAG_SEND_DATA;
    if(!sendDataToPort(data,1))
        return;

    // Calculate checksum
    for(int index = 0; index < (2 + mPackageElementNum); index++)
        checksum += (unsigned char)mPackageHeadBuff[index];
    for(int index = 0; index < mPackageElementIndex; index++)
        checksum += (unsigned char)mPackageElementBuff[index];


    // Send head
    if(!sendDataToPort(mPackageHeadBuff, (2 + mPackageElementNum)))
        return;

    // Send element
    if(!sendDataToPort(mPackageElementBuff, mPackageElementIndex))
        return;

    // Send checksum
    data[0] = checksum;
    if(!sendDataToPort(data,1))
        return;

    do
    {
        responseSize = receiveDataFromPort(response, 3);
        retry--;
        if(retry < 0)
            break;
    } while(responseSize == 0);

    if(responseSize == 3)
    {
        // Check if the response equal the package size
        data[0] = COM_TAG_SEND_DATA;
        data[1] = dataSize & 0x00FF;
        data[2] = (dataSize & 0xFF00) >> 8;

        if(memcmp(data, response, 3) == 0)
        {
            qDebug() << "Send Package Done...";
        }
    }
    else if(responseSize == 2)
    {
        qDebug() << tr("Send Package Error %1, error code %2")
                    .arg(hexToString(response[0])).arg(hexToString(response[1]));
    }
    else
    {
        qDebug() << "Send Package Error...";
    }

}
