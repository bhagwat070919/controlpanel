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

#include <iostream>
#include <sstream>
#include <cstdio>
#include <signal.h>
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <alljoyn/controlpanel/GenericLogger.h>
#include <PinKeyXListener.h>
#include <CommonSampleUtil.h>
#include <ControlPanelGenerated.h>

#define SERVICE_PORT 900

using namespace ajn;
using namespace services;
using namespace qcc;

AboutPropertyStoreImpl* propertyStoreImpl = 0;
CommonBusListener* controlpanelBusListener = 0;
BusAttachment* bus = 0;
ControlPanelService* controlPanelService = 0;
ControlPanelControllee* controlPanelControllee = 0;
PinKeyXListener* pinKeyXListener = 0;

NotificationService* prodService = 0;
NotificationSender* sender = 0;

void exitApp(int32_t signum)
{
    std::cout << "Program Finished" << std::endl;

    CommonSampleUtil::aboutServiceDestroy(bus, controlpanelBusListener);
    if (controlPanelService)
        controlPanelService->shutdownControllee();
    if (prodService)
        prodService->shutdown();
    ControlPanelGenerated::Shutdown();
    if (sender)
        delete sender;
    if (controlPanelControllee)
        delete controlPanelControllee;
    if (controlpanelBusListener)
        delete controlpanelBusListener;
    if (propertyStoreImpl)
        delete (propertyStoreImpl);
    if (controlPanelService)
        delete controlPanelService;
    if (pinKeyXListener)
        delete pinKeyXListener;
    if (bus)
        delete bus;

    std::cout << "Goodbye!" << std::endl;
    exit(signum);
}

int32_t main()
{
    QStatus status;

    // Allow CTRL+C to end application
    signal(SIGINT, exitApp);
    std::cout << "Beginning ControlPanel Application. (Press CTRL+C to end application)" << std::endl;

    // Initialize Service objects
#ifdef QCC_USING_BD
    PasswordManager::SetCredentials("ALLJOYN_PIN_KEYX", "000000");
#endif

    controlpanelBusListener = new CommonBusListener();;
    controlPanelService = ControlPanelService::getInstance();
    controlPanelService->setLogLevel(Log::LogLevel::LEVEL_INFO);

    // Initialize Service object and Sender Object
    prodService = NotificationService::getInstance();
    prodService->setLogLevel(Log::LogLevel::LEVEL_DEBUG);

    pinKeyXListener = new PinKeyXListener();

    bus = CommonSampleUtil::prepareBusAttachment(pinKeyXListener);
    if (bus == NULL) {
        std::cout << "Could not initialize BusAttachment." << std::endl;
        exitApp(1);
    }

    qcc::String device_id = "123456", device_name = "testdeviceName";
    qcc::String app_id = "2826752ae35c416a82bcef272c55eace", app_name = "testappName";
    propertyStoreImpl = new AboutPropertyStoreImpl();
    status = CommonSampleUtil::fillPropertyStore(propertyStoreImpl, app_id, app_name, device_id, device_name);
    if (status != ER_OK) {
        std::cout << "Could not fill PropertyStore." << std::endl;
        exitApp(1);
    }

    status = CommonSampleUtil::prepareAboutService(bus, propertyStoreImpl,
                                                   controlpanelBusListener, SERVICE_PORT);
    if (status != ER_OK) {
        std::cout << "Could not register bus object." << std::endl;
        exitApp(1);
    }

    status = ControlPanelGenerated::PrepareWidgets(controlPanelControllee); //TODO send ptr to ptr?
    if (status != ER_OK) {
        std::cout << "Could not prepare Widgets." << std::endl;
        exitApp(1);
    }

    status = controlPanelService->initControllee(bus, controlPanelControllee);
    if (status != ER_OK) {
        std::cout << "Could not initialize Controllee." << std::endl;
        exitApp(1);
    }

    sender = prodService->initSend(bus, propertyStoreImpl);
    if (!sender) {
        std::cout << "Could not initialize Sender - exiting application" << std::endl;
        exitApp(1);
    }

    status = CommonSampleUtil::aboutServiceAnnounce();
    if (status != ER_OK) {
        std::cout << "Could not announce." << std::endl;
        exitApp(1);
    }

    std::cout << "Sent announce, waiting for Contollers" << std::endl;
    std::cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << std::endl;

    std::string input;
    qcc::String controlPanelServiceObjectPath;
    qcc::String defaultControlPanelServiceObjectPath = "/ControlPanel/MyDevice/areYouSure";

    getline(std::cin, input);
    while (!std::cin.eof()) {
        controlPanelServiceObjectPath = input.length() ? input.c_str() : defaultControlPanelServiceObjectPath;

        NotificationMessageType messageType = INFO;
        NotificationText textToSend("defaultLang", "Sending CPS ObjectPath");
        std::vector<NotificationText> vecMessages;
        vecMessages.push_back(textToSend);
        Notification notification(messageType, vecMessages);
        notification.setControlPanelServiceObjectPath(controlPanelServiceObjectPath.c_str());

        status = sender->send(notification, 7200);
        if (status != ER_OK) {
            std::cout << "Notification was not sent successfully" << std::endl;
        } else {
            std::cout << "Notification sent successfully" << std::endl;
        }

        std::cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << std::endl;
        getline(std::cin, input);
    }
    std::cout << "Exiting in 10 seconds" << std::endl;
    sleep(10);
    exitApp(0);
}
