package com.xkkj.hwspi;

public class CmdType {

    /**
     * 用户信息清除指令（恢复空片，不清除COS）
     */
    public static final int CMD_PRODUCE_CLEAR_ALLINFO = 0x82;
    /**
     * 获取随机数
     */
    public static final int CMD_GET_RANDOM_32 = 0x10;
    /**
     * 获取随机数16
     */
    public static final int CMD_GET_RANDOM_16 = 0x11;
    /**
     * 获取芯片信息
     */
    public static final int CMD_GET_DEVICE_INFO = 0x01;
    /**
     * 设置芯片信息
     */
    public static final int CMD_PRODUCE_SET_DEVICE_INFO = 0x81;
    /**
     * 设置UserPin
     */
    public static final int CMD_SET_USER_PIN = 0x02;
    /**
     * 获取PIN信息和状态
     */
    public static final int CMD_GET_PIN_INFO = 0x04;
    /**
     * 验证PIN
     */
    public static final int CMD_VERIFY_USERPIN = 0x05;
    /**
     * 生成ecdsa密钥对
     */
    public static final int CMD_GENERATE_KEYPARI_BY_ID = 0x0A;
    /**
     * 导出公钥
     */
    public static final int CMD_EXPORT_PUBLICKEY_BY_ID = 0x0D;
    /**
     * ECDSA签名
     */
    public static final int CMD_ECDSA_SIGN = 0x0B;

    /**
     * ECDSA签名 repeat
     */
    public static final int CMD_ECDSA_SIGN_REPEAT = 0x0C;
}
