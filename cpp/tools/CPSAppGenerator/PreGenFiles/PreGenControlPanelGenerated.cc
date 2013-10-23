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

#include "ControlPanelGenerated.h"
#include "alljoyn/controlpanel/LanguageSets.h"
#include "alljoyn/controlpanel/Label.h"
//INCLUDES_GO_HERE


using namespace ajn;
using namespace services;

bool ControlPanelGenerated::languageSetsDone = false;
//STATIC_DECLARATION_HERE

#define CHECK(x) if ((x) != ER_OK) return status;
#define UNIT_NAME "//UNITNAME_GO_HERE"

void ControlPanelGenerated::PrepareLanguageSets()
{
    if (languageSetsDone)
        return;

//LANGUAGESET_CODE_HERE    languageSetsDone = true;
}

QStatus ControlPanelGenerated::PrepareWidgets(ControlPanelControllee*& controlPanelControllee)
{
    if (controlPanelControllee)
        return ER_BAD_ARG_1;

    PrepareLanguageSets();

    QStatus status = ER_OK;
    controlPanelControllee = new ControlPanelControllee(UNIT_NAME);
//INITCODE_GO_HERE
    return status;
}

void ControlPanelGenerated::Shutdown()
{
//SHUTDOWN_GO_HERE
}
