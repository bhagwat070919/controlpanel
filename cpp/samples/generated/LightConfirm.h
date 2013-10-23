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

#ifndef LIGHTCONFIRM_H_
#define LIGHTCONFIRM_H_

#include "alljoyn/controlpanel/Dialog.h"

namespace ajn {
namespace services {

/**
 * Generated class
 */
class LightConfirm : public ajn::services::Dialog {
  public:
    LightConfirm(qcc::String name);
    virtual ~LightConfirm();

    bool executeAction1CallBack();
    bool executeAction2CallBack();
    bool executeAction3CallBack();
};
} //namespace services
} //namespace ajn

#endif /* LIGHTCONFIRM_H_ */
