package android_xkkj_api;

public class HwAcl {
    static
    {
        System.loadLibrary("hwacl");
    }
    /*
     * 函数名：produce_set_config(byte[]  produce_config);
     * 描述： 生产配置命令： CMD_PRODUCE_SET_CONFIG 0x81
     * 传参：produce_config 组合后的Acl16ProduceConfig数据
     * 返回值：正确返回0x9000，错误查看对应的错误码
     */
    public native int  produce_set_config(byte[]  produce_config);

    /*
     * 函数名：produce_Clear_AllInfo;
     * 描述：清除用户数据：CMD_PRODUCE_CLEAR_ALLINFO 0x82
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  produce_Clear_AllInfo();

    /*
     * 函数名：produce_Clear_Cos;
     * 描述：清除COS：CMD_PRODUCE_CLEAR_COS 0x83
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  produce_Clear_Cos();
    /*
     * 函数名：get_random_data(byte[] randdata, char randLenth);
     * 描述：获取随机数：CMD_GET_RANDOM 0x10
     * 传参：randdata 返回的随机数数据，
     *      randLenth 设置的随机数长度
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  get_random_data(byte[] randdata, char randLenth);
    /*
     * 函数名：get_device_info(byte[] deviceinfo);
     * 描述：获取设备信息： CMD_GET_DEVICE_INFO		0x01
     * 传参：deviceinfo 返回的设备信息数据
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  get_device_info(byte[] deviceinfo);
    /*
     * 函数名：set_pin(byte[] pin_info);
     * 描述：设置userpin CMD_SET_USER_PIN 0x02
     * 传参：pin_info 设置的pin值
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  set_pin(byte[] pin_info);

    /*
     * 函数名： change_pin(byte[] pin_info);
     * 描述：修改userpin CMD_CHANGE_USERPIN	0x03
     * 传参：pin_info 修改后的pin值
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  change_pin(byte[] pin_info);
    /*
     * 函数名：get_pin_info(byte[] pin_info);
     * 描述：获取PIN信息和状态   CMD_GET_PIN_INFO 0x04
     * 传参：pin_info 返回的pin数据，
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  get_pin_info(byte[] pin_info);


    /*
     * 函数名：verify_pin(byte[] pin_info);
     * 描述：验证USERPIN CMD_VERIFY_USERPIN 0x05
     * 传参：
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */

    public native int  verify_pin(byte[] pin_info);


    /*
     * 函数名：generate_KeyPariById(byte[]  KeyPar);
     * 描述：生成ecdsa密钥对  CMD_GENERATE_KEYPARI_BY_ID		0x0A
     * 传参：KeyPar  返回的数据
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */

    public native int generate_KeyPariById(byte[]  KeyPar);



    /*
     * 函数名：ecdsa_sign(byte[] txData,byte[] signature);
     * 描述：Ecdsa签名  CMD_ECDSA_SIGN	0x0B
     * 传参：txData  传入的数据
     *      signature  返回的数据
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  ecdsa_sign(byte[] txData,byte[] signature);
    /*
     * 函数名：ecdsa_verify(byte[] signature);
     * 描述：Ecdsa验签 CMD_ECDSA_VERIFY 0x0C
     * 传参：signature  Hash值+签名值(96字节)
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  ecdsa_verify(byte[] signature);
    /*
     * 函数名：export_public_key(byte[] pubkey);
     * 描述：导出公钥  CMD_EXPORT_PUBLICKEY_BY_ID		0x0D
     * 传参：pubkey  返回的公钥数据
     * 返回值：正确返回0x9000,错误查看对应的错误码
     */
    public native int  export_public_key(byte[] pubkey);

    /*
     * 函数名：acl_write(byte[] txdata);
     * 描述：写数据
     * 传参：txdata 写入的数据
     * 返回值：正确返回写入的长度,错误返回对应的错误码
     */
    public native int  acl_write(byte[] txdata);
    /*
     * 函数名：acl_read(byte[] rxdata, int lenth);
     * 描述：读数据
     * 传参：rxdata  读取的数据
     *      lenth  读取的长度
     * 返回值：正确返回读取的长度,错误返回对应的错误码
     */
    public native int  acl_read(byte[] rxdata, int lenth);
    /*
     * 函数名： acl_poweron();
     * 描述：设备上电
     * 返回值：正确0 ，错误-1
     */
    public native int   acl_poweron();
    /*
     * 函数名： acl_poweron();
     * 描述：设备下电
     * 返回值：正确0，错误：-1
     */
    public native int   acl_poweroff();
    public native int  acl_open();
    public native  int acl_close();
    public native  int get_backlight();
    public native  int set_backlight(int  brightness);
    public native  int get_lightvalue();
    public native  int board_select();
    public native  void DebugSwitch(boolean status);
}
