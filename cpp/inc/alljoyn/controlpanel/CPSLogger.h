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

#ifndef CPSLOGGER_H_
#define CPSLOGGER_H_

#include <alljoyn/controlpanel/GenericLogger.h>
#include <alljoyn/Status.h>
#include <qcc/Debug.h>

namespace ajn {
namespace services {

/**
 * Logger implementation of Generic Logger
 * This is the default logger of the service
 */
class CPSLogger : public GenericLogger {
  public:

    /**
     * Constructor for ControlPanel Service Logger
     */
    CPSLogger();

    /**
     * Destructor for ControlPanel Service Logger
     */
    virtual ~CPSLogger();

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
     * Get the class' default log level filter
     * @return logLevel enum value
     */
    static Log::LogLevel getDefaultLogLevel();

    /**
     * Log in Debug Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    void debug(const char* Tag, const char* logText);

    /**
     * Log in Info Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    void info(const char* Tag, const char* logText);

    /**
     * Log in Warn Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    void warn(const char* Tag, const char* logText);

    /**
     * Log in Error Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    void error(const char* Tag, const char* logText);

    /**
     * Log in Fatal Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    void fatal(const char* Tag, const char* logText);

    /**
     * Defines the logging callback functionality implemented for the
     * user-supplied logger object. This callback, called by the AllJoyn
     * layer, will pass AllJoyn log messages to the user-supplied logger.
     * @param type AllJoyn-defined debug mode
     * @param module "section" of the software producing the log message
     * @param msg message to be logged
     * @param context output channel on which to generate the log message
     */
    static void GenericLoggerCallBack(DbgMsgType type, const char* module, const char* msg, void* context);

    /**
     * Registers the callback function to be used for the passed-in
     * logger object. For the built-in ControlPanel Service logger,
     * the AllJoyn built-in callback function is registered. For a
     * user-supplied logger, the ControlPanel Services's logger callback
     * function, GenericLoggerCallBack, is registered.
     * @param logger GenericLogger object currently in use
     */
    static void RegisterCallBack(GenericLogger* logger);

  private:

    /**
     * Stores and keeps track of the initial, default logger object.
     */
    static GenericLogger* m_initialLogger;

    /**
     * Currently-configured log level filter value.
     */
    Log::LogLevel m_logLevel;

    /**
     * Stores the class' default log level filter value.
     */
    static Log::LogLevel m_defaultLogLevel;
};
} //namespace services
} //namespace ajn

#endif /* CPSLOGGER_H_ */
