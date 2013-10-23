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

#include "alljoyn/BusAttachment.h"
#include "alljoyn/BusObject.h"
#include "alljoyn/InterfaceDescription.h"

namespace ajn {
namespace services {

class Widget;

class WidgetBusObject : public ajn::BusObject {
  public:
    WidgetBusObject(qcc::String const& servicePath, uint16_t langIndx, qcc::String const& tag, Widget* widget);
    virtual ~WidgetBusObject();

    virtual QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    virtual QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

    virtual QStatus SendPropertyChangedSignal();

  protected:

    /**
     * addDefaultInterfaceVariables
     * @param intf
     * @return
     */
    QStatus addDefaultInterfaceVariables(InterfaceDescription* intf);

    /**
     * Pointer to Widget represented by this busobject
     */
    Widget* m_Widget;

    uint16_t languageIndx;

    /**
     * The pointer used to send signal/register Signal Handler
     */
    const ajn::InterfaceDescription::Member* m_SignalPropertyChanged;

    /**
     *
     */
    qcc::String TAG;
};
} //namespace services
} //namespace ajn
#endif /* WIDGETBUSOBJECT_H_ */
