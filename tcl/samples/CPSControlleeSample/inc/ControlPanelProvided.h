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

#include "alljoyn.h"
#include "alljoyn/controlpanel/Common/DateTimeUtil.h"
#include "ControlPanelGenerated.h"

#define UNICODE_HI_IN_HEBREW "\xd7\xa9\xd7\x9c\xd7\x95\xd7\x9d\x00"
#define UNICODE_HI_IN_CHINESE "\xe5\x97\xa8"

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

void* getLPDateProperty();
void setLPDateProperty(DatePropertyValue* datePropertyValue);

void* getLPTimeProperty();
void setLPTimeProperty(TimePropertyValue* timePropertyValue);

void* getLPuint16Var();
void setLPuint16Var(uint16_t newuint16Var);

void* getLPint16Var();
void setLPint16Var(int16_t newint8Var);

void* getLPuint32Var();
void setLPuint32Var(uint32_t newuint32Var);

void* getLPint32Var();
void setLPint32Var(int32_t newint32Var);

void* getLPuint64Var();
void setLPuint64Var(uint64_t newuint64Var);

void* getLPint64Var();
void setLPint64Var(int64_t newint64Var);

void* getLPdoubleVar();
void setLPdoubleVar(double newdoubleVar);

void* getLPStringVar();
void setLPStringVar(char* newStringVar);

void* getLPRecordName();
void setLPRecordName(char* newStringVar);

uint8_t viewLPRecord(uint16_t recordId);
uint8_t updateLPRecord(uint16_t recordId);
uint8_t deleteLPRecord(uint16_t recordId);
uint8_t addLPRecord();
uint8_t confirmLPRecord();
uint8_t confirmDeleteLPRecord();
uint8_t cancelLPRecord();

uint16_t getLPNumRecords();
uint16_t getLPRecordIdByIndx(uint16_t indx);
char* getLPRecordNameByIndx(uint16_t indx);

void copyLPRecord(uint16_t from, uint16_t to);
void initLPRecord(uint16_t indx);

#define ADDED_RECORD 1
#define UPDATED_RECORD 2
#define DELETED_RECORD 3

typedef struct {
    uint16_t recordId;
    uint16_t recordStatus;
    char recordName[25];
    char* recordNamePtr;

    DatePropertyValue date;
    TimePropertyValue time;

    uint16_t uint16Var;
    int16_t int16Var;

    uint32_t uint32Var;
    int32_t int32Var;

    uint64_t uint64Var;
    int64_t int64Var;

    double doubleVar;
    char charVar[25];
    char* charPtr;
} ListPropertyTemplate;

#endif /* CONTROLPANELPROVIDED_H_ */

