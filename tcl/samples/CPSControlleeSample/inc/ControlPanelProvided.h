/******************************************************************************
 * Copyright 2013, Qualcomm Innovation Center, Inc.
 *
 *    All rights reserved.
 *    This file is licensed under the 3-clause BSD license in the NOTICE.txt
 *    file for this project. A copy of the 3-clause BSD license is found at:
 *
 *        http://opensource.org/licenses/BSD-3-Clause.
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the license is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the license for the specific language governing permissions and
 *    limitations under the license.
 ******************************************************************************/

#ifndef CONTROLPANELPROVIDED_H_
#define CONTROLPANELPROVIDED_H_

#include <alljoyn.h>
#include <alljoyn/controlpanel/Common/DateTimeUtil.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelGenerated.h"

#define UNICODE_HI_IN_HEBREW "\xd7\xa9\xd7\x9c\xd7\x95\xd7\x9d\x00"
#define UNICODE_HI_IN_CHINESE "\xe5\x97\xa8"

/* For Consistency with C++ code */
#define getboolVar getuint32Var
#define setboolVar setuint32Var

void addDismissSignal(ExecuteActionContext* context, int32_t dismissSignal);

uint8_t getEnabledFunc();
uint8_t getWriteableFunc();
const char* getTestString(uint16_t language);
const char* getUrlString();

void* getDateProperty();
void setDateProperty(DatePropertyValue* datePropertyValue);

void* getTimeProperty();
void setTimeProperty(TimePropertyValue* timePropertyValue);

void* getuint16Var();
void setuint16Var(uint16_t newuint16Var);

void* getint16Var();
void setint16Var(int16_t newint16Var);

void* getuint32Var();
void setuint32Var(uint32_t newuint32Var);

void* getint32Var();
void setint32Var(int32_t newint32Var);

void* getuint64Var();
void setuint64Var(uint64_t newuint64Var);

void* getint64Var();
void setint64Var(int64_t newint64Var);

void* getdoubleVar();
void setdoubleVar(double newdoubleVar);

void* getStringVar();
void setStringVar(const char* newStringVar);

void startOven();
void stopOven();
void*getTemperature();
void setTemperature(uint16_t temperature);
void*getProgram();
void setProgram(uint16_t program);
const char* getProgramString(uint16_t language);

#endif /* CONTROLPANELPROVIDED_H_ */

