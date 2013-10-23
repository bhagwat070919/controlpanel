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

#ifndef GENERICLOGGER_H_
#define GENERICLOGGER_H_

#include "qcc/String.h"

namespace ajn {
namespace services {
namespace Log {

/**
 * LogLevel enum for log level filtering
 */
enum LogLevel {
    LEVEL_FATAL = 1,            //!< LEVEL_FATAL
    LEVEL_ERROR = 2,            //!< LEVEL_ERROR
    LEVEL_WARN  = 3,            //!< LEVEL_WARN
    LEVEL_INFO  = 4,            //!< LEVEL_INFO
    LEVEL_DEBUG = 5,            //!< LEVEL_DEBUG
};
} //namespace Log

/**
 * Abstract class GenericLogger can be overridden to allow custom logging
 * Logging functions are debug, info, warn, error and fatal
 * They receive a Tag String to represent the current context and a logText String
 */
class GenericLogger {
  public:
    /**
     * Constructor for GenericLogger
     */
    GenericLogger() { };

    /**
     * Destructor for GenericLogger
     */
    virtual ~GenericLogger() { };

    /**
     * Log in Debug Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void debug(const char* Tag, const char* logText) = 0;

    /**
     * Log in Info Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void info(const char* Tag, const char* logText)  = 0;

    /**
     * Log in Warn Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void warn(const char* Tag, const char* logText)  = 0;

    /**
     * Log in Error Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void error(const char* Tag, const char* logText) = 0;

    /**
     * Log in Fatal Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void fatal(const char* Tag, const char* logText) = 0;

    /**
     * Log in Debug Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void debug(qcc::String const& Tag, qcc::String const& logText);

    /**
     * Log in Info Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void info(qcc::String const& Tag, qcc::String const& logText);

    /**
     * Log in Warn Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void warn(qcc::String const& Tag, qcc::String const& logText);

    /**
     * Log in Error Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void error(qcc::String const& Tag, qcc::String const& logText);

    /**
     * Log in Fatal Level
     * @param Tag identifies area of code
     * @param logText Text to be logged
     */
    virtual void fatal(qcc::String const& Tag, qcc::String const& logText);

    /**
     * Virtual method to set log level filter for subsequent logging messages
     * @param logLevel enum value
     * @return logLevel enum value that was in effect prior to this change
     */
    virtual Log::LogLevel setLogLevel(Log::LogLevel logLevel) = 0;

    /**
     * Virtual method to get log level filter value currently in effect
     * @return logLevel enum value currently in effect
     */
    virtual Log::LogLevel getLogLevel() = 0;
};
} //namespace services
} //namespace ajn

#endif /* GENERICLOGGER_H_ */
