//
// Created by EDZ on 2021/11/30.
//
#include "acl16.h"
static Acl16 acl16_boot;
/************************************************************************
 * function   : ACL16_BOOT_CMD_0xB0
 * Description: acl16 bootloader common command -> check key
 * input 			: none
 * return			: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_B0(Acl16* fd)
{
	uint8_t bSendCmd[12] = {0xAA, 0xB0, 0x08, 0x30, 0x32, 0x31, 0x38, 0x37, 0x36, 0x30, 0x37, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData = &databuf[0];
	unsigned int i= 10000;//没有具体算，
	unsigned int tmp;//没有具体算，
    acl16_xkkj_csopen(fd);
	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 8);
	acl16_write(fd, &bSendCmd[11], 1);
	usleep(10000);
	while(i--)
	{
	    usleep(50);
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}

	}
	usleep(200);
    acl16_xkkj_csclose(fd);
    if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
    {
    	return 1;
    }
    return 0;
}

/************************************************************************
 * function   : ACL16_BOOT_CMD_0xD3
 * Description: acl16 bootloader common command -> erase eflash
 * input 			: none
 * return			: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_D3(Acl16* fd)
{
	uint8_t	bSendCmd[4] = {0xAA, 0xD3, 0x00, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData =&databuf[0];
	int bRcvLen = 5;
	unsigned int i= 100000;//没有具体算，
	unsigned int tmp;//没有具体算，
    acl16_xkkj_csopen(fd);

	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 1);
	usleep(10000);
	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}

	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}

/************************************************************************
 * function   : ACL16_BOOT_CMD_0xD7
 * Description: acl16 bootloader common command -> download hex code
 * input : int addr: download code address
 *         uint8_t *data: download code data
 *         uint8_t length: download code length
 * return	: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_D7(Acl16* fd, int addr, uint8_t *data, uint8_t length)
{
	uint8_t	bSendCmd[256] = {0x00, 0xAA, 0xD7, 0x00, 0x00};
	uint8_t  load_length;
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData = &databuf[0];
	int bRcvLen = 5;
	unsigned int i= 100000;//没有具体算，
	unsigned int tmp;//没有具体算，
    acl16_xkkj_csopen(fd);
	load_length = (length%16)?(16-length%16+length):(length);			//
	bSendCmd[3] = load_length + 4;
	bSendCmd[4] = (uint8_t)((addr >>  0) & 0xff);
	bSendCmd[5] = (uint8_t)((addr >>  8) & 0xff);
	bSendCmd[6] = (uint8_t)((addr >> 16) & 0xff);
	bSendCmd[7] = (uint8_t)((addr >> 24) & 0xff);
	memcpy(&bSendCmd[8], data, length);
	bSendCmd[8+load_length] = 0x55;
	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 1);
	acl16_write(fd, &bSendCmd[4], load_length + 4);
	acl16_write(fd, &bSendCmd[8+load_length], 1);
	usleep(10000);

	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}

	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[2]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}

/************************************************************************
 * function   : ACL16_BOOT_CMD_0xD8
 * Description: acl16 bootloader common command -> check crc
 * input 			: none
 * return			: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_D8(Acl16* fd)
{
	uint8_t	bSendCmd[4] = {0xAA, 0xD8, 0x00, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData = &databuf[0];
	int bRcvLen = 5;
	unsigned int i= 1000;		//没有具体算，
	unsigned int tmp;		//没有具体算，
    acl16_xkkj_csopen(fd);
	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 1);
	usleep(10000);
	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}
	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}

/************************************************************************
 * function   : ACL16_BOOT_CMD_0xD9
 * Description: acl16 bootloader common command -> download code_length and crc16_value
 * input :
 *         int code_straddr: download code start address
 *         int code_size: download code length
 *         WORD crc16_value: download code crc16 value
 * return			: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_D9(Acl16* fd, int code_straddr, int code_size, uint16_t crc16_value)
{
	uint8_t	bSendCmd[14] = {0xAA, 0xD9, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData =&databuf[0];
	int bRcvLen = 5;
	unsigned int i= 1000;//没有具体算，
	unsigned int tmp;//没有具体算，
    acl16_xkkj_csopen(fd);

	bSendCmd[3] = (uint8_t)((code_size >>  0) & 0xff);
	bSendCmd[4] = (uint8_t)((code_size >>  8) & 0xff);
	bSendCmd[5] = (uint8_t)((code_size >> 16) & 0xff);
	bSendCmd[6] = (uint8_t)((code_size >> 24) & 0xff);

	bSendCmd[7] = (uint8_t)((crc16_value >>  0) & 0xff);
	bSendCmd[8] = (uint8_t)((crc16_value >>  8) & 0xff);

	bSendCmd[9] = (uint8_t)((code_straddr >>  0) & 0xff);
	bSendCmd[10] = (uint8_t)((code_straddr >>  8) & 0xff);
	bSendCmd[11] = (uint8_t)((code_straddr >> 16) & 0xff);
	bSendCmd[12] = (uint8_t)((code_straddr >> 24) & 0xff);


	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 10);
	acl16_write(fd, &bSendCmd[13], 1);
	usleep(10000);
	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}
	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}

/************************************************************************
 * function   : ACL16_BOOT_CMD_0xE3
 * Description: acl16 bootloader common command -> run app
 * input 			: none
 * return			: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_E3(Acl16* fd)
{
	uint8_t	bSendCmd[4] = {0xAA, 0xE3, 0x00, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData =&databuf[0];
	int bRcvLen = 5;
	unsigned int i= 10000;//没有具体算，
	unsigned int tmp;//没有具体算，
    acl16_xkkj_csopen(fd);
	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 1);
	usleep(10000);
	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}
	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}
/************************************************************************
 * function   : ACL16_BOOT_CMD_0xC7
 * Description: acl16 bootloader common command -> selftest
 * input 	: none
 * return	: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_C7(Acl16* fd)
{
	uint8_t	bSendCmd[4] = {0xAA, 0xc7, 0x00, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData =&databuf[0];
	int bRcvLen = 5;
	unsigned int i= 100000;//没有具体算，
	unsigned int tmp;//没有具体算，
    acl16_xkkj_csopen(fd);
	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 1);
	usleep(10000);
	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}
	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}



/************************************************************************
 * function   : ACL16_BOOT_CMD_0xCC
 * Description: acl16 bootloader common command -> security code
 * input 			: none
 * return			: 0->success, other->failure
 ************************************************************************/
static uint8_t ACL16_BOOT_CMD_CC(Acl16* fd)
{
	uint8_t	bSendCmd[4] = {0xAA, 0xCC, 0x00, 0x55};
	uint8_t databuf[64] = {0};
	uint8_t *bRcvData =&databuf[0];
	int bRcvLen = 5;
	unsigned int i= 1000;			//没有具体算，
	unsigned int tmp;			//没有具体算，
    acl16_xkkj_csopen(fd);
	acl16_write(fd, &bSendCmd[0], 1);
	acl16_write(fd, &bSendCmd[1], 1);
	acl16_write(fd, &bSendCmd[2], 1);
	acl16_write(fd, &bSendCmd[3], 1);
	usleep(10000);
	while(i --)
	{
		acl16_read(fd, databuf, 1);
		if(databuf[0] == 0xAA)
		{
			acl16_read(fd, &databuf[1], 4);
			break;
		}
	}
	usleep(200);
    acl16_xkkj_csclose(fd);
	if((bRcvData[1] != bSendCmd[1]) || (bRcvData[2] != 0x01) || (bRcvData[3] != 0x00) || (bRcvData[4] != 0x55))
	{
		return 1;
	}
	return 0;
}


static uint16_t crc16_ccitt_to_acl16(uint8_t *buffer, uint32_t len, uint16_t crc_init)
{
	int i,j;
	uint16_t current;
	uint16_t crc_reg;

	if(len <= 0)
	{
		return crc_init;
	}
	crc_reg = crc_init;
	for (i = 0; i < len; i++)
	{
		current = buffer[i];
		for(j = 0; j < 8; j++)
		{
			if((crc_reg ^ current) & 0x0001)
			{
				crc_reg = (crc_reg >> 1) ^ 0x8408;
			}
			else
			{
				crc_reg >>= 1;
			}
			current >>= 1;
		}
	}
	return crc_reg;
}


/************************************************************************
 * function   : acl16_code_download_proc
 * Description: acl16 bootloader download hex data
 * input :
 *         int hex_straddr: download code hex start address
 *         uint8_t *hex_code: download code hex data
 *         int hex_len: download code hex length
 *         int runapp: 0x12345678->runapp enable, other->disable
 *         int bootcode: 0x87654321->bootcode enable, other->disable
 *         int chiperase: 0xAAD3AAD3->chiperase enable, other->disable
 * return			: 0->success, other->failure
 uint16_t runapp, uint16_t bootcode, ui ************************************************************************/
static uint8_t acl16_code_download_proc(Acl16* fd, int hex_straddr, uint8_t *hex_code, uint32_t hex_len, uint32_t runapp, uint32_t bootcode, uint32_t chiperase)
{
	uint16_t crc16_result;
	int bin_len, bin_offset;
	int csFd;
	print_array(NULL,0,"acl16_code_download_proc -> check key start");
	if(ACL16_BOOT_CMD_B0(fd))
	{
		return 0xB0;
	}
	print_array(NULL,0,"acl16_code_download_proc -> check key successful");
	usleep(5000);
	print_array(NULL,0,"acl16_code_download_proc-> self test start...\n");
	if(ACL16_BOOT_CMD_C7(fd))
	{
		return 0xC7;
	}
	print_array(NULL,0,"acl16_code_download_proc-> self test successful.\n");

	usleep(5000);
	print_array(NULL,0,"acl16_code_download_proc-> erase acl16 start...\n");
	if(chiperase == 0xAAD3AAD3)
	{
		if(ACL16_BOOT_CMD_D3(fd))					//erase acl16
		{
			return 0xD3;
		}
	}
	print_array(NULL,0,"acl16_code_download_proc-> erase acl16 successful.\n");
	usleep(5000);
	bin_len = hex_len;
	bin_offset = 0;
	while(bin_len >= 240)
	{
		if(ACL16_BOOT_CMD_D7(fd, hex_straddr + bin_offset, &hex_code[bin_offset], 240))
		{
			LOGE("acl16_code_download_proc download file error\n");
			return 0xD7;
		}
		bin_len -= 240;
		bin_offset += 240;
	}
	usleep(5000);
	if(bin_len)
	{
		if(ACL16_BOOT_CMD_D7(fd, hex_straddr + bin_offset, &hex_code[bin_offset], bin_len))
		{
			LOGE("acl16_code_download_proc download file error\n");
			return 0xD7;
		}
		bin_len = 0;
		bin_offset = 0;
	}

	print_array(NULL,0,"acl16_code_download_proc -> Download hex code successful.");

	/*CRC-CCITT=X16+X12+X5+1*/
	crc16_result = crc16_ccitt_to_acl16((uint8_t *)hex_code, hex_len, 0xffff);

	crc16_result ^= 0xFFFF;

	usleep(5000);

	print_array(NULL,0,"acl16_code_download_proc-> download code_len and crc16_value start...");

	if(ACL16_BOOT_CMD_D9(fd, hex_straddr, hex_len, crc16_result))		//download code_len and crc16_value
	{
		LOGE("acl16_code_download_proc crc download file error");
		return 0xD9;
	}


	usleep(5000);
	print_array(NULL,0,"acl16_code_download_proc -> check crc start...\n");
	if(ACL16_BOOT_CMD_D8(fd))						//check crc
	{
		LOGE("acl16_code_download_proc check crc error\n");
		return 0xD8;
	}
	print_array(NULL,0,"acl16_code_download_proc -> check crc successful.\n");
	 usleep(5000);
	 if (bootcode == 0x87654321)
	 {
		if(ACL16_BOOT_CMD_CC(fd))					//security code
		{
		return 0xCC;
		}
	  }
	print_array(NULL,0,"acl16_code_download_proc -> run app start...\n");
	if (runapp == 0x12345678)
	{
		if(ACL16_BOOT_CMD_E3(fd))					//run app
		{
			return 0xE3;
		}
	}
	print_array(NULL,0,"acl16_code_download_proc -> run app successful.\n");
	return 0;
}



int codeDownLoad(char security_code)
{

    acl16_poweroff();
    acl16_poweron();
    LOGE("codeDownLoad enter.\n");
    char *cosFile = "/etc/BlockChainModule_SPI.bin";
    int cosFd;
    uint32_t fileLen;
    uint8_t *fPoint;
    int ret;
    int i;
    cosFd = open(cosFile, O_RDONLY);
    if(!cosFd)
    {
        LOGE("codeDownLoad open file error.\n");
        return -1;
    }
    fileLen= lseek(cosFd, 0L, SEEK_END);
    lseek(cosFd, 0L,SEEK_SET);
    fPoint = (uint8_t *)malloc(fileLen);
    ret = read(cosFd, fPoint, fileLen);
    if(ret < 0)
    {
        LOGE("read file error.\n");
        return -1;
    }
    acl16_open(&acl16_boot,1);
    if(security_code == 0x01)
        ret = acl16_code_download_proc(&acl16_boot, 0x00000000, fPoint, fileLen, 0x12345678, 0x87654321, 0xAAD3AAD3);
    else
        ret = acl16_code_download_proc(&acl16_boot, 0x00000000, fPoint, fileLen, 0x12345678, 0x87654322, 0xAAD3AAD3);
    free(fPoint);
    close(cosFd);
    acl16_close(&acl16_boot);
    LOGE("codeDownLoad successful.\n");
    return 0;
}

