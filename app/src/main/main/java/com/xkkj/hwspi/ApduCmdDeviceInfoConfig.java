package com.xkkj.hwspi;

import struct.StructClass;
import struct.StructField;

@StructClass
public class ApduCmdDeviceInfoConfig {
    /**
     * 	uint8_t deviceName[16];//设备定制名称-如需要 （可设置）
     * 	uint8_t productInfo[8];//设备生产信息-产线-工厂-编号 如需要 （可设置）
     * 	uint8_t updateInfo[8];//如检测到需要恢复配置区和密钥区，则在恢复后，将宏记录信息版本覆盖进去，置0即可
     * 	uint8_t keyPairNum;//设备内私钥数量，生产无需设置，置0即可
     * 	uint8_t isAllowClearCos;//是否允许远程升级COS（可设置）
     * 	uint8_t backUpMode;//备份模式，远程升级时需要备份什么2*2（密钥和PIN码）四种配置组合0，1，2，3（可设置）
     * 	uint8_t pinMaxRetryTimes;//pin码最大重试次数（可设置）
     * 	uint32_t backUpFlag;//备份标记，COS内部处理，置0即可
     * 	uint8_t reserved[8];//保留字段，用于扩展
     */

    @StructField(order = 0)
    byte[] deviceName = new byte[16];//设备定制名称-如需要 （可设置）  dphotosCryptobox
    @StructField(order = 1)
    byte[] productInfo = new byte[8];//0 设备生产信息-产线-工厂-编号 如需要 （可设置）
    @StructField(order = 2)
    byte[] updateInfo = new byte[8];//0  如检测到需要恢复配置区和密钥区，则在恢复后，将宏记录信息版本覆盖进去，置0即可
    @StructField(order = 3)
    byte keyPairNum;//0 设备内私钥数量，生产无需设置，置0即可
    @StructField(order = 4)
    byte isAllowClearCos;//0 是否允许远程升级COS（可设置）
    @StructField(order = 5)
    byte backUpMode;//0 备份模式，远程升级时需要备份什么2*2（密钥和PIN码）四种配置组合0，1，2，3（可设置）
    @StructField(order = 6)
    byte pinMaxRetryTimes;//10 pin码最大重试次数（可设置）
    @StructField(order = 7)
    byte[] backUpFlag = new byte[4];//0 备份标记，COS内部处理，置0即可
    @StructField(order = 8)
    byte[] reserved = new byte[8];//保留字段

    public byte[] getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(byte[] deviceName) {
        this.deviceName = deviceName;
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

    public byte[] getBackUpFlag() {
        return backUpFlag;
    }

    public void setBackUpFlag(byte[] backUpFlag) {
        this.backUpFlag = backUpFlag;
    }

    public byte[] getReserved() {
        return reserved;
    }

    public void setReserved(byte[] reserved) {
        this.reserved = reserved;
    }
}
