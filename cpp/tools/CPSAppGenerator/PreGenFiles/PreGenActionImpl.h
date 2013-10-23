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

#ifndef CAPITAL_NAME_HERE_H_
#define CAPITAL_NAME_HERE_H_

#include "alljoyn/controlpanel/Action.h"

namespace ajn {
namespace services {

/**
 * Generated class - implements Action Widget
 */
class REGULAR_NAME_HERE : public ajn::services::Action {
  public:
    REGULAR_NAME_HERE(qcc::String name);
    virtual ~REGULAR_NAME_HERE();

    bool executeCallBack();
};
} //namespace services
} //namespace ajn

#endif /* CAPITAL_NAME_HERE_H_ */
