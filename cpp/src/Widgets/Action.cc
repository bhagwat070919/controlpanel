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

#include "alljoyn/controlpanel/Action.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../BusObjects/ActionBusObject.h"

using namespace ajn;
using namespace services;
using namespace cpsConsts;

Action::Action(qcc::String name) : Widget(name, TAG_ACTION_WIDGET), m_Dialog(0)
{
}

Action::~Action()
{
}

WidgetBusObject* Action::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
		uint16_t langIndx, QStatus status)
{
	return new ActionBusObject(bus, objectPath, langIndx, status, this);
}

void Action::executeCallBack()
{

}

QStatus Action::addChildDialog(Dialog* childElement)
{
    if (!childElement)
    	return ER_BAD_ARG_1;

    m_Dialog = childElement;
    return ER_OK;
}

QStatus Action::registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
		qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot)
{
	GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

	QStatus status = Widget::registerObjects(bus, languageSet, objectPathPrefix, objectPathSuffix, isRoot);
	if (status != ER_OK)
	    return status;

	qcc::String newObjectPathSuffix = isRoot ? objectPathSuffix : objectPathSuffix + "/" + m_Name;

	if (m_Dialog) {
	    status = m_Dialog->registerObjects(bus, languageSet, objectPathPrefix, newObjectPathSuffix);
        if (status != ER_OK) {
        	if (logger)
        	    logger->warn(TAG, "Could not register childDialog objects");
        	return status;
        }
    }
    return status;
}
