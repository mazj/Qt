#ifndef PERSONNELMANAGE_H
#define PERSONNELMANAGE_H

#include <QWidget>

namespace Ui {
class PersonnelManage;
}

class PersonnelManage : public QWidget
{
    Q_OBJECT

public:
    explicit PersonnelManage(QWidget *parent = 0);
    ~PersonnelManage();

private:
    Ui::PersonnelManage *ui;
};

#endif // PERSONNELMANAGE_H
