#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#include "cocos2d.h"
#include"CardDef.h"

class MathUtils
{
public:
	//牌面是否连续
	static bool isFaceContinuous(CardFaceType face1, CardFaceType face2)
	{
		int continuous = abs(static_cast<int>(face1) - static_cast<int>(face2));
		return continuous == 1;
	}
};

#endif // !_MATH_UTILS_H_
