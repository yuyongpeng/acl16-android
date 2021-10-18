/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class android_xkkj_api_HwAcl */

#ifndef _Included_android_xkkj_api_HwAcl
#define _Included_android_xkkj_api_HwAcl
#ifdef __cplusplus
extern "C" {
#include "acl16.h"
#include "light.h"
#include <string.h>
#include <stdlib.h>
#endif
/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    produce_set_config
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_produce_1set_1config
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    produce_Clear_AllInfo
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_produce_1Clear_1AllInfo
  (JNIEnv *, jobject);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    produce_Clear_Cos
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_produce_1Clear_1Cos
  (JNIEnv *, jobject);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    get_random_data
 * Signature: ([BC)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1random_1data
  (JNIEnv *, jobject, jbyteArray, jchar);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    get_device_info
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1device_1info
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    set_pin
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_set_1pin
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    change_pin
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_change_1pin
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    get_pin_info
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1pin_1info
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    verify_pin
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_verify_1pin
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    generate_KeyPariById
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_generate_1KeyPariById
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    ecdsa_sign
 * Signature: ([B[B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_ecdsa_1sign
  (JNIEnv *, jobject, jbyteArray, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    ecdsa_verify
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_ecdsa_1verify
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    export_public_key
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_export_1public_1key
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_write
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1write
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_read
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1read
  (JNIEnv *, jobject, jbyteArray, jint);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_permission
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1permission
  (JNIEnv *, jobject);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_poweron
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1poweron
  (JNIEnv *, jobject);

/*
 * Class:     android_xkkj_api_HwAcl
 * Method:    acl_poweroff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1poweroff
  (JNIEnv *, jobject);


  /*
   * Class:     android_xkkj_api_HwAcl
   * Method:    acl_open
   * Signature: ()I
   */
  JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1open
    (JNIEnv *, jobject);

  /*
   * Class:     android_xkkj_api_HwAcl
   * Method:    acl_close
   * Signature: ()I
   */
  JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_acl_1close
    (JNIEnv *, jobject);

  JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1backlight
    (JNIEnv *, jobject);

  /*
   * Class:     android_xkkj_api_HwAcl
   * Method:    set_backlight
   * Signature: (I)I
   */
  JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_set_1backlight
    (JNIEnv *, jobject, jint);

  /*
   * Class:     android_xkkj_api_HwAcl
   * Method:    get_lightvalue
   * Signature: ()I
   */
  JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_get_1lightvalue
    (JNIEnv *, jobject);

    /*
     * Class:     android_xkkj_api_HwAcl
     * Method:    board_select
     * Signature: ()I
     */
    JNIEXPORT jint JNICALL Java_android_1xkkj_1api_HwAcl_board_1select
      (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
