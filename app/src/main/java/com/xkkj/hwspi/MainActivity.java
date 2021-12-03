package com.xkkj.hwspi;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import android_xkkj_api.HwAcl;
//
//import java.security.MessageDigest;
//import java.security.NoSuchAlgorithmException;


public class MainActivity extends AppCompatActivity {
    int produce_Clear_AllInfo_error = 0, produce_set_config_error = 0, get_device_info_error = 0, get_random_data32_error = 0, get_random_data16_error = 0,
            ecdsa_sign_error = 0, export_public_key_error = 0, cmd_set_user_pin_error = 0, get_pin_info1_error = 0, verify_pin_error = 0, get_pin_info2_error = 0, generate_KeyPariById_error = 0,
            security_setConfig_error = 0, security_getConfig_error = 0;

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        HwAcl loader = new HwAcl();
        int board_select = loader.board_select();
        switch (board_select) {
            case -1://凡高
                testFangao_acl();
                break;
            case 1://ArtTV
                testArtTV_acl();
                break;
            case 2://DPhotos
                testDPhotos_acl();
                break;
            default:
                break;
        }
    }

    private void testDPhotos_acl() {
        HwAcl loader = new HwAcl();
        int backlight = 110;
        loader.set_backlight(backlight);//设置背光亮度
        backlight = loader.get_backlight();//获取背光亮度
        Log.d(TAG, "backlight == " + backlight);
        int light = loader.get_lightvalue(); //获取光敏值
        Log.d(TAG, "lightvalue == " + light);
        loader.DebugSwitch(true);
        backlight = loader.board_select();
        Log.d(TAG, "board_select == " + backlight);
//        statusCode = loader.code_DownLoad(false);// 正式是true，测试是false， Launcher里调用
//        Log.d(TAG, "code_DownLoad == " + statusCode);
        activateTask(loader);
    }

    private void testArtTV_acl() {
        HwAcl loader = new HwAcl();
        int statusCode;
        int backlight = 110;
        loader.set_backlight(backlight);//设置背光亮度
        backlight = loader.get_backlight();//获取背光亮度
        Log.d(TAG, "backlight == " + backlight);
        int light = loader.get_lightvalue(); //获取光敏值
        Log.d(TAG, "lightvalue == " + light);
        loader.DebugSwitch(true);
        backlight = loader.board_select();
        Log.d(TAG, "board_select == " + backlight);
        statusCode = loader.code_DownLoad(false);// 正式是true，测试是false， Launcher里调用
        Log.d(TAG, "code_DownLoad == " + statusCode);
        activateTask(loader);
    }

    private void testFangao_acl() {
        HwAcl loader = new HwAcl();
        int backlight = 110;
        loader.set_backlight(backlight);//设置背光亮度
        backlight = loader.get_backlight();//获取背光亮度
        Log.d(TAG, "backlight == " + backlight);
        int light = loader.get_lightvalue(); //获取光敏值
        Log.d(TAG, "lightvalue == " + light);
        loader.DebugSwitch(true);
        backlight = loader.board_select();
        Log.d(TAG, "board_select == " + backlight);
//        statusCode = loader.code_DownLoad(false);// 正式是true，测试是false， Launcher里调用  凡高的板子不需要
        activateTask(loader);
    }

    private void activateTask(HwAcl loader) {
        ApduCmd apd = new ApduCmd();
        byte[] userpin = new byte[4];
        String s;
        int statusCode;
        String cmd;
        for (int i = 1; i <= 1; i++) {
            try {
                Thread.sleep((long) 2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            //打开设备
            loader.acl_open();

            //清除信息
            statusCode = loader.produce_Clear_AllInfo();
            Log.d(TAG, "produce_Clear_AllInfo_configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                produce_Clear_AllInfo_error = produce_Clear_AllInfo_error + 1;

            //设置安全码
            statusCode = loader.security_setConfig(true);
            Log.d(TAG, "acl16_security_setConfig== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                security_setConfig_error = security_setConfig_error + 1;
            byte[] get_status = new byte[1];
            //获取安全码
            statusCode = loader.security_getConfig(get_status);
            s = HexUtils.toHex(get_status);
            Log.d(TAG, "security_getConfig== " + String.format("%04X", statusCode));
            Log.d(TAG, "get_status== " + s);
            if (statusCode != 0x9000)
                security_getConfig_error = security_getConfig_error + 1;

            //设置生产信息
            cmd = apd.cmd_produce_set_device_info();
            statusCode = loader.produce_set_config(HexUtils.toBytes(cmd));
            Log.d(TAG, "cmd = apd.cmd_produce_set_device_info_configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                produce_set_config_error = produce_set_config_error + 1;
            //获取设备信息
            byte[] deviceinfobytes = new byte[80];
            statusCode = loader.get_device_info(deviceinfobytes);
            s = HexUtils.toHex(deviceinfobytes);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "get_device_info== " + s);
            if (statusCode != 0x9000)
                get_device_info_error = get_device_info_error + 1;
////       获取随机数
            char length = 32;
            byte[] randomdata = new byte[length];
            statusCode = loader.get_random_data(randomdata, length);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            String randomNum = HexUtils.toHex(randomdata);
            Log.d(TAG, "randomNum== " + randomNum);
            if (statusCode != 0x9000)
                get_random_data32_error = get_random_data32_error + 1;
            //设置userpin
            randomNum = StringHelper.getNoBlankString(randomNum);
            cmd = apd.cmd_set_user_pin(randomNum);
            statusCode = loader.set_pin(HexUtils.toBytes(cmd));
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                cmd_set_user_pin_error = cmd_set_user_pin_error + 1;
//     获取userpin
            statusCode = loader.get_pin_info(userpin);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "userpin== " + HexUtils.toHex(userpin));
            if (statusCode != 0x9000)
                get_pin_info1_error = get_pin_info1_error + 1;
            //获取随机数
            byte[] randomdata16 = new byte[16];
            statusCode = loader.get_random_data(randomdata16, (char) 16);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            String randomNum16 = HexUtils.toHex(randomdata16);
            Log.d(TAG, "randomNum== " + randomNum16);
            if (statusCode != 0x9000)
                get_random_data16_error = get_random_data16_error + 1;
            //验证userpin
            statusCode = loader.verify_pin(apd.cmd_verify_userpin(randomNum16));
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            if (statusCode != 0x9000)
                verify_pin_error = verify_pin_error + 1;
            //获取userpin
            statusCode = loader.get_pin_info(userpin);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "userpin== " + HexUtils.toHex(userpin));
            if (statusCode != 0x9000)
                get_pin_info2_error = get_pin_info2_error + 1;
            //        //获取公钥
            byte[] publickey = new byte[64];
            statusCode = loader.export_public_key(publickey);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "publickey== " + HexUtils.toHex(publickey));
            if (statusCode != 0x9000)
                export_public_key_error = export_public_key_error + 1;
            //生成keypair
            byte[] keypair = new byte[64];
            statusCode = loader.generate_KeyPariById(keypair);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "keypair== " + HexUtils.toHex(keypair));
            if (statusCode != 0x9000)
                generate_KeyPariById_error = generate_KeyPariById_error + 1;
//        //获取公钥
            byte[] publickey2 = new byte[64];
            statusCode = loader.export_public_key(publickey2);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "publickey2== " + HexUtils.toHex(publickey2));
            if (statusCode != 0x9000)
                export_public_key_error = export_public_key_error + 1;
            //签名
            String msgHash = "4ad24b522ead1746acfc6b7db2cf5d888c7247cbf8af3ae856ad614673613c68";
            byte[] signature = new byte[65];
            statusCode = loader.ecdsa_sign(HexUtils.toBytes(msgHash), signature);
            Log.d(TAG, "configStatus== " + String.format("%04X", statusCode));
            Log.d(TAG, "signature== " + HexUtils.toHex(signature));
            if (statusCode != 0x9000)
                ecdsa_sign_error = ecdsa_sign_error + 1;
            //验签
            byte[] signatureBytes = new byte[64];
            System.arraycopy(signature, 0, signatureBytes, 0, 64);
            byte[] hashBytes = HexUtils.toBytes(msgHash);
            byte[] verifyBytes = new byte[96];
            System.arraycopy(hashBytes, 0, verifyBytes, 0, 32);
            System.arraycopy(signatureBytes, 0, verifyBytes, 32, 64);
            statusCode = loader.ecdsa_verify(verifyBytes);
            Log.d(TAG, "loader.ecdsa_verify  statusCode == " + String.format("%04X", statusCode));

            loader.acl_close();
            Log.d(TAG, "=======测试的第" + i + "次===========");
            Log.d(TAG, "produce_Clear_AllInfo errorr：" + produce_Clear_AllInfo_error + "次");
            Log.e(TAG, "cmd_produce_set_device_info errorr：" + produce_set_config_error + "次");
            Log.e(TAG, "get_device_info_error errorr：" + get_device_info_error + "次");
            Log.e(TAG, "get_random_data32_error errorr：" + get_random_data32_error + "次");
            Log.e(TAG, "cmd_set_user_pin_error errorr：" + cmd_set_user_pin_error + "次");
            Log.e(TAG, "get_pin_info1_error errorr：" + get_pin_info1_error + "次");
            Log.e(TAG, "get_random_data16_error errorr：" + get_random_data16_error + "次");
            Log.e(TAG, "verify_pin_error errorr：" + verify_pin_error + "次");
            Log.e(TAG, "get_pin_info2_error errorr：" + get_pin_info2_error + "次");
            Log.e(TAG, "generate_KeyPariById_error errorr：" + generate_KeyPariById_error + "次");
            Log.e(TAG, "export_public_key_error errorr：" + export_public_key_error + "次");
            Log.e(TAG, "ecdsa_sign_error errorr：" + ecdsa_sign_error + "次");
            Log.e(TAG, "security_setConfig_error: " + security_setConfig_error + "次");
            Log.e(TAG, "security_getConfig_error:" + security_getConfig_error + "次");
        }
    }

}










