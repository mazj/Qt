
#ifndef CORNERPROMPTBOX_H
#define CORNERPROMPTBOX_H

#include <QRect>
#include <QDialog>
#include <QTimer>
#include <QDesktopWidget>

class QHBoxLayout;
class QWidget;
class QCloseEvent;
class QPropertyAnimation;
class QLabel;
class QFont;

/**
 * @brief 屏幕右下角的消息提示框
 * 可以设置消失时间长度，可以 设置是否使用动画划入滑出
 */
class CornerPromptBox : public /*QMessageBox*/ QDialog
{
    Q_OBJECT
public:
    explicit CornerPromptBox(bool useAnimation = true, bool hasBorder = true);
    ~CornerPromptBox();
    void setUseAnimation(bool use);
    void showMsg(int msecs);


    void setContent(const QString &text, const QFont *pFont = 0);
    void setContent(QWidget *w);

protected:
    void closeEvent(QCloseEvent *e);

private:
    const QRect deskRect();

private:
    QTimer m_timer;
    bool m_bUseAnimation;
    QDesktopWidget m_desktop;
    QPropertyAnimation *m_animation;
    QLabel *m_lable;
    QHBoxLayout *m_layout;
    QWidget *m_content;

    enum EContent
    {
        ContentNone,
        ContentText,
        ContentWidget
    };
    EContent m_contentType;

public slots:
    void slotHideMsg();

private slots:
    void closeAnimation();
    void _hide();
};



#endif // CORNERPROMPTBOX_H
