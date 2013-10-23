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

#include "alljoyn/BusAttachment.h"
#include "alljoyn/controlpanel/GenericLogger.h"
#include "alljoyn/controlpanel/ControlPanelControllee.h"
#include "alljoyn/controlpanel/ControlPanelBusListener.h"

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
     */
    QStatus initControllee(BusAttachment* bus, ControlPanelControllee* controlPanelControllee);

    /**
     * Cleanup and get ready for shutdown
     */
    void shutdown();

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
     * Virtual method to get the busAttachment used in the service.
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
     * instance variable - ControlPanelServiceImpl is a singleton
     */
    static ControlPanelService* s_Instance;

    /**
     *
     */
    BusAttachment* m_Bus;

    /**
     *
     */
    ControlPanelBusListener* m_BusListener;

    /**
     *
     */
    ControlPanelControllee* m_ControlPanelControllee;

    /**
     * Logger that is used in library
     */
    GenericLogger* logger;

    /**
     * Tag for logging
     */
    qcc::String TAG;
};
} //namespace services
} //namespace ajn

#endif /* CONTROLPANELSERVICE_H_ */
