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

#ifndef CONTROLPANEL_H_
#define CONTROLPANEL_H_

#include "ControlPanelInterfaces.h"
#include "ControlPanelResponses.h"
#include "alljoyn.h"

#ifdef CONTROLPANEL_SERVICE
#include "ControlPanelGenerated.h"
#else
#include "ControlPanelClientGenerated.h"
typedef enum {
    SERVICE_STATUS_HANDLED,       //!< SERVICE_STATUS_HANDLED
    SERVICE_STATUS_NOT_HANDLED    //!< SERVICE_STATUS_NOT_HANDLED
} Service_Status;
#endif

/**
 * Message Id's based on Interfaces defined in service
 */

#define CONTROLPANEL_APPOBJECTS  \
    CONTROLPANELAPPOBJECTS

#define CONTROLPANEL_ANNOUNCEOBJECTS \
    CONTROLPANELANNOUNCEOBJECTS

/**
 * Port used for controlpanelservice
 */
extern const uint16_t CPSPort;

/**
 * SessionId used in controlpanelservice
 */
extern uint32_t CPSsessionId;

/**
 * A NULL terminated collection of all interfaces.
 */

void CPS_Init();

Service_Status CPS_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status*msgStatus);

uint8_t CPS_CheckSessionAccepted(uint16_t port, uint32_t sessionId, char*joiner);

void ControlPanel_ConnectedHandler(AJ_BusAttachment*bus);

AJ_Status CPS_StartService(AJ_BusAttachment* bus, const char* daemonName, uint32_t timeout, uint8_t connected);

void CPS_IdleConnectedHandler(AJ_BusAttachment*bus);

void CPS_Finish();

void Controllee_DoWork(AJ_BusAttachment*bus);

#endif /* CONTROLPANEL_H_ */
