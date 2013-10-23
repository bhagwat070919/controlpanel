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
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../ControlPanelConstants.h"
#include "../BusObjects/ContainerBusObject.h"
#include "../BusObjects/NotificationActionBusObject.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

Container::Container(qcc::String const& name) : RootWidget(name, TAG_CONTAINER_WIDGET),
    m_IsDismissable(false)
{
}

Container::~Container()
{
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
        NotificationActionBusObject* NaBusObject = new NotificationActionBusObject(bus, newObjectPathSuffix, status);

        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not create NotificationActionBusObjects");
            delete NaBusObject;
            return status;
        }

        status = setNotificationActionBusObject(NaBusObject);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not set NotificationActionBusObjects");
            delete NaBusObject;
            return status;
        }
    }

    for (size_t indx = 0; indx < m_ChildWidgets.size(); indx++) {
        status = m_ChildWidgets[indx]->registerObjects(bus, languageSet, objectPathPrefix, newObjectPathSuffix);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not register childWidgets objects");
            return status;
        }
    }
    return status;
}

QStatus Container::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus returnStatus = ER_OK;
    QStatus status = RootWidget::unregisterObjects(bus);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not unregister BusObjects");
        returnStatus = status;
    }

    for (size_t indx = 0; indx < m_ChildWidgets.size(); indx++) {
        status = m_ChildWidgets[indx]->unregisterObjects(bus);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not unregister Objects for the childWidget");
            returnStatus = status;
        }
    }
    return ER_OK;
}

QStatus Container::addChildWidget(Widget* childWidget)
{
    if (!childWidget)
        return ER_BAD_ARG_1;

    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Adding childWidget named: " + childWidget->getWidgetName());
    m_ChildWidgets.push_back(childWidget);
    return ER_OK;
}

const std::vector<Widget*>& Container::getChildWidgets() const
{
    return m_ChildWidgets;
}

bool Container::getIsDismissable() const
{
    return m_IsDismissable;
}

void Container::setIsDismissable(bool isDismissable)
{
    m_IsDismissable = isDismissable;
}

} /* namespace services */
} /* namespace ajn */
