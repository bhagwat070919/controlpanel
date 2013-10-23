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

#include "alljoyn/controlpanel/WidgetBusObject.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/Widget.h"

using namespace ajn;
using namespace services;
using namespace qcc;
using namespace cpsConsts;

WidgetBusObject::WidgetBusObject(String const& servicePath, uint16_t langIndx, String const& tag, Widget* widget) :
    BusObject(servicePath.c_str()), m_Widget(widget), languageIndx(langIndx), m_SignalPropertyChanged(0), TAG(tag) {

}

WidgetBusObject::~WidgetBusObject() {
}

QStatus WidgetBusObject::addDefaultInterfaceVariables(InterfaceDescription* intf)
{
    if (!intf)
        return ER_BAD_ARG_1;

    QStatus status;

    CHECK_AND_RETURN(intf->AddProperty(AJ_PROPERTY_VERSION.c_str(), AJPARAM_UINT16.c_str(), PROP_ACCESS_READ));
    CHECK_AND_RETURN(intf->AddProperty(AJ_PROPERTY_STATES.c_str(), AJPARAM_UINT32.c_str(), PROP_ACCESS_READ));
    CHECK_AND_RETURN(intf->AddProperty(AJ_PROPERTY_OPTPARAMS.c_str(), AJPARAM_ARRAY_DICT_UINT16_VAR.c_str(),
                                       PROP_ACCESS_READ));
    return intf->AddSignal(AJ_SIGNAL_PROPERTIES_CHANGED.c_str(), "", "", 0);
}

QStatus WidgetBusObject::SendPropertyChangedSignal()
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    ControlPanelBusListener* busListener = ControlPanelService::getInstance()->getBusListener();
    QStatus status = ER_BUS_PROPERTY_VALUE_NOT_SET;

    if (!m_SignalPropertyChanged) {
        if (logger)
            logger->warn(TAG, "Can't send propertyChanged signal. Signal to set");
        return status;
    }

    if (!busListener) {
        if (logger)
            logger->warn(TAG, "Can't send valueChanged signal. SessionIds are unknown");
        return status;
    }

    const std::vector<SessionId>& sessionIds = busListener->getSessionIds();
    for (size_t indx = 0; indx < sessionIds.size(); indx++) {
        status = Signal(NULL, sessionIds[indx], *m_SignalPropertyChanged, NULL, 0);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not send PropertyChanged Signal for sessionId: " + sessionIds[indx]);
        }
    }
    return status;
}

QStatus WidgetBusObject::Get(const char* ifcName, const char* propName, MsgArg& val)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Get property was called - in WidgetBusObject class:\n");

    if (0 == strcmp(AJ_PROPERTY_VERSION.c_str(), propName)) {
        return m_Widget->GetVersionForArg(val, languageIndx);
    } else if (0 == strcmp(AJ_PROPERTY_STATES.c_str(), propName)) {
        return m_Widget->getStatesForArg(val, languageIndx);
    } else if (0 == strcmp(AJ_PROPERTY_OPTPARAMS.c_str(), propName)) {
        return m_Widget->getOptParamsForArg(val, languageIndx);
    }

    return ER_BUS_NO_SUCH_PROPERTY;
}

QStatus WidgetBusObject::Set(const char* ifcName, const char* propName, MsgArg& val)
{
    return ER_ALLJOYN_ACCESS_PERMISSION_ERROR;
}

