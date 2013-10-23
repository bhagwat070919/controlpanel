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
/*
 * HttpControl.c
 *
 *  Created on: May 28, 2013
 */

#include "alljoyn/controlpanel/Common/HttpControl.h"
#include "alljoyn/controlpanel/Definitions.h"
#include "alljoyn/controlpanel/Common/ControlMarshalUtil.h"

void initializeHttpControl(HttpControl* httpControl)
{
    httpControl->url = 0;
    httpControl->getUrl = 0;
}

AJ_Status marshalHttpControlUrl(HttpControl* httpControl, AJ_Message* reply, uint16_t language)
{
    if (httpControl->getUrl == 0 && httpControl->url == 0)
        return AJ_ERR_UNEXPECTED;
    return AJ_MarshalArgs(reply, PROPERTY_TYPE_URL_SIG, httpControl->getUrl ? httpControl->getUrl() : httpControl->url);
}
