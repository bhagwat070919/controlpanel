# Copyright 2013, Qualcomm Innovation Center, Inc.
#
#    All rights reserved.
#    This file is licensed under the 3-clause BSD license in the NOTICE.txt
#    file for this project. A copy of the 3-clause BSD license is found at:
#
#        http://opensource.org/licenses/BSD-3-Clause.
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the license is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the license for the specific language governing permissions and
#    limitations under the license.
#
import sys

class HttpControl:

    def __init__(self, generated, url) :
        self.generated = generated
        self.url = url
        
        self.httpCasesString = """#define HTTP_CONTROL_GET_VALUE             AJ_APP_MESSAGE_ID({0} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET)
#define HTTP_CONTROL_SET_VALUE             AJ_APP_MESSAGE_ID({0} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_SET)
#define HTTP_CONTROL_GET_ALL_VALUES        AJ_APP_MESSAGE_ID({0} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET_ALL)
#define HTTP_CONTROL_VERSION_PROPERTY      AJ_APP_PROPERTY_ID({0} + NUM_PRECEDING_OBJECTS, 1, 0)
#define HTTP_CONTROL_GET_ROOT_URL          AJ_APP_MESSAGE_ID({0} + NUM_PRECEDING_OBJECTS, 1, 1)\n\n"""
         
        self.httpIdentifyString = """    case HTTP_CONTROL_GET_ROOT_URL:
        *widgetType = WIDGET_TYPE_HTTP;
        *propType = PROPERTY_TYPE_URL;
        return &{0};\n\n"""

        self.httpRootIdentifyString = """    case HTTP_CONTROL_GET_ALL_VALUES:
    case HTTP_CONTROL_VERSION_PROPERTY:
        return TRUE;\n\n"""

    def generate(self) :
        name = "httpControl"
        objectPathVar = "{0}ObjectPath".format(name)

        self.generated.appObjects += "    {0}  {1}, HttpControlInterfaces  {2}, \\\n".format("{", objectPathVar, "}")
        self.generated.announceObjects += "    {0}  {1}, HttpControlInterfaces  {2}, \\\n".format("{", objectPathVar, "}")
        
        self.generated.defines += self.httpCasesString.format(self.generated.definesIndx)  

        self.generated.definesIndx += 1	
        self.generated.getRootValuesCases += "        case HTTP_CONTROL_GET_VALUE:\\\n"
        self.generated.setValuesCases += "        case HTTP_CONTROL_SET_VALUE:\\\n"
        self.generated.getAllRootCases += "        case HTTP_CONTROL_GET_ALL_VALUES:\\\n"
        self.generated.httpCases += "        case HTTP_CONTROL_GET_ROOT_URL:\\\n"

        self.generated.identifyRoot += self.httpRootIdentifyString
        self.generated.identify += self.httpIdentifyString.format(name)

        self.generated.objectPathsDecl += "extern const char {0}[];\n".format(objectPathVar)
        self.generated.objectPathsDef += "const char {0}[] = \"{1}\";\n".format(objectPathVar, self.generated.ObjectPathPrefix + "HTTPControl")

        self.generated.staticVars += "static HttpControl {0};\n".format(name)
        self.generated.initFunction += "    initializeHttpControl(&{0});\n".format(name)

        if hasattr(self.url, "attr") and "code" in self.url.attr and self.url.attr["code"] == "true" : 
           self.generated.initFunction += "    {0}.getUrl = {1};\n".format(name, self.url)
        else :
           self.generated.staticVars += "static const char* {0}Url = \"{1}\";\n".format(name, self.url)    
           self.generated.initFunction += "    {0}.url = {0}Url;\n\n".format(name)

        self.generated.initTests += "    testsToRun[{0}].msgId = HTTP_CONTROL_GET_ROOT_URL;\n    testsToRun[{0}].numParams = 0;\n""".format(self.generated.numTests)
        self.generated.numTests = self.generated.numTests + 1

        self.generated.allReplies += "case AJ_REPLY_ID(HTTP_CONTROL_GET_ROOT_URL): \\\n"

