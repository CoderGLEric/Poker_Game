#ifndef __APPMICRAOS_H__
#define __APPMICRAOS_H__

#include "cocos2d.h"
USING_NS_CC;

#define winSize CCDirector::sharedDirector()->getWinSize()  

//�Լ���д����ת�����룬���õ����ĵĵط��ֶ�ת����

//ת���������£��ɵ�������Ϊ.hͷ�ļ�����ʹ�õ�����ת����cpp�ļ�include ���ɡ�

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

