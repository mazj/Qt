#ifndef XMLMAINWND_H
#define XMLMAINWND_H

#include <QMainWindow>

namespace Ui {
class XmlMainWnd;
}

class XmlMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit XmlMainWnd(QWidget *parent = 0);
    ~XmlMainWnd();

private slots:
    void on_pushButtonDomRead_clicked();

    void on_pushButtonDomWrite_clicked();

private:
    Ui::XmlMainWnd *ui;
};

#endif // XMLMAINWND_H
