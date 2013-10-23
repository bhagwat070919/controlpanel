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

#ifndef ACTION_H_
#define ACTION_H_

#include "alljoyn/controlpanel/Widget.h"
#include <map>

namespace ajn {
namespace services {

class Action : public Widget {
public:
	Action(qcc::String name);
	virtual ~Action();

	WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
			uint16_t langIndx, QStatus status);

	virtual void executeCallBack(); //TODO make abstract and remove from c

private:
};
} //namespace services
} //namespace ajn

#endif /* ACTION_H_ */
