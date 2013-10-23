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

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "alljoyn/controlpanel/Widget.h"
#include <map>

namespace ajn {
namespace services {

class Property : public Widget {
public:
	Property(qcc::String name);
	virtual ~Property();

	QStatus registerObjects(BusAttachment* bus, LanguageSet const& m_LanguageSet,
			qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix);

private:
};
} //namespace services
} //namespace ajn

#endif /* PROPERTY_H_ */
