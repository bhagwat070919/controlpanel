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

#include "alljoyn/controlpanel/Action.h"
#include "../BusObjects/ActionBusObject.h"
#include "../ControlPanelConstants.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

Action::Action(qcc::String const& name) : Widget(name, TAG_ACTION_WIDGET)
{
}

Action::~Action()
{
}

WidgetBusObject* Action::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                               uint16_t langIndx, QStatus& status)
{
    return new ActionBusObject(bus, objectPath, langIndx, status, this);
}

} /* namespace services */
} /* namespace ajn */
