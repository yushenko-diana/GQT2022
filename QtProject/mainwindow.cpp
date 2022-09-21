#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtBluetooth>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    discoveryAgent->start();


    ui->actList->addItem("ОТКРЫТЬ КИСТЬ");
    ui->actList->addItem("КОНЧИКОВЫЙ ЗАХВАТ");
    ui->actList->addItem("ЦИЛИНДРИЧЕСКИЙ ЗАХВАТ");
    ui->actList->addItem("СФЕРИЧЕСКИЙ ЗАХВАТ");
    ui->actList->addItem("БОКОВОЙ ЗАХВАТ");
    dataMap["СХВАТИТЬ"] = {20,20,20,20,20,20};
    dataMap["ОТПУСТИТЬ"] = {0,0,0,0,0,0};
    dataMap["ЩИПОК"] = {5,10,17,13,14,15};

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device) { //при обнаружении устройства
    ui->comboBox->addItem(device.address().toString());                 //оно добавляется в comboBox
}

void MainWindow::on_comboBox_activated(int index) { //подключение к устройству
    deviceName = ui->comboBox->QComboBox::itemText(index);
    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    socket->connectToService(QBluetoothAddress(deviceName),
                             QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
}

void MainWindow::sendData(std::vector<char> data) {
    for(auto bytes: data) {
        socket->write(&bytes, sizeof(char));
    }
}

void MainWindow::on_actList_itemClicked(QListWidgetItem *item) {  //получение имени элемента
    int lineNum = ui->actList->currentRow();
    actItem = ui->actList->item(lineNum)->text();
}

void MainWindow::on_addNewMove_clicked() {
    newAction->show();
}

void MainWindow::on_sendBtn_clicked() {    //отправка данных
    if(actItem == currentActItem) {
        QMessageBox::warning(this,"Ошибка","Выбранное дейтсвие уже выполнено");
    } else sendData(dataMap[actItem]);
    currentActItem = actItem;
}


void MainWindow::addToActionMap(QString key, std::vector<char> data) { //добавление элемента в контейнер
    dataMap[key] = data;
}

void MainWindow::on_saveBtn_clicked() {             //при сохранении
    ui->actList->addItem(newAction->getNamePose()); // в список добавляется новое действие
    newAction->close();
}


