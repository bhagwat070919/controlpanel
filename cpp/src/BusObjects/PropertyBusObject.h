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

#ifndef PROPERTYBUSOBJECT_H_
#define PROPERTYBUSOBJECT_H_

#include "WidgetBusObject.h"

namespace ajn {
namespace services {

/**
 * PropertyBusObject - BusObject for Property
 */
class PropertyBusObject : public WidgetBusObject {
  public:

    /**
     * Constructor for PropertyBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    PropertyBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath,
                      uint16_t langIndx, QStatus& status, Widget* widget);

    /**
     * Destructor for the BusObject
     */
    virtual ~PropertyBusObject();

    /**
     * Callback for Alljoyn when GetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg to fill
     * @return status - success/failure
     */
    QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Callback for Alljoyn when SetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg that contains the new Value
     * @return status - success/failure
     */
    QStatus Set(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Send a signal when the property's value has changed
     * @return status - success/failure
     */
    QStatus SendValueChangedSignal();

  private:

    /**
     * Store member to send Value Changed signal
     */
    const ajn::InterfaceDescription::Member* m_SignalValueChanged;
};

} /* namespace services */
} /* namespace ajn */
#endif /* PROPERTYBUSOBJECT_H_ */
