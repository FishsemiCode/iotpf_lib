/****************************************************************************
 * external/services/iotpf_lib/cis_log.h
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

#ifndef _CIS_LOG_H_
#define _CIS_LOG_H_


#include <stdio.h>
#include <stdarg.h>
#include "cis_def.h"


#define LOG_EXOUTPUT_TIME_MSK    (0x01)
#define LOG_EXOUTPUT_FILE_MSK    (0x02)
#define LOG_EXOUTPUT_LINE_MSK    (0x04)

#define LOG_LEVEL_ERROR          (0x00)
#define LOG_LEVEL_WARNING        (0x01)
#define LOG_LEVEL_INFO           (0x02)
#define LOG_LEVEL_DEBUG          (0x03)


#define LOG_TEXT_SIZE_MIN        (64)
#define LOG_TEXT_SIZE_MAX        (2048)
#define LOG_PREFIX_SIZE_MAX      (32)

#define LOG_DUMP_ENABLED         0
#define LOG_OUTPUT_EXTINFO       0

#ifndef LOG_TAG
#define LOG_TAG                  "cis"
#endif

#define STRINGIFY(x)  #x
#define STRCONCAT(x, y)  #x#y

extern int utils_strlen(const char *str);
extern int utils_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list args);
extern int utils_snprintf(char* buffer, size_t size, const char* format, ...);

extern void logData(const char* format, ...);
extern void logOutput(uint32_t level, const char *tag, const char* format, ...);


#if CIS_ENABLE_LOG
#if LOG_OUTPUT_EXTINFO
extern const char *cutFileName(const char *s);

#define LOGE(fmt, ...) logOutput(LOG_LEVEL_ERROR,	LOG_TAG, STRCONCAT("%s, line:%d, ", fmt), cutFileName(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...) logOutput(LOG_LEVEL_WARNING, LOG_TAG, STRCONCAT("%s, line:%d, ", fmt), cutFileName(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) logOutput(LOG_LEVEL_INFO,	LOG_TAG, STRCONCAT("%s, line:%d, ", fmt), cutFileName(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOGD(fmt, ...) logOutput(LOG_LEVEL_DEBUG,	LOG_TAG, STRCONCAT("%s, line:%d, ", fmt), cutFileName(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_PRINT(fmt, ...) logData( fmt, ##__VA_ARGS__)
#else
#define LOGE(fmt, ...) logOutput(LOG_LEVEL_ERROR,	LOG_TAG, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) logOutput(LOG_LEVEL_WARNING, LOG_TAG, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) logOutput(LOG_LEVEL_INFO,	LOG_TAG, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) logOutput(LOG_LEVEL_DEBUG,	LOG_TAG, fmt, ##__VA_ARGS__)
#define LOG_PRINT(fmt, ...) logData(fmt, ##__VA_ARGS__)
#endif
#else
#define LOGE(fmt, ...) do {} while(0)
#define LOGW(fmt, ...) do {} while(0)
#define LOGI(fmt, ...) do {} while(0)
#define LOGD(fmt, ...) do {} while(0)
#define LOG_PRINT(fmt, ...) do {} while(0)
#endif

#if LOG_DUMP_ENABLED
#define DUMP_BUF(b,l)	log_dump(NULL, b, l, 0)
#define LOG_BUF(t,b,l)	log_dump(t, b, l, 0)
#else
#define DUMP_BUF(b,l)    do {} while(0)
#define LOG_BUF(t,b,l)   do {} while(0)
#endif//LOG_DUMP_ENABLED


#ifdef __cplusplus
extern "C" {
#endif

void log_config(bool enable, uint8_t exoutput, uint8_t level, uint16_t bufsize);

#if LOG_DUMP_ENABLED
void log_dump(const char *title, const uint8_t *buffer, int length, int indent);
#endif//LOG_DUMP_ENABLED


#ifdef __cplusplus
};
#endif

#endif
