/****************************************************************************
 * external/services/iotpf_lib/cis_def.h
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

#ifndef _CIS_DEFINITION_HEADER_
#define _CIS_DEFINITION_HEADER_

#include <stdbool.h>

//some pre-defined macro
//#define  LWM2M_LITTLE_ENDIAN
#define  LWM2M_BIG_ENDIAN
#define  CIS_LINUX

#include <stdint.h>
#include <stdlib.h>

#ifndef TRUE
#define  TRUE (1)
#endif

#ifndef FALSE
#define  FALSE (0)
#endif

typedef int32_t      cis_evt_t;
typedef int32_t      cis_ret_t;
typedef uint8_t      cis_coapret_t;
typedef uint16_t     cis_oid_t;
typedef uint16_t     cis_iid_t;
typedef uint16_t     cis_rid_t;
typedef uint16_t     cis_coapid_t;//coap message id
typedef uint32_t     cis_mid_t;   //callback message id

typedef cis_iid_t    cis_instcount_t;
typedef cis_rid_t    cis_attrcount_t;
typedef cis_rid_t    cis_actcount_t;
typedef cis_rid_t    cis_rescount_t;
typedef int32_t      cis_time_t;  //normally in second unit

/*
 *
 */
#define     CIS_TWO_MCU                         1
#define     CIS_ONE_MCU                         0

#ifndef     CIS_TWO_MCU
#define     CIS_TWO_MCU                   0
#endif

#ifndef     CIS_ONE_MCU
#define     CIS_ONE_MCU                   0
#endif




#if !(CIS_TWO_MCU || CIS_ONE_MCU)
#error "You must select one scheme from ONE MCU scheme and two MCU scheme"
#elif (CIS_TWO_MCU && CIS_ONE_MCU)
#error "You can only select one scheme from ONE MCU scheme and two MCU scheme"
#endif

#define     CIS_ENABLE_LOG                      1
#define     CIS_ENABLE_PSK                      1
#define     CIS_ENABLE_DTLS                     1
#define     CIS_DTLS_LOG                        1
#define     CIS_LITTLE_ENDIAN                   1
#define     CIS_OPERATOR_CTCC                   1

#if 0
#define     CIS_ENABLE_DM                       1
#define     CIS_ENABLE_UPDATE                   1
#define     CIS_ENABLE_UPDATE_MCU               1

#define     CIS_ENABLE_AUTH                     1
#define     CIS_ENABLE_MONITER                  1
//#define     CIS_ENABLE_CMIOT_OTA                1
#define     CIS_ENABLE_DTLS                     1
#define     CIS_ENABLE_PSK                      1
#define     CIS_LITTLE_ENDIAN                   1
#define     CIS_ENABLE_LOG                      1
//#define     CIS_DTLS_LOG                        1

//#define     CIS_ENABLE_MEMORYTRACE              1
#endif

#ifndef     CIS_OPERATOR_CTCC
#define     CIS_OPERATOR_CTCC               0
#endif

#ifndef     CIS_VERSION_MAJOR
#define     CIS_VERSION_MAJOR                   2
#endif
#ifndef     CIS_VERSION_MINOR
#define     CIS_VERSION_MINOR                   3
#endif
#ifndef     CIS_VERSION_MICRO
#define     CIS_VERSION_MICRO                   0
#endif

#ifndef     DM_VERSION_MAJOR
#define     DM_VERSION_MAJOR                   1
#endif
#ifndef     DM_VERSION_MINOR
#define     DM_VERSION_MINOR                   1
#endif
#ifndef     DM_VERSION_MICRO
#define     DM_VERSION_MICRO                   1
#endif


#ifndef     CIS_ENABLE_UPDATE_MCU
#define     CIS_ENABLE_UPDATE_MCU               0
#else
#undef      CIS_ENABLE_UPDATE_MCU
#define     CIS_ENABLE_UPDATE_MCU               1
#endif


#ifndef     CIS_ENABLE_UPDATE
#define     CIS_ENABLE_UPDATE                    0
#else
#undef      CIS_ENABLE_UPDATE
#define     CIS_ENABLE_UPDATE                    1
#endif

#ifndef     CIS_ENABLE_MONITER
#define     CIS_ENABLE_MONITER                   0
#else
#undef      CIS_ENABLE_MONITER
#define     CIS_ENABLE_MONITER                   1
#endif

#ifndef     CIS_ENABLE_DM
#define     CIS_ENABLE_DM                    0
#else
#undef      CIS_ENABLE_DM
#define     CIS_ENABLE_DM                    1
#endif

#ifndef     OTA_VERSION_MAJOR
#define     OTA_VERSION_MAJOR                   0
#endif
#ifndef     OTA_VERSION_MINOR
#define     OTA_VERSION_MINOR                   0
#endif
#ifndef     OTA_VERSION_MICRO
#define     OTA_VERSION_MICRO                   3
#endif



#ifndef		CIS_ENABLE_CMIOT_OTA
#define		CIS_ENABLE_CMIOT_OTA				0
#else
#undef		CIS_ENABLE_CMIOT_OTA
#define		CIS_ENABLE_CMIOT_OTA				1
#endif

#ifndef     CIS_ENABLE_AUTH
#define     CIS_ENABLE_AUTH                    0
#else
#undef      CIS_ENABLE_AUTH
#define     CIS_ENABLE_AUTH                    1
#endif


//default
#define     CIS_ENABLE_BLOCK

#ifndef     CIS_ENABLE_BLOCK
#define     CIS_ENABLE_BLOCK                    0
#else
#undef      CIS_ENABLE_BLOCK
#define     CIS_ENABLE_BLOCK                    1
#endif

#ifndef     CIS_ENABLE_MEMORYTRACE
#define     CIS_ENABLE_MEMORYTRACE              0
#else
#undef      CIS_ENABLE_MEMORYTRACE
#define     CIS_ENABLE_MEMORYTRACE              1
#endif

#ifndef     CIS_ENABLE_LOG
#define     CIS_ENABLE_LOG                      0
#else
#undef      CIS_ENABLE_LOG
#define     CIS_ENABLE_LOG                      1
#endif



#ifndef     CIS_ENABLE_DTLS
#define     CIS_ENABLE_DTLS                      0
#else
#undef      CIS_ENABLE_DTLS
#define     CIS_ENABLE_DTLS                      1
#endif

#ifndef     CIS_DTLS_LOG
#define     CIS_DTLS_LOG                      0
#else
#undef      CIS_DTLS_LOG
#define     CIS_DTLS_LOG                      1
#endif

#ifndef     CIS_LITTLE_ENDIAN
#define     CIS_LITTLE_ENDIAN                      0
#else
#undef      CIS_LITTLE_ENDIAN
#define     CIS_LITTLE_ENDIAN                      1
#endif


#ifndef     CIS_ENABLE_PSK
#define     CIS_ENABLE_PSK                       0
#else
#undef      CIS_ENABLE_PSK
#define     CIS_ENABLE_PSK                       1
#endif


#define     CIS_CONFIG_LOCK_INFINITY              0xFFFFFFFF
#define     CIS_CONFIG_MEMORYTRACE_TIMEOUT        (5)
#define     CIS_CONFIG_CALLBACK_TIMEOUT           (30)
#define     CIS_CONFIG_BOOTSTRAP_TIMEOUT          (20)

#define     CIS_CONFIG_CONNECT_RETRY_TIME         (2)
#define     CIS_CONFIG_REG_INTERVAL_TIME          (5)

#define     CIS_COFNIG_REG_QUERY_SIZE             (256)
#define     CIS_COFNIG_REG_PAYLOAD_SIZE           (512)

// the maximum payload transfered by block1 we accumulate per server
#define     CIS_CONFIG_BLOCK1_SIZE_MAX            (2048)


#if CIS_ENABLE_UPDATE_MCU

#define  sota_event_unknow    0
#define	 sota_erase_success   1       //for erase, handle /5/0/26501
#define  sota_erase_fail      2
#define	 sota_write_success   3            //for write
#define	 sota_write_fail      4
#define	 sota_validate_success 5       //for validate
#define	 sota_validate_fail    6
#define	 sota_update_success   7   //for update
#define	 sota_update_fail      8

#endif


#endif //_CIS_DEFINITION_HEADER_
