#ifndef __APPMICRAOS_H__
#define __APPMICRAOS_H__

#include "cocos2d.h"
USING_NS_CC;

#define winSize CCDirector::sharedDirector()->getWinSize()  

//自己编写编码转换代码，在用到中文的地方手动转换。

//转换代码如下，可单独保存为.h头文件，在使用到编码转换的cpp文件include 即可。

#ifdef WIN32
#define UTEXT(str) AppMicraos::MYGBKToUTF8(str)
#else
#define UTEXT(str) str
#endif

#include <stdlib.h>
#include <string.h>
#include  "cocos2d\external\win32-specific\icon\include\iconv.h"

class AppMicraos
{
public:
	static char* MYGBKToUTF8(const char *strChar)
	{
		char g_GBKConvUTF8Buf[5000] = { 0 };
		iconv_t iconvH;
		iconvH = iconv_open("utf-8", "gb2312");
		if (iconvH == 0)
		{
			return NULL;
		}
		size_t strLength = strlen(strChar);
		size_t outLength = strLength << 2;
		size_t copyLength = outLength;
		memset(g_GBKConvUTF8Buf, 0, 5000);

		char* outbuf = (char*)malloc(outLength);
		char* pBuff = outbuf;
		memset(outbuf, 0, outLength);

		if (-1 == iconv(iconvH, &strChar, &strLength, &outbuf, &outLength))
		{
			iconv_close(iconvH);
			return NULL;
		}
		memcpy(g_GBKConvUTF8Buf, pBuff, copyLength);
		free(pBuff);
		iconv_close(iconvH);
		return g_GBKConvUTF8Buf;
	}
};

#endif // !__APPMICRAOS_H__

