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

#ifndef DIALOG_H_
#define DIALOG_H_

#include "alljoyn/controlpanel/RootWidget.h"
#include <map>

namespace ajn {
namespace services {

class Dialog : public RootWidget {
public:
	Dialog(qcc::String name);
	virtual ~Dialog();

	WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
			uint16_t langIndx, QStatus status);

	virtual void executeAction1CallBack();
	virtual void executeAction2CallBack();
	virtual void executeAction3CallBack();

	virtual GetMessageFptr getGetMessage() const;
	virtual void setGetMessage(GetMessageFptr getMessage);

	virtual const std::vector<qcc::String>& getMessage() const;
	virtual void setMessage(const std::vector<qcc::String>& message);

	virtual const uint16_t getNumActions() const;
	virtual void setNumActions(const uint16_t numActions);

private:

    std::vector<qcc::String> m_Message;
    GetMessageFptr m_GetMessage;

    uint16_t m_NumActions;
};
} //namespace services
} //namespace ajn

#endif /* DIALOG_H_ */
