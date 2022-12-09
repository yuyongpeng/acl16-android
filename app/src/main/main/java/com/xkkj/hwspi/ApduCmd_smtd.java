package com.xkkj.hwspi;

import static com.xkkj.hwspi.HexHelper.hexStringToByteArray;

import android.util.Log;

import org.apache.commons.lang3.ArrayUtils;

import java.nio.ByteOrder;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import struct.JavaStruct;
import struct.StructException;


public class ApduCmd_smtd {
    /**
     * {(byte) 0x80, (byte) 0x10, (byte) 0x01, (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x20};
     */
    String header = "80";
    String length;
    String channel; //通道
    String cmd;//命令
    String p1;//第一个参数
    String p2;//第二个参数
    String lc;//下发的数据长度
    String le;//接收的数据长度
    String crc; //crc高位+crc低位


    public String crc16(String text) {
        int crc = ApduCmdCRC16.crc(text);
        String crcStr = Integer.toHexString(crc);
        System.out.println(crcStr);
        return crcStr;
    }

    /**
     * 0x82 用户信息清除指令（恢复空片，不清除COS）
     * <p>
     * 80 00 08 80 82 A8 E1 00 00 00 00 FB 7C
     *
     * @return
     */
    public String cmd_produce_clear_allinfo() {
        header = "80";
        channel = "80";
        cmd = "82";
        p1 = "A8";
        p2 = "E1";
        lc = "0000";
        le = "0000";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "cmdHex==" + all);
        return all;
    }

    /**
     * 0x10 获取随机数  32字节
     * <p>
     * 80 00 08 80 10 01 00 00 00 00 20 5b 02
     *
     * @return
     */
    public String cmd_get_random() {
        header = "80";
        length = "";
        channel = "80";
        cmd = "10";
        p1 = "01";//"P1 = 0时，获取Le固定数；P1 =1 时，获取le长度的随机数"
        p2 = "01";//"P2 = 0时，随机数不做缓存；P2=1 时，随机数缓存；
        lc = "0000";
        le = "0020";
        crc = "";
        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "cmdHex==" + all);
        return all;
    }

    /**
     * 0x10 获取随机数   16字节
     * 80 00 08 80 10 01 00 00 00 00 20 5b 02
     *
     * @return
     */
    public String cmd_get_random16() {
        header = "80";
        length = "";
        channel = "80";
        cmd = "10";
        p1 = "01";//"P1 = 0时，获取Le固定数；P1 =1 时，获取le长度的随机数"
        p2 = "01";//"P2 = 0时，随机数不做缓存；P2=1 时，随机数缓存；
        lc = "0000";
        le = "0010";
        crc = "";
        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "cmdHex==" + all);
        return all;
    }


    /**
     * 0x01 获取芯片信息
     *
     * @return
     */
    public String cmd_get_device_info() {
        header = "80";
        channel = "80";
        cmd = "01";
        p1 = "00";
        p2 = "00";
        lc = "0000";
        le = "0050";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "all==" + all);
        return all;
    }

    /**
     * 0x81 设置芯片信息
     *
     * @return
     */
    public String cmd_produce_set_device_info() {

        header = "80";
        channel = "80";
        cmd = "81";
        p1 = "7C";
        p2 = "4D";
        lc = "0030";
        le = "0000";

        ApduCmdDeviceInfoConfig apduCmdDeviceInfoConfig = new ApduCmdDeviceInfoConfig();
        byte[] bytesName = "dphotosCrypto999".getBytes();
        apduCmdDeviceInfoConfig.setDeviceName(bytesName);
        apduCmdDeviceInfoConfig.setPinMaxRetryTimes((byte) 0X0F);
        byte[] dataArr = new byte[48];
        try {
            dataArr = JavaStruct.pack(apduCmdDeviceInfoConfig, ByteOrder.LITTLE_ENDIAN);
        } catch (StructException e) {
            e.printStackTrace();
        }
        Log.d(MainActivity.class.getSimpleName(),"dataArr== "+HexUtils.toHex(dataArr));
        //return HexUtils.toHex(dataArr);
        String contentStr = channel + cmd + p1 + p2 + lc + le;
        byte[] contentArr = hexStringToByteArray(contentStr);

        length = String.format("%04X", contentArr.length + dataArr.length);

        byte[] bodyArr = ArrayUtils.addAll(contentArr, dataArr);

        int crcb = ApduCmdCRC16.crcb(bodyArr);
        crc = String.format("%04X", crcb);

        String body = HexHelper.bytes2HexStr(bodyArr);

        String cmd = header + length + body + crc;
        Log.e("cmdpack", "cmd---" + cmd);
        return cmd;
    }



    /**
     * 0x02 设置UserPin
     * 权限：无
     * 1.调用随机数命令，获取32字节的随机数，P2=1(随机数需要COS缓存)
     * 2.将随机数做SHA1处理，得到20字节的摘要值，取前16字节，作为AES128 ECB算法的密钥。
     * 3.用第二步中的密钥加密用户PIN码（用户PIN码不足32字节的，随意填充至32字节）；
     * 4.将加密后的密文作为APDU的data下发；
     * LC为密文的长度，必须为32字节
     * P1参数为实际数据中有效PIN码的长度；
     *
     * @return
     */
    public String cmd_set_user_pin(String randomNum) {
     //   randomNum = "43 26 bd e8 5a 82 93 2e 86 df c8 47 0c fb 7b 3e 76 6e 44 c5 b0 2f 3b 98 cd cf 9e 8e 46 85 df f0";
        randomNum = StringHelper.getNoBlankString(randomNum);
        byte[] dataArr = new byte[32];
        String data = null;
        try {
            //构成一个消息，计算其散列函数值
            MessageDigest sha1 = MessageDigest.getInstance("SHA-1");
            byte[] bytes = hexStringToByteArray(randomNum);
            sha1.update(bytes);
            //对digest方法的调用则说明输入消息结束。进行初始化，update提交的数据丢失。Digest方法也可以把输入的最后一部分作为参数：
            byte[] hash = sha1.digest();
            byte[] key = ArrayUtils.subarray(hash, 0, 16);
//            System.out.println("cmd==key== " + HexHelper.bytes2HexStr(key));
            byte[] pin = new byte[32];
            pin = "00000000000000000000000000000000".getBytes();
            byte[] encrypt = EncryptUtil.encrypt(pin, key);
            dataArr = ArrayUtils.subarray(encrypt, 0, 32);
            data = HexHelper.bytes2HexStr(dataArr);
//            System.out.println("cmd== " + bytes2HexString);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
         // return  data;
        header = "80";
        channel = "80";
        cmd = "02";
        p1 = "20";
        p2 = "00";
        lc = "0020";
        le = "0000";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] contentArr = hexStringToByteArray(content);

        length = String.format("%04X", contentArr.length + dataArr.length);

        byte[] bodyArr = ArrayUtils.addAll(contentArr, dataArr);

        int crcb = ApduCmdCRC16.crcb(bodyArr);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + data + crc;
        Log.e("cmdpack", "cmd_set_user_pin_all==" + all);
        return all;
    }

    /**
     * 0x03 修改UserPin
     * 权限：需userpin认证通过
     * 1.修改PIN码参数前，需保证cos内部pin码认证已经通过；
     * 使用用户输入的旧的pin码，做SHA1摘要，计算摘要值，取前20字节；
     * 加密用AES128ECB加密新的PIN码；
     * 与设置userpin一样，用户的PIN码最长支持32字节，不足32字节的，填充补齐；
     * LC，加密后的密文长度
     * P1，实际的新的PIN码长度
     */
    public String cmd_change_user_pin() {
        return "";
    }


    /**
     * 0x04  获取PIN信息和状态
     * 权限：无
     * 获取PIN码的状态和信息，状态结构体为：
     * typedef struct
     * {
     * UINT8 PinIsExist;//pin码是否存在
     * UINT8 PinAuthStatus;//PIN码的认证状态 0为未认证； 0x10为user认证通过； 0xf0为锁定；
     * UINT8 MaxRetryTimes;//pin码的最大可重试次数
     * UINT8 LeftRetryTimes;//PIN码的剩余重试次数
     * }PinStatusInfo;
     */
    public String cmd_get_pin_info() {
        header = "80";
        channel = "80";
        cmd = "04";
        p1 = "00";
        p2 = "00";
        lc = "0000";
        le = "0004";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "cmd_get_pin_info_all==" + all);
        return all;
    }

    /**
     * 0x05  验证PIN （认证PIN / 登录）
     * 权限：无
     * 调用验证userpin前需调用获取随机数命令获取16字节随机数，且P2=1缓存随机数
     * 使用用户PIN码计算SHA1值，取前16字节作为密钥；
     * 用AES128 ECB加密获取来的随机数；
     * 下发到COS，cos用同样的计算方式比对
     * <p>
     * 硬件断电后，需要重新验证PIN
     * @param
     */
    public String cmd_verify_userpin(String randomNum) {
        //randomNum = "fb 6b 8a 93 ca 44 6b 9e 49 06 e6 52 78 f1 a4 47";
        randomNum = StringHelper.getNoBlankString(randomNum);
        byte[] dataArr = new byte[16];

        try {
            //构成一个消息，计算其散列函数值
            MessageDigest sha1 = MessageDigest.getInstance("SHA-1");
            String pin = "00000000000000000000000000000000";
            byte[] bytes = pin.getBytes();
            sha1.update(bytes);
            //对digest方法的调用则说明输入消息结束。进行初始化，update提交的数据丢失。Digest方法也可以把输入的最后一部分作为参数：
            byte[] hash = sha1.digest();
            byte[] key = ArrayUtils.subarray(hash, 0, 16);
//            System.out.println("cmd==key== " + HexHelper.bytes2HexStr(key));
            byte[] randomNumArray = hexStringToByteArray(randomNum);
            byte[] encrypt = EncryptUtil.encrypt(randomNumArray, key);
            dataArr = ArrayUtils.subarray(encrypt, 0, 16);
//            data = HexHelper.bytes2HexStr(dataArr);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
          //return dataArr;
        header = "80";
        channel = "80";
        cmd = "05";
        p1 = "00";
        p2 = "00";
        lc = "0010";
        le = "0000";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] contentArr = hexStringToByteArray(content);

        length = String.format("%04X", contentArr.length + dataArr.length);

        byte[] bodyArr = ArrayUtils.addAll(contentArr, dataArr);
        String body = HexHelper.bytes2HexStr(bodyArr);
        System.out.println("cmd1== " + body);
        int crcb = ApduCmdCRC16.crcb(bodyArr);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + body + crc;
        Log.e("cmdpack", "cmd_verify_userpin_all==" + all);
        return all;
    }

    /**
     * 0x0A 生成ecdsa密钥对
     * 权限：PIN码认证通过
     */
    public String cmd_generate_keypari_by_id() {
        header = "80";
        channel = "80";
        cmd = "0A";
        p1 = "01";
        p2 = "00";
        lc = "0000";
        le = "0040";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "cmd_generate_keypari_by_id_cmdHex==" + all);
        return all;
    }

    /**
     * 0x0D 导出公钥
     * 权限：PIN码认证通过
     */
    public String cmd_export_publickey_by_id() {
        header = "80";
        channel = "80";
        cmd = "0D";
        p1 = "01";
        p2 = "00";
        lc = "0000";
        le = "0040";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] bytes = hexStringToByteArray(content);

        length = String.format("%04X", bytes.length);

        int crcb = ApduCmdCRC16.crcb(bytes);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + content + crc;
        Log.e("cmdpack", "cmd_export_publickey_by_id_cmdHex==" + all);
        return all;
    }

    /**
     * 0x0B ECDSA签名
     * 权限：PIN码认证通过
     * 首次调用，必须P2=0，在签名的同时会将随机数缓存；
     * 重复签名，如果需要固定签名值，则传入P2=1；如不需要固定签名值，则P2继续传0，重新生成随机数；
     */
    public String cmd_ecdsa_sign(String msgHash) {
      //  String msgHash = "4ad24b522ead1746acfc6b7db2cf5d888c7247cbf8af3ae856ad614673613c68";
        byte[] dataArr = hexStringToByteArray(msgHash);

        header = "80";
        channel = "80";
        cmd = "0B";
        p1 = "01";
        p2 = "00";
        lc = "0020";
        le = "0041";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] contentArr = hexStringToByteArray(content);

        length = String.format("%04X", contentArr.length + dataArr.length);

        byte[] bodyArr = ArrayUtils.addAll(contentArr, dataArr);
        String body = HexHelper.bytes2HexStr(bodyArr);
        System.out.println("cmd1== " + body);
        int crcb = ApduCmdCRC16.crcb(bodyArr);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + body + crc;
        Log.e("cmdpack", "cmd_ecdsa_sign_all==" + all);
        return all;
    }

    public String cmd_ecdsa_sign_repeat(String msgHash) {
        byte[] dataArr = hexStringToByteArray(msgHash);

        header = "80";
        channel = "80";
        cmd = "0B";
        p1 = "01";
        p2 = "01";
        lc = "0020";
        le = "0041";

        String content = channel + cmd + p1 + p2 + lc + le;
        byte[] contentArr = hexStringToByteArray(content);

        length = String.format("%04X", contentArr.length + dataArr.length);

        byte[] bodyArr = ArrayUtils.addAll(contentArr, dataArr);
        String body = HexHelper.bytes2HexStr(bodyArr);
        System.out.println("cmd1== " + body);
        int crcb = ApduCmdCRC16.crcb(bodyArr);
        crc = String.format("%04X", crcb);
        Log.e("cmdpack", "crc==" + crc);

        String all = header + length + body + crc;
        Log.e("cmdpack", "all==" + all);
        return all;
    }


    public void cmd_set_user_pin() {
    }
}
