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

def as_list(s):
	if isinstance(s, list): return s
	return [s]

class Generator:

    def __init__(self, scriptDir, path):
        self.scriptDir = scriptDir
        self.path = path
        self.languageSets = {}
        self.languageSetsCode = ""
        self.headerIncludes = ""
        self.initCode = ""
        self.varDecl = ""
        self.varDef = ""

    def setControlDeviceData(self, unitName, headerCode) :
        self.unitName = unitName
        self.ObjectPathPrefix = "/ControlPanel/" + self.unitName + "/"
        self.srcIncludes = headerCode

    def setLanguageSets(self, languageSet) :
        for langElement in languageSet:
            name = langElement.attr["name"]
            self.languageSets[name] = []
            self.languageSetsCode += """    LanguageSet {0}("{0}");\n""".format(name)
            languages = as_list(langElement.language)
            for language in languages :
                self.languageSets[name].append(language)
                self.languageSetsCode += """    {0}.addLanguage("{1}");\n""".format(name, language.replace("-", "_"))
            self.languageSetsCode += """    LanguageSets::add({0}.getLanguageSetName(), {0});\n\n""".format(name)    
    
    def addControlPanel(self, rootElement, languageSet) :
        name = rootElement.name + "ControlPanel"
        self.varDecl += """    static ajn::services::ControlPanel* {0};\n""".format(name)
        self.varDef += """ControlPanel* ControlPanelGenerated::{0} = 0;\n""".format(name)

        self.initCode += """\n    {0} = ControlPanel::createControlPanel(LanguageSets::get("{1}"));\n""".format(name, languageSet)
        self.initCode += """    if (!{0})\n        return ER_FAIL;\n""".format(name)
        self.initCode += """    controlPanelControllee->addControlPanel({0});\n""".format(name)

    def addNotificationAction(self, rootElement, languageSet) :
        name = rootElement.name + "NotificationAction"
        self.varDecl += """    static ajn::services::NotificationAction* {0};\n""".format(name)
        self.varDef += """NotificationAction* ControlPanelGenerated::{0} = 0;\n""".format(name)

        self.initCode += """\n    {0} = NotificationAction::createNotificationAction(LanguageSets::get("{1}"));\n""".format(name, languageSet)
        self.initCode += """    if (!{0})\n        return ER_FAIL;\n""".format(name)
        self.initCode += """    controlPanelControllee->addNotificationAction({0});\n""".format(name)

    def initializeFiles(self) :

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenControlPanelGenerated.h', 'r')
        self.genHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenControlPanelGenerated.cc', 'r')
        self.genSrcFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenActionImpl.h', 'r')
        self.actionHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenActionImpl.cc', 'r')
        self.actionSrcFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenDialogImpl.h', 'r')
        self.dialogHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenDialogImpl.cc', 'r')
        self.dialogSrcFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenPropertyImpl.h', 'r')
        self.propertyHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenPropertyImpl.cc', 'r')
        self.propertySrcFile = inputFile.read()
        inputFile.close()


    def writeFiles(self) :

        genH = open(self.path + "ControlPanelGenerated.h", 'w')
        genH.write(self.genHeaderFile)
        genH.close()

        genC = open(self.path + "/ControlPanelGenerated.cc", 'w')
        genC.write(self.genSrcFile)
        genC.close()


    def replaceInFiles(self) :

        self.genHeaderFile = self.genHeaderFile.replace("//VARIABLE_DECLARATIONS_GO_HERE", self.varDecl)
        self.genHeaderFile = self.genHeaderFile.replace("//NEW_WIDGET_CLASSES_HERE", self.headerIncludes)

        self.genSrcFile = self.genSrcFile.replace("//UNITNAME_GO_HERE", self.unitName)
        self.genSrcFile = self.genSrcFile.replace("//INCLUDES_GO_HERE", self.srcIncludes)
        self.genSrcFile = self.genSrcFile.replace("//STATIC_DECLARATION_HERE", self.varDef)
        self.genSrcFile = self.genSrcFile.replace("//LANGUAGESET_CODE_HERE", self.languageSetsCode)
        self.genSrcFile = self.genSrcFile.replace("//INITCODE_GO_HERE", self.initCode)


