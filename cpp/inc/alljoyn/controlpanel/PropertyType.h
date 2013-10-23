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

enum PropertyType {
    BOOL_PROPERTY = 0,
    UINT16_PROPERTY = 1,
    INT16_PROPERTY = 2,
    UINT32_PROPERTY = 3,
    INT32_PROPERTY = 4,
    UINT64_PROPERTY = 5,
    INT64_PROPERTY = 6,
    DOUBLE_PROPERTY = 7,
    STRING_PROPERTY = 8,
    DATE_PROPERTY = 9,
    TIME_PROPERTY = 10,
    UNDEFINED = 11
};

} //namespace services
} //namespace ajn

#endif /* CONTROLPANELPROPERTYTYPE_H_ */
