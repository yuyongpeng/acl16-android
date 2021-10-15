//
// Created by EDZ on 2021/9/29.
//

#include "light.h"

static const char* backlight_node = "/sys/class/backlight/backlight/brightness";
static const char* light_node="/sys/bus/iio/devices/iio:device0/in_voltage2_raw";

int xkkj_backlight_read() {
    int backlight_fd = -1;
    char brightness[5];
    backlight_fd  = open(backlight_node, O_RDWR);
    if ( backlight_fd < 0) {
        LOGE("can't open node, %s", backlight_node);
        return -1;
    }
    int ret = read(backlight_fd, brightness, 5);
    if (ret < 0) {
    	LOGE("xkkj_backlight_read, can't read xkkj_backlight_read data");
    }
    close(backlight_fd);
    return atoi(brightness);
}

int xkkj_backlight_write(int backlight) {
    LOGE("========xkkj_backlight_write,%d\n",backlight);
    int backlight_fd = -1;
    int bytes = -1 ;
    char brightness[5];
    backlight_fd  = open(backlight_node, O_RDWR);
    if ( backlight_fd < 0) {
        LOGE("can't open node, %s", backlight_node);
        return -1;
    }
    if(0 > backlight){
        bytes = sprintf(brightness, "%d\n", 0);
    }else if(255 < backlight){
        bytes = sprintf(brightness, "%d\n", 255);
    }
    else{
        bytes = sprintf(brightness, "%d\n", backlight);
    }
    int ret = write(backlight_fd, brightness,bytes);
    close(backlight_fd);
    return ret;
}


int xkkj_light_read() {
    int light_fd;
    char light[10];
    light_fd  = open(light_node, O_RDONLY);
    if ( light_fd < 0) {
        LOGE("can't open node, %s", light_node);
        return -1;
    }
    int ret = read(light_fd, light, 10);
    if (ret < 0) {
    	LOGE("xkkj_backlight_read, can't read xxkj_light data");
    }
    close(light_fd);
    return atoi(light);
}