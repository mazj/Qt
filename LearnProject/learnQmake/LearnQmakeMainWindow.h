#ifndef LEARNQMAKEMAINWINDOW_H
#define LEARNQMAKEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LearnQmakeMainWindow;
}

class LearnQmakeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LearnQmakeMainWindow(QWidget *parent = 0);
    ~LearnQmakeMainWindow();

private:
    Ui::LearnQmakeMainWindow *ui;
};

#endif // LEARNQMAKEMAINWINDOW_H
