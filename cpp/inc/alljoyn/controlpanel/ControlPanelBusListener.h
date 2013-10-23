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
#include <vector>

namespace ajn {
namespace services {

/**
 * Class that implements BusListener, SessionPortListener and SessionListener
 */
class ControlPanelBusListener : public BusListener, public SessionPortListener,
    public SessionListener {

  public:

    /**
     * Constructor of ControlPanelBusListener
     */
    ControlPanelBusListener();

    /**
     * Destructor of ControlPanelBusListener
     */
    ~ControlPanelBusListener();

    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void setSessionPort(SessionPort sessionPort);

    /**
     * Get the SessionPort of the listener
     * @return
     */
    SessionPort getSessionPort();

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts);

    /**
     * SessionJoined
     * @param sessionPort
     * @param sessionId
     * @param joiner
     */
    void SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner);

    /**
     * SessionMemberAdded
     * @param sessionId
     * @param uniqueName
     */
    void SessionMemberAdded(SessionId sessionId, const char* uniqueName);

    /**
     * SessionMemberRemoved
     * @param sessionId
     * @param uniqueName
     */
    void SessionMemberRemoved(SessionId sessionId, const char* uniqueName);

    /**
     * SessionLost
     * @param sessionId
     * @param reason
     */
    void SessionLost(SessionId sessionId, SessionLostReason reason);

    /**
     * Get the SessionIds associated with this Listener
     * @return vector of sessionIds
     */
    const std::vector<SessionId>& getSessionIds() const;

  private:

    /**
     * The port used as part of the join session request
     */
    SessionPort m_SessionPort;

    /**
     * The sessionIds for the port
     */
    std::vector<SessionId> m_SessionIds;
};
}
}

#endif /* CONTROLPANELBUSLISTENER_H_ */
