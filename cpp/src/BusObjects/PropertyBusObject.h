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

#include "alljoyn/controlpanel/WidgetBusObject.h"

namespace ajn {
namespace services {

class PropertyBusObject : public WidgetBusObject {
  public:
    PropertyBusObject(ajn::BusAttachment* bus, qcc::String const& servicePath,
                      uint16_t langIndx, QStatus& status, Widget* widget);
    virtual ~PropertyBusObject();

    QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

    QStatus SendValueChangedSignal();

  private:

    const ajn::InterfaceDescription::Member* m_SignalValueChanged;
};

} /* namespace services */
} /* namespace ajn */
#endif /* PROPERTYBUSOBJECT_H_ */
