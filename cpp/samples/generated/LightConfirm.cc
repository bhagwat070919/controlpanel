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

#include "LightConfirm.h"
#include "../provided/ControlPanelProvided.h"

using namespace ajn;
using namespace services;

LightConfirm::LightConfirm(qcc::String name) : Dialog(name)
{

}

LightConfirm::~LightConfirm()
{

}

void LightConfirm::executeAction1CallBack()
{
    //AJ_Printf("Execute Action1 was called\n");;
}

void LightConfirm::executeAction2CallBack()
{
    //AJ_Printf("Execute Action2 was called\n");;
}

void LightConfirm::executeAction3CallBack()
{
    //AJ_Printf("Execute Action3 was called\n");;
}
