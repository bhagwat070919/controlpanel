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

class Dialog (common.Widget):

    def __init__(self, generated, dialogElement, parentObjectPath, languageSetName, isRoot = 0) :
        common.Widget.__init__(self, generated, dialogElement, parentObjectPath, languageSetName)
        self.widgetName = "DialogWidget"
        self.widgetType = "WIDGET_TYPE_DIALOG"
        self.nonSecuredInterfaceName = "DialogInterfaces"
        self.securedInterfaceName = "SecuredDialogInterfaces"
        self.hintPrefix = "DIALOG_HINT_"
        self.execute1Cases = ""
        self.execute2Cases = ""
        self.execute3Cases = ""
        if isRoot:
            self.objectPathSuffix = ""  

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_MESSAGE_PROPERTY           AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 4)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_NUM_ACTIONS_PROPERTY       AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 5)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_EXEC_ACTION1               AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 6)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_EXEC_ACTION2               AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 7)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_EXEC_ACTION3               AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 8)\n".format(capName, self.generated.definesIndx)

        self.generated.actionCases += "        		case {0}_EXEC_ACTION1:\\\n".format(capName)
        self.generated.actionCases += "        		case {0}_EXEC_ACTION2:\\\n".format(capName)
        self.generated.actionCases += "        		case {0}_EXEC_ACTION3:\\\n".format(capName)

        self.execute1Cases += "\t\tcase {0}_EXEC_ACTION1:\n".format(capName) 
        self.execute2Cases += "\t\tcase {0}_EXEC_ACTION2:\n".format(capName) 
        self.execute3Cases += "\t\tcase {0}_EXEC_ACTION3:\n".format(capName) 

    def generateTests(self, capName) : 
        common.Widget.generateTests(self, capName) 
        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC_ACTION1;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "\t\t\t\tcase AJ_REPLY_ID({0}_EXEC_ACTION1):\\\n".format(capName)

        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC_ACTION2;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "\t\t\t\tcase AJ_REPLY_ID({0}_EXEC_ACTION2):\\\n".format(capName)

        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC_ACTION3;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "\t\t\t\tcase AJ_REPLY_ID({0}_EXEC_ACTION3):\\\n".format(capName)

    def generateMandatoryVariables (self) :
        self.generated.initFunction  += "\tinitializeDialogWidget(&{0});\n".format(self.name)
        self.setNumLanguages()
        self.setEnabled()
        self.setMessage()
        self.setNumActions() 
        self.generated.initFunction += "\n"

    def setNumActions (self) :
        self.generated.initFunction += "\t{0}.numActions = {1};\n".format(self.name, self.element.numActions)

    def generateOptionalVariables (self) :
        self.setBgColor()
        self.setLabel() 
        self.setHints() 
        self.setLabelAction("labelAction1") 
        self.setLabelAction("labelAction2") 
        self.setLabelAction("labelAction3") 

    def generateOnAction (self) :
        error = "AJ_MarshalErrorMsg(msg, &reply, AJ_ErrServiceUnknown);"

        self.generated.executeAction += self.execute1Cases + "\t\t{0}\n".format("{")    
        self.generated.executeAction += "\t\t\t{0}\n\t\t{1}\n\t\tbreak;\n".format(self.element.executeCode1, "}")

        self.generated.executeAction += self.execute2Cases + "\t\t{0}\n".format("{")    
        if hasattr(self.element, "executeCode2") :
            self.generated.executeAction += "\t\t\t{0}\n\t\t{1}\n\t\tbreak;\n".format(self.element.executeCode2, "}")
        else :
            self.generated.executeAction += "\t\t\t{0}\n\t\t{1}\n\t\tbreak;\n".format(error, "}")

        self.generated.executeAction += self.execute3Cases + "\t\t{0}\n".format("{")    
        if hasattr(self.element, "executeCode3") :
            self.generated.executeAction += "\t\t\t{0}\n\t\t{1}\n\t\tbreak;\n".format(self.element.executeCode3, "}")
        else :
            self.generated.executeAction += "\t\t\t{0}\n\t\t{1}\n\t\tbreak;\n".format(error, "}")






