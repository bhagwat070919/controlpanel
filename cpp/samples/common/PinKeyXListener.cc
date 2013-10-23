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

#include "PinKeyXListener.h"
#include "alljoyn/controlpanel/GenericLogger.h"
#include "alljoyn/controlpanel/ControlPanelService.h"

#define TAG "PinKeyXListener"

using namespace ajn;
using namespace services;

bool PinKeyXListener::RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount,
                                         const char* userId, uint16_t credMask, Credentials& creds)
{
    if (strcmp(authMechanism, "ALLJOYN_PIN_KEYX") == 0) {
        if (credMask & AuthListener::CRED_PASSWORD) {
            if (authCount <= 3) {
                creds.SetPassword("000000");
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void PinKeyXListener::AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger) {
        if (success)
            logger->debug(TAG, "Authentication completed successfully");
        else
            logger->debug(TAG, "Authentication did not complete successfully");
    }
}
