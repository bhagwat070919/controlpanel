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

#include "PropertyBusObject.h"
#include "../ControlPanelConstants.h"
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/Property.h>

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

PropertyBusObject::PropertyBusObject(BusAttachment* bus, String const& objectPath, uint16_t langIndx,
                                     QStatus& status, Widget* widget) :
    WidgetBusObject(objectPath, langIndx, TAG_PROPERTY_BUSOBJECT,
                    status, widget), m_SignalValueChanged(0)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create the BusObject");
        return;
    }

    String interfaceName = widget->getIsSecured() ? AJ_SECURED_PROPERTY_INTERFACE : AJ_PROPERTY_INTERFACE;
    InterfaceDescription* intf = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
    if (!intf) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(interfaceName.c_str(), intf, widget->getIsSecured()));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(intf));
            CHECK_AND_BREAK(intf->AddProperty(AJ_PROPERTY_VALUE.c_str(), AJPARAM_VAR.c_str(), PROP_ACCESS_RW));
            CHECK_AND_BREAK(intf->AddSignal(AJ_SIGNAL_VALUE_CHANGED.c_str(), AJPARAM_VAR.c_str(), AJ_PROPERTY_VALUE.c_str(), 0));
            intf->Activate();
        } while (0);
    }
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create interface");
        return;
    }

    status = AddInterface(*intf);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not add interface");
        return;
    }

    //Get the signal methods for future use
    m_SignalPropertyChanged = intf->GetMember(AJ_SIGNAL_PROPERTIES_CHANGED.c_str());
    m_SignalValueChanged = intf->GetMember(AJ_SIGNAL_VALUE_CHANGED.c_str());
    if (logger)
        logger->debug(TAG, "Created PropertyBusObject successfully");
}

PropertyBusObject::~PropertyBusObject()
{
}

QStatus PropertyBusObject::Get(const char* interfaceName, const char* propName, MsgArg& val)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Get property was called - in PropertyBusObject class:\n");

    if (0 == strcmp(AJ_PROPERTY_VALUE.c_str(), propName)) {
        return ((Property*)m_Widget)->fillPropertyValueArg(val, languageIndx);
    }

    return WidgetBusObject::Get(interfaceName, propName, val);
}

QStatus PropertyBusObject::Set(const char* interfaceName, const char* propName, MsgArg& val)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Set property was called - in PropertyBusObject class:\n");

    if (0 != strcmp(AJ_PROPERTY_VALUE.c_str(), propName))
        return ER_BUS_PROPERTY_ACCESS_DENIED;

    return ((Property*)m_Widget)->setPropertyValue(val, languageIndx);
}

QStatus PropertyBusObject::SendValueChangedSignal()
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    ControlPanelBusListener* busListener = ControlPanelService::getInstance()->getBusListener();

    if (!m_SignalValueChanged) {
        if (logger)
            logger->warn(TAG, "Can't send valueChanged signal. Signal not set");
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    }

    if (!busListener) {
        if (logger)
            logger->warn(TAG, "Can't send valueChanged signal. SessionIds are unknown");
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    }

    QStatus status;
    MsgArg value;

    CHECK_AND_RETURN(((Property*)m_Widget)->fillPropertyValueArg(value, languageIndx));

    const std::vector<SessionId>& sessionIds = busListener->getSessionIds();
    for (size_t indx = 0; indx < sessionIds.size(); indx++) {
        status = Signal(NULL, sessionIds[indx], *m_SignalValueChanged, &value, 1);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not send ValueChanged Signal for sessionId: " + sessionIds[indx]);
        }
    }
    return status;
}

} /* namespace services */
} /* namespace ajn */

