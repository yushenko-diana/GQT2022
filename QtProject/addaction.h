#ifndef ADDACTION_H
#define ADDACTION_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class AddAction;
}

class AddAction : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddAction(QWidget *parent = nullptr);
    ~AddAction();

    std::vector<char> getFingerPose();

    QString getNamePose();

    void addToActionMap(QString key, std::vector<char> data);

private slots:

    void on_pushButton_clicked();

private:

    Ui::AddAction *ui;

    std::vector<char> fingerPos;

    QString actionName;
};

#endif // ADDACTION_H
