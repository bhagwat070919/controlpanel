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
        if hasattr(self.element.onAction, "executeCode") : 
            self.widgetName = self.name[:1].upper() + self.name [1:]
            self.name = self.name[:1].lower() + self.name [1:]
        else :
            self.widgetName = "ActionWithDialog"

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateOnAction (self) :
        onAction = self.element.onAction
        if hasattr(onAction, "executeCode") : 
            actionHeaderFile = self.generated.actionHeaderFile
            actionSrcFile = self.generated.actionSrcFile

            regularName = self.widgetName
            capitalName = self.name.upper()

            actionHeaderFile = actionHeaderFile.replace("CAPITAL_NAME_HERE", capitalName)
            actionHeaderFile = actionHeaderFile.replace("REGULAR_NAME_HERE", regularName)

            actionSrcFile = actionSrcFile.replace("CAPITAL_NAME_HERE", capitalName)
            actionSrcFile = actionSrcFile.replace("REGULAR_NAME_HERE", regularName)
            actionSrcFile = actionSrcFile.replace("ADDITIONAL_INCLUDES_HERE", self.generated.srcIncludes)
            actionSrcFile = actionSrcFile.replace("EXECUTE_ACTION_HERE", onAction.executeCode)

            self.generated.headerIncludes += """#include "../generated/{0}.h"\n""".format(regularName)

            genH = open(self.generated.path + "/" + regularName + ".h", 'w')
            genH.write(actionHeaderFile)
            genH.close()
            genC = open(self.generated.path + "/" + regularName + ".cc", 'w')
            genC.write(actionSrcFile)
            genC.close()

        elif hasattr(onAction, "dialog") : 
            dialog = dw.Dialog(self.generated, onAction.dialog, self.name, self.languageSetName)
            dialog.generate()




