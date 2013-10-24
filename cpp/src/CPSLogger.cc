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

#include <alljoyn/controlpanel/CPSLogger.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <qcc/Log.h>

namespace ajn {
namespace services {
using namespace qcc;

#define CALLBACKTAG "AllJoynInternal"
#define QCC_MODULE "ControlPanelService"

Log::LogLevel CPSLogger::m_defaultLogLevel = Log::LEVEL_ERROR;
GenericLogger* CPSLogger::m_initialLogger = NULL;

CPSLogger::CPSLogger()
{
    /*
     * AllJoyn loglevels
     * default is 0 (none, except for errors)
     * 1 = high-level-debug (binary 1)                   "debug"
     * 2 = general-debug   (binary 10)                   "info"
     * 3 = high-level-debug, general-debug (binary 11)   "debug + info"
     * 4 = trace (binary 100)                            "warn"
     * 5 = trace, high-level-debug (binary 101)          "warn + debug"
     * 6 = trace, general-debug (binary 110)             "warn + info"
     * 7 = trace, general-debug, high-level-debug (binary 111)  "warn + info + debug"
     *     error is always printed
     */
    setLogLevel(m_defaultLogLevel);
    // save this initial default logger. we don't want to register AJ callback
    // on it (because then our callback calls itself endlessly). if it's passed
    // to us later on in setLogger, we will not set our callback on it.
    m_initialLogger = this;
}

CPSLogger::~CPSLogger()
{

}

Log::LogLevel CPSLogger::setLogLevel(Log::LogLevel newLogLevel)
{
    Log::LogLevel prevLogLevel = m_logLevel;
    m_logLevel = newLogLevel;
    QCC_SetDebugLevel(QCC_MODULE, 7);     // AJ should not block any of our log messages
    return prevLogLevel;
}

Log::LogLevel CPSLogger::getLogLevel()
{
    return m_logLevel;
}

Log::LogLevel CPSLogger::getDefaultLogLevel()
{
    return m_defaultLogLevel;
}

void CPSLogger::debug(const char* Tag, const char* logText)
{
    if (m_logLevel >= Log::LEVEL_DEBUG)
        QCC_DbgTrace(("[DEBUG] %s: %s", Tag, logText));
}

void CPSLogger::info(const char* Tag, const char* logText)
{
    if (m_logLevel >= Log::LEVEL_INFO)
        QCC_DbgPrintf(("[INFO] %s: %s", Tag, logText));
}
void CPSLogger::warn(const char* Tag, const char* logText)
{
    if (m_logLevel >= Log::LEVEL_WARN)
        QCC_DbgHLPrintf(("[WARN] %s: %s", Tag, logText));
}

void CPSLogger::error(const char* Tag, const char* logText)
{
    if (m_logLevel >= Log::LEVEL_ERROR)
        QCC_LogError(ER_FAIL, ("[ERROR] %s: %s", Tag, logText));
}

void CPSLogger::fatal(const char* Tag, const char* logText)
{
    if (m_logLevel >= Log::LEVEL_FATAL)
        QCC_LogError(ER_FAIL, ("[FATAL] %s: %s", Tag, logText));
}

void CPSLogger::GenericLoggerCallBack(DbgMsgType type, const char* module, const char* msg, void* context)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger) {
        Log::LogLevel currLogLevel = logger->getLogLevel();
        switch (type) {
        case DBG_LOCAL_ERROR:
        case DBG_REMOTE_ERROR:
            if (currLogLevel >= Log::LEVEL_ERROR)
                logger->error(CALLBACKTAG, msg);
            break;

        case DBG_GEN_MESSAGE:
            if (currLogLevel >= Log::LEVEL_INFO)
                logger->info(CALLBACKTAG, msg);
            break;

        case DBG_API_TRACE:
            if (currLogLevel >= Log::LEVEL_DEBUG)
                logger->debug(CALLBACKTAG, msg);
            break;

        case DBG_HIGH_LEVEL:
            if (currLogLevel >= Log::LEVEL_WARN)
                logger->warn(CALLBACKTAG, msg);
            break;

        case DBG_REMOTE_DATA:
        case DBG_LOCAL_DATA:
            if (currLogLevel >= Log::LEVEL_DEBUG)
                logger->debug(CALLBACKTAG, msg);
            break;

        default:
            if (currLogLevel >= Log::LEVEL_DEBUG)
                logger->debug(CALLBACKTAG, msg);
        }
    }
} // void CPSLogger::GenericLoggerCallBack

void CPSLogger::RegisterCallBack(GenericLogger* newLogger)
{
    // arrange for AJ logging to come back to us, for redirection to the logger instance
    if (newLogger == m_initialLogger) {
        QCC_RegisterOutputFile(stderr);
    } else {
        QCC_RegisterOutputCallback(&CPSLogger::GenericLoggerCallBack, stderr);         // stderr or NULL?
    }
}

} /* namespace services */
} /* namespace ajn */
