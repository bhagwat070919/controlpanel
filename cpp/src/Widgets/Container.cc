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

#include "alljoyn/controlpanel/Container.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../BusObjects/ContainerBusObject.h"
#include "../BusObjects/NotificationActionBusObject.h"
#include <iostream>

using namespace ajn;
using namespace services;
using namespace cpsConsts;

Container::Container(qcc::String name) : RootWidget(name, TAG_CONTAINER_WIDGET),
    m_IsDismissable(false)
{
}

Container::~Container()
{
}

bool Container::getIsDismissable() const
{
    return m_IsDismissable;
}

void Container::setIsDismissable(bool isDismissable)
{
    m_IsDismissable = isDismissable;
}

QStatus Container::addChildElement(Widget* childElement)
{
    if (!childElement)
        return ER_BAD_ARG_1;

    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Adding childElement named: " + childElement->getWidgetName());
    m_ChildElements.push_back(childElement);
    return ER_OK;
}

WidgetBusObject* Container::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                                  uint16_t langIndx, QStatus& status)
{
    return new ContainerBusObject(bus, objectPath, langIndx, status, this);
}

QStatus Container::registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
                                   qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    QStatus status = Widget::registerObjects(bus, languageSet, objectPathPrefix, objectPathSuffix, isRoot);
    if (status != ER_OK)
        return status;

    qcc::String newObjectPathSuffix = isRoot ? objectPathSuffix : objectPathSuffix + "/" + m_Name;

    if (m_IsDismissable) {
        NotificationActionBusObject* NAbusObject = new NotificationActionBusObject(bus, newObjectPathSuffix, status);

        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not create NotificationActionBusObjects");
            return status;
        }

        status = setNotificationActionBusObject(NAbusObject);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not set NotificationActionBusObjects");
            return status;
        }
    }

    for (size_t indx = 0; indx < m_ChildElements.size(); indx++) {
        status = m_ChildElements[indx]->registerObjects(bus, languageSet, objectPathPrefix, newObjectPathSuffix);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not register childElements objects");
            return status;
        }
    }
    return status;
}

QStatus Container::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus returnStatus = ER_OK;
    QStatus status = Widget::unregisterObjects(bus);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not unregister BusObjects");
        returnStatus = status;
    }

    if (m_NotificationActionBusObject) {
        bus->UnregisterBusObject(*m_NotificationActionBusObject);
        delete m_NotificationActionBusObject;
        m_NotificationActionBusObject = 0;
    }

    for (size_t indx = 0; indx < m_ChildElements.size(); indx++) {
        status = m_ChildElements[indx]->unregisterObjects(bus);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not unregister Objects for the childElement");
            returnStatus = status;
        }
    }
    return ER_OK;
}
