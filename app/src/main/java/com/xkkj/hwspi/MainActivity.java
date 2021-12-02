package com.xkkj.hwspi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android_xkkj_api.HwAcl;

import android.util.Log;
import android.widget.TextView;
//
//import java.security.MessageDigest;
//import java.security.NoSuchAlgorithmException;




public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        TextView tv = findViewById(R.id.TW);
        int produce_Clear_AllInfo_error=0,produce_set_config_error=0,get_device_info_error=0,get_random_data32_error=0,get_random_data16_error=0,
        ecdsa_sign_error=0,export_public_key_error=0,cmd_set_user_pin_error=0,get_pin_info1_error=0,verify_pin_error=0,get_pin_info2_error=0,generate_KeyPariById_error=0;
        HwAcl loader = new HwAcl();
        ApduCmd apd = new ApduCmd();
        byte[] userpin = new byte[4];
        int statusCode;
        String cmd ,s;
        int backlight =110;
        loader.set_backlight(backlight);//设置背光亮度
        backlight = loader.get_backlight();//获取背光亮度
        Log.d(TAG, "backlight == " + backlight);
        int light=loader.get_lightvalue(); //获取光敏值
        Log.d(TAG, "lightvalue == " + light);
        loader.DebugSwitch(false);
        //loader.code_update(false);
        backlight=loader.board_select();
        Log.d(TAG, "board_select == " + backlight);
        //loader.code_update(false);
        //loader.code_DownLoad(false);
        for(int i=1; i<=0; i++){
        try {
            Thread.sleep((long) 2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
            //打开设备
//            loader.acl_open();
//            statusCode = loader.security_setConfig(false);
//            Log.d(TAG, "acl16_security_setConfig== " + String.format("%04X", statusCode));
//            byte[] get_status = new byte[1];
//            statusCode = loader.security_getConfig(get_status);
//            s = HexUtils.toHex(get_status);
//            Log.d(TAG, "security_getConfig== " + String.format("%04X", statusCode));
//            Log.d(TAG, "get_status== " + s);

            //清除信息
//            statusCode = loader.produce_Clear_AllInfo();
//            Log.d(TAG, "produce_Clear_AllInfo_configStatus== " + String.format("%04X", statusCode));
//            if(statusCode != 0x9000)
//                produce_Clear_AllInfo_error = produce_Clear_AllInfo_error + 1;
//            statusCode = loader.produce_Clear_Cos();
//            Log.d(TAG, "produce_Clear_COS== " + String.format("%04X", statusCode));
//            loader.acl_close();
//            loader.acl_poweroff();
//            loader.acl_poweron();
//            loader.code_DownLoad(false);
//            loader.acl_close();
            loader.code_update(false);
            loader.acl_open();
            //设置生产信息
            cmd = apd.cmd_produce_set_device_info();
            statusCode = loader.produce_set_config(HexUtils.toBytes(cmd));
            Log.d(TAG, "cmd = apd.cmd_produce_set_device_info_configStatus== " + String.format("%04X", statusCode));
            if(statusCode != 0x9000)
                produce_set_config_error = produce_set_config_error + 1;
            //获取设备信息
            byte[] deviceinfobytes = new byte[80];
            statusCode = loader.get_device_info(deviceinfobytes);
            s = HexUtils.toHex(deviceinfobytes);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "get_device_info== " + s);
            if(statusCode != 0x9000)
                get_device_info_error = get_device_info_error + 1;
//       获取随机数
            char length = 32;
            byte[] randomdata = new byte[length];
            statusCode = loader.get_random_data(randomdata, length);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            String randomNum = HexUtils.toHex(randomdata);
            Log.d(TAG, "randomNum== " + randomNum);
            if(statusCode != 0x9000)
                get_random_data32_error = get_random_data32_error + 1;
            //设置userpin
            randomNum = StringHelper.getNoBlankString(randomNum);
            cmd = apd.cmd_set_user_pin(randomNum);
            statusCode = loader.set_pin(HexUtils.toBytes(cmd));
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            if(statusCode != 0x9000)
                cmd_set_user_pin_error = cmd_set_user_pin_error + 1;
//     获取userpin
            statusCode = loader.get_pin_info(userpin);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "userpin== " + HexUtils.toHex(userpin));
            if(statusCode != 0x9000)
                get_pin_info1_error = get_pin_info1_error + 1;
            //获取随机数
            byte[] randomdata16 = new byte[16];
            statusCode = loader.get_random_data(randomdata16, (char) 16);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            String randomNum16 = HexUtils.toHex(randomdata16);
            Log.d(TAG, "randomNum== " + randomNum16);
            if(statusCode != 0x9000)
                get_random_data16_error = get_random_data16_error + 1;
            //验证userpin
            statusCode = loader.verify_pin(apd.cmd_verify_userpin(randomNum16));
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            if(statusCode != 0x9000)
                verify_pin_error = verify_pin_error + 1;
            //获取userpin
            statusCode = loader.get_pin_info(userpin);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "userpin== " + HexUtils.toHex(userpin));
            if(statusCode != 0x9000)
                get_pin_info2_error = get_pin_info2_error + 1;
            //生成keypair
            byte[] keypair = new byte[64];
            statusCode = loader.generate_KeyPariById(keypair);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "keypair== " + HexUtils.toHex(keypair));
            if(statusCode != 0x9000)
                generate_KeyPariById_error = generate_KeyPariById_error + 1;
//        //获取公钥
            byte[] publickey = new byte[64];
            statusCode = loader.export_public_key(publickey);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "keypair== " + HexUtils.toHex(publickey));
            if(statusCode != 0x9000)
                export_public_key_error = export_public_key_error + 1;
            //签名
            String msgHash = "4ad24b522ead1746acfc6b7db2cf5d888c7247cbf8af3ae856ad614673613c68";

            byte[] signature = new byte[65];
            statusCode = loader.ecdsa_sign(HexUtils.toBytes(msgHash), signature);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "signature== " + HexUtils.toHex(signature));
            if(statusCode != 0x9000)
                ecdsa_sign_error = ecdsa_sign_error + 1;
//        //验签


            //刷cos，写安全序列
            loader.acl_close();
            Log.d(TAG, "=======测试的第"+i+"次===========");
            Log.d(TAG,"produce_Clear_AllInfo errorr："+produce_Clear_AllInfo_error+"次");
            Log.e(TAG,"cmd_produce_set_device_info errorr："+ produce_set_config_error +"次");
            Log.e(TAG,"get_device_info_error errorr："+ get_device_info_error+"次");
            Log.e(TAG,"get_random_data32_error errorr："+get_random_data32_error+"次");
            Log.e(TAG,"cmd_set_user_pin_error errorr："+cmd_set_user_pin_error +"次");
            Log.e(TAG,"get_pin_info1_error errorr："+ get_pin_info1_error +"次");
            Log.e(TAG,"get_random_data16_error errorr："+ get_random_data16_error +"次");
            Log.e(TAG,"verify_pin_error errorr："+ verify_pin_error +"次");
            Log.e(TAG,"get_pin_info2_error errorr："+ get_pin_info2_error+"次");
            Log.e(TAG,"generate_KeyPariById_error errorr："+ generate_KeyPariById_error +"次");
            Log.e(TAG,"export_public_key_error errorr："+ export_public_key_error+"次");
            Log.e(TAG,"ecdsa_sign_error errorr："+ecdsa_sign_error +"次");
        }


//        ApduCmd apd = new ApduCmd();
//        apd.cmd_get_device_info();
//        apd.cmd_produce_set_device_info();
//        String randomNum32 = "31 29 59 1A 65 A4 6C B0 01 D8 82 C7 4C 4A E9 C0 D1 1E 1C 3C 77 D3 E1 34 92 17 78 3A 0B 67 CB EB";
//        apd.cmd_set_user_pin(randomNum32);
//        apd.cmd_get_pin_info();
//        String randomNum16 = "8D 30 25 F3 1B AC FD F2 15 B4 DA 7A 74 20 7A 93";
//        apd.cmd_verify_userpin(randomNum16);
//        apd.cmd_get_random16();
//        apd.cmd_get_random();
//        apd.cmd_generate_keypari_by_id();
//        apd.cmd_export_publickey_by_id();
//        String msgHash = "4ad24b522ead1746acfc6b7db2cf5d888c7247cbf8af3ae856ad614673613c68";
//        apd.cmd_ecdsa_sign(msgHash);

//        Threadtest T1 = new Threadtest("acl16_test1");
//        T1.start();

//        Threadtest T2 = new Threadtest("acl16_test2");
//        T2.start();
    }
}










