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

#ifndef CONTROLPANELCONSTANTS_H_
#define CONTROLPANELCONSTANTS_H_

#include <qcc/String.h>

/*
 * Common Macros
 */
#define CHECK_AND_BREAK(x) if ((status = x))  { break; }
#define CHECK_AND_RETURN(x) if ((status = x))  { return status; }

namespace ajn {
namespace services {
namespace cpsConsts {

static const uint16_t CONTROLPANELSERVICE_PORT = 1000;
static const uint16_t DATE_PROPERTY_TYPE = 0;
static const uint16_t TIME_PROPERTY_TYPE = 1;

static const qcc::String TAG_CONTROLPANEL = "ControlPanel";
static const qcc::String TAG_NOTIFICATIONACTION = "NotificationAction";
static const qcc::String TAG_CONTROLPANELCONTROLLEE = "ControlPanelControllee";
static const qcc::String TAG_CONTROLPANELSERVICE = "ControlPanelService";
static const qcc::String TAG_CONTROLPANELBUSOBJECT = "ControlPanelBusObject";
static const qcc::String TAG_NOTIFICATIONACTIONBUSOBJECT = "NotificationActionBusObject";
static const qcc::String TAG_CONTAINER_BUSOBJECT = "ContainerBusObject";
static const qcc::String TAG_LABEL_BUSOBJECT = "LabelBusObject";
static const qcc::String TAG_ACTION_BUSOBJECT = "ActionBusObject";
static const qcc::String TAG_DIALOG_BUSOBJECT = "DialogBusObject";
static const qcc::String TAG_PROPERTY_BUSOBJECT = "PropertyBusObject";
static const qcc::String TAG_HTTPCONTROL_BUSOBJECT = "HttpControlBusObject";
static const qcc::String TAG_CONTAINER_WIDGET = "ContainerWidget";
static const qcc::String TAG_ACTION_WIDGET = "ActionWidget";
static const qcc::String TAG_PROPERTY_WIDGET = "PropertyWidget";
static const qcc::String TAG_LABEL_WIDGET = "LabelWidget";
static const qcc::String TAG_DIALOG_WIDGET = "DialogWidget";
static const qcc::String TAG_HTTPCONTROL = "HttpControl";
static const qcc::String TAG_CONSTRAINTLIST = "ConstraintList";
static const qcc::String TAG_CONSTRAINTRANGE = "ConstraintRange";


static const qcc::String AJ_OBJECTPATH_PREFIX = "/ControlPanel/";
static const qcc::String AJ_HTTP_OBJECTPATH_SUFFIX = "/HTTPControl";
static const qcc::String AJ_CONTROLPANEL_INTERFACE = "org.alljoyn.ControlPanel.ControlPanel";
static const qcc::String AJ_NOTIFICATIONACTION_INTERFACE = "org.alljoyn.ControlPanel.NotificationAction";
static const qcc::String AJ_HTTPCONTROL_INTERFACE = "org.alljoyn.ControlPanel.HTTPControl";
static const qcc::String AJ_SECURED_CONTAINER_INTERFACE = "org.alljoyn.ControlPanel.SecuredContainer";
static const qcc::String AJ_CONTAINER_INTERFACE = "org.alljoyn.ControlPanel.Container";
static const qcc::String AJ_SECURED_PROPERTY_INTERFACE = "org.alljoyn.ControlPanel.SecuredProperty";
static const qcc::String AJ_PROPERTY_INTERFACE = "org.alljoyn.ControlPanel.Property";
static const qcc::String AJ_SECURED_ACTION_INTERFACE = "org.alljoyn.ControlPanel.SecuredAction";
static const qcc::String AJ_ACTION_INTERFACE = "org.alljoyn.ControlPanel.Action";
static const qcc::String AJ_SECURED_DIALOG_INTERFACE = "org.alljoyn.ControlPanel.SecuredDialog";
static const qcc::String AJ_DIALOG_INTERFACE = "org.alljoyn.ControlPanel.Dialog";
static const qcc::String AJ_LABEL_INTERFACE = "org.alljoyn.ControlPanel.LabelProperty";

static const qcc::String AJ_PROPERTY_VERSION = "Version";
static const qcc::String AJ_PROPERTY_STATES = "States";
static const qcc::String AJ_PROPERTY_OPTPARAMS = "OptParams";
static const qcc::String AJ_PROPERTY_LABEL = "Label";
static const qcc::String AJ_PROPERTY_VALUE = "Value";
static const qcc::String AJ_PROPERTY_MESSAGE = "Message";
static const qcc::String AJ_PROPERTY_NUMACTIONS = "NumActions";
static const qcc::String AJ_PROPERTY_URL = "Url";

static const qcc::String AJ_SIGNAL_PROPERTIES_CHANGED = "MetadataChanged";
static const qcc::String AJ_SIGNAL_VALUE_CHANGED = "ValueChanged";
static const qcc::String AJ_SIGNAL_DISMISS = "Dismiss";

static const qcc::String AJ_METHOD_EXECUTE = "Exec";
static const qcc::String AJ_METHOD_ACTION1 = "Action1";
static const qcc::String AJ_METHOD_ACTION2 = "Action2";
static const qcc::String AJ_METHOD_ACTION3 = "Action3";
static const qcc::String AJ_METHOD_GETROOTURL = "GetRootURL";

static const qcc::String AJPARAM_EMPTY = "";
static const qcc::String AJPARAM_VAR = "v";
static const qcc::String AJPARAM_STR = "s";
static const qcc::String AJPARAM_BOOL = "b";
static const qcc::String AJPARAM_UINT16 = "q";
static const qcc::String AJPARAM_INT16 = "n";
static const qcc::String AJPARAM_UINT32 = "u";
static const qcc::String AJPARAM_INT32 = "i";
static const qcc::String AJPARAM_UINT64 = "t";
static const qcc::String AJPARAM_INT64 = "x";
static const qcc::String AJPARAM_DOUBLE = "d";
static const qcc::String AJPARAM_DICT_UINT16_VAR = "{qv}";
static const qcc::String AJPARAM_ARRAY_DICT_UINT16_VAR = "a{qv}";
static const qcc::String AJPARAM_ARRAY_UINT16 = "aq";
static const qcc::String AJPARAM_STRUCT_VAR_STR = "(vs)";
static const qcc::String AJPARAM_ARRAY_STRUCT_VAR_STR = "a(vs)";
static const qcc::String AJPARAM_STRUCT_VAR_VAR_VAR = "(vvv)";
static const qcc::String AJPARAM_DATE_OR_TIME = "(q(qqq))";

static const qcc::String AJ_ERROR_UNKNOWN = "Unknown Error";
static const qcc::String AJ_ERROR_UNKNOWN_MESSAGE = "An Unknown Error occured";

enum OPT_PARAM_KEYS {
    LABEL_KEY = 0,
    BGCOLOR_KEY = 1,
    HINT_KEY = 2,
    UNIT_MEASURE = 3,
    CONSTRAINT_LIST = 4,
    CONSTRAINT_RANGE = 5,
    LABEL_ACTION1 = 6,
    LABEL_ACTION2 = 7,
    LABEL_ACTION3 = 8,
    NUM_OPT_PARAMS = 9
};

} //namespace cpsConsts
} //namespace services
} //namespace ajn

#endif


