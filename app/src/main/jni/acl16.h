
#ifndef __ACL16__
#define __ACL16__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include<Android/log.h>
#define LOG_TAG "HwAcl"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG ,__VA_ARGS__) // 定义LOGF类型

#define		CMD_TX_TAG					0x80
#define		CMD_TX_CH					0x80
#define		CMD_RX_CH					0x81 
#define		CMD_TX_BASE_LENTH				0x000d
#define		CMD_RX_BASE_LENTH				0x0007

#define		P1_DEFAULT_VALUE			0x01

//Factory Command
#define		CMD_PARAMTER_ENABLE			0x01
#define		CMD_PARAMTER_DISABLE			0x00

#define		CMD_PRODUCE_SET_CONFIG			0x81
#define		CMD_PRODUCE_SET_CONFIG_P1		0x7c
#define		CMD_PRODUCE_SET_CONFIG_P2		0x4d
#define		CMD_PRODUCE_SET_CONFIG_TX_LENTH		0x0030
#define		CMD_PRODUCE_SET_CONFIG_RX_LENTH		0x0000 


#define		CMD_PRODUCE_CLEAR_ALLINFO		0x82
#define		CMD_PRODUCE_CLEAR_ALLINFO_P1		0xa8
#define		CMD_PRODUCE_CLEAR_ALLINFO_P2		0xe1
#define		CMD_PRODUCE_CLEAR_ALLINFO_TX_LENTH	0x0000
#define		CMD_PRODUCE_CLEAR_ALLINFO_RX_LENTH	0x0000

#define		CMD_PRODUCE_CLEAR_COS			0x83
#define		CMD_PRODUCE_CLEAR_COS_P1		0xdb
#define		CMD_PRODUCE_CLEAR_COS_P2		0x69
#define		CMD_PRODUCE_CLEAR_COS_TX_LENTH	0x0000
#define		CMD_PRODUCE_CLEAR_COS_RX_LENTH	0x0000

#define		CMD_GET_RANDOM				0x10
#define		CMD_GET_RANDOM_TX_LENTH		0x0000

#define		CMD_GET_DEVICE_INFO			0x01
#define		CMD_GET_DEVICE_INFO_TX_LENTH	0x0000
#define		CMD_GET_DEVICE_INFO_RX_LENTH	0x0050

//6.设置userpin
#define		CMD_SET_USER_PIN			0x02
#define		CMD_SET_USER_PIN_TX_LENTH		0x0020
#define		CMD_SET_USER_PIN_RX_LENTH		0x0000

//7.修改userpin
#define		CMD_CHANGE_USERPIN			0x03
#define		CMD_CHANGE_USERPIN_RX_LENTH		0x0000

//8.获取PIN信息和状态
#define		CMD_GET_PIN_INFO			0x04
#define		CMD_GET_PIN_INFO_TX_LENTH		0x0000
#define		CMD_GET_PIN_INFO_RX_LENTH		0x0004

//9.验证USERPIN
#define		CMD_VERIFY_USERPIN			0x05
#define		CMD_VERIFY_USERPIN_TX_LENTH		0x0010
#define		CMD_VERIFY_USERPIN_RX_LENTH		0x0000

//10.获取请求码 
#define		CMD_GET_REQUEST_CODE			0x06
#define		CMD_GET_REQUEST_CODE_P1			0x01
#define		CMD_GET_REQUEST_CODE_P2			0x01
#define		CMD_GET_REQUEST_CODE_RX_LENTH		0x0020

//11.重置userpin
#define		CMD_RESET_USERPIN			0x07
#define		CMD_RESET_USERPIN_TX_LENTH		0x0020
#define		CMD_RESET_USERPIN_RX_LENTH		0x0000

//12.重置userpin重试次数
#define   CMD_RESET_USERPIN_RETRY_TIME		0x08
#define   CMD_RESET_USERPIN_RETRY_TIME_TX_LENTH	0x0020
#define   CMD_RESET_USERPIN_RETRY_TIME_RX_LENTH	0x0000

//13.远程升级清除COS
#define   CMD_REMOTE_CLEAR_COS			0x09
#define   CMD_REMOTE_CLEAR_COS_TX_LENTH		0x0020
#define   CMD_REMOTE_CLEAR_COS_RX_LENTH		0x0000

//14.生成ecdsa密钥对
#define   CMD_GENERATE_KEYPARI_BY_ID		0x0A
#define   CMD_GENERATE_KEYPARI_BY_ID_P1		0x01
#define   CMD_GENERATE_KEYPARI_BY_ID_TX_LENTH	0x0000
#define   CMD_GENERATE_KEYPARI_BY_ID_RX_LENTH	0x0040

//15.Ecdsa签名
#define   CMD_ECDSA_SIGN				0x0B
#define   CMD_ECDSA_SIGN_TX_LENTH			0x0020
#define   CMD_ECDSA_SIGN_RX_LENTH			0x0041

//16.Ecdsa验签
#define   CMD_ECDSA_VERIFY			0x0C
#define   CMD_ECDSA_VERIFY_TX96_LENTH		0x0060
#define   CMD_ECDSA_VERIFY_TX160_LENTH	0x00a0
#define   CMD_ECDSA_VERIFY_RX_LENTH		0x0000

//17.导出公钥
#define   CMD_EXPORT_PUBLICKEY_BY_ID		0x0D
#define   CMD_EXPORT_PUBLICKEY_BY_ID_TX_LENTH	0x0000
#define   CMD_EXPORT_PUBLICKEY_BY_ID_RX_LENTH	0x0040


//18.安全标志设置
#define		CMD_SECURITY_SET_CONFIG   0x0F
#define		CMD_SECURITY_SET_CONFIG_P1		0x00
#define		CMD_SECURITY_SET_CONFIG_P2		0x00
#define		CMD_SECURITY_SET_CONFIG_TX_LENTH	0x0001
#define		CMD_SECURITY_SET_CONFIG_RX_LENTH	0x0000


//19.安全标志获取
#define		CMD_SECURITY_GET_CONFIG   0x1F
#define		CMD_SECURITY_GET_CONFIG_P1		0x00
#define		CMD_SECURITY_GET_CONFIG_P2		0x00
#define		CMD_SECURITY_GET_CONFIG_TX_LENTH	0x0000
#define		CMD_SECURITY_GET_CONFIG_RX_LENTH	0x0001


//20.COS状态获取
#define		CMD_COS_STATUS   0x1E
#define		CMD_COS_STATUS_P1		0x00
#define		CMD_COS_STATUS_P2		0x00
#define		CMD_COS_STATUS_TX_LENTH	0x0000
#define		CMD_COS_STATUS_RX_LENTH	0x0001



#define   CLEAR_COS_BACKUP_ALL   4

#define ISOSW_COMMUNI_OUT_ERROR				0x8001 
#define ISOSW_COMMUNI_IN_ERROR				0x8002

#define ISOSW_PACK_ERROR					0x8A01  //pack解包错误
#define ISOSW_CRC_ERROR						0x8A02  //Crc校验错误

/******************ISO7816标准相关SW**************************/
#define ISOSW_SUCCESSFUL					0x9000  //执行成功
#define ISOSW_UNKNOW_ERROR				    0x6F00  //未知错误(没有精确的诊断)
#define ISOSW_CLA_ERROR						0x6E00  //类别码错误
#define ISOSW_INS_ERROR						0x6D00  //命令码错误
#define ISOSW_P1P2_ERROR					0x6A86  //参数错误
#define ISOSW_LC_ERROR						0x6700  //下发长度错误
#define ISOSW_DATA_ERROR					0x6A80  //数据域数据错误
#define ISOSW_LE_ERROR						0x6C00	//上传长度错误(0x6C??)

#define ISOSW_AUTH_FAILED					0x63C0  //认证失败(0x63C?)
#define ISOSW_PIN_IS_EXIST					0x63C1  //pin已经存在
#define ISOSW_PIN_NOPIN						0x63C2  //pin不存在
#define ISOSW_INSFILE_NOTMATCH	            0x6981  //命令与文件结构不兼容
#define ISOSW_SECURITY_ERROR				0x6982  //权限不满足 
#define ISOSW_AUTHMETHD_LOCKED				0x6983	//认证方法已被锁定 
#define ISOSW_DATAREF_INVALID				0x6984	//引用的数据无效 
#define ISOSW_USECONDITION_ERROR			0x6985	//使用的条件不被满足
#define ISOSW_INS_NOTALLOWED				0x6986  //命令不被允许(如:无当前EF等)
#define ISOSW_SMOBJECT_ERROR				0x6988	//SM数据对象不正确

#define ISOSW_FUNCTION_NOTSUPPORT           0x6A81  //功能不被支持(如:创建不允许/目录无效/应用锁定) 	

#define ISOSW_NOFREE_SPACE					0x6A84  //存储空间不足 
#define ISOSW_STORAGE_ERROR					0x6581  //存储器故障

#define ISOSW_FILE_NOTFOUND					0x6A82  //文件未找到
#define ISOSW_FILE_EXISTENT					0x6A89  //文件已经存在
#define ISOSW_DFNAME_EXISTENT				0x6A8A  //DF文件名已经存在
#define ISOSW_FILE_CUROVERFLOW				0x6B00  //文件游标溢出
#define ISOSW_REMOTE_UPDATE_ERROR			0x6B01 //升级参数错误，升级失败
#define ISOSW_REMOTE_UPDATE_FAILD			0x6B02 // 升级失败，解密数据不匹配

/******************算法相关SW********************************/	
#define ALGSW_ASYMCIPHER_OPERATIONFAILD		0x6A98  //非对称运算失败 
#define ALGSW_ASYM_CIPHER_VERIFYFAILD		0x6A91// 非对称验签失败

#define ALGSW_SYM_CIPHER_ENDECRYPTFAILD		0x6AA1//对称算法加密或者解密失败
#define ALGSW_ALGTYPE_NOTSUPPORT			0x6A9D  //算法不被支持



typedef struct {
	uint8_t ch;
	uint8_t cmd;
	uint8_t p1;
	uint8_t p2;
	uint16_t lc;
	uint16_t le;
} ApduCmd;

typedef struct {
	uint8_t deviceName[16];//设备定制名称-如需要 （可设置）
	uint8_t productInfo[8];//设备生产信息-产线-工厂-编号 如需要 （可设置）
	uint8_t updateInfo[8];//如检测到需要恢复配置区和密钥区，则在恢复后，将宏记录信息版本覆盖进去，置0即可
	uint8_t keyPairNum;//设备内私钥数量，生产无需设置，置0即可
	uint8_t isAllowClearCos;//是否允许远程升级COS（可设置）
	uint8_t backUpMode;//备份模式，远程升级时需要备份什么2*2（密钥和PIN码）四种配置组合0，1，2，3（可设置）
	uint8_t pinMaxRetryTimes;//pin码最大重试次数（可设置）
	uint32_t backUpFlag;//备份标记，COS内部处理，置0即可
	uint8_t reserved[8];//保留字段，用于扩展
} Acl16ProduceConfig;  //能设置的为：（可设置），其余的是COS内部自动更新的；imo20200106

typedef struct {
	uint8_t deviceID[16]; //芯片唯一ID
	uint8_t deviceName[16]; //设备名称
	uint8_t cosVersion[16]; //COS版本
	uint8_t hardWareVersion[8]; //硬件版本
	uint8_t productInfo[8]; //出厂生产信息
	uint8_t updateInfo[8]; //升级记录信息
	uint8_t pinIsExist; //PIN码是否存在
	uint8_t keyPairNum; //私钥数量
	uint8_t isAllowClearCos; //是否允许清除
	uint8_t backUpMode; //备份模式
	uint8_t pinMaxRetryTimes; //pin最大重试次数
	uint8_t reserved[3]; //保留字段
} Acl16Info;

typedef struct {
	int _fd;
	int _fd_cs;
	int _fd_board;
	uint8_t modePa;
} Acl16;

typedef struct {
	uint8_t pinIsEixist;        //pin码是否存在                                                                                                                                                        
	uint8_t pinAuthStatus;      //pin码的认证状态
	uint8_t maxRextryTimes;     //pin码的最大重试次数
	uint8_t leftRetryTimes;     //pin码的剩余重试次数
} Acl16PinInfo;


typedef struct{
    uint8_t  device_num;
    const char* device_name;
}xkkj_device;


int acl16_produce_set_config(Acl16* fd, uint8_t* set);
int acl16_produce_Clear_AllInfo(Acl16 *fd);
int acl16_produce_Clear_Cos(Acl16* fd);
int acl16_get_random_data(Acl16* fd, uint8_t* rdBuf, uint16_t rdLenth);
int acl16_get_device_info(Acl16* fd, uint8_t* rdAcl16);
int acl16_set_pin(Acl16* fd, uint8_t* txData); // 固定32字节的 txData
int acl16_change_pin(Acl16* fd, uint8_t* txData); // 固定32字节的 txData
int acl16_get_pin_info(Acl16* fd, uint8_t* status);
int acl16_verify_pin(Acl16* fd, uint8_t* txData); // 固定16字节的
int acl16_get_RequestCode(Acl16* fd, uint8_t p1, uint16_t txLenth, uint8_t *txData, uint8_t *rxdata);
int acl16_reset_UserPin(Acl16* fd, uint8_t *txData);
int acl16_reset_UserPinRetryTime(Acl16* fd, uint8_t p1, uint8_t p2, uint8_t *txData);
int acl16_remote_ClearCos(Acl16* fd, uint8_t p1, uint8_t p2, uint8_t *txData);
int acl16_generateKeyPariById(Acl16* fd,uint8_t *rdBuf);
int acl16_ecdsa_sign(Acl16* fd, uint8_t *msg, uint8_t *signature); // msg=32byte, signature=64byte
int acl16_ecdsa_verify(Acl16* fd, uint8_t *signature); // msg=32byte,verifyData=64byte,pubkey=64byte
int acl16_export_public_key(Acl16* fd, uint8_t* pubkey); // 固定65字节的 rxData
int acl16_security_setConfig(Acl16* fd,uint8_t *security_status);
int acl16_security_getConfig(Acl16* fd,uint8_t* security_status);
int acl16_cos_status(Acl16* fd,uint8_t* cos_status);



int acl16_xkkj_open(Acl16* fd,uint8_t modePa);
int acl16_xkkj_close(Acl16* fd);
int acl16_xkkj_csopen(Acl16* fd);
int acl16_xkkj_csclose(Acl16* fd);
int acl16_xkkj_read(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_xkkj_write(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_xkkj_poweron();
int acl16_xkkj_poweroff();




int acl16_smdt_open(Acl16* fd);
int acl16_smdt_close(Acl16* fd);
int acl16_smdt_read(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_smdt_read2(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_smdt_write(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_smdt_poweron();
int acl16_smdt_poweroff();


int acl16_open(Acl16* fd,uint8_t modePa);
int acl16_close(Acl16* fd);
int acl16_read(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_write(Acl16* fd, uint8_t *data, size_t lenth);
int acl16_poweron();
int acl16_poweroff();


void print_array(uint8_t* data, int len, const char* name);
int  board_select();
void DebugSwitch(int status);
int codeDownLoad(char security_code);
int isExist();
#endif