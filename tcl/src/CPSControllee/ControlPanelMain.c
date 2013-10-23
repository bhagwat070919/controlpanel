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

void ControlPanel_ConnectedHandler(AJ_BusAttachment* bus)
{
}

void CPS_Init()
{
    WidgetsInit();
}

AJ_Status CPS_StartService(AJ_BusAttachment* bus, const char* daemonName, uint32_t timeout, uint8_t connected)
{
    AJ_SessionOpts sessionOpts = {
        AJ_SESSION_TRAFFIC_MESSAGES,
        AJ_SESSION_PROXIMITY_ANY,
        AJ_TRANSPORT_ANY,
        TRUE
    };

    AJ_Status status;
    AJ_Time timer = {0, 0};
    uint8_t serviceStarted = FALSE;
    uint8_t initial = TRUE;
    AJ_InitTimer(&timer);

    while (TRUE) {
        if (AJ_GetElapsedTime(&timer, TRUE) > timeout) {
            return AJ_ERR_TIMEOUT;
        }
        if (!initial || !connected) {
            initial = FALSE;
            AJ_Printf("Attempting to connect to bus\n");
            status = AJ_Connect(bus, daemonName, CONNECT_TIMEOUT);
            if (status != AJ_OK) {
                AJ_Printf("Failed to connect to bus sleeping for %d seconds\n", CONNECT_PAUSE / 1000);
                AJ_Sleep(CONNECT_PAUSE);
                continue;
            }
            AJ_Printf("AllJoyn service connected to bus\n");
        }
        /*
         * Kick things off by binding a session port
         */
        status = AJ_BusBindSessionPort(bus, CPSPort, &sessionOpts);
        if (status == AJ_OK) {
            break;
        }
        AJ_Printf("Failed to send bind session port message\n");
        AJ_Disconnect(bus);
    }

    while (!serviceStarted && (status == AJ_OK)) {
        AJ_Message msg;

        AJ_GetElapsedTime(&timer, TRUE);

        status = AJ_UnmarshalMsg(bus, &msg, UNMARSHAL_TIMEOUT);

        /*
         * TODO This is a temporary hack to work around buggy select imlpementations
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

        case AJ_REPLY_ID(AJ_METHOD_ADVERTISE_NAME):
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
        AJ_Disconnect(bus);
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
        *msgStatus = ExecuteAction(msg, msg->msgId);
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
