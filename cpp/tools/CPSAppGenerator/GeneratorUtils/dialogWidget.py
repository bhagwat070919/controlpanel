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

    def __init__(self, generated, dialogElement, parentName, languageSetName, isRoot = 0) :
        common.Widget.__init__(self, generated, dialogElement, parentName, languageSetName)
        self.isRoot = 1
        self.widgetName = self.name[:1].upper() + self.name [1:]
        self.name = self.name[:1].lower() + self.name [1:]
        if not isRoot :
            self.parentAddFunc = "addChildDialog"
        else :
            self.parentAddFunc = "setRootWidget"

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateMandatoryVariables (self) :
        common.Widget.generateMandatoryVariables(self)
        self.setMessage()
        self.setNumActions() 

    def setMessage (self) :
        self.setCodeOrValueString ("message", "setMessage", "setGetMessage")

    def setNumActions (self) :
        self.generated.initCode += "    {0}->setNumActions({1});\n".format(self.name, len(self.element.button))

    def setLabelAction (self, i) :
        self.setCodeOrValueString ('label', "setLabelAction%i" % (i+1), "setGetLabelAction%i" % (i+1), "LabelAction%i" % (i+1), self.element.button[i])


    def generateOnAction (self) :
        dialogHeaderFile = self.generated.dialogHeaderFile
        dialogSrcFile = self.generated.dialogSrcFile

        regularName = self.widgetName
        capitalName = self.name.upper()

        dialogHeaderFile = dialogHeaderFile.replace("CAPITAL_NAME_HERE", capitalName)
        dialogHeaderFile = dialogHeaderFile.replace("REGULAR_NAME_HERE", regularName)

        dialogSrcFile = dialogSrcFile.replace("CAPITAL_NAME_HERE", capitalName)
        dialogSrcFile = dialogSrcFile.replace("REGULAR_NAME_HERE", regularName)
        dialogSrcFile = dialogSrcFile.replace("ADDITIONAL_INCLUDES_HERE", self.generated.srcIncludes)

        self.generated.headerIncludes += """#include "../generated/{0}.h"\n""".format(regularName)

        notDefined = "    executeActionNotDefined();"
        for i in range(0, len(self.element.button)):
            self.setLabelAction(i)
            dialogSrcFile = dialogSrcFile.replace("CODE_OF_EXECUTE_ACTION%i_HERE" % (i+1), self.element.button[i].executeCode)            
        for i in range(len(self.element.button), 3):    
            dialogSrcFile = dialogSrcFile.replace("CODE_OF_EXECUTE_ACTION%i_HERE" % (i+1), notDefined)            

        genH = open(self.generated.path + "/" + regularName + ".h", 'w')
        genH.write(dialogHeaderFile)
        genH.close()
        genC = open(self.generated.path + "/" + regularName + ".cc", 'w')
        genC.write(dialogSrcFile)
        genC.close()



