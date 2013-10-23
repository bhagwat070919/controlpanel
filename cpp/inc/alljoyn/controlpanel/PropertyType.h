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

#ifndef CONTROLPANELPROPERTYTYPE_H_
#define CONTROLPANELPROPERTYTYPE_H_

#include <qcc/String.h>

namespace ajn {
namespace services {

/**
 * Enum to define the type of Property
 */
enum PropertyType {
    BOOL_PROPERTY = 0,  //!< BOOL_PROPERTY
    UINT16_PROPERTY = 1, //!< UINT16_PROPERTY
    INT16_PROPERTY = 2, //!< INT16_PROPERTY
    UINT32_PROPERTY = 3, //!< UINT32_PROPERTY
    INT32_PROPERTY = 4, //!< INT32_PROPERTY
    UINT64_PROPERTY = 5, //!< UINT64_PROPERTY
    INT64_PROPERTY = 6, //!< INT64_PROPERTY
    DOUBLE_PROPERTY = 7, //!< DOUBLE_PROPERTY
    STRING_PROPERTY = 8, //!< STRING_PROPERTY
    DATE_PROPERTY = 9,  //!< DATE_PROPERTY
    TIME_PROPERTY = 10, //!< TIME_PROPERTY
    UNDEFINED = 11      //!< UNDEFINED
};

} //namespace services
} //namespace ajn

#endif /* CONTROLPANELPROPERTYTYPE_H_ */
