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

class Widget:

    def __init__(self, generated, element, parentObjectPath, languageSetName) :
        self.generated = generated
        self.element = element
        self.languageSetName = languageSetName
        self.languageSet = self.generated.languageSets[languageSetName]
        self.parentObjectPath = parentObjectPath
        self.name = element.name
        self.objectPathSuffix = "/" + self.name
        if hasattr(self.element, "secured") :
            self.secured = self.element.secured.upper()
        else :
            self.secured = "FALSE"

    def generate(self) :
        self.generateBasics()
        self.generateMandatoryVariables()
        self.generateOptionalVariables()

    def generateBasics(self) :
        self.generated.staticVars += "static {0} {1};\n".format(self.widgetName, self.name)
        for language in self.languageSet :
            self.generateBasicsPerLanguage(language.replace("-", "_")) 

    def generateBasicsPerLanguage(self, language) :
        ### objectPath stuff
        objectPathVar = "{0}{1}ObjectPath".format(language, self.name.capitalize())
        myObjectPath = self.parentObjectPath.replace("REPLACE_LANG",language) + self.objectPathSuffix

        self.generated.objectPathsDecl += "extern const char {0}[];\n".format(objectPathVar)
        self.generated.objectPathsDef += "const char {0}[] = \"{1}\";\n".format(objectPathVar, myObjectPath)

        ### Defines for Interfaces
        capName = language.upper() + "_" + self.name.upper()        
        self.generateDefines(capName)
         
        self.generated.defines += "\n"
        self.generated.definesIndx += 1	
    
        self.generateIdentify(capName, self.languageSetName.upper() + "_" + language.upper())

        ### Add Interface to AppObjects
        if self.secured == "FALSE" :
            self.generated.appObjects += "\t{0}  {1}, {2}  {3}, \\\n".format("{", objectPathVar, self.nonSecuredInterfaceName, "}")
        else :
            self.generated.appObjects += "\t{0}  {1}, {2}  {3}, \\\n".format("{", objectPathVar, self.securedInterfaceName, "}")

        ### tests
        self.generateTests(capName)


    def generateDefines(self, capName) :
        self.generated.defines += """#define {0}_GET_VALUE                  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET)
#define {0}_SET_VALUE                  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_SET)
#define {0}_GET_ALL_VALUES             AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 0, AJ_PROP_GET_ALL)
#define {0}_VERSION_PROPERTY           AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 0)
#define {0}_STATES_PROPERTY            AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 1)
#define {0}_OPTPARAMS_PROPERTY         AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 2)
#define {0}_SIGNAL_PROPERTIES_CHANGED  AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 3)\n""".format(capName, self.generated.definesIndx)

        self.generated.getValuesCases += "        		case {0}_GET_VALUE:\\\n".format(capName)
        self.generated.setValuesCases += "        		case {0}_SET_VALUE:\\\n".format(capName)
        self.generated.getAllCases += "        		case {0}_GET_ALL_VALUES:\\\n".format(capName)


    def generateIdentify(self, capName, language) :
        self.generated.identify += """\t\tcase {0}_GET_ALL_VALUES :
            *widgetType = {2};
            *language = {3};
            return &{1};
        case {0}_VERSION_PROPERTY :
            *widgetType = {2};
            *propType = PROPERTY_TYPE_VERSION;
            *language = {3};
            return &{1};            
        case {0}_STATES_PROPERTY :
            *widgetType = {2};
            *propType = PROPERTY_TYPE_STATES;
            *language = {3};
            return &{1};            
        case {0}_OPTPARAMS_PROPERTY :
            *widgetType = {2};
            *propType = PROPERTY_TYPE_OPTPARAMS;
            *language = {3};
            return &{1};\n""".format(capName, self.name, self.widgetType, language)
        self.generated.identifySignal += "\t\tcase {0}_SIGNAL_PROPERTIES_CHANGED :\n\t\t\treturn &{1};\n".format(capName, self.name)


    def generateTests(self, capName) : 
        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_GET_ALL_VALUES;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "\t\t\t\tcase AJ_REPLY_ID({0}_GET_ALL_VALUES):\\\n".format(capName)

    def generateMandatoryVariables (self) :
        self.generated.initFunction  += "\tinitialize{1}(&{0});\n".format(self.name, self.widgetName)
        self.setNumLanguages()
        self.setEnabled()
        self.generated.initFunction += "\n"

    def generateOptionalVariables (self) :
        self.setBgColor()
        self.setLabel()
        self.setHints() 

    def setNumLanguages (self) :
        self.generated.initFunction += "\t{0}.base.numLanguages = {1};\n".format(self.name, len(self.languageSet))
  
    def setEnabled (self) :
        enabled = self.element.enabled
        if hasattr(enabled, "attr") and "code" in enabled.attr and enabled.attr["code"] == "true" : 
            self.generated.initFunction += "\t{0}.base.getEnabled = {1};\n".format(self.name, enabled)
        else :
            enabledText = enabled.upper()
            if enabledText != "TRUE" and enabledText != "FALSE" :
                print "ERROR - The value {0} is not supported for enabled in {1}. Exiting".format(enabled, self.name)
                sys.exit(0)	
            self.generated.initFunction += "\tsetBaseEnabled(&{0}.base, {1});\n".format(self.name, enabledText)

    def setWritable (self) :
        writable = self.element.writable
        if hasattr(writable, "attr") and "code" in writable.attr and writable.attr["code"] == "true" : 
            self.generated.initFunction += "\t{0}.base.getWritable = {1};\n".format(self.name, writable)
        else :
            writableText = writable.upper()
            if writableText != "TRUE" and writableText != "FALSE" :
                print "ERROR - The value {0} is not supported for writable in {1}. Exiting".format(writable, self.name)
                sys.exit(0)	
            self.generated.initFunction += "\tsetBaseWritable(&{0}.base, {1});\n".format(self.name, writableText)

    def setBgColor (self) :
        if hasattr(self.element, "bgcolor") :
            bgColor = self.element.bgcolor
            if hasattr(bgColor, "attr") and "code" in bgColor.attr and bgColor.attr["code"] == "true" : 
                self.generated.initFunction += "\t{0}.base.optParams.getBgColor = {1};\n".format(self.name, bgColor)
            else :
                self.generated.initFunction += "\t{0}.base.optParams.bgColor = {1};\n".format(self.name, bgColor)
    		
    def setHints (self) :
        if not hasattr(self.element, "hints") :
            return;

        if isinstance(self.element.hints.hint, list) :
            hints = self.element.hints.hint
        else :
            hints = [self.element.hints.hint];

        self.generated.staticVars += "static const uint16_t {0}Hints[] = {1}".format(self.name, "{")                        
        for hint in hints:
            self.generated.staticVars += "{0}{1}, ".format(self.hintPrefix, hint.upper())                        
        self.generated.staticVars = self.generated.staticVars[:-2]
        self.generated.staticVars += "};\n"

        self.generated.initFunction += "\t{0}.base.optParams.hints = {0}Hints;\n".format(self.name)
        self.generated.initFunction += "\t{0}.base.optParams.numHints = {1};\n".format(self.name, len(hints))

    def setLabel (self, isMandatory = 0) :
        if isMandatory :
            self.setCodeOrValueString ("label", "label", "getLabel", "Label")    
        else :
            self.setCodeOrValueString ("label", "base.optParams.label", "base.optParams.getLabel", "Label")

    def setMessage (self) :
        self.setCodeOrValueString ("message", "message", "getMessage", "Message")

    def setUnitMeasure (self) :
        self.setCodeOrValueString ("unitMeasure", "optParams.unitOfMeasure", "optParams.getUnitMeasure", "UnitMeasure")

    def setLabelAction (self, labelActionType) :
        self.setCodeOrValueString (labelActionType, "optParams.{0}".format(labelActionType), "optParams.get{0}".format(labelActionType[0].upper() + labelActionType[1:]) , labelActionType.capitalize())

    def setCodeOrValueString (self, fieldName, variableName, codeVariableName, defineName, elementToUse = 0) :
 
        if elementToUse == 0 :
            element = self.element
        else :
            element = elementToUse

        if not hasattr(element, fieldName) :
            return;

        if isinstance(getattr(element, fieldName) , list) :
            fields = getattr(element, fieldName) 
        else :
            fields = [getattr(element, fieldName) ];

        if len(fields) == 1 and hasattr(fields[0], "attr") and "code" in fields[0].attr and fields[0].attr["code"] == "true" : 
            self.generated.initFunction += "\t{0}.{1} = {2};\n".format(self.name, codeVariableName, fields[0])
        elif len(fields) != len(self.languageSet) :
            print "ERROR - Missing a {1} or too many {1}s defined for {0}. Exiting".format(self.name, fieldName)
            sys.exit(0)
        else :
            self.generated.initFunction += "\t{0}.{1} = {0}{2};\n".format(self.name, variableName, defineName)

            fieldDefineStr = "static const char* const {0}{1}[] = {2}".format(self.name, defineName, "{")     
            for lang in self.languageSet :
                field = filter(lambda x: x.attr["language"] == lang, fields)
                if len(field) !=  1:
                    print "ERROR - No {0} is defined or multiple {0}s are defined for language: {1} in {2}. Exiting".format(fieldName, lang, self.name)
                    sys.exit(0)
                if hasattr(field[0], "attr") and "constant" in field[0].attr and field[0].attr["constant"] == "true" :
                    fieldDefineStr += "{0}, ".format(field[0])                        
                else:
                    fieldDefineStr += "\"{0}\", ".format(field[0])                        
            fieldDefineStr = fieldDefineStr[:-2] + "};\n"
            self.generated.staticVars += fieldDefineStr

    def setConstraintRange (self) :
        if not hasattr(self.element, "constraintRange") :
            return;

        constraintRange = self.element.constraintRange
        self.generated.initFunction += "\n"
        self.generated.staticVars += "static const {2} {0}ConstraintRangeMin = {1};\n".format(self.name, constraintRange.min, self.varType)
        self.generated.staticVars += "static const {2} {0}ConstraintRangeMax = {1};\n".format(self.name, constraintRange.max, self.varType)    
        self.generated.staticVars += "static const {2} {0}ConstraintRangeInc = {1};\n".format(self.name, constraintRange.increment, self.varType)  

        self.generated.initFunction += "\t{0}.optParams.constraintRangeDefined = TRUE;\n".format(self.name)                
        self.generated.initFunction += "\t{0}.optParams.constraintRange.minValue = &{0}ConstraintRangeMin;\n".format(self.name)
        self.generated.initFunction += "\t{0}.optParams.constraintRange.maxValue = &{0}ConstraintRangeMax;\n".format(self.name)
        self.generated.initFunction += "\t{0}.optParams.constraintRange.increment = &{0}ConstraintRangeInc;\n".format(self.name)

    def setConstraintList (self) :
        if not hasattr(self.element, "constraintVals") :
            return;

        constraintList = self.element.constraintVals
        self.generated.initFunction += "\n"

        if isinstance(constraintList.constraint, list) :
            constraints = constraintList.constraint
        else :
            constraints = [constraintList.constraint];

        if len(constraints) > 0:
            numConstraints = len(constraints)
            self.generated.staticVars += "static ConstraintList {0}ConstraintList[{1}];\n".format(self.name, numConstraints)    
            self.generated.initFunction += "\t{0}.optParams.numConstraints = {1};\n".format(self.name, numConstraints)
            self.generated.initFunction += "\t{0}.optParams.constraintList = {0}ConstraintList;\n".format(self.name)

            indx = 0
            for constraint in constraints:
                if self.varType == "char*" : 
                    self.generated.staticVars += "static const {3} {0}ConstraintValue{1} = \"{2}\";\n".format(self.name, indx, constraint.value, self.varType)    
                else :
                    self.generated.staticVars += "static const {3} {0}ConstraintValue{1} = {2};\n".format(self.name, indx, constraint.value, self.varType)    
                self.generated.initFunction += "\t{0}.optParams.constraintList[{1}].value = &{0}ConstraintValue{1};\n".format(self.name, indx)  
                self.setCodeOrValueString ("display", "optParams.constraintList[{0}].display".format(indx), "optParams.constraintList[{0}].getDisplay".format(indx), "Display{0}".format(indx), constraint)
                indx = indx + 1


