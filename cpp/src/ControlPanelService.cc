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
#include <sstream>

#include <alljoyn/PasswordManager.h>
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/CPSLogger.h"
#include "ControlPanelConstants.h"

using namespace ajn;
using namespace services;
using namespace qcc;
using namespace cpsConsts;

ControlPanelService* ControlPanelService::s_Instance(0);
uint16_t const ControlPanelService::CONTROLPANEL_SERVICE_VERSION = 1;

ControlPanelService* ControlPanelService::getInstance()
{
    if (!s_Instance) {
        PasswordManager::SetCredentials("ALLJOYN_PIN_KEYX", "000000");
        s_Instance = new ControlPanelService();
    }
    return s_Instance;
}

ControlPanelService::ControlPanelService() :
    m_Bus(0), m_BusListener(0), m_ControlPanelControllee(0),
    logger(0), TAG(TAG_CONTROLPANELSERVICE)
{
    CPSLogger* cpsLogger = new CPSLogger();
    setLogger(cpsLogger);
}

ControlPanelService::~ControlPanelService()
{

}

uint16_t ControlPanelService::getVersion()
{
    return CONTROLPANEL_SERVICE_VERSION;
}

QStatus ControlPanelService::initControllee(BusAttachment* bus, ControlPanelControllee* controlPanelControllee)
{
    if (!bus) {
        if (logger)
            logger->warn(TAG, "Bus cannot be NULL");
        return ER_BAD_ARG_1;
    }

    if (!bus->IsStarted()) {
        if (logger)
            logger->warn(TAG, "Bus is not started");
        return ER_BAD_ARG_1;
    }

    if (!bus->IsConnected()) {
        if (logger)
            logger->warn(TAG, "Bus is not connected");
        return ER_BAD_ARG_1;
    }

    if (m_Bus && m_Bus->GetUniqueName().compare(bus->GetUniqueName()) != 0) {
        if (logger)
            logger->warn(TAG, "Bus is already set to different BusAttachment");
        return ER_BAD_ARG_1;
    }

    if (!controlPanelControllee) {
        if (logger)
            logger->warn(TAG, "ControlPanelControllee cannot be null");
        return ER_BAD_ARG_2;
    }

    if (m_ControlPanelControllee) {
        if (logger)
            logger->warn(TAG, "ControlPanelControllee already initialized");
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    if (m_BusListener) {
        if (logger)
            logger->warn(TAG, "BusListener already initialized");
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    m_Bus = bus;
    m_ControlPanelControllee = controlPanelControllee;

    QStatus status = controlPanelControllee->registerObjects(bus);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register the BusObjects");
        return status;
    }

    m_BusListener = new ControlPanelBusListener();
    m_BusListener->setSessionPort(CONTROLPANELSERVICE_PORT);
    m_Bus->RegisterBusListener(*m_BusListener);

    TransportMask transportMask = TRANSPORT_ANY;
    SessionPort sp = CONTROLPANELSERVICE_PORT;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, transportMask);

    return m_Bus->BindSessionPort(sp, opts, *m_BusListener);
}

void ControlPanelService::shutdown()
{
    if (logger) logger->debug(TAG, "Shutdown");

    if (!m_Bus) {
        if (logger)
            logger->warn(TAG, "Something went wrong. Could not shut down property");
        return;
    }

    if (m_BusListener) {
        m_Bus->UnregisterBusListener(*m_BusListener);
        delete m_BusListener;
        m_BusListener = 0;
    }

    //if (m_ControlPanelControllee)
    //TODO: unregister all objects

    s_Instance = 0;
    delete this;
}

BusAttachment* ControlPanelService::getBusAttachment()
{
    if (logger) logger->debug(TAG, "In Get BusAttachment");
    return m_Bus;
}

ControlPanelBusListener* ControlPanelService::getBusListener() const
{
    return m_BusListener;
}

GenericLogger* ControlPanelService::setLogger(GenericLogger* newLogger)
{
    GenericLogger* prevLogger = getLogger();
    Log::LogLevel prevLogLevel = getLogLevel();
    logger = newLogger;
    if (logger) {
        setLogLevel(prevLogLevel);
        // reroute internal AJ logging to logger
        CPSLogger::RegisterCallBack(logger);
    }
    return prevLogger;
}

GenericLogger* ControlPanelService::getLogger()
{
    return logger;
}

Log::LogLevel ControlPanelService::setLogLevel(Log::LogLevel newLogLevel)
{
    return logger ? logger->setLogLevel(newLogLevel) : Log::LogLevel::LEVEL_INFO; //NSLogger::getDefaultLogLevel();
}

Log::LogLevel ControlPanelService::getLogLevel()
{
    return logger ? logger->getLogLevel() : Log::LogLevel::LEVEL_INFO; //NSLogger::getDefaultLogLevel();
}

