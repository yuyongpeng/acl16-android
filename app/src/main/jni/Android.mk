LOCAL_PATH := $(call my-dir)  #获取Android.mk所在目录

include $(CLEAR_VARS)
# 下面一句是用来指定so库生成位置的，感兴趣的朋友可以试试，确实可以改变so库生成位置。
# NDK_APP_DST_DIR=../../../../../SharedLibs/$(TARGET_ARCH_ABI)

LOCAL_MODULE    := hwacl   #指定生成so库的名称
LOCAL_SRC_FILES := hwacl.cpp acl16.c acl16_smdt.c acl16_xkkj.c crc16_ccitt.c light.c  acl16_boot.c  #指定生成so库所需源码文件
LOCAL_LDLIBS += -llog
include $(BUILD_SHARED_LIBRARY)  #说明生成的是动态so库（这句是废话）