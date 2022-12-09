package com.xkkj.hwspi;

import struct.StructClass;
import struct.StructField;

@StructClass
public class ApduCmdDeviceInfo {
    @StructField(order = 0)
    byte[] deviceID = new byte[16];//芯片唯一ID
    @StructField(order = 1)
    byte[] deviceName = new byte[16];//设备名称
    @StructField(order = 2)
    byte[] cosVersion = new byte[16];//COS版本
    @StructField(order = 3)
    byte[] hardWareVersion = new byte[8];//硬件版本
    @StructField(order = 4)
    byte[] productInfo = new byte[8];//出厂生产信息
    @StructField(order = 5)
    byte[] updateInfo = new byte[8];//升级记录信息
    @StructField(order = 6)
    byte pinIsExist;//PIN码是否存在
    @StructField(order = 7)
    byte keyPairNum;//私钥数量
    @StructField(order = 8)
    byte isAllowClearCos;//是否允许清除
    @StructField(order = 9)
    byte backUpMode;//备份模式
    @StructField(order = 10)
    byte pinMaxRetryTimes;//pin最大重试次数
    @StructField(order = 11)
    byte[] reserved = new byte[3];//保留字段

    public byte[] getDeviceID() {
        return deviceID;
    }

    public void setDeviceID(byte[] deviceID) {
        this.deviceID = deviceID;
    }

    public byte[] getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(byte[] deviceName) {
        this.deviceName = deviceName;
    }

    public byte[] getCosVersion() {
        return cosVersion;
    }

    public void setCosVersion(byte[] cosVersion) {
        this.cosVersion = cosVersion;
    }

    public byte[] getHardWareVersion() {
        return hardWareVersion;
    }

    public void setHardWareVersion(byte[] hardWareVersion) {
        this.hardWareVersion = hardWareVersion;
    }

    public byte[] getProductInfo() {
        return productInfo;
    }

    public void setProductInfo(byte[] productInfo) {
        this.productInfo = productInfo;
    }

    public byte[] getUpdateInfo() {
        return updateInfo;
    }

    public void setUpdateInfo(byte[] updateInfo) {
        this.updateInfo = updateInfo;
    }

    public byte getPinIsExist() {
        return pinIsExist;
    }

    public void setPinIsExist(byte pinIsExist) {
        this.pinIsExist = pinIsExist;
    }

    public byte getKeyPairNum() {
        return keyPairNum;
    }

    public void setKeyPairNum(byte keyPairNum) {
        this.keyPairNum = keyPairNum;
    }

    public byte getIsAllowClearCos() {
        return isAllowClearCos;
    }

    public void setIsAllowClearCos(byte isAllowClearCos) {
        this.isAllowClearCos = isAllowClearCos;
    }

    public byte getBackUpMode() {
        return backUpMode;
    }

    public void setBackUpMode(byte backUpMode) {
        this.backUpMode = backUpMode;
    }

    public byte getPinMaxRetryTimes() {
        return pinMaxRetryTimes;
    }

    public void setPinMaxRetryTimes(byte pinMaxRetryTimes) {
        this.pinMaxRetryTimes = pinMaxRetryTimes;
    }

    public byte[] getReserved() {
        return reserved;
    }

    public void setReserved(byte[] reserved) {
        this.reserved = reserved;
    }
}
