//
// Created by EDZ on 2021/9/18.
//

#include "acl16.h"
#include <termios.h>
static const char* ACL16_smdt_device = "/dev/ttyS0";

static speed_t getBaudrate(int baudrate)
{
    switch(baudrate) {
        case 0:       return B0;
        case 50:      return B50;
        case 75:      return B75;
        case 110:     return B110;
        case 134:     return B134;
        case 150:     return B150;
        case 200:     return B200;
        case 300:     return B300;
        case 600:     return B600;
        case 1200:    return B1200;
        case 1800:    return B1800;
        case 2400:    return B2400;
        case 4800:    return B4800;
        case 9600:    return B9600;
        case 19200:   return B19200;
        case 38400:   return B38400;
        case 57600:   return B57600;
        case 115200:  return B115200;
        case 230400:  return B230400;
        case 460800:  return B460800;
        case 500000:  return B500000;
        case 576000:  return B576000;
        case 921600:  return B921600;
        case 1000000: return B1000000;
        case 1152000: return B1152000;
        case 1500000: return B1500000;
        case 2000000: return B2000000;
        case 2500000: return B2500000;
        case 3000000: return B3000000;
        case 3500000: return B3500000;
        case 4000000: return B4000000;
        default: return -1;
    }
}



static int acl16_smdt_config(Acl16* fd, int baudrate, int flow_ctrl,int databits, int stopbits, int parity) {
    speed_t speed = getBaudrate(baudrate);
    if (speed == -1)
    {
          return -1;
    }
    struct termios options;
    if(tcgetattr(fd->_fd, &options) != 0)
     {
            LOGE("uart:%s tcgetattr failed!\n", ACL16_smdt_device);
            close(fd->_fd);
            return -4;
     }

    //设置串口输入波特率和输出波特率
    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    options.c_cflag &= ~CSIZE; //屏蔽其他标志位
    options.c_cflag |= CLOCAL; //修改控制模式，保证程序不会占用串口
    options.c_cflag |= CREAD;  //修改控制模式，使得能够从串口中读取输入数据

    //设置数据流控制
    switch(flow_ctrl)
    {
        //不使用流控制
        case 0:
            options.c_cflag &= ~CRTSCTS;
            break;
        //使用硬件流控制
        case 1:
            options.c_cflag |= CRTSCTS;
            break;
        //使用软件流控制
        case 2:
            options.c_cflag |= IXON | IXOFF | IXANY;
            break;
    }
	   //设置数据位
    switch (databits)
    {
        case 5:
            options.c_cflag |= CS5;
            break;
        case 6:
            options.c_cflag |= CS6;
            break;
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
           return -1;
    }

    //设置校验位
    switch (parity)
    {
        //无奇偶校验位
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
        //设置为奇校验
        case 'o':
        case 'O':
            options.c_cflag |= (PARODD | PARENB);
            options.c_iflag |= INPCK;
            break;
        //设置为偶校验
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK;
            break;
        //设置为空格固定值0
        case 's':
        case 'S':
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
        break;
            default:
            return -1;
    }

  // 设置停止位
    switch (stopbits)
    {
       case 1:
          options.c_cflag &= ~CSTOPB;
          break;
       case 2:
          options.c_cflag |= CSTOPB;
          break;
       default:
          return -1;
    }
     //修改输出模式，原始数据输出
     options.c_oflag &= ~OPOST;
     options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
     options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

     //设置等待时间和最小接收字节
      options.c_cc[VTIME] = 150; /* 读取等待的时间 单位百毫秒*/
      options.c_cc[VMIN] = 0;   /* 读取最小字节数 */

      //刷清输入、输出队列
      //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
      tcflush(fd->_fd, TCIOFLUSH);

      //激活配置,将修改后的termios数据设置到串口中
      if (tcsetattr(fd->_fd, TCSANOW, &options) != 0)
      {
            LOGE("uart:%s tcsetattr failed!\n", ACL16_smdt_device);
            close(fd->_fd);
            return -1;
      }
      return 0;
}


int acl16_smdt_open(Acl16* fd){
        print_array(NULL,0,"acl16_smdt_open!");
        int errnoNu;
        fd->_fd = -1;
        fd->_fd_cs = -1;
        do {
        	fd->_fd = errnoNu = open(ACL16_smdt_device, O_RDWR);
        	//fd->_fd = errnoNu = open(ACL16_smdt_device, O_RDWR | O_NOCTTY);
        	if (errnoNu < 0) {
        		LOGE("can't open device, %s\n", ACL16_smdt_device);
        		break;
        	}
        	errnoNu = acl16_smdt_config(fd, 115200, 0,8, 1,'N');
        	if (errnoNu < 0) {
        		break;
        	}
        	return ISOSW_SUCCESSFUL;
        } while(0);

        if (fd->_fd >= 0) {
        	close(fd->_fd);
        }
        return errnoNu;
}

int  acl16_smdt_close(Acl16* fd){
        print_array(NULL,0,"acl16_smdt_close!");
        close(fd->_fd);
        return ISOSW_SUCCESSFUL;
}


int acl16_smdt_write(Acl16* fd, uint8_t *data, size_t lenth){
    print_array(NULL,0,"acl16_smdt_write!");
     int len = write(fd->_fd, data, lenth);
     if (len != lenth )
     {
         tcflush(fd->_fd, TCOFLUSH);
         LOGE("smdt_Write, can't write data to tty port\n");
     }
     return len;
}


int acl16_smdt_read2(Acl16* fd, uint8_t *recv_buf, size_t data_len)
{
    print_array(NULL,0,"acl16_smdt seclect read!");
    int i = 0;
    int len = 0;
    int fs_sel = 0;
    unsigned char tem = 0;
    fd_set fs_read;
    FD_ZERO(&fs_read);
    FD_SET(fd->_fd,&fs_read);

    struct timeval time;
    time.tv_sec = 5;
    time.tv_usec = 0;

    //使用select实现串口的多路通信
    //timeout == NULL 表示等待无限长的时间
    //超时返回0;失败返回-1;成功返回大于0，这个整数表示就绪描述符的数目
    for(i = 0; i < data_len; i++)
    {

        fs_sel = select(fd->_fd + 1, &fs_read, NULL, NULL, &time);
        if(fs_sel > 0)
        {
            len = read(fd->_fd, &tem, 1);
            if(1 == len)
            {
                recv_buf[i] = tem;
            }
        }
        else
        {
            return i;
        }
    }
    return data_len;
}



int acl16_smdt_read(Acl16* fd, uint8_t *data, size_t lenth){
    print_array(NULL,0,"acl16_smdt_read!");
    int ret = read(fd->_fd, data, lenth);
    if (ret < 0)
    {
    	LOGE("smdt_read, can't read data to ttyS0 port");
    	return ret;
    }
    return ret;
}



int acl16_smdt_poweron()
{
   return 0;
}

int acl16_smdt_poweroff()
{
   return 0;
}