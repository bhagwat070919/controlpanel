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

#ifndef ACTIONBUSOBJECT_H_
#define ACTIONBUSOBJECT_H_

#include "WidgetBusObject.h"

namespace ajn {
namespace services {

/**
 * ActionBusObject - BusObject for Actions
 */
class ActionBusObject : public WidgetBusObject {
  public:

    /**
     * Constructor for ActionBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    ActionBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath,
                    uint16_t langIndx, QStatus& status, Widget* widget);

    /**
     * Destructor for the BusObject
     */
    virtual ~ActionBusObject();

    /**
     * Callback when Execute is called
     * @param member - the member (method) of the interface that was executed
     * @param msg - the Message of the method
     */
    void ActionExecute(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
};

} /* namespace services */
} /* namespace ajn */
#endif /* ACTIONBUSOBJECT_H_ */
