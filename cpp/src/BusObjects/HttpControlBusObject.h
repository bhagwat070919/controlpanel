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

#ifndef HTTPCONTROLBUSOBJECT_H_
#define HTTPCONTROLBUSOBJECT_H_

#include "alljoyn/BusAttachment.h"
#include "alljoyn/BusObject.h"
#include "alljoyn/InterfaceDescription.h"
#include "alljoyn/controlpanel/HttpControl.h"

namespace ajn {
namespace services {

class HttpControlBusObject : public BusObject {
  public:

    HttpControlBusObject(BusAttachment* bus, qcc::String const& servicePath,
                         QStatus& status, HttpControl* httpControl);

    virtual ~HttpControlBusObject();

    void HttpControlGetUrl(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

  private:

    HttpControl* m_HttpControl;

    qcc::String const& TAG;
};

} /* namespace services */
} /* namespace ajn */
#endif /* HTTPCONTROLBUSOBJECT_H_ */

