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
import dialogWidget as dw

class Action (common.Widget):

    def __init__(self, generated, actionElement, parentObjectPath, languageSetName) :
        common.Widget.__init__(self, generated, actionElement, parentObjectPath, languageSetName)
        self.widgetName = "ActionWidget"
        self.widgetType = "WIDGET_TYPE_ACTION"
        self.nonSecuredInterfaceName = "ActionInterfaces"
        self.securedInterfaceName = "SecuredActionInterfaces"
        self.hintPrefix = "ACTION_WIDGET_HINT_"
        self.executeCases = ""

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_EXEC                       AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 4)\n".format(capName, self.generated.definesIndx)
        self.generated.actionCases += "        		case {0}_EXEC:\\\n".format(capName)
        self.executeCases += "\t\tcase {0}_EXEC:\n".format(capName) 

    def generateTests(self, capName) : 
        common.Widget.generateTests(self, capName) 
        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "\t\t\t\tcase AJ_REPLY_ID({0}_EXEC):\\\n".format(capName)

    def generateOnAction (self) :
        onAction = self.element.onAction
        if hasattr(onAction, "executeCode") : 
            self.generated.executeAction += self.executeCases + "\t\t{0}\n".format("{")    
            self.generated.executeAction += "\t\t\t{0}\n\t\t{1}\n\t\tbreak;\n".format(onAction.executeCode, "}")
        elif hasattr(onAction, "dialog") : 
            dialogElem = onAction.dialog
            dialog = dw.Dialog(self.generated, dialogElem, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
            dialog.generate()




