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

#include <algorithm>
#include "ControlPanelServiceSampleUtil.h"
#include "PinKeyXListener.h"
#include "alljoyn/about/AboutServiceApi.h"
#include "alljoyn/about/AnnouncementRegistrar.h"

using namespace ajn;
using namespace services;

qcc::String ControlPanelServiceSampleUtil::TAG = "ControlPanelServiceSampleUtil";
qcc::String ControlPanelServiceSampleUtil::DEFAULT_LANGUAGE = "en";
const char* ControlPanelServiceSampleUtil::SUPPORTED_LANGUAGES[] = { "en" };


BusAttachment* ControlPanelServiceSampleUtil::prepareBusAttachment(GenericLogger* logger)
{
    BusAttachment* bus = new BusAttachment("ControlPanelServiceApp", true);

    /* Start the BusAttachment */
    QStatus status = bus->Start();
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not start BusAttachment. Status: " + qcc::String(QCC_StatusText(status)));
        return NULL;
    }

    /* Connect to the daemon using address provided*/
    status = bus->Connect();
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not connect BusAttachment. Status: " + qcc::String(QCC_StatusText(status)));
        return NULL;
    }

    ControlPanelServiceSampleUtil::EnableSecurity(bus);
    return bus;
}

PropertyStoreImpl* ControlPanelServiceSampleUtil::preparePropertyStore(qcc::String appIdHex, qcc::String appName, qcc::String deviceId, qcc::String deviceName)
{
    std::multimap<qcc::String, PropertyStoreProperty> data;

    qcc::String appId;
    static const char* const chars = "0123456789ABCDEF";
    uint32_t i;
    appId.reserve(appIdHex.size() / 2);
    for (i = 0; i < appIdHex.size(); i += 2) {
        char c = appIdHex[i];
        const char* p = std::lower_bound(chars, chars + 16, c);

        char b = appIdHex[i + 1];
        const char* q = std::lower_bound(chars, chars + 16, b);
        appId.push_back(((p - chars) << 4) | (q - chars));
    }

    data.insert(std::pair<qcc::String, PropertyStoreProperty> ("DefaultLanguage",
                                                               PropertyStoreProperty("DefaultLanguage", MsgArg("s", DEFAULT_LANGUAGE.c_str()))));
    data.insert(std::pair<qcc::String, PropertyStoreProperty> ("SupportedLanguages",
                                                               PropertyStoreProperty("SupportedLanguages", MsgArg("as", 1, SUPPORTED_LANGUAGES))));
    data.insert(std::pair<qcc::String, PropertyStoreProperty> ("DeviceName",
                                                               PropertyStoreProperty("DeviceName", MsgArg("s", deviceName.c_str()))));
    data.insert(std::pair<qcc::String, PropertyStoreProperty> ("DeviceId",
                                                               PropertyStoreProperty("DeviceId", MsgArg("s", deviceId.c_str()))));
    data.insert(std::pair<qcc::String, PropertyStoreProperty> ("AppId",
                                                               PropertyStoreProperty("AppId", MsgArg("ay", appId.size(), appId.c_str()))));
    data.insert(std::pair<qcc::String, PropertyStoreProperty> ("AppName",
                                                               PropertyStoreProperty("AppName", MsgArg("s", appName.c_str()))));

    PropertyStoreImpl* propertyStoreImpl = new PropertyStoreImpl(data);
    return (propertyStoreImpl);
}

QStatus ControlPanelServiceSampleUtil::prepareAboutService(BusAttachment* bus,
                                                           PropertyStoreImpl* propertyStoreImpl, ControlPanelBusListener* busListener, uint16_t port)
{
    if (!bus)
        return ER_BAD_ARG_1;

    if (!propertyStoreImpl)
        return ER_BAD_ARG_2;

    if (!busListener)
        return ER_BAD_ARG_3;

    AboutServiceApi::Init(*bus, *propertyStoreImpl);
    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService)
        return ER_BUS_NOT_ALLOWED;

    busListener->setSessionPort(port);
    bus->RegisterBusListener(*busListener);

    TransportMask transportMask = TRANSPORT_ANY;
    SessionPort sp = port;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, transportMask);

    QStatus status = bus->BindSessionPort(sp, opts, *busListener);
    if (status != ER_OK)
        return status;

    status = aboutService->Register(port);
    if (status != ER_OK)
        return status;

    return (bus->RegisterBusObject(*aboutService));
}

QStatus ControlPanelServiceSampleUtil::aboutServiceAnnounce()
{
    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService)
        return ER_BUS_NOT_ALLOWED;

    return (aboutService->Announce());
}

void ControlPanelServiceSampleUtil::aboutServiceDestroy(BusAttachment* bus,
                                                        ControlPanelBusListener* busListener)
{
    if (busListener) {
        bus->UnregisterBusListener(*busListener);
        bus->UnbindSessionPort(busListener->getSessionPort());
    }

    AboutServiceApi::DestroyInstance();
    return;
}

QStatus ControlPanelServiceSampleUtil::addSessionlessMatch(BusAttachment*bus)
{
    if (!bus)
        return ER_BAD_ARG_1;

    return bus->AddMatch("sessionless='t',type='error'");
}

QStatus ControlPanelServiceSampleUtil::EnableSecurity(BusAttachment* bus)
{
    QStatus status = bus->EnablePeerSecurity("ALLJOYN_PIN_KEYX", new PinKeyXListener());
    return status;
}
