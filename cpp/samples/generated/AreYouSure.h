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

#ifndef AREYOUSURE_H_
#define AREYOUSURE_H_

#include <alljoyn/controlpanel/Dialog.h>

namespace ajn {
namespace services {

/**
 * Generated class
 */
class AreYouSure : public ajn::services::Dialog {
  public:
    AreYouSure(qcc::String name);
    virtual ~AreYouSure();

    bool executeAction1CallBack();
    bool executeAction2CallBack();
    bool executeAction3CallBack();
};
} //namespace services
} //namespace ajn

#endif /* AREYOUSURE_H_ */
