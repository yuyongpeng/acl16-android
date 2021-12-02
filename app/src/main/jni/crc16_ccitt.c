
#include <stdint.h>
#include "crc16_ccitt.h"

void InvertUint8(uint8_t *DesBuf, uint8_t *SrcBuf)
{
	int i;
	uint8_t temp = 0;

	for(i = 0; i < 8; i++)
	{
		if(SrcBuf[0] & (1 << i))
		{
			temp |= 1<<(7-i);
		}
	}
	DesBuf[0] = temp;
}

void InvertUint16(uint16_t *DesBuf, uint16_t *SrcBuf)
{
	int i;
	uint16_t temp = 0;

	for(i = 0; i < 16; i++)
	{
		if(SrcBuf[0] & (1 << i))
		{
			temp |= 1<<(15 - i);
		}
	}
	DesBuf[0] = temp;
}

uint16_t CRC16_CCITT(uint8_t *puchMsg, uint16_t usDataLen)
{
	uint16_t wCRCin = 0x0000;
	uint16_t wCPoly = 0x1021;
	uint8_t wChar = 0;
	int i;

	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		InvertUint8(&wChar, &wChar);
		wCRCin ^= (wChar << 8);

		for(i = 0; i < 8; i++)
		{
			if(wCRCin & 0x8000)
			{
				wCRCin = (wCRCin << 1) ^ wCPoly;
			}
			else
			{
				wCRCin = wCRCin << 1;
			}
		}
	}
	InvertUint16(&wCRCin, &wCRCin);
	return (wCRCin) ;
}

