
#ifndef __CRC16_CCITT
#define __CRC16_CCITT

#include <stdint.h>

void invertUint8(uint8_t *desBuf, uint8_t *srcBuf);
void invertUint16(uint16_t *desBuf, uint16_t *srcBuf);
uint16_t CRC16_CCITT(uint8_t *puchMsg, uint16_t usDataLen);

#endif