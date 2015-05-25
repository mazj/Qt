#ifndef SETTINGTEXTCODEC_HPP
#define SETTINGTEXTCODEC_HPP

#include <QTextCodec>
#include "QHToolConfig.h"

/**
 * @brief The SettingTextCodec class
 * �ڹ��캯�������� QTextCodec
 * QTextCodec::setCodecForLocale(cl);
        QTextCodec::setCodecForCStrings(cs);
        QTextCodec::setCodecForTr(ct);
   �����������������ûع��캯������ǰ��
    QTextCodec::codecForLocale();
    QTextCodec::codecForCStrings();
    QTextCodec::codecForTr();
 */
#ifdef QHTOOL_QT4
class SettingTextCodec
{
public:
    SettingTextCodec(QTextCodec *cl, QTextCodec *cs, QTextCodec *ct)
    {
        m_cl = QTextCodec::codecForLocale();
        m_cs = QTextCodec::codecForCStrings();
        m_ct = QTextCodec::codecForTr();

        QTextCodec::setCodecForLocale(cl);
        QTextCodec::setCodecForCStrings(cs);
        QTextCodec::setCodecForTr(ct);
    }

    ~SettingTextCodec()
    {
        QTextCodec::setCodecForLocale(m_cl);
        QTextCodec::setCodecForCStrings(m_cs);
        QTextCodec::setCodecForTr(m_ct);
    }
private:
    QTextCodec *m_cl;
    QTextCodec *m_cs;
    QTextCodec *m_ct;
};
#endif

#ifdef QHTOOL_QT5
class SettingTextCodec
{
public:
    SettingTextCodec(QTextCodec *cl)
    {
        m_cl = QTextCodec::codecForLocale();

        QTextCodec::setCodecForLocale(cl);
    }

    ~SettingTextCodec()
    {
        QTextCodec::setCodecForLocale(m_cl);
    }
private:
    QTextCodec *m_cl;
};
#endif

#endif // SETTINGTEXTCODEC_HPP
