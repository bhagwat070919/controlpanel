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

/**
 * HttpControlBusObject - BusObject for HttpControls
 */
class HttpControlBusObject : public BusObject {
  public:

    /**
     * Constructor for HttpControlBusObject
     * @param bus - bus used to create the interface
     * @param objectPath - objectPath of BusObject
     * @param status - success/failure
     * @param httpControl - httpControl Widget
     */
    HttpControlBusObject(BusAttachment* bus, qcc::String const& objectPath,
                         QStatus& status, HttpControl* httpControl);

    /**
     * Destructor for HttpControlBusObject
     */
    virtual ~HttpControlBusObject();

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
     * Callback when GetUrl  is called
     * @param member - the member (method) of the interface that was executed
     * @param msg - the Message of the method
     */
    void HttpControlGetUrl(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

  private:

    /**
     * HttpControl widget of this BusObject
     */
    HttpControl* m_HttpControl;

};

} /* namespace services */
} /* namespace ajn */
#endif /* HTTPCONTROLBUSOBJECT_H_ */

