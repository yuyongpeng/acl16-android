#include "android_xkkj_api_HwAcl.h"

static Acl16 acl16;
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
   LOGE("===%d,%02x",chars_len,chars[0]);
   return chars;
}


/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_open
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1open
  (JNIEnv *env, jobject obj)
 {
        int errnoNu = acl16_open(&acl16);
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
    LOGD("Java_android_1xkkj_1api_HwAcl_produce_1set_1config");
   // jbyte *buffer = env->GetByteArrayElements(product_config,0);
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
        LOGD("Java_android_1xkkj_1api_HwAcl_produce_1Clear_1AllInfo");
        int errnoNu = acl16_produce_Clear_AllInfo(&acl16);
        if (errnoNu != ISOSW_SUCCESSFUL) {
            LOGE("acl16_produce_Clear_AllInfo exec failed！");
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
         LOGD("Java_android_1xkkj_1api_HwAcl_get_1random_1data");
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
  (JNIEnv *env , jobject job, jbyteArray deviceinfo)
{
    LOGD("Java_android_1xkkj_1api_HwAcl_get_1device_1info");
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
    LOGD("Java_android_1xkkj_1api_HwAcl_set_1pin!");
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
        LOGD("Java_android_1xkkj_1api_HwAcl_change_1pin!");
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
        LOGD("Java_android_1xkkj_1api_HwAcl_get_1pin_1info!");
        jbyte *buffer = (jbyte*)malloc(sizeof(Acl16PinInfo));
        if(NULL == buffer)
        {
            LOGE("malloc failed！");
            return NULL;
        }
        memset(buffer, 0, sizeof(Acl16PinInfo));
        LOGD("%p,%02x,%02x,%02x,%02x",buffer,*buffer,*(buffer+1),*(buffer+2),*(buffer+3));
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
                LOGD("Java_android_1xkkj_1api_HwAcl_verify_1pin!");
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
       LOGD("Java_android_1xkkj_1api_HwAcl_get_1pin_1info!");
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
                LOGD("Java_android_1xkkj_1api_HwAcl_ecdsa_1sign!");
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
    LOGD("Java_android_1xkkj_1api_HwAcl_ecdsa_1verify!");
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
            LOGD("Java_android_1xkkj_1api_HwAcl_export_1public_1key!");
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
          LOGD("Java_android_1xkkj_1api_HwAcl_acl_1write");
          jbyte *buffer = env->GetByteArrayElements(txdata, 0);
          jint size = env->GetArrayLength(txdata);
          int write_len = acl16_write(&acl16, (uint8_t *)buffer, size);
          LOGI("call jni spiWrite write_len=%d", write_len);
          env->ReleaseByteArrayElements(txdata, buffer, 0);
          return write_len;
}


JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1read
  (JNIEnv *env, jobject jobj, jbyteArray rxdata, jint Length)
 {
        LOGD("Java_android_1xkkj_1api_HwAcl_acl_1read");
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

 JNIEXPORT void JNICALL Java_android_1xkkj_1api_HwAcl_devicereboot
   (JNIEnv *env, jobject  obj)
 {
      system("/system/bin/reboot");
 }

