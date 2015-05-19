#ifndef FULLSCREENMAINWND_H
#define FULLSCREENMAINWND_H

#include <QMainWindow>

namespace Ui {
class FullScreenMainWnd;
}

class FullScreenMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit FullScreenMainWnd(QWidget *parent = 0);
    ~FullScreenMainWnd();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FullScreenMainWnd *ui;
    bool m_bMainWinFull;
    bool m_bCentrlWinFull;
    bool m_bStatusBarFull;
};

#endif // FULLSCREENMAINWND_H
