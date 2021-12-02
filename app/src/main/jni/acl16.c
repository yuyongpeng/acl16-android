/**
 * @copyright © 2021 Copyright dphone.com
 * @date 2021-01-22
 */


#include "acl16.h"
#include "crc16_ccitt.h"
#include <string.h>
#include <stdlib.h>

static int Debug=0;

static xkkj_device device_id[]={
    {1,"arttv10"},
    {2,"dphotos10"},
    {},
};

void DebugSwitch(int status)
{
    Debug=status;
    LOGD("%d",Debug);
}


const char* ACL16_board_select= "/proc/boardinfo";
int board_select(){
        int board_tmp=0;;
        char board_name[10] = {0};
        int board_fd = open(ACL16_board_select, O_RDONLY);
        if(board_fd < 0){
            return -1;
        }else{
            read(board_fd,board_name,10);
            for(board_tmp=0;board_tmp<sizeof(device_id)/sizeof(xkkj_device);board_tmp++){
               if(strncmp(device_id[board_tmp].device_name,board_name,strlen(device_id[board_tmp].device_name))==0)
                    break;
            }
            close(board_fd);
            return  device_id[board_tmp].device_num;
        }
}
int acl16_open(Acl16* fd,uint8_t modePa){
    int errnoNu;
    fd->_fd_board =  errnoNu = open(ACL16_board_select, O_RDONLY);
    if(fd->_fd_board < 0){
        return acl16_smdt_open(fd);
    }else{
        return acl16_xkkj_open(fd,modePa);
    }
}

int acl16_close(Acl16* fd){
    if(fd->_fd_board < 0){
          return acl16_smdt_close(fd);
        }else{
          return acl16_xkkj_close(fd);
     }
}

int acl16_write(Acl16* fd, uint8_t *data, size_t lenth){
            if(fd->_fd_board < 0){
                return acl16_smdt_write(fd,data,lenth);
            }else{
                return acl16_xkkj_write(fd,data,lenth);
            }
}



int acl16_poweron(){
    if(board_select() < 0){
          return acl16_smdt_poweron();//此处并未具体实现
    }else{
           return acl16_xkkj_poweron();
    }

}
int acl16_poweroff(){
    if(board_select() < 0){
          return acl16_smdt_poweroff();//此处并未具体实现
     }else{
          return acl16_xkkj_poweroff();
    }
}



int acl16_read(Acl16* fd, uint8_t *data, size_t lenth){
             if(fd->_fd_board < 0){
                //return acl16_smdt_read(fd,data,lenth);
                return acl16_smdt_read2(fd,data,lenth);
             }else{
                 return acl16_xkkj_read(fd,data,lenth);
             }
}

static void error_num(uint16_t errorData) {
	switch(errorData) {
		case ISOSW_COMMUNI_OUT_ERROR:
			LOGE("error number is ISOSW_COMMUNI_OUT_ERROR");
			break;
		case ISOSW_COMMUNI_IN_ERROR:
			LOGE("error number is ISOSW_COMMUNI_IN_ERROR");
			break;
		case ISOSW_PACK_ERROR:
			LOGE("error number is ISOSW_PACK_ERROR");
			break;
		case ISOSW_CRC_ERROR:
			LOGE("error number is ISOSW_CRC_ERROR");
			break;
		case ISOSW_SUCCESSFUL:
			LOGE("ISOSW_SUCCESSFUL");
			break;
		case ISOSW_UNKNOW_ERROR:
			LOGE("error number is ISOSW_UNKNOW_ERROR");
			break;
		case ISOSW_CLA_ERROR:
			LOGE("error number is ISOSW_CLA_ERROR");
			break;
		case ISOSW_INS_ERROR:
			LOGE("error number is ISOSW_INS_ERROR");
			break;
		case ISOSW_P1P2_ERROR:
			LOGE("error number is ISOSW_P1P2_ERROR");
			break;
		case ISOSW_LC_ERROR:
			LOGE("error number is ISOSW_LC_ERROR");
			break;
		case ISOSW_DATA_ERROR:
			LOGE("error number is ISOSW_DATA_ERROR");
			break;
		case ISOSW_LE_ERROR:
			LOGE("error number is ISOSW_LE_ERROR");
			break;
		case ISOSW_AUTH_FAILED:
			LOGE("error number is ISOSW_AUTH_FAILED");
			break;
		case ISOSW_PIN_IS_EXIST:
			LOGE("error number is ISOSW_PIN_IS_EXIST");
			break;
		case ISOSW_PIN_NOPIN:
			LOGE("error number is ISOSW_PIN_NOPIN");
			break;
		case ISOSW_INSFILE_NOTMATCH:
			LOGE("error number is ISOSW_INSFILE_NOTMATCH");
			break;
		case ISOSW_SECURITY_ERROR:
			LOGE("error number is ISOSW_SECURITY_ERROR");
			break;
		case ISOSW_AUTHMETHD_LOCKED:
			LOGE("error number is ISOSW_AUTHMETHD_LOCKED");
			break;
		case ISOSW_DATAREF_INVALID:
			LOGE("error number is ISOSW_DATAREF_INVALID");
			break;
		case ISOSW_USECONDITION_ERROR:	
			LOGE("error number is ISOSW_USECONDITION_ERROR");
			break;
		case ISOSW_INS_NOTALLOWED:
			LOGE("error number is ISOSW_INS_NOTALLOWED");
			break;
		case ISOSW_SMOBJECT_ERROR:
			LOGE("error number is ISOSW_SMOBJECT_ERROR");
			break;
		case ISOSW_FUNCTION_NOTSUPPORT:	
			LOGE("error number is ISOSW_FUNCTION_NOTSUPPORT");
			break;
		case ISOSW_NOFREE_SPACE:	
			LOGE("error number is ISOSW_NOFREE_SPACE");
			break;
		case ISOSW_STORAGE_ERROR:	
			LOGE("error number is ISOSW_STORAGE_ERROR");
			break;
		case ISOSW_FILE_NOTFOUND:
			LOGE("error number is ISOSW_FILE_NOTFOUND");
			break;
		case ISOSW_FILE_EXISTENT:
			LOGE("error number is ISOSW_FILE_EXISTENT");
			break;
		case ISOSW_DFNAME_EXISTENT:
			LOGE("error number is ISOSW_DFNAME_EXISTENT");
			break;
		case ISOSW_FILE_CUROVERFLOW:
			LOGE("error number is ISOSW_FILE_CUROVERFLOW");
			break;
		case ISOSW_REMOTE_UPDATE_ERROR:	
			LOGE("error number is ISOSW_REMOTE_UPDATE_ERROR");
			break;
		case ISOSW_REMOTE_UPDATE_FAILD:	
			LOGE("error number is ISOSW_REMOTE_UPDATE_FAILD");
			break;
		case ALGSW_ASYMCIPHER_OPERATIONFAILD:
			LOGE("error number is ALGSW_ASYMCIPHER_OPERATIONFAILD");
			break;	
		case ALGSW_ASYM_CIPHER_VERIFYFAILD:
			LOGE("error number is ALGSW_ASYM_CIPHER_VERIFYFAILD");
			break;	
		case ALGSW_SYM_CIPHER_ENDECRYPTFAILD:
			LOGE("error number is ALGSW_SYM_CIPHER_ENDECRYPTFAILD");
			break;	
		case ALGSW_ALGTYPE_NOTSUPPORT:
			LOGE("error number is ALGSW_ALGTYPE_NOTSUPPORT");
			break;
		default:
			LOGE("error number is 0x%04x", errorData);
			break;
	}
}



void print_array(uint8_t* data, int len, const char* name){
    if( 1 == Debug ){
        if(data){
	        char temp[4] = {0};
            const int LEN = len * 2;
            char *buf = (char*)malloc(LEN * sizeof(char));
            if (NULL == buf) {
                return;
            }
            memset(buf, 0, LEN);
            for (int i = 0; i < len; i++) {
                memset(temp, 0, 4);
                snprintf(temp, 4, "%02x", *(data + i));
                strcat(buf, temp);
            }
            LOGD("%s:%s",name,buf);
            free(buf);
            buf = NULL;
        }else
        LOGD("%s",name);
    }
}





static int cmd_pack_tx_rx(Acl16* fd, ApduCmd *apduPack, uint8_t *apduData, uint8_t** out) {
	uint16_t crc16Tmp;
	uint16_t crc16Tmp1;
	uint16_t apduCmdLenth;
	uint16_t apduRdLenth;
	uint16_t rdLenth;
	uint16_t errorNu = ISOSW_UNKNOW_ERROR;

	uint32_t apduDataLen = apduPack->lc;

	uint16_t cmdTxAllLenth = apduPack->lc + CMD_TX_BASE_LENTH;
	uint16_t cmdRxAllLenth = apduPack->le + CMD_RX_BASE_LENTH;

	uint8_t* apduCmdTmp = (uint8_t *)malloc(cmdTxAllLenth);
	uint8_t* rdBuf = (uint8_t *)malloc(cmdRxAllLenth);
    memset(rdBuf,0,cmdRxAllLenth);
    memset(apduCmdTmp,0,cmdTxAllLenth);
	do {
		*out = NULL;

		apduCmdLenth = apduPack->lc;
		apduRdLenth = apduPack->le;

		//apdu tag/lenth push in Pack
		*apduCmdTmp = CMD_TX_TAG; 
		*(apduCmdTmp + 1) = (uint8_t)(((cmdTxAllLenth - 5) >> 8) & 0xff); 
		*(apduCmdTmp + 2) = (uint8_t)((cmdTxAllLenth - 5) & 0xff);

		//little > big
		apduPack->le = (apduPack->le >> 8) + (apduPack->le << 8);
		apduPack->lc = (apduPack->lc >> 8) + (apduPack->lc << 8);

		//apdu tx pack push in Pack
		memcpy( (apduCmdTmp + 3), (uint8_t*)apduPack, (CMD_TX_BASE_LENTH - 5));

		if (apduData != NULL) {
			//apdu tx pack push in Pack
			memcpy( (apduCmdTmp + 11), apduData, apduDataLen);
		}

		//crc16 push in Pack
		crc16Tmp = CRC16_CCITT((apduCmdTmp + 3), (cmdTxAllLenth - 5));
		*(apduCmdTmp + cmdTxAllLenth - 2) = (uint8_t)((crc16Tmp >> 8) & 0xff);
		*(apduCmdTmp + cmdTxAllLenth - 1) = (uint8_t)(crc16Tmp & 0xff);

		usleep(50000);
		acl16_write(fd, apduCmdTmp, cmdTxAllLenth);
		//usleep(50000);


		//spi read data
		int i;

		for (i = 0; i < 10; i++) {
			//acl16_read(fd, &rdBuf[0], 1);
			acl16_read(fd, &rdBuf[0], 1);
			if(rdBuf[0] == 0x81)
			break;
			usleep(5000);
		}
		if (rdBuf[0] != 0x81) {
			break;
		}
		acl16_read(fd, &rdBuf[1], cmdRxAllLenth - 1);
		rdLenth = (uint16_t)(((rdBuf[1] << 8) & 0xff00) | (rdBuf[2] & 0x00ff));

		crc16Tmp = CRC16_CCITT((rdBuf + 3), rdLenth);
		crc16Tmp1 = ((uint16_t)((rdBuf[cmdRxAllLenth - 2] & 0x00ff) << 8) | (uint16_t)(rdBuf[cmdRxAllLenth - 1]));

		if (crc16Tmp1 == crc16Tmp) {
			errorNu = (uint16_t)(rdBuf[cmdRxAllLenth - 3] << 8 &0xff00) | (uint16_t)(rdBuf[cmdRxAllLenth - 4] &0x00ff);
		}
		else if (crc16Tmp1 == 0x8888) {
			crc16Tmp1 = ((uint16_t)((rdBuf[5] & 0x00ff) << 8) | (uint16_t)(rdBuf[6]));
			if (crc16Tmp1 != crc16Tmp) {
				LOGE("crc 16 error, crc16Tmp1 = %02x, crc16 = %02x, data lenth error", crc16Tmp1, crc16Tmp);
				break;
			}
			errorNu = (uint16_t)(rdBuf[4] << 8 &0xff00) | (uint16_t)(rdBuf[3] &0x00ff);
		} else {
			LOGE("crc 16 error, crc16Tmp1 = %02x, crc16 = %02x", crc16Tmp1, crc16Tmp);
		}
	} while(0);

	error_num(errorNu);

	free(apduCmdTmp);

	if (errorNu == ISOSW_SUCCESSFUL) {
		*out = rdBuf;
	} else {
		free(rdBuf);
	}

	return errorNu;
}


//1 生产配置命令： CMD_PRODUCE_SET_CONFIG 0x81
int acl16_produce_set_config(Acl16* fd, uint8_t* rxData){
	uint8_t* rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_PRODUCE_SET_CONFIG;
	apduCmdTmp.p1 = CMD_PRODUCE_SET_CONFIG_P1;
	apduCmdTmp.p2 = CMD_PRODUCE_SET_CONFIG_P2;
	apduCmdTmp.lc = CMD_PRODUCE_SET_CONFIG_TX_LENTH; //设置结构体长度48字节固定 imo20200106
	apduCmdTmp.le = CMD_PRODUCE_SET_CONFIG_RX_LENTH;
	print_array(rxData,CMD_PRODUCE_SET_CONFIG_TX_LENTH,"CMD_PRODUCE_SET_CONFIG_TX");
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, (uint8_t*)rxData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
	return errnoNu;
}


//2.清除用户数据：CMD_PRODUCE_CLEAR_ALLINFO 0x82
int acl16_produce_Clear_AllInfo(Acl16* fd)
{
    uint8_t *rdBufTmp;
    ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_PRODUCE_CLEAR_ALLINFO;
    apduCmdTmp.p1 = CMD_PRODUCE_CLEAR_ALLINFO_P1;
    apduCmdTmp.p2 = CMD_PRODUCE_CLEAR_ALLINFO_P2;
    apduCmdTmp.lc = CMD_PRODUCE_CLEAR_ALLINFO_TX_LENTH;
    apduCmdTmp.le = CMD_PRODUCE_CLEAR_ALLINFO_RX_LENTH;
    int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
    free(rdBufTmp);
	rdBufTmp = NULL;
    return errnoNu;
}


//3.清除COS：CMD_PRODUCE_CLEAR_COS 0x83

int acl16_produce_Clear_Cos(Acl16* fd)
{
	uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_PRODUCE_CLEAR_COS;
    apduCmdTmp.p1 = CMD_PRODUCE_CLEAR_COS_P1;
    apduCmdTmp.p2 = CMD_PRODUCE_CLEAR_COS_P2;
    apduCmdTmp.lc = CMD_PRODUCE_CLEAR_COS_TX_LENTH;
    apduCmdTmp.le = CMD_PRODUCE_CLEAR_COS_RX_LENTH;
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
    return errnoNu;
}





//4.获取随机数：CMD_GET_RANDOM 0x10
int acl16_get_random_data(Acl16* fd, uint8_t* rdBuf, uint16_t rdLenth) {
	uint8_t* rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_GET_RANDOM;
	apduCmdTmp.p1 = 1; // "P1 = 0时，获取Le固定数；P1 =1 时，获取le长度的随机数"
	apduCmdTmp.p2 = 1; // "P2 = 0时，随机数不做缓存；P2=1 时，随机数缓存；
	apduCmdTmp.lc = CMD_GET_RANDOM_TX_LENTH;
	apduCmdTmp.le = rdLenth;

	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
	if (rdBufTmp) {
		memcpy(rdBuf, (rdBufTmp + 3), rdLenth);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
    print_array(rdBuf,rdLenth,"CMD_GET_RANDOM_16");
	return errnoNu;
}

//5.获取设备信息： CMD_GET_DEVICE_INFO			0x01


int acl16_get_device_info(Acl16* fd, uint8_t* rdAcl16){
	uint8_t* rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_GET_DEVICE_INFO;
	apduCmdTmp.p1 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.lc = CMD_GET_DEVICE_INFO_TX_LENTH;
	apduCmdTmp.le = CMD_GET_DEVICE_INFO_RX_LENTH;	//取回数据的长度是固定的80个字节 imo20200106

	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
	if (rdBufTmp) {
		memcpy(rdAcl16, (rdBufTmp + 3), CMD_GET_DEVICE_INFO_RX_LENTH);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
    print_array(rdAcl16,CMD_GET_DEVICE_INFO_RX_LENTH,"CMD_GET_DEVICE_INFO_RX");
	return errnoNu;
}


//6.设置userpin CMD_SET_USER_PIN 0x02 
int acl16_set_pin(Acl16* fd, uint8_t* txData) { // 固定32字节的 txData
	uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_SET_USER_PIN;
	apduCmdTmp.p1 = CMD_SET_USER_PIN_TX_LENTH;
	apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.lc = CMD_SET_USER_PIN_TX_LENTH;
	apduCmdTmp.le = CMD_SET_USER_PIN_RX_LENTH;
    print_array(txData,CMD_SET_USER_PIN_TX_LENTH,"CMD_SET_USER_PIN_TX");
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
	return errnoNu;
}

//7.修改userpin CMD_CHANGE_USERPIN	0x03
int acl16_change_pin(Acl16* fd, uint8_t* txData) { // 固定32字节的 txData
	uint8_t* rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_CHANGE_USERPIN;
	apduCmdTmp.p1 = CMD_SET_USER_PIN_TX_LENTH;
	apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.lc = CMD_SET_USER_PIN_TX_LENTH;
	apduCmdTmp.le = CMD_CHANGE_USERPIN_RX_LENTH;
    print_array(txData,CMD_SET_USER_PIN_TX_LENTH,"CMD_CHANGE_USERPIN_TX");
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
	return errnoNu;
}



//8.获取PIN信息和状态   CMD_GET_PIN_INFO			0x04
int acl16_get_pin_info(Acl16* fd, uint8_t* status){
	uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_GET_PIN_INFO;
	apduCmdTmp.p1 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.lc = CMD_GET_PIN_INFO_TX_LENTH;
	apduCmdTmp.le = CMD_GET_PIN_INFO_RX_LENTH;

	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
	if (rdBufTmp) {
		memcpy(status, (rdBufTmp + 3), CMD_GET_PIN_INFO_RX_LENTH);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
    print_array(status,CMD_GET_PIN_INFO_RX_LENTH,"CMD_GET_PIN_INFO_RX");
	return errnoNu;
}



//9.验证USERPIN CMD_VERIFY_USERPIN 0x05
int acl16_verify_pin(Acl16* fd, uint8_t* txData) { // 固定16字节的
	uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_VERIFY_USERPIN;
	apduCmdTmp.p1 = P1_DEFAULT_VALUE;
	apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.lc = CMD_VERIFY_USERPIN_TX_LENTH;// 这里下发是16个字节 imo20200106
	apduCmdTmp.le = CMD_VERIFY_USERPIN_RX_LENTH;
    print_array(txData,CMD_VERIFY_USERPIN_TX_LENTH,"CMD_VERIFY_USERPIN_TX");
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
	return errnoNu;
}
//10.获取请求码    CMD_GET_REQUEST_CODE			0x06

int acl16_get_RequestCode(Acl16* fd, uint8_t p1, uint16_t txLenth, uint8_t *txData, uint8_t *rxdata)
{   
    uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_GET_REQUEST_CODE;
    apduCmdTmp.p1 = p1;
    apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
    apduCmdTmp.lc = txLenth;
    apduCmdTmp.le = txLenth + CMD_GET_REQUEST_CODE_RX_LENTH;
    int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
    if (rdBufTmp) {
		memcpy(rxdata, (rdBufTmp + 3), txLenth + CMD_GET_REQUEST_CODE_RX_LENTH);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
    return errnoNu;
}





//11.重置userpin   CMD_RESET_USERPIN			0x07

int acl16_reset_UserPin(Acl16* fd, uint8_t *txData)
{
    uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_RESET_USERPIN;
    apduCmdTmp.p1 = CMD_PARAMTER_DISABLE;
    apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
    apduCmdTmp.lc = CMD_RESET_USERPIN_TX_LENTH;
    apduCmdTmp.le = CMD_RESET_USERPIN_RX_LENTH;
    int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
    return errnoNu;
}


//12.重置userpin重试次数  CMD_RESET_USERPIN_RETRY_TIME		0x08

int acl16_reset_UserPinRetryTime(Acl16* fd, uint8_t p1, uint8_t p2, uint8_t *txData)
{
    uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_RESET_USERPIN_RETRY_TIME;
    apduCmdTmp.p1 = p1;
    apduCmdTmp.p2 = p2;
    apduCmdTmp.lc = CMD_RESET_USERPIN_RETRY_TIME_TX_LENTH;
    apduCmdTmp.le = CMD_RESET_USERPIN_RETRY_TIME_RX_LENTH;
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
    return errnoNu;
}






//13.远程升级清除COS   CMD_REMOTE_CLEAR_COS			0x09
int acl16_remote_ClearCos(Acl16* fd, uint8_t p1, uint8_t p2, uint8_t *txData)
{
    uint8_t *rdBufTmp;
    ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_REMOTE_CLEAR_COS;
    apduCmdTmp.p1 = p1;
    apduCmdTmp.p2 = p2;
    apduCmdTmp.lc = CMD_REMOTE_CLEAR_COS_TX_LENTH;
    apduCmdTmp.le = CMD_REMOTE_CLEAR_COS_RX_LENTH;
	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
    return errnoNu;
}


//14.生成ecdsa密钥对  CMD_GENERATE_KEYPARI_BY_ID		0x0A


int acl16_generateKeyPariById(Acl16* fd, uint8_t *rdBuf)
{
    uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
    apduCmdTmp.ch = CMD_TX_CH;
    apduCmdTmp.cmd = CMD_GENERATE_KEYPARI_BY_ID;
    apduCmdTmp.p1 = CMD_GENERATE_KEYPARI_BY_ID_P1;
    apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
    apduCmdTmp.lc = CMD_GENERATE_KEYPARI_BY_ID_TX_LENTH;
    apduCmdTmp.le = CMD_GENERATE_KEYPARI_BY_ID_RX_LENTH;

    int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
	if (rdBufTmp) {
		memcpy(rdBuf, (rdBufTmp + 3), CMD_GENERATE_KEYPARI_BY_ID_RX_LENTH);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
	print_array(rdBuf,CMD_GENERATE_KEYPARI_BY_ID_RX_LENTH,"CMD_GENERATE_KEYPARI_BY_ID_RX");
    return errnoNu;
}



//15.Ecdsa签名  CMD_ECDSA_SIGN	0x0B

int acl16_ecdsa_sign(Acl16* fd, uint8_t *txData, uint8_t *signature) { // 固定32字节的 txData, 固定65字节的 rxData
	uint8_t *rdBufTmp = NULL;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_ECDSA_SIGN;
	apduCmdTmp.p1 = P1_DEFAULT_VALUE;
	apduCmdTmp.p2 = 0;
	apduCmdTmp.lc = CMD_ECDSA_SIGN_TX_LENTH;
	apduCmdTmp.le = CMD_ECDSA_SIGN_RX_LENTH;
    print_array(txData,CMD_ECDSA_SIGN_TX_LENTH,"CMD_ECDSA_SIGN_TX");
	int errorNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	if (rdBufTmp) {
		memcpy(signature, (rdBufTmp + 3), CMD_ECDSA_SIGN_RX_LENTH);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
	print_array(signature,CMD_ECDSA_SIGN_RX_LENTH,"CMD_ECDSA_SIGN_RX");
	return errorNu;
}

//16.Ecdsa验签 CMD_ECDSA_VERIFY 0x0C
int acl16_ecdsa_verify(Acl16* fd,  uint8_t *signature) { // msg=32,verifyData=64
	uint8_t *rdBufTmp = NULL;
	uint8_t txData[96];
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_ECDSA_VERIFY;
	apduCmdTmp.p1 = P1_DEFAULT_VALUE;
	apduCmdTmp.p2 = 0;
	apduCmdTmp.lc = CMD_ECDSA_VERIFY_TX96_LENTH;
	apduCmdTmp.le = CMD_ECDSA_VERIFY_RX_LENTH;
    print_array(signature,CMD_ECDSA_VERIFY_TX96_LENTH,"CMD_ECDSA_VERIFY_TX");

	memcpy(txData, signature, 96);
	uint16_t errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, txData, &rdBufTmp);
	free(rdBufTmp);
	rdBufTmp = NULL;
	return errnoNu;
}

//17.导出公钥  CMD_EXPORT_PUBLICKEY_BY_ID		0x0D
int acl16_export_public_key(Acl16* fd, uint8_t* pubkey) { // 固定64字节的 pubkey
	uint8_t *rdBufTmp;
	ApduCmd apduCmdTmp;
	apduCmdTmp.ch = CMD_TX_CH;
	apduCmdTmp.cmd = CMD_EXPORT_PUBLICKEY_BY_ID;
	apduCmdTmp.p1 = P1_DEFAULT_VALUE;
	apduCmdTmp.p2 = CMD_PARAMTER_DISABLE;
	apduCmdTmp.lc = CMD_EXPORT_PUBLICKEY_BY_ID_TX_LENTH;
	apduCmdTmp.le = CMD_EXPORT_PUBLICKEY_BY_ID_RX_LENTH;

	int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
	if (rdBufTmp) {
		memcpy(pubkey, (rdBufTmp + 3), CMD_EXPORT_PUBLICKEY_BY_ID_RX_LENTH);
		free(rdBufTmp);
		rdBufTmp = NULL;
	}
	print_array(pubkey,CMD_EXPORT_PUBLICKEY_BY_ID_RX_LENTH,"CMD_EXPORT_PUBLICKEY_BY_ID_RX");
	return errnoNu;
}

//18.安全标志设置   CMD_SECURITY_SET_CONFIG   0x0F
int acl16_security_setConfig(Acl16* fd,uint8_t *security_status){
    	uint8_t *rdBufTmp;
    	ApduCmd apduCmdTmp;
    	apduCmdTmp.ch = CMD_TX_CH;
    	apduCmdTmp.cmd = CMD_SECURITY_SET_CONFIG;
    	apduCmdTmp.p1 = CMD_SECURITY_SET_CONFIG_P1;
    	apduCmdTmp.p2 = CMD_SECURITY_SET_CONFIG_P2;
    	apduCmdTmp.lc = CMD_SECURITY_SET_CONFIG_TX_LENTH;
    	apduCmdTmp.le = CMD_SECURITY_SET_CONFIG_RX_LENTH;
    	print_array(security_status,CMD_SECURITY_SET_CONFIG_TX_LENTH,"CMD_SECURITY_SET_CONFIG");
        int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, security_status, &rdBufTmp);
        free(rdBufTmp);
        rdBufTmp = NULL;
        return errnoNu;
}


//19.安全标志获取   CMD_SECURITY_GET_CONFIG   0x1F
int acl16_security_getConfig(Acl16* fd,uint8_t* security_status){
       	uint8_t *rdBufTmp;
       	ApduCmd apduCmdTmp;
       	apduCmdTmp.ch = CMD_TX_CH;
       	apduCmdTmp.cmd = CMD_SECURITY_GET_CONFIG;
       	apduCmdTmp.p1 = CMD_SECURITY_GET_CONFIG_P1;
       	apduCmdTmp.p2 = CMD_SECURITY_GET_CONFIG_P2;
       	apduCmdTmp.lc = CMD_SECURITY_GET_CONFIG_TX_LENTH;
       	apduCmdTmp.le = CMD_SECURITY_GET_CONFIG_RX_LENTH;
        int errnoNu = cmd_pack_tx_rx(fd, &apduCmdTmp, NULL, &rdBufTmp);
    	if (rdBufTmp) {
    		memcpy(security_status, (rdBufTmp + 3), CMD_SECURITY_GET_CONFIG_RX_LENTH);
    		free(rdBufTmp);
    		rdBufTmp = NULL;
    	}
    	print_array(security_status,CMD_SECURITY_GET_CONFIG_RX_LENTH,"CMD_SECURITY_GET_CONFIG");
    	return errnoNu;
}

