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

#ifndef CONTROLPANELSERVICESAMPLEUTIL_H_
#define CONTROLPANELSERVICESAMPLEUTIL_H_

#include "alljoyn/BusAttachment.h"
#include "qcc/String.h"
#include "alljoyn/controlpanel/GenericLogger.h"
#include "PropertyStoreImpl.h"
#include "alljoyn/controlpanel/ControlPanelBusListener.h"

/**
 * Util class that creates a busAttachment, starts it and connects it
 */
class ControlPanelServiceSampleUtil {
  public:

    /**
     * static method that prepares the BusAttachment
     * @param logger
     * @return the busattachment created. NULL if failed
     */
    static ajn::BusAttachment* prepareBusAttachment(ajn::services::GenericLogger* logger = 0);

    /**
     * static method preparePropertyStore
     * @param appIdHex
     * @param appName
     * @param deviceId
     * @param deviceName
     * @return the property store created. NULL if failed
     */
    static PropertyStoreImpl* preparePropertyStore(qcc::String appIdHex, qcc::String appName, qcc::String deviceId, qcc::String deviceName);

    /**
     * static method prepareAboutService
     * @param bus
     * @param propertyStoreImpl
     * @param busListener
     * @param port
     * @return Qstatus
     */
    static QStatus prepareAboutService(ajn::BusAttachment*bus, PropertyStoreImpl*propertyStoreImpl,
    		ControlPanelBusListener* busListener, uint16_t port);

    /**
     * static method aboutServiceAnnounce
     * @return Qstatus
     */
    static QStatus aboutServiceAnnounce();

    /**
     * static method aboutServiceDestory
     * @param bus
     * @param busListener
     * @param port
     */
    static void aboutServiceDestroy(ajn::BusAttachment* bus, ControlPanelBusListener* busListener);

    /**
     * adds appropriate addMatch to Consumer application
     * @param bus
     * @return status - success/fail
     */
    static QStatus addSessionlessMatch(ajn::BusAttachment*bus);

  private:

    /**
     * TAG for logging
     */
    static qcc::String TAG;

    /**
     * Default Language
     */
    static qcc::String DEFAULT_LANGUAGE;

    /**
     * Supported Languages
     */
    static const char* SUPPORTED_LANGUAGES[];
};

#endif /* CONTROLPANELSERVICESAMPLEUTIL_H_ */
