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

#ifndef HTTPCONTROL_H_
#define HTTPCONTROL_H_

#include <alljoyn/BusObject.h>

namespace ajn {
namespace services {

/**
 * HttpControl class. Allows definition of a url
 */
class HttpControl {
  public:

    /**
     * Constructor for HttpControl
     * @param url - url of HttpControl
     */
    HttpControl(qcc::String const& url);

    /**
     * Destructor of HttpControl
     */
    virtual ~HttpControl();

    /**
     * Get the Interface Version of the HttpControl
     * @return interface Version
     */
    const uint16_t getInterfaceVersion() const;

    /**
     * Register the HttpControl BusObject
     * @param bus - bus used for registering the object
     * @param unitName - name of unit
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus, qcc::String const& unitName);

    /**
     * Unregister the HttpControl BusObject
     * @param bus - bus used to unregister the object
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

    /**
     * Fill MsgArg passed in with Url
     * @param val - msgArg to fill
     * @return status - success/failure
     */
    QStatus fillUrlArg(MsgArg& val);

  private:

    /**
     * Url of HttpControl
     */
    qcc::String m_Url;

    /**
     * BusObject of HttpControl
     */
    BusObject* m_HttpControlBusObject;
};
} //namespace services
} //namespace ajn

#endif /* HTTPCONTROL_H_ */
