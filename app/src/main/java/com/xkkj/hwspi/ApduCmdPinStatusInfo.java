package com.xkkj.hwspi;

import struct.StructClass;
import struct.StructField;

@StructClass
public class ApduCmdPinStatusInfo {
    /**
     * 获取PIN码的状态和信息，状态结构体为：
     * typedef struct
     * {
     * UINT8 PinIsExist;//pin码是否存在
     * UINT8 PinAuthStatus;//PIN码的认证状态 0为未认证； 0x10为user认证通过； 0xf0为锁定；
     * UINT8 MaxRetryTimes;//pin码的最大可重试次数
     * UINT8 LeftRetryTimes;//PIN码的剩余重试次数
     * }PinStatusInfo;
     */
    @StructField(order = 0)
    byte pinIsExist;//PIN码是否存在
    @StructField(order = 1)
    byte PinAuthStatus;//PIN码是否存在
    @StructField(order = 2)
    byte MaxRetryTimes;//PIN码是否存在
    @StructField(order = 3)
    byte LeftRetryTimes;//PIN码是否存在

    public byte getPinIsExist() {
        return pinIsExist;
    }

    public void setPinIsExist(byte pinIsExist) {
        this.pinIsExist = pinIsExist;
    }

    public byte getPinAuthStatus() {
        return PinAuthStatus;
    }

    public void setPinAuthStatus(byte pinAuthStatus) {
        PinAuthStatus = pinAuthStatus;
    }

    public byte getMaxRetryTimes() {
        return MaxRetryTimes;
    }

    public void setMaxRetryTimes(byte maxRetryTimes) {
        MaxRetryTimes = maxRetryTimes;
    }

    public byte getLeftRetryTimes() {
        return LeftRetryTimes;
    }

    public void setLeftRetryTimes(byte leftRetryTimes) {
        LeftRetryTimes = leftRetryTimes;
    }
}
