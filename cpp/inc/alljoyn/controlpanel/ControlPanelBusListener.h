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

#ifndef CONTROLPANELBUSLISTENER_H_
#define CONTROLPANELBUSLISTENER_H_

#include "alljoyn/BusListener.h"
#include "alljoyn/SessionPortListener.h"
#include "alljoyn/controlpanel/GenericLogger.h"

class ControlPanelBusListener : public ajn::BusListener, public ajn::SessionPortListener {

public:

	/**
	 * Constructor of ControlPanelBusListener
	 * @param sessionPort
	 */
	ControlPanelBusListener();

	/**
	 * Destructor of ControlPanelBusListener
	 */
    ~ControlPanelBusListener();

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    bool AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts);

    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void setSessionPort(ajn::SessionPort sessionPort);

    /**
     * Get the SessionPort of the listener
     * @return
     */
    ajn::SessionPort getSessionPort();

private:

    /**
     * The port used as part of the join session request
     */
    ajn::SessionPort m_SessionPort;
};

#endif /* CONTROLPANELBUSLISTENER_H_ */
