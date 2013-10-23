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
#include <iostream>

using namespace ajn;
using namespace services;
using namespace cpsConsts;

Container::Container(qcc::String name) : Widget(name, TAG_CONTAINER_WIDGET)
{
}

Container::~Container()
{
}

QStatus Container::addChildElement(Widget* childElement)
{
    if (!childElement)
    	return ER_BAD_ARG_1;

    std::cout << "Child name is: " << childElement->getWidgetName().c_str() << std::endl;
    m_ChildElements.push_back(childElement);
    return ER_OK;
}

WidgetBusObject* Container::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
		uint16_t langIndx, QStatus status)
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

    //TODO if m_RootContainer->isdismissable add notificaitonActionObjectPath
	qcc::String newObjectPathSuffix = isRoot ? objectPathSuffix : objectPathSuffix + "/" + m_Name;
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
