package com.xkkj.hwspi;



import static android.content.ContentValues.TAG;

import android.util.Log;

import android_xkkj_api.HwAcl;

public class Threadtest  implements Runnable {
    private Thread t;
    private String threadName;
    int produce_Clear_AllInfo_error=0,produce_set_config_error=0,get_device_info_error=0,get_random_data32_error=0,get_random_data16_error=0,
            ecdsa_sign_error=0,export_public_key_error=0,cmd_set_user_pin_error=0,get_pin_info1_error=0,verify_pin_error=0,get_pin_info2_error=0,generate_KeyPariById_error=0;
    HwAcl loader = new HwAcl();
    ApduCmd apd = new ApduCmd();
    byte[] userpin = new byte[4];
    int statusCode;
    String cmd;
    Threadtest(String name){
        threadName = name;
    }
    public void run(){
        Log.d(TAG,"Running " +  threadName );
        for (int i = 1; i <= 1500; i++) {
            Log.d(TAG, "线程"+threadName+"测试的第" + i + "次===========");
            try {
                Thread.sleep((long) 2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            //打开设备
            loader.acl_open("/dev/ttyS4",115200);
            //清除信息
            statusCode = loader.produce_Clear_AllInfo();
            Log.d(TAG, "produce_Clear_AllInfo_configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                Log.d(TAG, "produce_Clear_AllInfo errorr：" + (produce_Clear_AllInfo_error = produce_Clear_AllInfo_error + 1) + "次");
            //设置生产信息
            cmd = apd.cmd_produce_set_device_info();
            statusCode = loader.produce_set_config(HexUtils.toBytes(cmd));
            Log.d(TAG, "cmd = apd.cmd_produce_set_device_info_configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                Log.e(TAG, "cmd_produce_set_device_info errorr：" + (produce_set_config_error = produce_set_config_error + 1) + "次");
            //获取设备信息
            byte[] deviceinfobytes = new byte[80];
            statusCode = loader.get_device_info(deviceinfobytes);
            String s = HexUtils.toHex(deviceinfobytes);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "get_device_info== " + s);
            if (statusCode != 0x9000)
                Log.e(TAG, "get_device_info_error errorr：" + (get_device_info_error = get_device_info_error + 1) + "次");
//       获取随机数
            char length = 32;
            byte[] randomdata = new byte[length];
            statusCode = loader.get_random_data(randomdata, length);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            String randomNum = HexUtils.toHex(randomdata);
            Log.d(TAG, "randomNum== " + randomNum);
            if (statusCode != 0x9000)
                Log.e(TAG, "get_random_data32_error errorr：" + (get_random_data32_error = get_random_data32_error + 1) + "次");
            //设置userpin
            randomNum = StringHelper.getNoBlankString(randomNum);
            cmd = apd.cmd_set_user_pin(randomNum);
            statusCode = loader.set_pin(HexUtils.toBytes(cmd));
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                Log.e(TAG, "cmd_set_user_pin_error errorr：" + (cmd_set_user_pin_error = cmd_set_user_pin_error + 1) + "次");
//     获取userpin
            statusCode = loader.get_pin_info(userpin);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "userpin== " + HexUtils.toHex(userpin));
            if (statusCode != 0x9000)
                Log.e(TAG, "get_pin_info1_error errorr：" + (get_pin_info1_error = get_pin_info1_error + 1) + "次");
            //获取随机数
            byte[] randomdata16 = new byte[16];
            statusCode = loader.get_random_data(randomdata16, (char) 16);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            String randomNum16 = HexUtils.toHex(randomdata16);
            Log.d(TAG, "randomNum== " + randomNum16);
            if (statusCode != 0x9000)
                Log.e(TAG, "get_random_data16_error errorr：" + (get_random_data16_error = get_random_data16_error + 1) + "次");
            //验证userpin
            statusCode = loader.verify_pin(apd.cmd_verify_userpin(randomNum16));
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                Log.e(TAG, "verify_pin_error errorr：" + (verify_pin_error = verify_pin_error + 1) + "次");
            //获取userpin
            statusCode = loader.get_pin_info(userpin);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "userpin== " + HexUtils.toHex(userpin));
            if (statusCode != 0x9000)
                Log.e(TAG, "get_pin_info2_error errorr：" + (get_pin_info2_error = get_pin_info2_error + 1) + "次");
            //生成keypair
            byte[] keypair = new byte[64];
            statusCode = loader.generate_KeyPariById(keypair);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "keypair== " + HexUtils.toHex(keypair));
            if (statusCode != 0x9000)
                Log.e(TAG, "generate_KeyPariById_error errorr：" + (generate_KeyPariById_error = generate_KeyPariById_error + 1) + "次");
//        //获取公钥
            byte[] publickey = new byte[64];
            statusCode = loader.export_public_key(publickey);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "keypair== " + HexUtils.toHex(publickey));
            if (statusCode != 0x9000)
                Log.e(TAG, "export_public_key_error errorr：" + (export_public_key_error = export_public_key_error + 1) + "次");
            //签名
            String msgHash = "4ad24b522ead1746acfc6b7db2cf5d888c7247cbf8af3ae856ad614673613c68";
            byte[] signature = new byte[65];
            statusCode = loader.ecdsa_sign(HexUtils.toBytes(msgHash), signature);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "signature== " + HexUtils.toHex(signature));
            if (statusCode != 0x9000)
                Log.e(TAG, "ecdsa_sign_error errorr：" + (ecdsa_sign_error = ecdsa_sign_error + 1) + "次");

//        //验签
            loader.acl_close();
        }

    }
    public void start() {
        if (t == null) {
            t = new Thread (this, threadName);
            t.start ();
        }
    }
}
