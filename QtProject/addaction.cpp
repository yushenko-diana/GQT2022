#include "addaction.h"
#include "ui_addaction.h"
#include "mainwindow.h"

AddAction::AddAction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddAction) {
    ui->setupUi(this);

}

AddAction::~AddAction() {
    delete ui;
}

std::vector<char> AddAction::getFingerPose() { //получение данных нового действия для приводов
    return fingerPos;
}

QString AddAction::getNamePose() { //получение названия нового действия
    return actionName;
}

void AddAction::on_pushButton_clicked() {

    fingerPos.push_back(ui->motorLine1->text().toInt()); //получение данных
    fingerPos.push_back(ui->motorLine2->text().toInt()); //из пользовательских полей
    fingerPos.push_back(ui->motorLine3->text().toInt());
    fingerPos.push_back(ui->motorLine4->text().toInt());
    fingerPos.push_back(ui->motorLine5->text().toInt());
    fingerPos.push_back(ui->motorLine6->text().toInt());

    actionName = ui->nameLine->text();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->addToActionMap(actionName,fingerPos); //передача данных в контейнер
}
