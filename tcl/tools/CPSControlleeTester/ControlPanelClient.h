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

#ifndef CONTROLPANELCLIENT_H_
#define CONTROLPANELCLIENT_H_

#ifdef COMBINED_SERVICES
#include "Services_Common.h"
#endif

#include "ControlPanelClientGenerated.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/Definitions.h"
#include "aj_debug.h"

/**
 * Static non consts.
 */
char announceSender[16];

/**
 * Objects implemented by the application. The first member in the AJ_Object structure is the path.
 * The second is the collection of all interfaces at that path.
 */

#define CONTROLPANEL_APPOBJECTS \
    CONTROLPANELAPPOBJECTS

#ifndef COMBINED_SERVICES
typedef enum {
    SERVICE_STATUS_HANDLED,
    SERVICE_STATUS_NOT_HANDLED
} Service_Status;
#endif

void CPS_Init();

AJ_Status CPS_StartService(AJ_BusAttachment* bus, const char* daemonName, uint32_t timeout, uint8_t connected);

void MakeMethodCall(uint32_t sessionId);

void CPS_IdleConnectedHandler(AJ_BusAttachment*bus);

Service_Status CPS_NotifySessionAccepted(uint32_t sessionId, const char*sender);

Service_Status CPS_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status*msgStatus);

void CPS_Finish();

#endif //end CONTROLPANELCLIENT_H_
