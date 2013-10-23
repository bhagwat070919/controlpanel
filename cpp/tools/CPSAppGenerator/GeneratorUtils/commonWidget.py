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

def as_list(s):
	if isinstance(s, list): return s
	return [s]


class Widget:

    def __init__(self, generated, element, parentName, languageSetName) :
        self.generated = generated
        self.element = element
        self.parentName = parentName
        self.name = element.name
        self.languageSetName = languageSetName
        self.languageSet = self.generated.languageSets[languageSetName]
        self.parentAddFunc = "addChildElement"
        self.additionalParams = ""


    def generate(self) :
        self.generateBasics()
        self.generateMandatoryVariables()
        self.generateOptionalVariables()

    def generateBasics(self) :

        self.generated.varDecl += """    static ajn::services::{0}* {1};\n""".format(self.widgetName, self.name)
        self.generated.varDef += """{0}* ControlPanelGenerated::{1} = 0;\n""".format(self.widgetName, self.name)

        self.generated.initCode += """\n    {0} = new {1}("{0}"{2});\n""".format(self.name, self.widgetName, self.additionalParams)
        self.generated.initCode += """    CHECK({0}->{1}({2}));\n\n""".format(self.parentName, self.parentAddFunc, self.name)

        self.generated.shutdown += """    if ({0}) {1}\n        delete ({0});\n        {0} = 0;\n    {2}\n""".format(self.name, "{", "}")

    def generateMandatoryVariables (self) :

        self.setEnabled()
        self.setSecured()

    def generateOptionalVariables (self) :
        self.setBgColor()
        self.setLabel()
        self.setHints() 

    def setSecured (self) :
        if not hasattr(self.element, "secured") :
            return
        self.generated.initCode += "    {0}->setIsSecured({1});\n".format(self.name, self.element.secured)

    def setEnabled (self) :
        enabled = self.element.enabled
        if hasattr(enabled, "attr") and "code" in enabled.attr and enabled.attr["code"] == "true" : 
            self.generated.initCode += "    {0}->setGetEnabled({1});\n".format(self.name, enabled)
        else :
            if enabled != "true" and enabled != "false" :
                print "ERROR - The value {0} is not supported for enabled in {1}. Exiting".format(enabled, self.name)
                sys.exit(0)	
            self.generated.initCode += "    {0}->setEnabled({1});\n".format(self.name, enabled)

    def setBgColor (self) :
        if hasattr(self.element, "bgcolor") :
            bgColor = self.element.bgcolor
            if hasattr(bgColor, "attr") and "code" in bgColor.attr and bgColor.attr["code"] == "true" : 
                self.generated.initCode += "    {0}->setGetBgColor({1});\n".format(self.name, bgColor)
            else :
                self.generated.initCode += "    {0}->setBgColor({1});\n".format(self.name, bgColor)
    		
    def setHints (self) :
        if not hasattr(self.element, "hints") :
            return;

        hints = as_list(self.element.hints.hint)
        vectorName = self.name + "HintsVec"
        self.generated.initCode += "\n    std::vector<uint16_t> {0};\n".format(vectorName)

        for hint in hints:
            self.generated.initCode += "    {0}.push_back({1});\n".format(vectorName, hint.upper())                        
        self.generated.initCode += "    {0}->setHints({1});\n".format(self.name, vectorName)

    def setLabel (self) :
        self.setCodeOrValueString ("label", "setLabel", "setGetLabel")    

    def setCodeOrValueString (self, fieldName, variableName, codeVariableName, vectorName = "", elementToUse = 0, elementName = "") :
        if elementToUse == 0 :
            element = self.element
        else :
            element = elementToUse
        if not hasattr(element, fieldName) :
            return;
        root = getattr(element, fieldName) 
        if root._has("code") : 
            self.generated.initCode += "    {0}->{1}({2});\n".format(self.name, codeVariableName, root.code)
            return
        if root._has("value"):
            values = as_list(root.value)
            if len(values) != len(self.languageSet) :
                print "ERROR - Missing a {1} or too many {1}s defined for {0}. Exiting".format(self.name, fieldName)
                sys.exit(1)

            if len(vectorName) :
                vectorName = self.name + vectorName + "Vec"
            else :
                vectorName = self.name + fieldName + "Vec"
            self.generated.initCode += "\n    std::vector<qcc::String> {0};\n".format(vectorName)

            for lang in self.languageSet :
                value = filter(lambda x: x.attr["language"] == lang, values)
                if len(value) !=  1:
                    print "ERROR - No {0} is defined or multiple {0}s are defined for language: {1} in {2}. Exiting".format(fieldName, lang, self.name)
                    sys.exit(0)
                if value[0].attr['type'] == 'constant':
                    self.generated.initCode += """    {0}.push_back({1});\n""".format(vectorName, value[0])                        
                else:
                    self.generated.initCode += """    {0}.push_back("{1}");\n""".format(vectorName, value[0])
            if len(elementName) :
                self.generated.initCode += "    {0}.{1}({2});\n".format(elementName, variableName, vectorName)
            else :
                self.generated.initCode += "    {0}->{1}({2});\n".format(self.name, variableName, vectorName)



