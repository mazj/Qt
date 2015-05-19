#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

class Global
{
public:
    Global();

    bool m_bIsManage;
    QString m_userName;
};

extern Global g_g;

#endif // GLOBAL_H
