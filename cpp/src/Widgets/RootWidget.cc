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

#include "alljoyn/controlpanel/RootWidget.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../BusObjects/NotificationActionBusObject.h"

namespace ajn {
namespace services {

RootWidget::RootWidget(qcc::String const& name, qcc::String const& tag) : Widget(name, tag),
    m_NotificationActionBusObject(0)
{
}

RootWidget::~RootWidget()
{
}

QStatus RootWidget::SendDismissSignal()
{
    if (!m_NotificationActionBusObject)
        return ER_BUS_OBJECT_NOT_REGISTERED;

    return ((NotificationActionBusObject*)m_NotificationActionBusObject)->SendDismissSignal();
}

QStatus RootWidget::setNotificationActionBusObject(BusObject* notificationActionBusObject)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (!notificationActionBusObject) {
        if (logger)
            logger->warn(TAG, "Could not add a NULL notificationActionBusObject");
        return ER_BAD_ARG_1;
    }

    if (m_NotificationActionBusObject) {
        if (logger)
            logger->warn(TAG, "Could not set notificationActionBusObject. NotificationActionBusObject already set");
        return ER_BUS_PROPERTY_ALREADY_EXISTS;
    }

    m_NotificationActionBusObject = notificationActionBusObject;
    return ER_OK;
}

QStatus RootWidget::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus status = Widget::unregisterObjects(bus);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not unregister BusObjects");
    }

    if (m_NotificationActionBusObject) {
        bus->UnregisterBusObject(*m_NotificationActionBusObject);
        delete m_NotificationActionBusObject;
        m_NotificationActionBusObject = 0;
    }
    return status;
}

} /* namespace services */
} /* namespace ajn */
