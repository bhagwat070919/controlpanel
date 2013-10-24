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
import xml.etree.ElementTree as xml
import commonWidget as common

class Label (common.Widget):

    def __init__(self, generated, labelElement, parentObjectPath, languageSetName) :
        common.Widget.__init__(self, generated, labelElement, parentObjectPath, languageSetName)
        self.widgetName = "LabelWidget"
        self.widgetType = "WIDGET_TYPE_LABEL"
        self.nonSecuredInterfaceName = "LabelPropertyInterfaces"
        self.hintPrefix = "LABEL_HINT_"

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_LABEL_PROPERTY             AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 4)\n".format(capName, self.generated.definesIndx)

    def generateIdentify(self, capName, language) :
        common.Widget.generateIdentify(self, capName, language)
        self.generated.identify += """    case {0}_LABEL_PROPERTY:
        *widgetType = WIDGET_TYPE_LABEL;
        *propType = PROPERTY_TYPE_LABEL;
        *language = {2};
        return &{1};\n\n""".format(capName, self.name, language)

    def generateMandatoryVariables (self) :
        self.generated.initFunction  += "    initializeLabelWidget(&{0});\n".format(self.name)
        self.setNumLanguages()
        self.setEnabled()
        self.setLabel(1)
        self.generated.initFunction += "\n"

    def generateOptionalVariables (self) :
        self.setBgColor()
        self.setHints() 
    	

