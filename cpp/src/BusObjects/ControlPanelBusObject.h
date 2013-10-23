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

#ifndef CONTROLPANELBUSOBJECT_H_
#define CONTROLPANELBUSOBJECT_H_

#include "alljoyn/BusAttachment.h"
#include "alljoyn/BusObject.h"
#include "alljoyn/InterfaceDescription.h"

namespace ajn {
namespace services {

class ControlPanelBusObject : public BusObject {
public:
	ControlPanelBusObject(ajn::BusAttachment* bus, qcc::String const& servicePath, QStatus& status);

	virtual ~ControlPanelBusObject();

	QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

	QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

private:

	qcc::String const& TAG;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANELBUSOBJECT_H_ */
