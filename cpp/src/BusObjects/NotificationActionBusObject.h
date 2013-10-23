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

#ifndef NOTIFICATIONACTIONBUSOBJECT_H_
#define NOTIFICATIONACTIONBUSOBJECT_H_

#include "alljoyn/BusAttachment.h"
#include "alljoyn/BusObject.h"
#include "alljoyn/InterfaceDescription.h"

namespace ajn {
namespace services {

class NotificationActionBusObject : public BusObject {
public:
	NotificationActionBusObject(ajn::BusAttachment* bus, qcc::String const& servicePath, QStatus& status);

	virtual ~NotificationActionBusObject();

	QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

	QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

	QStatus SendDismissSignal();

private:

    /**
     * The pointer used to send signal/register Signal Handler
     */
    const ajn::InterfaceDescription::Member* m_SignalDismiss;

	qcc::String const& TAG;

};

} /* namespace services */
} /* namespace ajn */
#endif /* NOTIFICATIONACTIONBUSOBJECT_H_ */
