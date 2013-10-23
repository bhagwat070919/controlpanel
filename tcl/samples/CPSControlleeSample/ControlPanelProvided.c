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
    context->numSignals = 1;
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
