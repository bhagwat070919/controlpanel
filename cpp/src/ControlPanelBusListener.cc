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

#include "alljoyn/controlpanel/ControlPanelBusListener.h"
#include <iostream>

using namespace ajn;
using namespace services;

ControlPanelBusListener::ControlPanelBusListener () :
		BusListener(), SessionPortListener(), m_SessionPort(0)
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

