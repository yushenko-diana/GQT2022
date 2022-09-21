#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QMainWindow>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QListWidget>
#include <map>
#include "addaction.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QListWidget getList();

    void addToActionMap(QString key, std::vector<char> data);

    void sendData(std::vector<char> data);


private slots:

    void on_comboBox_activated(int index);

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void on_actList_itemClicked(QListWidgetItem *item);

    void on_sendBtn_clicked();

    void on_addNewMove_clicked();

    void on_saveBtn_clicked();


private:

    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent;

    QBluetoothSocket *socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    QString deviceName;

    Ui::MainWindow *ui;

    QListWidget *actList;

    std::map<QString, std::vector<char>> dataMap;

    QListWidgetItem* actionItem;

    QString actItem;

    QString currentActItem = "none";

    AddAction *newAction = new AddAction;

};
#endif // MAINWINDOW_H
