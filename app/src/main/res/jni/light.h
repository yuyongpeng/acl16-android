//
// Created by EDZ on 2021/9/29.
//

#ifndef HWSPI_LIGHT_H
#define HWSPI_LIGHT_H
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<Android/log.h>
#include "acl16.h"
int backlight_read();
int backlight_write(int backlight);
int light_read();

#endif //HWSPI_LIGHT_H
