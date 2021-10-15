//
// Created by EDZ on 2021/9/18.
//

#include "acl16.h"
#include "spidev.h"
#define ACL16_CS_ON 1

static const char* ACL16_xxkj_device = "/dev/acl162.0";
static const char* ACL16_xxkj_power = "/sys/class/leds/acl16-en/brightness";
static const uint8_t ACL16_power_on = '0';
static const uint8_t ACL16_power_down = '1';
#if ACL16_CS_ON
static const char* ACL16_cs = "/sys/class/leds/hx-cs/brightness";
static const uint8_t ACL16_cs_state_open = '0';
static const uint8_t ACL16_cs_state_close = '1';
#endif
static int acl16_xkkj_config(int fd, uint8_t modePa, uint8_t bitsPa, uint32_t speedPa) {
	int ret;
	/*
	* spi mode
	*/
	ret = ioctl(fd, SPI_IOC_WR_MODE, &modePa);
	if (ret < 0)
	{
		LOGE("can't set spi mode");
		return ret;
	}

	ret = ioctl(fd, SPI_IOC_RD_MODE, &modePa);
	if (ret < 0)
	{
		LOGE("can't get spi mode");
		return ret;
	}

	/*
	* bits per word
	*/
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bitsPa);
	if (ret < 0)
	{
		LOGE("can't set bits per word");
		return ret;
	}

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bitsPa);
	if (ret < 0)
	{
		LOGE("can't get bits per word ");
		return ret;
	}

	/*
	* max speed hz
	*/
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speedPa);
	if (ret < 0)
	{
		LOGE("can't set max speed hz ");
		return ret;
	}

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speedPa);
	if (ret < 0)
	{
		LOGE("can't get max speed hz ");
		return ret;
	}

	LOGD("spi mode: %d", modePa);
	LOGD("bits per word: %d", bitsPa);
	LOGD("max speed: %d Hz (%d KHz)", speedPa, speedPa/1000);

	return 0;
}

int acl16_xkkj_read(Acl16* fd, uint8_t *data, size_t lenth) {
    LOGD("acl16_xkkj_read!");
	#if ACL16_CS_ON
		if (write(fd->_fd_cs, &ACL16_cs_state_open, 1) < 0) {
			LOGE("spiRead, can't write cs pin");
			return -1;
		}
	#endif

	int ret = read(fd->_fd, data, lenth);
	if (ret < 0) {
		LOGE("spiRead, can't read data from spi port");
	}

	#if ACL16_CS_ON
		usleep(200);
		if (write(fd->_fd_cs, &ACL16_cs_state_close, 1) < 0) {
			LOGE("spiRead, can't write cs pin");
			return -1;
		}
	#endif

	return ret;
}

int acl16_xkkj_write(Acl16* fd, uint8_t *data, size_t lenth) {
    LOGD("acl16_xkkj_write!");
	#if ACL16_CS_ON
		if (write(fd->_fd_cs, &ACL16_cs_state_open, 1) < 0) {
			LOGE("spiWrite, can't write cs pin");
			return -1;
		}
	#endif

	int ret = write(fd->_fd, data, lenth);
	if (ret < 0)
	{
		LOGE("spiWrite, can't write data to spi port");
		return ret;
	}

	#if ACL16_CS_ON
		usleep(200);
		if(write(fd->_fd_cs, &ACL16_cs_state_close, 1) < 0) {
			LOGE("spiWrite, can't write cs pin");
			return -1;
		}
	#endif

	return ret;
}


int acl16_xkkj_open(Acl16* fd) {
    LOGD("acl16_xkkj_open!");
	int errnoNu;
	fd->_fd = -1;
	fd->_fd_cs = -1;
	do {
		fd->_fd = errnoNu = open(ACL16_xxkj_device, O_RDWR);
		if (errnoNu < 0) {
			LOGE("can't open device, %s", ACL16_xxkj_device);
			break;
		}
		#if ACL16_CS_ON
			fd->_fd_cs = errnoNu = open(ACL16_cs, O_RDWR);
			if (errnoNu < 0) {
				LOGE("can't open ACL16_cs, %s", ACL16_cs);
				break;
			}
		#endif
		errnoNu = acl16_xkkj_config(fd->_fd, 0, 8, 20000000);
		if (errnoNu < 0) {
			break;
		}

		return ISOSW_SUCCESSFUL;
	} while(0);

	if (fd->_fd >= 0) {
		close(fd->_fd);
	}
	if (fd->_fd_cs >= 0) {
		close(fd->_fd_cs);
	}

	return errnoNu;
}

int acl16_xkkj_close(Acl16* fd) {
    LOGD("acl16_xkkj_close!");
	close(fd->_fd);
	close(fd->_fd_cs);
	close(fd->_fd_board);
	return ISOSW_SUCCESSFUL;
}

int acl16_xkkj_permission(){
    LOGD("acl16_xkkj_permission!");
    LOGD("/dev/acl162.0:%d",system("/system/bin/chmod 666 /dev/acl162.0"));
    LOGD("/sys/class/leds/hx-cs/brightness:%d",system("/system/bin/chmod 666 /sys/class/leds/hx-cs/brightness"));
    LOGD("/sys/class/leds/acl16-en/brightness:%d",system("/system/bin/chmod 666 /sys/class/leds/acl16-en/brightness"));
    return 0;
}

int acl16_xkkj_poweron()
{
    int power_fd = open(ACL16_xxkj_power, O_RDWR);
    if (write(power_fd,&ACL16_power_on, 1) < 0) {
    	LOGE("spiwrite, can't write power pin");
    	return -1;
   }
   close(power_fd);
   return 0;
}

int acl16_xkkj_poweroff()
{
   int power_fd = open(ACL16_xxkj_power, O_RDWR);
   if (write(power_fd,&ACL16_power_down, 1) < 0) {
    	LOGE("spiwrite, can't write power pin");
    	return -1;
   }
   close(power_fd);
   return 0;
}