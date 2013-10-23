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

#include "alljoyn/controlpanel/GenericLogger.h"

using namespace ajn;
using namespace services;

void GenericLogger::debug(qcc::String const& Tag, qcc::String const& logText)
{
    return debug(Tag.c_str(), logText.c_str());
}

void GenericLogger::info(qcc::String const& Tag, qcc::String const& logText)
{
    return info(Tag.c_str(), logText.c_str());
}

void GenericLogger::warn(qcc::String const& Tag, qcc::String const& logText)
{
    return warn(Tag.c_str(), logText.c_str());
}

void GenericLogger::error(qcc::String const& Tag, qcc::String const& logText)
{
    return error(Tag.c_str(), logText.c_str());
}

void GenericLogger::fatal(qcc::String const& Tag, qcc::String const& logText)
{
    return fatal(Tag.c_str(), logText.c_str());
}

