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

#ifndef LISTPROPERTYWIDGET_H_
#define LISTPROPERTYWIDGET_H_

#include "alljoyn/controlpanel/Common/BaseWidget.h"

#define SENDER_ID_LENGTH 15

/////////////////////////*     ListPropertyWidget     *//////////////////////////////////////

typedef struct ListPropertyWidget {
    BaseWidget base;
    char currentViewer[SENDER_ID_LENGTH];
    AJ_Time lockTimer;

    uint8_t (*viewRecord)(uint16_t recordId);
    uint8_t (*updateRecord)(uint16_t recordId);
    uint8_t (*deleteRecord)(uint16_t recordId);
    uint8_t (*addRecord)();
    uint8_t (*confirmRecord)();
    uint8_t (*cancelRecord)();

    uint16_t (*getNumRecords)();
    uint16_t (*getRecordId)(uint16_t indx);
    char* (*getRecordName)(uint16_t indx);


} ListPropertyWidget;

void initializeListPropertyWidget(ListPropertyWidget* widget);

AJ_Status marshalListPropertyValue(ListPropertyWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalAllListPropertyProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status checkLock(ListPropertyWidget* widget, const char* lockerId);

AJ_Status addRecord(ListPropertyWidget* widget, const char* lockerId);

AJ_Status viewRecord(ListPropertyWidget* widget, const char* lockerId, uint16_t recordId);

AJ_Status updateRecord(ListPropertyWidget* widget, const char* lockerId, uint16_t recordId);

AJ_Status deleteRecord(ListPropertyWidget* widget, const char* lockerId, uint16_t recordId);

AJ_Status confirmRecord(ListPropertyWidget* widget, const char* lockerId);

AJ_Status cancelRecord(ListPropertyWidget* widget, const char* lockerId);

#endif /* LISTPROPERTYWIDGET_H_ */
