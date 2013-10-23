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

#include "REGULAR_NAME_HERE.h"
ADDITIONAL_INCLUDES_HERE

namespace ajn {
namespace services {

REGULAR_NAME_HERE::REGULAR_NAME_HERE(qcc::String name) : Dialog(name)
{

}

REGULAR_NAME_HERE::~REGULAR_NAME_HERE()
{

}

bool REGULAR_NAME_HERE::executeAction1CallBack()
{
    CODE_OF_EXECUTE_ACTION1_HERE

    //by default return success
    return true;
}

bool REGULAR_NAME_HERE::executeAction2CallBack()
{
    CODE_OF_EXECUTE_ACTION2_HERE

    //by default return success
    return true;
}

bool REGULAR_NAME_HERE::executeAction3CallBack()
{
    CODE_OF_EXECUTE_ACTION3_HERE

    //by default return success
    return true;
}

} /* namespace services */
} /* namespace ajn */
