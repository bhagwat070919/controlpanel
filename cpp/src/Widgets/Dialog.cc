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

#include "alljoyn/controlpanel/Dialog.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../BusObjects/DialogBusObject.h"

using namespace ajn;
using namespace services;
using namespace cpsConsts;

Dialog::Dialog(qcc::String name) : RootWidget(name, TAG_DIALOG_WIDGET),
		m_GetMessage(0), m_NumActions(0)
{
}

Dialog::~Dialog()
{
}

GetMessageFptr Dialog::getGetMessage() const
{
	return m_GetMessage;
}

void Dialog::setGetMessage(GetMessageFptr getMessage)
{
    m_GetMessage = getMessage;
}

const std::vector<qcc::String>& Dialog::getMessage() const
{
    return m_Message;
}

void Dialog::setMessage(const std::vector<qcc::String>& message)
{
    m_Message = message;
}

const uint16_t Dialog::getNumActions() const
{
    return m_NumActions;
}

void Dialog::setNumActions(const uint16_t numActions)
{
    m_NumActions = numActions;
}

WidgetBusObject* Dialog::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
		uint16_t langIndx, QStatus status)
{
	return new DialogBusObject(bus, objectPath, langIndx, status, this);
}

void Dialog::executeAction1CallBack()
{

}

void Dialog::executeAction2CallBack()
{

}

void Dialog::executeAction3CallBack()
{

}
