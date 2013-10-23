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

#include "AreYouSure.h"
#include "ControlPanelProvided.h"

namespace ajn {
namespace services {

AreYouSure::AreYouSure(qcc::String name) : Dialog(name)
{

}

AreYouSure::~AreYouSure()
{

}

bool AreYouSure::executeAction1CallBack()
{
    AJ_Printf("Execute Action1 was called\n");

    //by default return success
    return true;
}

bool AreYouSure::executeAction2CallBack()
{
    return executeActionNotDefined();

    //by default return success
    return true;
}

bool AreYouSure::executeAction3CallBack()
{
    return executeActionNotDefined();

    //by default return success
    return true;
}

} /* namespace services */
} /* namespace ajn */
