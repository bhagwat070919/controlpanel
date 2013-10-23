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

#include <qcc/platform.h>
#include <stdio.h>
#include "alljoyn/controlpanel/CPSDate.h"
#include "alljoyn/controlpanel/CPSTime.h"

#define AJ_Printf(fmat, ...) \
    do { printf(fmat, ## __VA_ARGS__); } while (0)

#define UNICODE_HI_IN_HEBREW "\xd7\xa9\xd7\x9c\xd7\x95\xd7\x9d\x00"
#define UNICODE_HI_IN_CHINESE "\xe5\x97\xa8"

bool getboolVar();
void setboolVar(bool value);

double getdoubleVar();
void setdoubleVar(double value);

const char* getStringVar();
void setStringVar(const char* value);

uint16_t getuint16Var();
void setuint16Var(uint16_t value);

int16_t getint16Var();
void setint16Var(int16_t value);

uint32_t getuint32Var();
void setuint32Var(uint32_t value);

int32_t getint32Var();
void setint32Var(int32_t value);

uint64_t getuint64Var();
void setuint64Var(uint64_t value);

int64_t getint64Var();
void setint64Var(int64_t value);

bool getEnabledFunc();
bool getWriteableFunc();

const char* getTestString(uint16_t language);
const char* getUrlString();

const ajn::services::CPSDate& getDateProperty();
void setDateProperty(const ajn::services::CPSDate& datePropertyValue);

const ajn::services::CPSTime& getTimeProperty();
void setTimeProperty(const ajn::services::CPSTime& timePropertyValue);

/**
 * Functions for Oven.xml
 */
void startOven();
void stopOven();
uint16_t getTemperature();
void setTemperature(uint16_t temperature);
uint16_t getProgram();
void setProgram(uint16_t program);
const char* getProgramString(uint16_t language);

