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

#ifndef WIDGETBUSOBJECT_H_
#define WIDGETBUSOBJECT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * WidgetBusObject class. Base class to create a BusObject for a Widget
 */
class WidgetBusObject : public ajn::BusObject {
  public:

    /**
     * Constructor for WidgetBusObject class
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param tag - the Tag for logging
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    WidgetBusObject(qcc::String const& objectPath, uint16_t langIndx, qcc::String const& tag,
                    QStatus& status, Widget* widget);

    /**
     * Destructor of the WidgetBusObject class
     */
    virtual ~WidgetBusObject() = 0;

    /**
     * Get the Version of the Interface represented by this BusObject
     * @return - interfaceVersion
     */
    virtual uint16_t getInterfaceVersion();

    /**
     * Callback for Alljoyn when GetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg to fill
     * @return status - success/failure
     */
    virtual QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Callback for Alljoyn when SetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg that contains the new Value
     * @return status - success/failure
     */
    virtual QStatus Set(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Send a signal when a property has changed
     * @return status - success/failure
     */
    virtual QStatus SendPropertyChangedSignal();

  protected:

    /**
     * add the Default Interface Variables
     * @param intf
     * @return
     */
    QStatus addDefaultInterfaceVariables(InterfaceDescription* intf);

    /**
     * Pointer to Widget represented by this BusObject
     */
    Widget* m_Widget;

    /**
     * The language Index of this BusObject
     */
    uint16_t languageIndx;

    /**
     * The pointer used to send signal/register Signal Handler
     */
    const ajn::InterfaceDescription::Member* m_SignalPropertyChanged;

    /**
     * The Tag for logging
     */
    qcc::String const& TAG;
};
} //namespace services
} //namespace ajn
#endif /* WIDGETBUSOBJECT_H_ */
