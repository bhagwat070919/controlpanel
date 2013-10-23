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

#include "ControlPanelProvided.h"
#define MAX_LIST_PROPERY_RECORDS 10

static uint16_t lastRecordIndx = 1;
static uint16_t lastRecordId = 1;
static uint16_t selectedRecordIndx = 0;

static ListPropertyTemplate listPropTest[MAX_LIST_PROPERY_RECORDS + 1];

static uint16_t uint16Var = 0;
static int16_t int16Var = 0;

static uint32_t uint32Var = 0;
static int32_t int32Var = 0;

static uint64_t uint64Var = 0;
static int64_t int64Var = 0;

static double doubleVar = 0;

static char initialString[100] = "Initial String";
static char* stringVar = initialString;

static const char* sampleString = "This is a test";
static const char* sampleUrlString = "www.ControlPanelTest.com";

static DatePropertyValue date = { .fullYear = 2006, .month = 6, .mDay = 13 };
static TimePropertyValue time = { .hour = 18, .minute = 0, .second = 0 };

void addDismissSignal(ExecuteActionContext* context, int32_t dismissSignal)
{
	context->numSignals=1;
	context->signals[0].signalId = dismissSignal;
	context->signals[0].signalType = SIGNAL_TYPE_DISMISS;
}

const char* getUrlString()
{
	return sampleUrlString;
}

void* getDateProperty()
{
    return &date;
}

void setDateProperty(DatePropertyValue* datePropertyValue)
{
    date.fullYear = datePropertyValue->fullYear;
    date.month = datePropertyValue->month;
    date.mDay = datePropertyValue->mDay;
}

void* getTimeProperty()
{
    return &time;
}
void setTimeProperty(TimePropertyValue* timePropertyValue)
{
    time.hour = timePropertyValue->hour;
    time.minute = timePropertyValue->minute;
    time.second = timePropertyValue->second;
}

uint8_t getEnabledFunc()
{
    return TRUE;
}
uint8_t getWriteableFunc()
{
    return TRUE;
}

const char* getTestString(uint16_t language)
{
    return sampleString;
}

void* getuint16Var()
{
    return &uint16Var;
}

void setuint16Var(uint16_t newuint16Var)
{
    uint16Var = newuint16Var;
}

void* getint16Var()
{
    return &int16Var;
}

void setint16Var(int16_t newint16Var)
{
    int16Var = newint16Var;
}

void* getuint32Var()
{
    return &uint32Var;
}

void setuint32Var(uint32_t newuint32Var)
{
    uint32Var = newuint32Var;
}

void* getint32Var()
{
    return &int32Var;
}

void setint32Var(int32_t newint32Var)
{
    int32Var = newint32Var;
}

void* getuint64Var()
{
    return &uint64Var;
}

void setuint64Var(uint64_t newuint64Var)
{
    uint64Var = newuint64Var;
}

void* getint64Var()
{
    return &int64Var;
}

void setint64Var(int64_t newint64Var)
{
    int64Var = newint64Var;
}

void* getdoubleVar()
{
    return &doubleVar;
}

void setdoubleVar(double newdoubleVar)
{
    doubleVar = newdoubleVar;
}

void* getStringVar()
{
    return &stringVar;
}

void setStringVar(const char* newStringVar)
{
    strncpy(stringVar, newStringVar, 99);
    stringVar[99] = '\0';
}

void* getLPDateProperty()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].date;
    return 0;
}

void setLPDateProperty(DatePropertyValue* datePropertyValue)
{
    listPropTest[0].date.fullYear = datePropertyValue->fullYear;
    listPropTest[0].date.month = datePropertyValue->month;
    listPropTest[0].date.mDay = datePropertyValue->mDay;
}

void* getLPTimeProperty()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].time;
    return 0;
}

void setLPTimeProperty(TimePropertyValue* timePropertyValue)
{
    listPropTest[0].time.hour = timePropertyValue->hour;
    listPropTest[0].time.minute = timePropertyValue->minute;
    listPropTest[0].time.second = timePropertyValue->second;
}

void* getLPuint16Var()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].uint16Var;
    return 0;
}

void setLPuint16Var(uint16_t newuint16Var)
{
    listPropTest[0].uint16Var = newuint16Var;
}

void* getLPint16Var()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].int16Var;
    return 0;
}

void setLPint16Var(int16_t newint16Var)
{
    listPropTest[0].uint16Var = newint16Var;
}

void* getLPuint32Var()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].uint32Var;
    return 0;
}

void setLPuint32Var(uint32_t newuint32Var)
{
    listPropTest[0].uint32Var = newuint32Var;
}

void* getLPint32Var()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].int32Var;
    return 0;
}

void setLPint32Var(int32_t newint32Var)
{
    listPropTest[0].int32Var = newint32Var;
}

void* getLPuint64Var()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].uint64Var;
    return 0;
}

void setLPuint64Var(uint64_t newuint64Var)
{
    listPropTest[0].uint64Var = newuint64Var;
}

void* getLPint64Var()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].int64Var;
    return 0;
}

void setLPint64Var(int64_t newint64Var)
{
    listPropTest[0].int64Var = newint64Var;
}

void* getLPdoubleVar()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].doubleVar;
    return 0;
}

void setLPdoubleVar(double newdoubleVar)
{
    listPropTest[0].doubleVar = newdoubleVar;
}

void* getLPStringVar()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].charPtr;
    return 0;
}

void setLPStringVar(char* newStringVar)
{
    strncpy(listPropTest[0].charVar, newStringVar, 24);
    listPropTest[0].charVar[24] = '\0';
}

void* getLPRecordName()
{
    if (selectedRecordIndx != 0)
        return &listPropTest[selectedRecordIndx].recordNamePtr;
    return 0;
}

void setLPRecordName(char* newStringVar)
{
    strncpy(listPropTest[0].recordName, newStringVar, 24);
    listPropTest[0].recordName[24] = '\0';
}

uint8_t viewLPRecord(uint16_t recordId)
{
    if (selectedRecordIndx != 0) {   //was in middle of dealing with record
        cancelLPRecord(selectedRecordIndx);
    }

    uint16_t indx;
    for (indx = 1; indx < lastRecordIndx; indx++) {
        if (listPropTest[indx].recordId == recordId) {
            selectedRecordIndx = indx;
            return TRUE;
        }
    }
    return FALSE;
}

uint8_t updateLPRecord(uint16_t recordId)
{
    if (selectedRecordIndx != 0) {   //was in middle of dealing with record
        cancelLPRecord(selectedRecordIndx);
    }

    uint16_t indx;
    for (indx = 1; indx < lastRecordIndx; indx++) {
        if (listPropTest[indx].recordId == recordId) {
            selectedRecordIndx = indx;
            listPropTest[selectedRecordIndx].recordStatus = UPDATED_RECORD;
            copyLPRecord(selectedRecordIndx, 0);
            return TRUE;
        }
    }
    return FALSE;
}

uint8_t deleteLPRecord(uint16_t recordId)
{
    if (selectedRecordIndx != 0) {   //was in middle of dealing with record
        cancelLPRecord(selectedRecordIndx);
    }

    uint16_t indx;
    for (indx = 1; indx < lastRecordIndx; indx++) {
        if (listPropTest[indx].recordId == recordId) {
            selectedRecordIndx = indx;
            listPropTest[selectedRecordIndx].recordStatus = DELETED_RECORD;
            return TRUE;
        }
    }
    return FALSE;
}

uint8_t addLPRecord()
{
    if (selectedRecordIndx != 0) {   //was in middle of dealing with record
        cancelLPRecord(selectedRecordIndx);
    }

    if (lastRecordIndx == MAX_LIST_PROPERY_RECORDS)
        return FALSE;

    selectedRecordIndx = lastRecordIndx;
    lastRecordIndx++;

    initLPRecord(selectedRecordIndx);
    copyLPRecord(selectedRecordIndx, 0);
    return TRUE;
}

uint8_t confirmLPRecord()
{
    if (selectedRecordIndx == 0)
        return FALSE;

    if (listPropTest[selectedRecordIndx].recordStatus == DELETED_RECORD) {
        return confirmDeleteLPRecord();
    }

    copyLPRecord(0, selectedRecordIndx);
    listPropTest[selectedRecordIndx].recordStatus = 0;
    selectedRecordIndx = 0;
    return TRUE;
}

uint8_t cancelLPRecord()
{
    if (selectedRecordIndx == 0)
        return FALSE;

    if (listPropTest[selectedRecordIndx].recordStatus == ADDED_RECORD) {
        listPropTest[selectedRecordIndx].recordStatus = 0;
        lastRecordIndx--;
        selectedRecordIndx = 0;
        return TRUE;
    }

    listPropTest[selectedRecordIndx].recordStatus = 0;
    return TRUE;
}

uint8_t confirmDeleteLPRecord()
{
    if (lastRecordIndx == 1)
        return FALSE;

    copyLPRecord(lastRecordIndx - 1, selectedRecordIndx);
    lastRecordIndx--;
    selectedRecordIndx = 0;
    return TRUE;
}

void copyLPRecord(uint16_t from, uint16_t to)
{
    listPropTest[to].int16Var = listPropTest[from].int16Var;
    listPropTest[to].int32Var = listPropTest[from].int32Var;
    listPropTest[to].int64Var = listPropTest[from].int64Var;
    listPropTest[to].uint16Var = listPropTest[from].uint16Var;
    listPropTest[to].uint32Var = listPropTest[from].uint32Var;
    listPropTest[to].uint64Var = listPropTest[from].uint64Var;
    listPropTest[to].doubleVar = listPropTest[from].doubleVar;

    strncpy(listPropTest[to].recordName, listPropTest[from].recordName, 25);
    strncpy(listPropTest[to].charVar, listPropTest[from].charVar, 25);

    listPropTest[to].date.fullYear =  listPropTest[from].date.fullYear;
    listPropTest[to].date.month    =  listPropTest[from].date.month;
    listPropTest[to].date.mDay     =  listPropTest[from].date.mDay;

    listPropTest[to].time.hour     =  listPropTest[from].time.hour;
    listPropTest[to].time.minute   =  listPropTest[from].time.minute;
    listPropTest[to].time.second   =  listPropTest[from].time.second;
}

void initLPRecord(uint16_t indx)
{
    listPropTest[indx].recordStatus = ADDED_RECORD;
    listPropTest[indx].recordId = lastRecordId++;
    listPropTest[indx].recordNamePtr = listPropTest[indx].recordName;
    listPropTest[indx].charPtr = listPropTest[indx].charVar;


    listPropTest[indx].int16Var = 0;
    listPropTest[indx].int32Var = 0;
    listPropTest[indx].int64Var = 0;
    listPropTest[indx].uint16Var = 0;
    listPropTest[indx].uint32Var = 0;
    listPropTest[indx].uint64Var = 0;
    listPropTest[indx].doubleVar = 0;

    strncpy(listPropTest[indx].charVar, "Empty String", 25);
    strncpy(listPropTest[indx].recordName, "Empty String", 25);

    listPropTest[indx].date.fullYear =  2006;
    listPropTest[indx].date.month    =  6;
    listPropTest[indx].date.mDay     =  13;

    listPropTest[indx].time.hour     =  18;
    listPropTest[indx].time.minute   =  30;
    listPropTest[indx].time.second   =  30;
}

uint16_t getLPNumRecords()
{
    return lastRecordIndx - 1;
}

uint16_t getLPRecordIdByIndx(uint16_t indx)
{
    if (indx + 1 < lastRecordIndx)
        return listPropTest[indx + 1].recordId;
    return 0;
}

char* getLPRecordNameByIndx(uint16_t indx)
{
    if (indx + 1 < lastRecordIndx)
        return listPropTest[indx + 1].recordName;
    return 0;
}
