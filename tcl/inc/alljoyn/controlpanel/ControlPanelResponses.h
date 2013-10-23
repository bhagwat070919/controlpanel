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

#ifndef CONTROLPANELRESPONSES_H_
#define CONTROLPANELRESPONSES_H_

#include "alljoyn.h"

/**
 * "boolean" that reflects whether the bus is connected or not
 * Can be set to TRUE or FALSE - should default to FALSE
 */
extern uint8_t isBusConnected;

/**
 * busAttachment that will be used for connecting and sending messages
 * Needs to be defined in app
 */
extern AJ_BusAttachment busAttachment;

/**
 * Respond with an error Message
 * @param msg
 * @param error
 * @return
 */
AJ_Status ReturnErrorMessage(AJ_Message* msg, const char* error);

/**
 * Marshal and send the url for the controlPanel
 * @param msg
 * @param msgId
 * @return
 */
AJ_Status SendRootUrl(AJ_Message* msg, uint32_t msgId);

/**
 * Marshal and send a specific property for a Widget
 * @param replyMsg
 * @param propId
 * @param context
 * @return
 */
AJ_Status GetWidgetProperty(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Marshal and send all properties for a Widget
 * @param msg
 * @param msgId
 * @return
 */
AJ_Status GetAllWidgetProperties(AJ_Message* msg, uint32_t msgId);

/**
 * Marshal and send the version property for the Root Interfaces
 * @param replyMsg
 * @param propId
 * @param context
 * @return status
 */
AJ_Status GetRootProperty(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Marshal and send all properties for a Root Interface
 * @param msg
 * @param msgId
 * @return status
 */
AJ_Status GetAllRootProperties(AJ_Message* msg, uint32_t msgId);

/**
 * Execute one of the ListProperty Methods
 * @param msg
 * @param msgId
 * @param signalId
 * @return status
 */
AJ_Status ExecuteListPropertyMethod(AJ_Message* msg, uint32_t msgId, int32_t* signalId);

/**
 * Send Signal if a property of a widget has changed.
 * @param bus
 * @param propSignal
 * @param sessionId
 * @return status
 */
AJ_Status SendPropertyChangedSignal(AJ_BusAttachment* bus, uint32_t propSignal, uint32_t sessionId);

/**
 * Send a signal to dismiss the displayed NotificationAction
 * @param bus
 * @param propSignal
 * @param sessionId
 * @return status
 */
AJ_Status SendDismissSignal(AJ_BusAttachment* bus, uint32_t propSignal, uint32_t sessionId);

/**
 * Function used to identify what kind of request we're dealing with. Defined in Generated code.
 * @param identifier
 * @param widgetType
 * @param propType
 * @param language
 * @return widget
 */
extern void* identifyMsgOrPropId(uint32_t identifier, uint16_t* widgetType, uint16_t* propType, uint16_t* language);

/**
 * Function used to identify what kind of signal we're sending. Defined in Generated code.
 * @param identifier
 * @param isProperty
 * @param language
 * @return widget
 */
extern void* identifyMsgOrPropIdForSignal(uint32_t identifier, uint8_t* isProperty);

/**
 * Function used to identify what kind of request we're dealing with. Defined in Generated code.
 * @param identifier
 * @return true/false
 */
extern uint8_t identifyRootMsgOrPropId(uint32_t identifier);

#endif /* CONTROLPANELRESPONSES_H_ */
