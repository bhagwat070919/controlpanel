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

#ifndef CONTROL_GENERATED_H_
#define CONTROL_GENERATED_H_

#include "alljoyn.h"
#include "aj_msg.h"

#include "alljoyn/controlpanel/Definitions.h"
#ifdef CONTROLPANEL_SERVICE
#include "Services_Common.h"
#else
#define NUM_PRE_CONTROLPANEL_OBJECTS 0
#endif
/**
 * Defines and objectPaths
 */
#define NUM_PRECEDING_OBJECTS NUM_PRE_CONTROLPANEL_OBJECTS

#define UNIQUE_DEVICE_ID "//UNIQUEID_GO_HERE"

#define GET_WIDGET_VALUE_CASES //GETVALUES_GO_HERE

#define GET_WIDGET_ALL_VALUE_CASES //GETALLVALUES_GO_HERE

#define GET_ROOT_VALUE_CASES //GETVALUES_ROOT_GO_HERE

#define GET_ROOT_ALL_VALUE_CASES //GETALLVALUES_ROOT_GO_HERE

#define SET_VALUE_CASES //SETVALUES_GO_HERE

#define ACTION_CASES //ACTION_GO_HERE

#define LISTPROPERTY_CASES //LISTPROPERTY_GO_HERE

#define GET_URL_CASES //GET_URL_GO_HERE

#define CONTROLPANELAPPOBJECTS //APPOBJECTS_GO_HERE

#define CONTROLPANELANNOUNCEOBJECTS //ANNOUNCEOBJECTS_GO_HERE

#define MAX_NUM_LANGUAGES //MAXNUMLANGUAGES_GO_HERE

#define NUM_CONTROLPANEL_OBJECTS //NUM_CPSOBJ_GO_HERE

//DEFINES_GO_HERE

//OBJECTPATH_DECL_GO_HERE

typedef struct {
    const char* sender;
    uint16_t numSignals;
    int32_t signals[MAX_NUM_LANGUAGES];
} SetValueContext;

/**
 *
 * @return
 */
void WidgetsInit();

/**
 *
 * @param replyMsg
 * @param propId
 * @param context
 * @return
 */
AJ_Status SetValueProperty(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 *
 * @param msg
 * @param propId
 * @return
 */
AJ_Status ExecuteAction(AJ_Message* msg, uint32_t propId);

/* Defines and functions for Tester App */

typedef struct {
	uint32_t msgId;
    uint16_t numParams;
    uint16_t param[3];
} CPSTest;

#define NUMBER_OF_TESTS //NUM_TESTS_GO_HERE

#define ALL_REPLY_CASES //ALL_REPLIES_GO_HERE

void TestsInit(CPSTest* testsToRun);

#endif /* CONTROL_GENERATED_H_ */
