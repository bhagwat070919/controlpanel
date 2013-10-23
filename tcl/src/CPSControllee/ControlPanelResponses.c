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

#include "alljoyn/controlpanel/ControlPanel.h"
#include "alljoyn/controlpanel/ControlPanelResponses.h"
#include "alljoyn/controlpanel/Widgets/PropertyWidget.h"
#include "alljoyn/controlpanel/Widgets/LabelWidget.h"
#include "alljoyn/controlpanel/Widgets/DialogWidget.h"
#include "alljoyn/controlpanel/Common/HttpControl.h"
#include "alljoyn/controlpanel/Common/ControlMarshalUtil.h"

AJ_Status ReturnErrorMessage(AJ_Message* msg, const char* error)
{
    AJ_Message reply;
    AJ_MarshalErrorMsg(msg, &reply, error);
    return AJ_DeliverMsg(&reply);
}

AJ_Status SendRootUrl(AJ_Message* msg, uint32_t msgId)
{
    AJ_Message reply;
    AJ_MarshalReplyMsg(msg, &reply);

    uint16_t widgetType = 0;
    uint16_t propType = 0;
    uint16_t language = 0;

    HttpControl* control = identifyMsgOrPropId(msgId, &widgetType, &propType, &language);
    if (control == 0)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    if (marshalHttpControlUrl(control, &reply, language))
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    return AJ_DeliverMsg(&reply);
}

AJ_Status GetWidgetProperty(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    AJ_Status status = AJ_ERR_UNEXPECTED;

    uint16_t widgetType = 0;
    uint16_t propType = 0;
    uint16_t language = 0;

    BaseWidget* widget = identifyMsgOrPropId(propId, &widgetType, &propType, &language);
    if (widget == 0)
        return status;

    switch (propType) {
        case PROPERTY_TYPE_VERSION:
            if (widget->marshalVersion)
                return widget->marshalVersion(widget, replyMsg, language);
        	break;
        case PROPERTY_TYPE_STATES:
            if (widget->marshalStates)
            	return widget->marshalStates(widget, replyMsg, language);
        	break;
        case PROPERTY_TYPE_OPTPARAMS:
        	if (widget->marshalOptParam)
        	    return widget->marshalOptParam(widget, replyMsg, language);
        	break;
        case PROPERTY_TYPE_VALUE:
        	if (widgetType == WIDGET_TYPE_PROPERTY)
                return marshalPropertyValue(((PropertyWidget*)widget), replyMsg, language);
            else if (widgetType == WIDGET_TYPE_LISTPROPERTY)
                return marshalListPropertyValue(((ListPropertyWidget*)widget), replyMsg, language);
        	break;
        case PROPERTY_TYPE_LABEL:
       	    return marshalLabelLabel(((LabelWidget*)widget), replyMsg, language);
        case PROPERTY_TYPE_MESSAGE:
            return marshalDialogMessage(((DialogWidget*)widget), replyMsg, language);
        case PROPERTY_TYPE_NUM_ACTIONS:
            return marshalDialogNumActions(((DialogWidget*)widget), replyMsg, language);
    }
    return status;
}

AJ_Status GetRootProperty(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    AJ_Status status = AJ_ERR_UNEXPECTED;

    uint8_t found = identifyRootMsgOrPropId(propId);
    if (!found)
        return status;

   return MarshalVersionRootProperties(replyMsg);
}

AJ_Status GetAllRootProperties(AJ_Message* msg, uint32_t msgId)
{
    AJ_Message reply;
    AJ_Status status = AJ_ERR_UNEXPECTED;

    AJ_MarshalReplyMsg(msg, &reply);

    uint8_t found = identifyRootMsgOrPropId(msgId);
    if (!found)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    status = MarshalAllRootProperties(&reply);
    if (status)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    return AJ_DeliverMsg(&reply);
}

AJ_Status GetAllWidgetProperties(AJ_Message* msg, uint32_t msgId)
{
    AJ_Message reply;
    AJ_Status status = AJ_ERR_UNEXPECTED;

    AJ_MarshalReplyMsg(msg, &reply);

    uint16_t widgetType = 0;
    uint16_t propType = 0;
    uint16_t language = 0;

    BaseWidget* widget = identifyMsgOrPropId(msgId, &widgetType, &propType, &language);
    if (widget == 0)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    status = widget->marshalAllProp(widget, &reply, language);
    if (status)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    return AJ_DeliverMsg(&reply);
}

AJ_Status ExecuteListPropertyMethod(AJ_Message* msg, uint32_t msgId, int32_t* signalId)
{
    AJ_Message reply;
    AJ_Status status = AJ_ERR_UNEXPECTED;

    AJ_MarshalReplyMsg(msg, &reply);

    uint16_t widgetType = 0;
    uint16_t methodType = 0;
    uint16_t language = 0;
    uint16_t recordId = 0;

    ListPropertyWidget* widget = identifyMsgOrPropId(msgId, &widgetType, &methodType, &language);
    if (widget == 0)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    switch (methodType) {
    case METHOD_TYPE_ADD:
        status = addRecord(widget, msg->sender);
        break;

    case METHOD_TYPE_DELETE:
        CPS_CHECK_OR_BREAK(AJ_UnmarshalArgs(msg, "q", &recordId));
        status = deleteRecord(widget, msg->sender, recordId);
        break;

    case METHOD_TYPE_VIEW:
        CPS_CHECK_OR_BREAK(AJ_UnmarshalArgs(msg, "q", &recordId));
        status = viewRecord(widget, msg->sender, recordId);
        break;

    case METHOD_TYPE_UPDATE:
        CPS_CHECK_OR_BREAK(AJ_UnmarshalArgs(msg, "q", &recordId));
        status = updateRecord(widget, msg->sender, recordId);
        break;

    case METHOD_TYPE_CONFIRM:
        status = confirmRecord(widget, msg->sender);
        *signalId = msgId - 5;
        break;

    case METHOD_TYPE_CANCEL:
        status = cancelRecord(widget, msg->sender);
        break;
    }
    if (status)
        return ReturnErrorMessage(msg, AJ_ErrServiceUnknown);

    return AJ_DeliverMsg(&reply);
}

AJ_Status SendPropertyChangedSignal(AJ_BusAttachment* bus, uint32_t propSignal, uint32_t sessionId)
{
    AJ_Status status;
    AJ_Message msg;

    AJ_Printf("Sending Property Changed Signal.\n");

    uint8_t isProperty = FALSE;

    void* widget = identifyMsgOrPropIdForSignal(propSignal, &isProperty);
    if (widget == 0)
        return AJ_ERR_UNEXPECTED;

    if ((status = AJ_MarshalSignal(bus, &msg, propSignal, NULL, sessionId, 0, 0)))
        return status;

    if (isProperty) {
        if ((status = marshalPropertyValue(widget, &msg, 0)))
            return status;
    }

    return AJ_DeliverMsg(&msg);
}

AJ_Status SendDismissSignal(AJ_BusAttachment* bus, uint32_t propSignal, uint32_t sessionId)
{
    AJ_Status status;
    AJ_Message msg;

    AJ_Printf("Sending Dismiss Signal.\n");

    uint8_t found = identifyRootMsgOrPropId(propSignal);
    if (!found)
        return AJ_ERR_UNEXPECTED;

    if ((status = AJ_MarshalSignal(bus, &msg, propSignal, NULL, sessionId, 0, 0)))
        return status;

    return AJ_DeliverMsg(&msg);
}
