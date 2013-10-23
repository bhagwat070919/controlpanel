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

#ifndef LABELBUSOBJECT_H_
#define LABELBUSOBJECT_H_

#include "WidgetBusObject.h"

namespace ajn {
namespace services {

/**
 * LabelBusObject - BusObject for Labels
 */
class LabelBusObject : public WidgetBusObject {
  public:

    /**
     * Constructor for LabelBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    LabelBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath,
                   uint16_t langIndx, QStatus& status, Widget* widget);

    /**
     * Destructor for the BusObject
     */
    virtual ~LabelBusObject();

    /**
     * Callback for Alljoyn when GetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg to fill
     * @return status - success/failure
     */
    QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);
};

} /* namespace services */
} /* namespace ajn */
#endif /* LABELBUSOBJECT_H_ */
