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

#include <alljoyn/controlpanel/ControlPanelBusListener.h>
#include <iostream>
#include <algorithm>

namespace ajn {
namespace services {

ControlPanelBusListener::ControlPanelBusListener() :
    BusListener(), SessionPortListener(), SessionListener(), m_SessionPort(0)
{
}

ControlPanelBusListener::~ControlPanelBusListener()
{
}

void ControlPanelBusListener::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort ControlPanelBusListener::getSessionPort()
{
    return m_SessionPort;
}

bool ControlPanelBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    if (sessionPort != m_SessionPort) {
        return false;
    }

    std::cout << "Accepting JoinSessionRequest" << std::endl;
    return true;
}

void ControlPanelBusListener::SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
{
    if (std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId) != m_SessionIds.end())
        return;
    m_SessionIds.push_back(sessionId);
}

void ControlPanelBusListener::SessionMemberAdded(SessionId sessionId, const char* uniqueName)
{
    if (std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId) != m_SessionIds.end())
        return;
    m_SessionIds.push_back(sessionId);
}

void ControlPanelBusListener::SessionMemberRemoved(SessionId sessionId, const char* uniqueName)
{
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end())
        m_SessionIds.erase(it);
}

void ControlPanelBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end())
        m_SessionIds.erase(it);
}

const std::vector<SessionId>& ControlPanelBusListener::getSessionIds() const
{
    return m_SessionIds;
}

} /* namespace services */
} /* namespace ajn */
