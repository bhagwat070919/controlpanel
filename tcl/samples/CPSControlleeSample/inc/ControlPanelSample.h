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

#include <Apps_Common.h>
#include "ControlPanelGenerated.h"

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

AJ_Status ControlPanel_ConnectedHandler(AJ_BusAttachment*bus);

void CPS_IdleConnectedHandler(AJ_BusAttachment*bus);

void CPS_Finish();

void Controllee_DoWork(AJ_BusAttachment*bus);

#endif /* CONTROLPANEL_H_ */
