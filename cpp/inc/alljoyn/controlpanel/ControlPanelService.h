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

#ifndef CONTROLPANELSERVICE_H_
#define CONTROLPANELSERVICE_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/controlpanel/GenericLogger.h>
#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <alljoyn/controlpanel/ControlPanelBusListener.h>
#include <alljoyn/controlpanel/CPSLogger.h>

namespace ajn {
namespace services {

/**
 * ControlPanel Service class. Used to initialize and shutdown the service
 */
class ControlPanelService {

  public:

    /**
     * Get Instance of ControlPanelServiceImpl - singleton implementation
     * @return instance
     */
    static ControlPanelService* getInstance();

    /**
     * Destructor for ControlPanelServiceImpl
     */
    ~ControlPanelService();

    /**
     * Initialize the controllee to be used
     * @param bus - bus used for Controllee
     * @param controlPanelControllee - controllee to initialize
     * @return
     */
    QStatus initControllee(BusAttachment* bus, ControlPanelControllee* controlPanelControllee);

    /**
     * Remove locally stored controllee. Allows a new call to initControllee to be made
     * @return status
     */
    QStatus shutdownControllee();

    /**
     * Receive GenericLogger* to use for logging
     * @param logger Implementation of GenericLogger
     * @return previous logger
     */
    GenericLogger* setLogger(GenericLogger* logger);

    /**
     * Get the currently-configured logger implementation
     * @return logger Implementation of GenericLogger
     */
    GenericLogger* getLogger();

    /**
     * Set log level filter for subsequent logging messages
     * @param newLogLevel enum value
     * @return logLevel enum value that was in effect prior to this change
     */
    Log::LogLevel setLogLevel(Log::LogLevel newLogLevel);

    /**
     * Get log level filter value currently in effect
     * @return logLevel enum value currently in effect
     */
    Log::LogLevel getLogLevel();

    /**
     * Method to get the busAttachment used in the service.
     * @return BusAttachment
     */
    ajn::BusAttachment* getBusAttachment();

    /**
     * Get the BusListener
     * @return ControlPanelBusListener
     */
    ControlPanelBusListener* getBusListener() const;

    /**
     * Get the Version of the ControlPanelService
     * @return the ControlPanelService version
     */
    static uint16_t getVersion();

  private:

    /**
     * Default constructor for ControlPanelServiceImpl
     * Private to allow for singleton implementation
     */
    ControlPanelService();

    /**
     * Version of the API
     */
    static uint16_t const CONTROLPANEL_SERVICE_VERSION;

    /**
     * Instance variable - ControlPanelServiceImpl is a singleton
     */
    static ControlPanelService* s_Instance;

    /**
     * BusAttachement used in Service
     */
    BusAttachment* m_Bus;

    /**
     * BusListener used in service
     */
    ControlPanelBusListener* m_BusListener;

    /**
     * ControlPanelControllee of service
     */
    ControlPanelControllee* m_ControlPanelControllee;

    /**
     * Logger that is used in library
     */
    GenericLogger* logger;

    /**
     * Logger that is used in library
     */
    CPSLogger cpsLogger;
};
} //namespace services
} //namespace ajn

#endif /* CONTROLPANELSERVICE_H_ */
