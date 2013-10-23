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

#include "alljoyn/controlpanel/Definitions.h"
#include "alljoyn.h"
#include "alljoyn/controlpanel/ControlPanel.h"
#include <aj_link_timeout.h>

#define UUID_LENGTH 16

/**
 * Static non consts.
 */

const uint16_t CPSPort = 1000;
uint32_t CPSsessionId = 0;

void CPS_Init()
{
    WidgetsInit();
}

AJ_Status ControlPanel_ConnectedHandler(AJ_BusAttachment* bus)
{
    AJ_SessionOpts sessionOpts = {
        AJ_SESSION_TRAFFIC_MESSAGES,
        AJ_SESSION_PROXIMITY_ANY,
        AJ_TRANSPORT_ANY,
        TRUE
    };

    AJ_Status status;
    AJ_Time timer = { 0, 0 };
    AJ_InitTimer(&timer);

    status = AJ_BusBindSessionPort(bus, CPSPort, &sessionOpts);
    if (status != AJ_OK) {
        AJ_Printf("Failed to send bind session port message\n");
    }

    uint8_t serviceStarted = FALSE;
    while (!serviceStarted && (status == AJ_OK)) {
        AJ_Message msg;

        AJ_GetElapsedTime(&timer, TRUE);

        status = AJ_UnmarshalMsg(bus, &msg, UNMARSHAL_TIMEOUT);

        /*
         * TODO This is a temporary hack to work around buggy select implementations
         */
        if (status == AJ_ERR_TIMEOUT) {
            if (AJ_GetElapsedTime(&timer, TRUE) < UNMARSHAL_TIMEOUT) {
                AJ_Printf("Spurious timeout error - continuing\n");
                status = AJ_OK;
                continue;
            }
        }

        if (status != AJ_OK) {
            break;
        }

        switch (msg.msgId) {
        case AJ_REPLY_ID(AJ_METHOD_BIND_SESSION_PORT):
            if (msg.hdr->msgType == AJ_MSG_ERROR) {
                status = AJ_ERR_FAILURE;
            } else {
                serviceStarted = TRUE;
            }
            break;

        default:
            /*
             * Pass to the built-in bus message handlers
             */
            status = AJ_BusHandleBusMessage(&msg);
            break;
        }
        AJ_CloseMsg(&msg);
    }

    if (status != AJ_OK) {
        AJ_Printf("AllJoyn disconnect bus status=%d\n", status);
        status = AJ_ERR_READ;
    }
    return status;
}

uint8_t CPS_CheckSessionAccepted(uint16_t port, uint32_t sessionId, char*joiner)
{
    if (port != CPSPort)
        return FALSE;
    CPSsessionId = sessionId;
    return TRUE;
}

Service_Status CPS_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status*msgStatus)
{
    Service_Status service_Status = SERVICE_STATUS_HANDLED;

    switch (msg->msgId) {
        GET_WIDGET_VALUE_CASES
        *msgStatus = AJ_BusPropGet(msg, GetWidgetProperty, NULL);
        break;

        GET_WIDGET_ALL_VALUE_CASES
        *msgStatus = GetAllWidgetProperties(msg, msg->msgId);
        break;

        GET_ROOT_VALUE_CASES
        *msgStatus = AJ_BusPropGet(msg, GetRootProperty, NULL);
        break;

        GET_ROOT_ALL_VALUE_CASES
        *msgStatus = GetAllRootProperties(msg, msg->msgId);
        break;

        SET_VALUE_CASES
        {
            SetValueContext context;
            context.sender = msg->sender;
            context.numSignals = 0;
            *msgStatus = AJ_BusPropSet(msg, SetValueProperty, &context);
            if (*msgStatus == AJ_OK && context.numSignals != 0) {
                uint16_t indx;
                for (indx = 0; indx < context.numSignals; indx++) {
                    *msgStatus = SendPropertyChangedSignal(bus, context.signals[indx], CPSsessionId);
                }
            }
        }
        break;

        ACTION_CASES
        {
            ExecuteActionContext context;
            context.numSignals = 0;
            *msgStatus = ExecuteAction(msg, msg->msgId, &context);
            if (*msgStatus == AJ_OK && context.numSignals != 0) {
                uint16_t indx;
                for (indx = 0; indx < context.numSignals; indx++) {
                    if (context.signals[indx].signalType == SIGNAL_TYPE_DATA_CHANGED)
                        *msgStatus = SendPropertyChangedSignal(bus, context.signals[indx].signalId, CPSsessionId);
                    else if (context.signals[indx].signalType == SIGNAL_TYPE_DISMISS)
                        *msgStatus = SendDismissSignal(bus, context.signals[indx].signalId, CPSsessionId);
                }
            }
        }
        break;

        LISTPROPERTY_CASES
        {
            int32_t signalId = 0;

            *msgStatus = ExecuteListPropertyMethod(msg, msg->msgId, &signalId);

            if (*msgStatus == AJ_OK && signalId != 0) {
                *msgStatus = SendPropertyChangedSignal(bus, signalId, CPSsessionId);
            }
            break;
        }
        GET_URL_CASES
        *msgStatus = SendRootUrl(msg, msg->msgId);
        break;

    case AJ_SIGNAL_SESSION_LOST:
        break;

    default:
        service_Status = SERVICE_STATUS_NOT_HANDLED;
        break;
    }

    return service_Status;
}

void Controllee_DoWork(AJ_BusAttachment*bus)
{
    return;
}

void CPS_Finish()
{
    return;
}
