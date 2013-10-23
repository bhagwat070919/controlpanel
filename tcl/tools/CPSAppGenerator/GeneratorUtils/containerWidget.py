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
import propertyWidget as pw
import listPropertyWidget as lpw
import actionWidget as aw
import labelWidget as lw
import commonWidget as common

class Container (common.Widget):

    def __init__(self, generated, containerElement, parentObjectPath, languageSetName, isRoot = 0) :
        common.Widget.__init__(self, generated, containerElement, parentObjectPath, languageSetName)
        self.isRoot = isRoot
        self.widgetName = "ContainerWidget"
        self.widgetType = "WIDGET_TYPE_CONTAINER"
        self.securedInterfaceName = "SecuredContainerInterfaces"
        self.nonSecuredInterfaceName = "ContainerInterfaces"
        self.hintPrefix = "LAYOUT_HINT_"
        if isRoot:
            self.objectPathSuffix = ""  

    def generate(self) :
        common.Widget.generate(self)
        self.generateChildElements()

    def generateChildElements (self) :
        elements = self.element.elements.sub_nodes

        for element in elements:
            elementType = element._name
            self.generated.initFunction += "\n"

            if elementType == "action" :
                action = aw.Action(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                action.generate()
            elif elementType == "container" :
                container = Container(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                container.generate()
            elif elementType == "scalarProperty" or elementType == "stringProperty" or elementType == "booleanProperty" :
                propertyW = pw.Property(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                propertyW.generate()
            elif elementType == "dateProperty" or elementType == "timeProperty" :
                propertyW = pw.Property(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                propertyW.generate()
            elif elementType == "labelProperty" :
                label = lw.Label(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                label.generate()
            elif elementType == "listProperty" :
                listProp = lpw.ListProperty(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                listProp.generate()
            else :
                print "ERROR - This type is not supported. Exiting " + elementType
                sys.exit(0)




