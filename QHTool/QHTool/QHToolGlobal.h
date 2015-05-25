#ifndef QHTOOLGLOBAL_H
#define QHTOOLGLOBAL_H

#include<stdexcept>
#include "QHToolConfig.h"

// ±àÂë·½Ê½
enum EQHEncode
{
    EQHEncodeUTF8,
    EQHEncodeUTF16,
    EQHEncodeGBK,
};

inline EQHEncode intToEQHEncode(int n)
{
    switch (n) {
        case EQHEncodeUTF8:
        case EQHEncodeUTF16:
        case EQHEncodeGBK:
            return (EQHEncode)n;
            break;
        default:
            throw std::logic_error("can not intToEQHEncode for n");
            break;
    }
}

#endif // QHTOOLGLOBAL_H
