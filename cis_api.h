/****************************************************************************
 * external/services/iotpf_lib/cis_api.h
 *
 *     Copyright (C) 2019 FishSemi Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#ifndef _CIS_API_H_
#define _CIS_API_H_
#include <time.h>
#include "cis_def.h"
#include "cis_list.h"


#ifdef __cplusplus
extern "C"
{
#endif


struct st_cis_context;

typedef struct st_cis_version       cis_version_t;
typedef struct st_cis_data          cis_data_t;
typedef struct st_cis_observe_attr  cis_observe_attr_t;
typedef struct st_cis_inst_bitmap   cis_inst_bitmap_t;
typedef struct st_cis_res_count		cis_res_count_t;
typedef struct st_cis_callback      cis_callback_t;
typedef struct st_cis_callback_ctcc  cis_callback_ctcc_t;

typedef struct st_uri               cis_uri_t;
typedef struct st_object            st_object_t;


typedef cis_coapret_t (*cis_read_callback_t)(void *context, cis_uri_t *uri, cis_mid_t mid);
typedef cis_coapret_t (*cis_write_callback_t)(void *context, cis_uri_t *uri, const cis_data_t *value, cis_attrcount_t attrcount, cis_mid_t mid);
typedef cis_coapret_t (*cis_exec_callback_t)(void *context, cis_uri_t *uri, const uint8_t *buffer, uint32_t length, cis_mid_t mid);
typedef cis_coapret_t (*cis_observe_callback_t)(void *context, cis_uri_t *uri, bool flag, cis_mid_t mid);
typedef cis_coapret_t (*cis_discover_callback_t)(void *context, cis_uri_t *uri, cis_mid_t mid);
typedef cis_coapret_t (*cis_set_params_callback_t)(void *context, cis_uri_t *uri, cis_observe_attr_t parameters, cis_mid_t mid);
typedef void (*cis_event_callback_t)(void *context, cis_evt_t id, void *param);

typedef cis_coapret_t (*cis_write_raw_callback_t)(void *context, const uint8_t *data, uint32_t length);


#define LIFETIME_INVALID      ((uint32_t)0xFFFFFFFF)
#define MESSAGEID_INVALID     ((uint32_t)0x00)
#define LIFETIME_LIMIT_MIN    ((uint32_t)0x0000000F)
#define LIFETIME_LIMIT_MAX    ((uint32_t)0x0FFFFFFF)

#define OBJECT_MAX_ID         ((uint16_t)0xFFFF - 1)
#define INSTANCE_MAX_ID       ((uint16_t)0xFFFF - 1)
#define RESOURCE_MAX_ID       ((uint16_t)0xFFFF - 1)


#define PUMP_RET_CUSTOM       ((uint32_t)0xFFFFFFFF)
#define PUMP_RET_NOSLEEP      ((uint32_t)0x00)

#define URI_INVALID           ((uint16_t)0xFFFF)
#define URI_MAX_ID            ((uint16_t)0xFFFF - 1)

#define URI_FLAG_OBJECT_ID    (uint8_t)0x04
#define URI_FLAG_INSTANCE_ID  (uint8_t)0x02
#define URI_FLAG_RESOURCE_ID  (uint8_t)0x01

#define CIS_URI_IS_SET_INSTANCE(uri) (((uri)->flag & URI_FLAG_INSTANCE_ID) != 0)
#define CIS_URI_IS_SET_RESOURCE(uri) (((uri)->flag & URI_FLAG_RESOURCE_ID) != 0)


#define CIS_ATTR_FLAG_MIN_PERIOD      (uint8_t)0x01
#define CIS_ATTR_FLAG_MAX_PERIOD      (uint8_t)0x02
#define CIS_ATTR_FLAG_GREATER_THAN    (uint8_t)0x04
#define CIS_ATTR_FLAG_LESS_THAN       (uint8_t)0x08
#define CIS_ATTR_FLAG_STEP            (uint8_t)0x10



struct st_uri
{
  uint8_t flag;           // indicates which segments are set
  cis_oid_t objectId;
  cis_iid_t instanceId;
  cis_rid_t resourceId;
};

struct st_object
{
  struct st_object *next;               // for internal use only.
  cis_listid_t objID;
  cis_instcount_t instBitmapBytes;
  cis_instcount_t instBitmapCount;
  uint8_t *instBitmapPtr;
  cis_instcount_t instValidCount;

  cis_attrcount_t attributeCount;
  cis_actcount_t actionCount;
  void *userData;
};


cis_ret_t cis_uri_make(cis_oid_t oid, cis_iid_t iid, cis_rid_t rid, cis_uri_t *uri);
cis_ret_t cis_uri_update(cis_uri_t *uri);
void cisapi_wakeup_pump(void);
uint32_t cis_pump_initialize(void);


typedef enum
{
  cis_data_type_undefine = 0,
  cis_data_type_string,
  cis_data_type_opaque,
  cis_data_type_integer,
  cis_data_type_float,
  cis_data_type_bool,
}cis_datatype_t;

struct st_cis_callback
{
  cis_read_callback_t onRead;
  cis_write_callback_t onWrite;
  cis_exec_callback_t onExec;
  cis_observe_callback_t onObserve;
  cis_event_callback_t onEvent;
  cis_discover_callback_t onDiscover;
  cis_set_params_callback_t onSetParams;
};

struct st_cis_callback_ctcc
{
  cis_read_callback_t onRead;
  cis_write_callback_t onWrite;
  cis_exec_callback_t onExec;
  cis_observe_callback_t onObserve;
  cis_event_callback_t onEvent;
  cis_write_raw_callback_t onWriteRaw;
};



struct st_cis_data
{
  cis_rid_t id;
  cis_datatype_t type;

  struct
    {
      uint32_t length;
      uint8_t *buffer;
    }asBuffer;

  union
    {
      bool asBoolean;
      int64_t asInteger;
      double asFloat;
    } value;
} ;


struct st_cis_version
{
  uint8_t major;
  uint8_t minor;
  uint8_t micro;
#if CIS_ENABLE_DM
  uint8_t dm_major;
  uint8_t dm_minor;
  uint8_t dm_micro;
#endif
};

struct st_cis_observe_attr
{
  uint8_t toSet;
  uint8_t toClear;
  cis_time_t minPeriod;
  cis_time_t maxPeriod;
  float greaterThan;
  float lessThan;
  float step;
};

struct st_cis_inst_bitmap
{
  cis_instcount_t instanceCount;
  cis_instcount_t instanceBytes;
  const uint8_t *instanceBitmap;
};



struct st_cis_res_count
{
  cis_attrcount_t attrCount;
  cis_actcount_t actCount;
};

typedef enum
{
  cis_res_result_undefine = 0,
  cis_res_result_content,
  cis_res_result_changed,
  cis_res_result_badResult = 11,
  cis_res_result_unuthorized,
  cis_res_result_notFound,
  cis_res_result_methodNotAllowed,
  cis_res_result_notAcceptable,
}cis_res_result_t;

typedef enum
{
  cis_iotpf_mode_at,
  cis_iotpf_mode_api,
}cis_iotpf_mode_t;

typedef enum
{
  cis_iotpf_operator_ctcc,
  cis_iotpf_operator_cmcc,
}cis_iotpf_operator_t;


typedef struct
{
  cis_iotpf_mode_t iotpf_mode;
  cis_iotpf_operator_t iotpf_operator;
} cis_iotpf_configs;

cis_ret_t cis_version(cis_version_t *version);

#if CIS_ENABLE_CMIOT_OTA
uint8_t cis_ota_get_version(char *ver);
cis_ret_t cis_init_ota(void **context, void *configPtr, uint16_t configLen, cis_time_t ota_timeout_duration);
#endif

#if CIS_ENABLE_DM
char *cis_get_version(char *ver);
#endif

cis_ret_t cis_init(void **context, void *configPtr, uint16_t configLen);
cis_ret_t cis_deinit(void **context);

cis_ret_t cis_register(void *context, cis_time_t lifetime, const cis_callback_t *cb);
cis_ret_t cis_register_ctcc(void *context, cis_time_t lifetime, const cis_callback_ctcc_t *cb);

cis_ret_t cis_unregister(void *context);

cis_ret_t cis_addobject(void *context, cis_oid_t objectid, const cis_inst_bitmap_t *bitmap, const cis_res_count_t *rescount);
cis_ret_t cis_delobject(void *context, cis_oid_t objectid);
st_object_t *cis_findObject(void *context, cis_oid_t objectid);


uint32_t cis_pump(void *context, time_t *timeoutP);
cis_ret_t cis_update_reg(void *context, cis_time_t lifetime, bool withObjects);

cis_ret_t cis_response(void *context, const cis_uri_t *uri, const cis_data_t *value, cis_mid_t mid, cis_coapret_t result);
cis_ret_t cis_notify(void *context, const cis_uri_t *uri, const cis_data_t *value, cis_mid_t mid, cis_coapret_t result, bool needAck);
cis_ret_t cis_notify_raw(void *context, uint8_t *data, uint32_t length);
cis_ret_t cis_discover_response(void *context, cis_mid_t msgId, cis_res_result_t result, char *valueStr);

void ciscom_destory(void);
int ciscom_initialize(cis_iotpf_configs *pIotpf_configs);

int cis_get_iotpf_mode(void);
int cis_get_iotpf_operator(void);



int cisat_readloop(int fd);
int cisat_initialize(void);

int cisapi_initialize(void);



void cis_data_encode_string(const char *string, cis_data_t *dataP);
void cis_data_encode_opaque(uint8_t *buffer, size_t length, cis_data_t *dataP);
void cis_data_encode_nstring(const char *string, size_t length, cis_data_t *dataP);
void cis_data_encode_int(int64_t value, cis_data_t *dataP);
int cis_data_decode_int(const cis_data_t *dataP, int64_t *valueP);
void cis_data_encode_float(double value, cis_data_t *dataP);
int cis_data_decode_float(const cis_data_t *dataP, double *valueP);
void cis_data_encode_bool(bool value, cis_data_t *dataP);
int cis_data_decode_bool(const cis_data_t *dataP, bool *valueP);


#if CIS_ENABLE_UPDATE_MCU
cis_ret_t cis_set_sota_info(char *version, uint16_t size);

cis_ret_t cis_notify_sota_result(void *context, uint8_t eventid);

#endif
/*
 * Event code
 * @cis_evt_t
 */
#define     CIS_EVENT_BASE                      (cis_evt_t)0x00
#define     CIS_EVENT_BOOTSTRAP_START           CIS_EVENT_BASE + 1
#define     CIS_EVENT_BOOTSTRAP_SUCCESS         CIS_EVENT_BASE + 2
#define     CIS_EVENT_BOOTSTRAP_FAILED          CIS_EVENT_BASE + 3
#define     CIS_EVENT_CONNECT_SUCCESS           CIS_EVENT_BASE + 4
#define     CIS_EVENT_CONNECT_FAILED            CIS_EVENT_BASE + 5

#define     CIS_EVENT_REG_SUCCESS               CIS_EVENT_BASE + 6
#define     CIS_EVENT_REG_FAILED                CIS_EVENT_BASE + 7
#define     CIS_EVENT_REG_TIMEOUT               CIS_EVENT_BASE + 8

#define     CIS_EVENT_LIFETIME_TIMEOUT          CIS_EVENT_BASE + 9
#define     CIS_EVENT_STATUS_HALT               CIS_EVENT_BASE + 10
#define     CIS_EVENT_UPDATE_SUCCESS            CIS_EVENT_BASE + 11
#define     CIS_EVENT_UPDATE_FAILED             CIS_EVENT_BASE + 12
#define     CIS_EVENT_UPDATE_TIMEOUT            CIS_EVENT_BASE + 13
#define     CIS_EVENT_UPDATE_NEED               CIS_EVENT_BASE + 14


#define     CIS_EVENT_UNREG_DONE                CIS_EVENT_BASE + 15

#define     CIS_EVENT_RESPONSE_FAILED           CIS_EVENT_BASE + 20
#define     CIS_EVENT_RESPONSE_SUCCESS          CIS_EVENT_BASE + 21
#define     CIS_EVENT_NOTIFY_FAILED             CIS_EVENT_BASE + 25
#define     CIS_EVENT_NOTIFY_SUCCESS            CIS_EVENT_BASE + 26

#define     CIS_EVENT_FIRMWARE_DOWNLOADING           CIS_EVENT_BASE + 40 //enter to downloading
#define     CIS_EVENT_FIRMWARE_DOWNLOAD_FAILED       CIS_EVENT_BASE + 41 //enter downloading error
#define     CIS_EVENT_FIRMWARE_DOWNLOADED            CIS_EVENT_BASE + 42  //download finish
#define     CIS_EVENT_FIRMWARE_UPDATING              CIS_EVENT_BASE + 43  //updating
#define     CIS_EVENT_FIRMWARE_UPDATE_SUCCESS        CIS_EVENT_BASE + 44  //update success
#define     CIS_EVENT_FIRMWARE_UPDATE_FAILED         CIS_EVENT_BASE + 45   //update fail
#define     CIS_EVENT_FIRMWARE_UPDATE_OVER           CIS_EVENT_BASE + 46   //update finish
#define     CIS_EVENT_FIRMWARE_DOWNLOAD_DISCONNECT   CIS_EVENT_BASE + 47    //update error
#define     CIS_EVENT_FIRMWARE_ERASE_SUCCESS         CIS_EVENT_BASE + 48
#define     CIS_EVENT_FIRMWARE_ERASE_FAIL            CIS_EVENT_BASE + 49
#define     CIS_EVENT_FIRMWARE_TRIGGER               CIS_EVENT_BASE + 50

#define     CIS_EVENT_SOTA_DOWNLOADING				 CIS_EVENT_BASE + 51
#define     CIS_EVENT_SOTA_DOWNLOAED				 CIS_EVENT_BASE + 52
#define     CIS_EVENT_SOTA_FLASHERASE				 CIS_EVENT_BASE + 53
#define     CIS_EVENT_SOTA_UPDATING					 CIS_EVENT_BASE + 54


#define     CIS_EVENT_CMIOT_OTA_START         		 CIS_EVENT_BASE + 60
#define     CIS_EVENT_CMIOT_OTA_SUCCESS            	 CIS_EVENT_BASE + 61
#define     CIS_EVENT_CMIOT_OTA_FAIL            	 CIS_EVENT_BASE + 62
#define     CIS_EVENT_CMIOT_OTA_FINISH            	 CIS_EVENT_BASE + 63



/*
 * Error code
 * @cis_ret_t
 */
#define     CIS_RET_BASE                         (cis_ret_t)0x00
#define     CIS_RET_OK                           CIS_RET_BASE
#define     CIS_RET_NO_ERROR                     CIS_RET_BASE
#define     CIS_RET_ERROR                        CIS_RET_BASE - 1
#define     CIS_RET_FAILED                       CIS_RET_BASE - 2
#define     CIS_RET_INVILID                      CIS_RET_BASE - 3
#define     CIS_RET_EXIST                        CIS_RET_BASE - 4
#define     CIS_RET_PARAMETER_ERR                CIS_RET_BASE - 5
#define     CIS_RET_MEMORY_ERR                   CIS_RET_BASE - 6
#define     CIS_RET_NOT_FOUND                    CIS_RET_BASE - 7
#define     CIS_RET_TIMEOUT                      CIS_RET_BASE - 8
#define     CIS_RET_COUNTOUT                     CIS_RET_BASE - 9
#define     CIS_RET_PENDING                      CIS_RET_BASE - 10
#define     CIS_RET_UNSUPPORTIVE                 CIS_RET_BASE - 11



/*
 *COAP result code
 *@cis_cbret_t
 */
#define     CIS_COAP_204_CHANGED                (uint8_t)0x44
#define     CIS_COAP_205_CONTENT                (uint8_t)0x45
#define     CIS_COAP_206_CONFORM                (uint8_t)0x46
#define     CIS_COAP_231_CONTINUE               (uint8_t)0x5F
#define     CIS_COAP_400_BAD_REQUEST            (uint8_t)0x80
#define     CIS_COAP_401_UNAUTHORIZED           (uint8_t)0x81
#define     CIS_COAP_404_NOT_FOUND              (uint8_t)0x84
#define     CIS_COAP_405_METHOD_NOT_ALLOWED     (uint8_t)0x85
#define     CIS_COAP_406_NOT_ACCEPTABLE         (uint8_t)0x86
#define     CIS_COAP_503_SERVICE_UNAVAILABLE    (uint8_t)0xA3


#define     CIS_CALLBACK_CONFORM               CIS_COAP_206_CONFORM
#define     CIS_CALLBACK_BAD_REQUEST           CIS_COAP_400_BAD_REQUEST
#define     CIS_CALLBACK_UNAUTHORIZED          CIS_COAP_401_UNAUTHORIZED
#define     CIS_CALLBACK_NOT_FOUND             CIS_COAP_404_NOT_FOUND
#define     CIS_CALLBACK_METHOD_NOT_ALLOWED    CIS_COAP_405_METHOD_NOT_ALLOWED
#define     CIS_CALLBACK_NOT_ACCEPTABLE        CIS_COAP_406_NOT_ACCEPTABLE
#define     CIS_CALLBACK_SERVICE_UNAVAILABLE   CIS_COAP_503_SERVICE_UNAVAILABLE


#define     CIS_RESPONSE_READ                    CIS_COAP_205_CONTENT
#define     CIS_RESPONSE_WRITE                   CIS_COAP_204_CHANGED
#define     CIS_RESPONSE_EXECUTE                 CIS_COAP_204_CHANGED
#define     CIS_RESPONSE_OBSERVE                 CIS_COAP_205_CONTENT
#define     CIS_RESPONSE_OBSERVE_PARAMS          CIS_COAP_204_CHANGED
#define     CIS_RESPONSE_DISCOVER                CIS_COAP_205_CONTENT
#define     CIS_RESPONSE_CONTINUE                CIS_COAP_231_CONTINUE
#define     CIS_RESPONSE_BAD_REQUEST             CIS_COAP_400_BAD_REQUEST
#define     CIS_RESPONSE_UNAUTHORIZED            CIS_COAP_401_UNAUTHORIZED
#define     CIS_RESPONSE_NOT_FOUND               CIS_COAP_404_NOT_FOUND
#define     CIS_RESPONSE_METHOD_NOT_ALLOWED      CIS_COAP_405_METHOD_NOT_ALLOWED
#define     CIS_RESPONSE_NOT_ACCEPTABLE          CIS_COAP_406_NOT_ACCEPTABLE
#define     CIS_RESPONSE_SERVICE_UNAVAILABLE     CIS_COAP_503_SERVICE_UNAVAILABLE

#define     CIS_NOTIFY_CONTENT                   CIS_COAP_205_CONTENT
#define     CIS_NOTIFY_CONTINUE                  CIS_COAP_231_CONTINUE



#if CIS_ENABLE_DM

typedef struct
{
  char szCMEI_IMEI[64]; 	//CMEI/IMEI
  char szIMSI[64];		//IMSI
  char szDMv[16]; 		//DM???
  char szAppKey[64]; 		//appkey
  char szPwd[64];			//pwd??
  int nAddressFamily; 	//4?6  ipv4,ipv6
  char szCMEI_IMEI2[64];	//CMEI/IMEI
} Options;
#endif


#ifdef __cplusplus
};
#endif

#endif//_CIS_API_H_
