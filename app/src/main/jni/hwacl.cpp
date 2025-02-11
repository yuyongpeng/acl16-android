#include "android_xkkj_api_HwAcl.h"

static Acl16 acl16;


char* jstringToChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength( barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}


jstring charToJstring(JNIEnv *env, const char *pat) {
    jclass strClass = env->FindClass( "java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>","([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}



char* ConvertJByteaArrayToChars(JNIEnv *env, jbyteArray bytearray)
{
   char *chars = NULL;
   jbyte *bytes = env->GetByteArrayElements(bytearray, 0);
   int chars_len = env->GetArrayLength(bytearray);
   chars = new char[chars_len + 1];
   memset(chars,0,chars_len + 1);
   memcpy(chars, bytes, chars_len);
   chars[chars_len] = 0;
   env->ReleaseByteArrayElements(bytearray, bytes, 0);
   return chars;
}


/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_open
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1open
  (JNIEnv *env, jobject jobj)
 {
        int errnoNu = acl16_open(&acl16,0);
        if (errnoNu != ISOSW_SUCCESSFUL) {
                LOGE("acl16_open exec failed!");
            	return errnoNu;
        }
        return ISOSW_SUCCESSFUL;
 }

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_close
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1close
  (JNIEnv *env, jobject jobj)
{
        int errnoNu = acl16_close(&acl16);
        if (errnoNu != ISOSW_SUCCESSFUL) {
            LOGE("acl16_close exec failed!");
            return errnoNu;
        }
        return ISOSW_SUCCESSFUL;
}


/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    produce_set_config
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_produce_1set_1config
  (JNIEnv *env, jobject job, jbyteArray product_config)
{
    char *buffer = ConvertJByteaArrayToChars(env, product_config);
    int errnoNu = acl16_produce_set_config(&acl16,(uint8_t*)buffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_produce_set_config exec failed！");
        return errnoNu;
    }
   // env->ReleaseByteArrayElements(product_config,buffer,0);
    return ISOSW_SUCCESSFUL;
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_produce_1Clear_1AllInfo
  (JNIEnv *env, jobject  jobj)
 {
    int errnoNu = acl16_produce_Clear_AllInfo(&acl16);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_produce_Clear_AllInfo exec failed！");
        return errnoNu;
     }
    return ISOSW_SUCCESSFUL;
 }

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    produce_Clear_Cos
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_produce_1Clear_1Cos
  (JNIEnv *env, jobject jobj)
 {
     int errnoNu = acl16_produce_Clear_Cos(&acl16);
     if (errnoNu != ISOSW_SUCCESSFUL) {
            LOGE("acl16_produce_Clear_Cos exec failed！");
          return errnoNu;
     }
     return ISOSW_SUCCESSFUL;
 }


 /*
  * Class:     com_xkkj_hwspi_HwSpi
  * Method:    get_random_data
  * Signature: ([BC)I
  */
 JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1random_1data
   (JNIEnv *env, jobject jobj, jbyteArray randdata, jchar randLenth)
 {
         jbyte *buffer = (jbyte*)malloc(randLenth+1);
         if(NULL == buffer)
         {
             LOGE("malloc failed！");
             return NULL;
         }
         int errnoNu = acl16_get_random_data(&acl16,(uint8_t*)buffer,(uint16_t)randLenth);
         if (errnoNu != ISOSW_SUCCESSFUL) {
             LOGE("acl16_get_random_data exec failed!");
         	return errnoNu;
         }
         env->SetByteArrayRegion(randdata,0,randLenth,(const jbyte*)buffer);
         free(buffer);
         return ISOSW_SUCCESSFUL;
 }

/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    get_device_info
 * Signature: ([B)I
 */

JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1device_1info
  (JNIEnv *env , jobject jobj, jbyteArray deviceinfo)
{
    int Lenth = env->GetArrayLength(deviceinfo);
    jbyte *buffer = (jbyte*)malloc(Lenth+1);
    if(NULL == buffer)
     {
         LOGE("malloc failed！");
          return NULL;
     }
    int errnoNu = acl16_get_device_info(&acl16,(uint8_t*)buffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_get_device_info exec failed!");
        return errnoNu;
    }
    env->SetByteArrayRegion(deviceinfo,0,Lenth,(const jbyte*)buffer);
    return ISOSW_SUCCESSFUL;
}




/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    set_pin
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_set_1pin
 (JNIEnv *env, jobject jobj, jbyteArray pin_info)
{
    jbyte *buffer = env->GetByteArrayElements(pin_info,0);
    int errnoNu =acl16_set_pin(&acl16,(uint8_t*)buffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_set_pin exec failed!");
        return errnoNu;
    }
    env->ReleaseByteArrayElements(pin_info,buffer,0);
    return ISOSW_SUCCESSFUL;

}

/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    change_pin
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_change_1pin
 (JNIEnv *env, jobject jobj, jbyteArray pin_info)
 {
        jbyte *buffer = env->GetByteArrayElements(pin_info,0);
        int errnoNu = acl16_change_pin(&acl16,(uint8_t*)buffer);
        if (errnoNu != ISOSW_SUCCESSFUL) {
            LOGE("acl16_change_pin exec failed!");
            return errnoNu;
        }
        env->ReleaseByteArrayElements(pin_info,buffer,0);
        return ISOSW_SUCCESSFUL;
 }


/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    get_pin_info
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1pin_1info
  (JNIEnv *env, jobject jobj, jbyteArray pin_info)
{
        jbyte *buffer = (jbyte*)malloc(sizeof(Acl16PinInfo));
        if(NULL == buffer)
        {
            LOGE("malloc failed！");
            return NULL;
        }
        memset(buffer, 0, sizeof(Acl16PinInfo));
        int errnoNu = acl16_get_pin_info(&acl16,(uint8_t*)buffer);
        if (errnoNu != ISOSW_SUCCESSFUL) {
            LOGE("acl16_get_pin_info exec failed!");
        	return errnoNu;
        }
        env->SetByteArrayRegion(pin_info,0,sizeof(Acl16PinInfo),(const jbyte*)buffer);
        free(buffer);
        return ISOSW_SUCCESSFUL;
}

/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    verify_pin
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_verify_1pin
  (JNIEnv *env, jobject jobj, jbyteArray pin_info)
  {
      jbyte *buffer = env->GetByteArrayElements(pin_info,0);
      int errnoNu = acl16_verify_pin(&acl16,(uint8_t*)buffer);
      if (errnoNu != ISOSW_SUCCESSFUL) {
           LOGE("acl16_verify_pin exec failed!");
           return errnoNu;
      }
      env->ReleaseByteArrayElements(pin_info,buffer,0);
      return ISOSW_SUCCESSFUL;
  }


/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    generate_KeyPariById
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_generate_1KeyPariById
  (JNIEnv *env, jobject jobj, jbyteArray KeyPari)
{
        int chars_len = env->GetArrayLength(KeyPari);
        jbyte *buffer = (jbyte*)malloc(chars_len+1);
        if(NULL == buffer)
        {
              LOGE("malloc failed！");
              return NULL;
        }
        int errnoNu = acl16_generateKeyPariById(&acl16,(uint8_t*)buffer);
        if (errnoNu != ISOSW_SUCCESSFUL) {
              LOGE("acl16_get_pin_info exec failed!");
              return errnoNu;
        }
        env->SetByteArrayRegion(KeyPari,0,chars_len,(const jbyte*)buffer);
        free(buffer);
        return ISOSW_SUCCESSFUL;
}



/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    ecdsa_sign
 * Signature: ([B[B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_ecdsa_1sign
  (JNIEnv *env, jobject jobj, jbyteArray  txData, jbyteArray  signature)
{
    jbyte *txbuffer = env->GetByteArrayElements(txData,0);
    jbyte *rxbuffer = (jbyte*)malloc(65);
    if(NULL == rxbuffer)
    {
         LOGE("malloc failed!");
         return NULL;
    }
    int errnoNu = acl16_ecdsa_sign(&acl16,(uint8_t*)txbuffer,(uint8_t*)rxbuffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
         LOGE("acl16_ecdsa_sign exec failed!");
         return errnoNu;
    }
    env->ReleaseByteArrayElements(txData,txbuffer,0);
    env->SetByteArrayRegion(signature,0,65,(const jbyte*)rxbuffer);
    return ISOSW_SUCCESSFUL;
}

/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    ecdsa_verify
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_ecdsa_1verify
  (JNIEnv *env, jobject jobj,  jbyteArray signature)
{
     jbyte *buffer = env->GetByteArrayElements(signature,0);
     int errnoNu = acl16_ecdsa_verify(&acl16,(uint8_t*)buffer);
     if (errnoNu != ISOSW_SUCCESSFUL) {
          LOGE("acl16_ecdsa_verify exec failed!");
          return errnoNu;
     }
     env->ReleaseByteArrayElements(signature,buffer,0);
     return ISOSW_SUCCESSFUL;
}
/*
 * Class:     com_xkkj_hwspi_HwSpi
 * Method:    export_public_key
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_export_1public_1key
  (JNIEnv *env, jobject jobj, jbyteArray pubkey)
{
    jbyte *buffer = (jbyte*)malloc(64);
    if(NULL == buffer)
    {
        LOGE("malloc failed!");
        return NULL;
    }
    int errnoNu = acl16_export_public_key(&acl16,(uint8_t*)buffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_export_public_key exec failed!");
        return errnoNu;
    }
    env->SetByteArrayRegion(pubkey,0,64,(const jbyte*)buffer);
    free(buffer);
    return ISOSW_SUCCESSFUL;

}




JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1write
  (JNIEnv *env , jobject jobj, jbyteArray txdata)
{
    jbyte *buffer = env->GetByteArrayElements(txdata, 0);
    jint size = env->GetArrayLength(txdata);
    int write_len = acl16_write(&acl16, (uint8_t *)buffer, size);
    env->ReleaseByteArrayElements(txdata, buffer, 0);
    return write_len;
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1read
  (JNIEnv *env, jobject jobj, jbyteArray rxdata, jint Length)
 {
        jbyte *buffer = (jbyte *)malloc(Length + 1);
        if (buffer == NULL) {
             LOGE(" malloc buffer error");
             return NULL;
        }
        int read_len = acl16_read(&acl16, (uint8_t *)buffer, Length);
        LOGI(" read_len=%d buffer=%s", read_len, buffer);
        env->SetByteArrayRegion(rxdata, 0, Length, (const jbyte *)buffer);
        free(buffer);
        buffer = NULL;
        return read_len;
 }




 /*
  * Class:     android_xkkj_api_HwAcl
  * Method:    acl_poweron
  * Signature: ()I
  */
 JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1poweron
   (JNIEnv *env, jobject jobj)
{
    return acl16_poweron();
}

 /*
  * Class:     android_xkkj_api_HwAcl
  * Method:    acl_poweroff
  * Signature: ()I
  */
 JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1poweroff
   (JNIEnv *env, jobject jobj)
{
    return acl16_poweroff();
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1backlight
    (JNIEnv *env, jobject jobj)
{
    return backlight_read();
}

  /*
   * Class:     android_xkkj_api_HwAcl
   * Method:    set_backlight
   * Signature: (I)I
   */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_set_1backlight
    (JNIEnv *env, jobject jobj, jint backlight)
{
    return backlight_write(backlight);
}

  /*
   * Class:     android_xkkj_api_HwAcl
   * Method:    get_lightvalue
   * Signature: ()I
   */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1lightvalue
    (JNIEnv *env, jobject  jobj)
{
    return light_read();
}

 JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_board_1select
      (JNIEnv *env , jobject obj)
 {
       return board_select();
 }


JNIEXPORT void JNICALL Java_android_1xkkj_1api_HwAcl_DebugSwitch
  (JNIEnv *env, jobject obj, jboolean status)
 {
    return DebugSwitch(status==JNI_TRUE ? 1: 0);
 }


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_security_1setConfig
  (JNIEnv *env, jobject jobj){
    //jbyte buffer = security_status==JNI_TRUE ? 1: 0;
    jbyte buffer = 1;
    int errnoNu = acl16_security_setConfig(&acl16,(uint8_t*)&buffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_security_set_config exec failed!");
        return errnoNu;
    }
   return ISOSW_SUCCESSFUL;
 }

JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_security_1getConfig
  (JNIEnv *env, jobject obj, jbyteArray security_status)
{
    jbyte buffer=0x00;
    int errnoNu = acl16_security_getConfig(&acl16,(uint8_t*)&buffer);
    env->SetByteArrayRegion(security_status,0,1,(const jbyte*)&buffer);
    if (errnoNu != ISOSW_SUCCESSFUL) {
        LOGE("acl16_security_get_config exec failed!");
        return errnoNu;
    }
    return ISOSW_SUCCESSFUL;
}



/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    Cos_Status
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_Cos_1Status
  (JNIEnv *env , jobject jobj, jbyteArray cos_status)
{
     jbyte buffer=0x00;
     int errnoNu = acl16_cos_status(&acl16,(uint8_t*)&buffer);
     env->SetByteArrayRegion(cos_status,0,1,(const jbyte*)&buffer);
     if (errnoNu != ISOSW_SUCCESSFUL) {
         LOGE("acl16_security_get_config exec failed!");
         return errnoNu;
     }
     return ISOSW_SUCCESSFUL;
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_code_1update
  (JNIEnv *env, jobject obj, jboolean security_code){

    acl16_open(&acl16,0);
    acl16_produce_Clear_AllInfo(&acl16);
    acl16_produce_Clear_Cos(&acl16);
    acl16_close(&acl16);
    acl16_poweroff();
    sleep(1);
    acl16_poweron();
    sleep(1);
    return codeDownLoad(security_code==JNI_TRUE ? 1: 0);
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_code_1DownLoad
  (JNIEnv *env, jobject obj, jboolean security_code)
{
    return codeDownLoad(security_code==JNI_TRUE ? 1: 0);
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_cos_1is_1Exist
  (JNIEnv *env, jobject  jobj){
    return isExist();
}

 JNIEXPORT void JNICALL Java_android_1xkkj_1api_HwAcl_devicereboot
   (JNIEnv *env, jobject  obj)
 {
      system("/system/bin/reboot");
 }


JNIEXPORT void JNICALL Java_android_1xkkj_1api_HwAcl_device_1reset
  (JNIEnv *, jobject)
{
    if(board_select()>0)
      system("su 0  /system/bin/device_recovery.sh --wipe_data ");
    else
        system("su -c 'echo --wipe_data > /cache/recovery/command;reboot recovery'");
}

JNIEXPORT void JNICALL Java_android_1xkkj_1api_HwAcl_device_1upgrade
  (JNIEnv *env, jobject jobj, jstring path)
{
    char* update_path = jstringToChar(env,path);
    char command[100];
    if(board_select()>0)
        sprintf(command,"su 0  /system/bin/device_recovery.sh --update_package=%s",update_path);
    //LOGD("update_path:%s",command);
    system(command);
    free(update_path);
    update_path=NULL;
}

JNIEXPORT jstring JNICALL Java_android_1xkkj_1api_HwAcl_device_1sn
  (JNIEnv *env, jobject jobj)
{
    char sn[40];
    FILE * p_file = NULL;
    p_file = popen("getprop sys.serialno", "r");
    if (!p_file) {
       LOGE("Erro to popen");
    }
    while (fgets(sn, 40, p_file) != NULL) {
        LOGD("SN:%s", sn);
    }
    pclose(p_file);
    return charToJstring(env,sn);
}