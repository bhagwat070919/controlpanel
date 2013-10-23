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

#ifndef CONTROL_MARSHAL_UTIL_H_
#define CONTROL_MARSHAL_UTIL_H_

#include "alljoyn.h"
#include "aj_msg.h"

#include "alljoyn/controlpanel/Definitions.h"

#define CPS_CHECK(s) if ((status = s)) return status;
#define CPS_CHECK_OR_BREAK(s) if ((status = s)) break;
#define StartOptionalParams(reply, arg) AJ_MarshalContainer(reply, arg, AJ_ARG_ARRAY)

/**
 * Add a layout Hint. Can be used for all kinds of MetaData (Property, ListProperty etc)
 * @param reply
 * @param hints
 * @param numHints
 * @return status
 */
AJ_Status AddHints(AJ_Message* reply, const uint16_t hints[], uint16_t numHints);

/**
 * Add Constraint Value
 * @param reply
 * @param sig
 * @param value
 * @param displayValue
 * @return status
 */
AJ_Status AddConstraintValue(AJ_Message* reply, const char* sig, const void* value, const char* displayValue);

/**
 * Add ConstraintRange component
 * @param reply
 * @param valueSig
 * @param min
 * @param max
 * @param increment
 * @return status
 */
AJ_Status AddConstraintRange(AJ_Message* reply, const char* valueSig, const void* min, const void* max, const void* increment);

/**
 * Start a Complex OptionalParam component
 * @param reply
 * @param arg
 * @param key
 * @param sig
 * @return status
 */
AJ_Status StartComplexOptionalParam(AJ_Message* reply, AJ_Arg* arg, uint16_t key, const char* sig);

/**
 * Add a basic type Optional Param
 * @param reply
 * @param key
 * @param sig
 * @param value
 * @return status
 */
AJ_Status AddBasicOptionalParam(AJ_Message* reply, uint16_t key, const char* sig, const void* value);

/**
 * Add a property for GetAll response
 * @param reply
 * @param key
 * @param sig
 * @param widget
 * @param language
 * @param functionPtr
 * @return status
 */
AJ_Status AddPropertyForGetAll(AJ_Message* reply, char* key, const char* sig,
                               void* widget, uint16_t lang, void* functionPtr);

/**
 * Helper functions. Receives sig value and void* and does the marshalling
 * @param reply
 * @param sig
 * @param value
 * @return status
 */
AJ_Status MarshalVariant(AJ_Message* reply, const char* sig, const void* value);

/**
 * MarshalAllRootProperties - includes only version
 * @param reply
 * @return status
 */
AJ_Status MarshalAllRootProperties(AJ_Message* reply);

/**
 * Marshal Version Property for root interfaces
 * @param reply
 * @return status
 */
AJ_Status MarshalVersionRootProperties(AJ_Message* reply);

#endif /* CONTROL_SERVICE_H_ */
