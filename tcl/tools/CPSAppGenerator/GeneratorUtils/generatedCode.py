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

class Generator:

    def __init__(self, scriptDir, path, testFilePath):
        self.scriptDir = scriptDir
        self.path = path
        self.testFilePath = testFilePath
        self.ns = ""
        self.languageSets = {}

        self.headerFile = ""
        self.sampleFile = ""
        self.generatedFile = ""
        self.testerFile = ""
        self.testerGeneratedFile = ""
        self.testerGeneratedHeader = ""

        self.getValuesCases = ""
        self.setValuesCases = ""
        self.getAllCases = ""
        self.getRootValuesCases = ""
        self.getAllRootCases = ""
        self.actionCases = ""
        self.listPropCases = ""
        self.httpCases = ""
        self.maxNumLang = 0

        self.appObjects = ""
        self.announceObjects = ""
        self.defines = ""
        self.definesIndx = 0
        self.objectPathsDef = ""
        self.objectPathsDecl = ""
        
        self.staticVars = ""
        self.initFunction = ""
        self.identify = ""
        self.identifySignal = ""
        self.identifyRoot = ""

        self.setWidgetPropFunc = ""
        self.executeAction = ""

        self.numTests = 0
        self.initTests = ""
        self.allReplies = ""

    def setControlDeviceData(self, uniqueId, headerCode) :
        self.uniqueId = uniqueId
        self.ObjectPathPrefix = "/ControlPanel/" + self.uniqueId + "/"
        self.headerIncludes = headerCode

    def setLanguageSets(self, languageSet) :

        for langElement in languageSet:
            name = langElement.attr["name"]
            self.languageSets[name] = []

            if isinstance(langElement.language, list) :
                langIndx = 0   
                for language in langElement.language :
                    self.languageSets[name].append(language)
                    self.defines += "#define {0}_{1} {2}\n".format(name.upper(), language.replace("-", "_").upper(), langIndx)
                    langIndx += 1
                self.defines += "\n"
                if langIndx > self.maxNumLang :
                    self.maxNumLang = langIndx
            else :
                self.languageSets[name].append(langElement.language)
                self.defines += "#define {0}_{1} {2}\n\n".format(name.upper(), langElement.language.replace("-", "_").upper(), 0)
                if 1 > self.maxNumLang :
                    self.maxNumLang = 1

    def addControlPanel(self, rootElement) :
        name = rootElement.name
        capName = "ROOT_CONTROLPANEL_" + name.upper()
        objectPathVar = "{0}ObjectPath".format(name)
        myObjectPath = self.ObjectPathPrefix + name
        self.objectPathsDecl += "extern const char {0}[];\n".format(objectPathVar)
        self.objectPathsDef += "const char {0}[] = \"{1}\";\n".format(objectPathVar, myObjectPath)
        self.appObjects += "\t{0}  {1}, ControlPanelInterfaces  {2}, \\\n".format("{", objectPathVar, "}")
        self.announceObjects += "\t{0}  {1}, ControlPanelInterfaces  {2}, \\\n".format("{", objectPathVar, "}")

        self.defines += """#define {0}_GET_VALUE                  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET)
#define {0}_SET_VALUE                  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_SET)
#define {0}_GET_ALL_VALUES             AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET_ALL)
#define {0}_VERSION_PROPERTY           AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 0)\n""".format(capName, self.definesIndx)
        self.defines += "\n"
        self.definesIndx += 1	

        self.getRootValuesCases += "        		case {0}_GET_VALUE:\\\n".format(capName)
        self.getAllRootCases += "        		case {0}_GET_ALL_VALUES:\\\n".format(capName)
        self.setValuesCases += "        		case {0}_SET_VALUE:\\\n".format(capName)
        self.identifyRoot += """\t\tcase {0}_VERSION_PROPERTY :
        case {0}_GET_ALL_VALUES : 
            return TRUE;\n""".format(capName)

        if rootElement._has("dismissable") and rootElement.dismissable :
            addNotificationAction(rootElement, 1)

    def addNotificationAction(self, rootElement, fromControlPanel = 0) :
        name = rootElement.name
        capName = "NOTIFICATION_ACTION_" + name.upper()
        objectPathVar = "{0}ObjectPath".format(name)
        self.appObjects += "\t{0}  {1}, NotificationActionInterfaces  {2}, \\\n".format("{", objectPathVar, "}")
       
        if not fromControlPanel :
            myObjectPath = self.ObjectPathPrefix + name
            self.objectPathsDecl += "extern const char {0}[];\n".format(objectPathVar)
            self.objectPathsDef += "const char {0}[] = \"{1}\";\n".format(objectPathVar, myObjectPath)

        self.defines += """#define {0}_GET_VALUE                  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET)
#define {0}_SET_VALUE                  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_SET)
#define {0}_GET_ALL_VALUES             AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET_ALL)
#define {0}_VERSION_PROPERTY           AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 0)
#define {0}_SIGNAL_DISMISS             AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 1)\n""".format(capName, self.definesIndx)
        self.defines += "\n"
        self.definesIndx += 1	

        self.getRootValuesCases += "        		case {0}_GET_VALUE:\\\n".format(capName)
        self.getAllRootCases += "        		case {0}_GET_ALL_VALUES:\\\n".format(capName)
        self.setValuesCases += "        		case {0}_SET_VALUE:\\\n".format(capName)
        self.identifyRoot += """\t\tcase {0}_VERSION_PROPERTY :
        case {0}_GET_ALL_VALUES : 
        case {0}_SIGNAL_DISMISS : 
            return TRUE;\n""".format(capName)


    def initializeFiles(self) :

        genH = open(self.scriptDir + '/PreGenFiles/PreGenControlPanelGenerated.h', 'r')
        self.headerFile = genH.read()
        genH.close()

        genC = open(self.scriptDir + '/PreGenFiles/PreGenControlPanelGenerated.c', 'r')
        self.generatedFile = genC.read()
        genC.close()

    def writeFiles(self) :

        genH = open(self.path + "/inc/ControlPanelGenerated.h", 'w')
        genH.write(self.headerFile)
        genH.close()

        genC = open(self.path + "/ControlPanelGenerated.c", 'w')
        genC.write(self.generatedFile)
        genC.close()

        client = open(self.testFilePath + "/ControlPanelClientGenerated.c", 'w')
        client.write(self.testerGeneratedFile)
        client.close()

        client = open(self.testFilePath + "/ControlPanelClientGenerated.h", 'w')
        client.write(self.testerGeneratedHeader)
        client.close()

    def replaceInFiles(self) :

        self.headerFile = self.headerFile.replace("//DEFINES_GO_HERE", self.defines)
        self.headerFile = self.headerFile.replace("//OBJECTPATH_DECL_GO_HERE", self.objectPathsDecl)
        self.headerFile = self.headerFile.replace("//APPOBJECTS_GO_HERE", self.appObjects)
        self.headerFile = self.headerFile.replace("//ANNOUNCEOBJECTS_GO_HERE", self.announceObjects)
        self.headerFile = self.headerFile.replace("//GETVALUES_GO_HERE", self.getValuesCases)
        self.headerFile = self.headerFile.replace("//SETVALUES_GO_HERE", self.setValuesCases)
        self.headerFile = self.headerFile.replace("//GETALLVALUES_GO_HERE", self.getAllCases)
        self.headerFile = self.headerFile.replace("//ACTION_GO_HERE", self.actionCases)
        self.headerFile = self.headerFile.replace("//LISTPROPERTY_GO_HERE", self.listPropCases)
        self.headerFile = self.headerFile.replace("//GET_URL_GO_HERE", self.httpCases)
        self.headerFile = self.headerFile.replace("//GETVALUES_ROOT_GO_HERE", self.getRootValuesCases)
        self.headerFile = self.headerFile.replace("//GETALLVALUES_ROOT_GO_HERE", self.getAllRootCases)
        self.headerFile = self.headerFile.replace("//UNIQUEID_GO_HERE", self.uniqueId)
        self.headerFile = self.headerFile.replace("//MAXNUMLANGUAGES_GO_HERE", str(self.maxNumLang))
        self.headerFile = self.headerFile.replace("//NUM_CPSOBJ_GO_HERE", str(self.definesIndx))

        self.generatedFile = self.generatedFile.replace("//OBJECTPATH_DEF_GO_HERE", self.objectPathsDef)
        self.testerGeneratedFile = self.generatedFile ## Catch it before all unnecessary replaces
        self.generatedFile = self.generatedFile.replace("//STATICS_GO_HERE", self.staticVars)
        self.generatedFile = self.generatedFile.replace("//INCLUDES_GO_HERE", self.headerIncludes)
        self.generatedFile = self.generatedFile.replace("//INITROOT_GO_HERE", self.initFunction)
        self.generatedFile = self.generatedFile.replace("//ADD_MAIN_CASE_HERE", self.identify)
        self.generatedFile = self.generatedFile.replace("//ADD_ROOT_CASE_HERE", self.identifyRoot)
        self.generatedFile = self.generatedFile.replace("//ADD_SIGNAL_CASE_HERE", self.identifySignal)
        self.generatedFile = self.generatedFile.replace("//SET_WIDGET_PROPERTY_GO_HERE", self.setWidgetPropFunc)
        self.generatedFile = self.generatedFile.replace("//EXECUTE_ACTION_GO_HERE", self.executeAction)
        self.generatedFile = self.generatedFile.replace("//INITTESTS_GO_HERE", "")

        self.testerGeneratedFile = self.testerGeneratedFile.replace("//INITTESTS_GO_HERE", self.initTests)
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//STATICS_GO_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//INCLUDES_GO_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//INITROOT_GO_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//ADD_MAIN_CASE_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//ADD_ROOT_CASE_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//ADD_SIGNAL_CASE_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//SET_WIDGET_PROPERTY_GO_HERE", "")
        self.testerGeneratedFile = self.testerGeneratedFile.replace("//EXECUTE_ACTION_GO_HERE", "")


        self.testerGeneratedHeader = self.headerFile ## Catch it after all replaces
        self.testerGeneratedHeader = self.testerGeneratedHeader.replace("//NUM_TESTS_GO_HERE", str(self.numTests))
        self.testerGeneratedHeader = self.testerGeneratedHeader.replace("//ALL_REPLIES_GO_HERE", self.allReplies)
        self.testerGeneratedHeader = self.testerGeneratedHeader.replace("AJ_APP_MESSAGE_ID", "AJ_PRX_MESSAGE_ID")
        self.testerGeneratedHeader = self.testerGeneratedHeader.replace("AJ_APP_PROPERTY_ID", "AJ_PRX_PROPERTY_ID")



