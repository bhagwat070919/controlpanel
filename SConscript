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

import os

Import('env')

env['_ALLJOYN_CONTROLPANEL_'] = True

# Make config library and header file paths available to the global environment
env.Append(LIBPATH = '$DISTDIR/controlpanel/lib');
env.Append(CPPPATH = '$DISTDIR/controlpanel/inc');

if not env.has_key('_ALLJOYN_ABOUT_') and os.path.exists('../about/SConscript'):
    env.SConscript('../about/SConscript')

if not env.has_key('_ALLJOYN_NOTIFICATION_') and os.path.exists('../notification/SConscript'):
    env.SConscript('../notification/SConscript')

if 'cpp' in env['bindings'] and not env.has_key('_ALLJOYNCORE_') and os.path.exists('../../alljoyn_core/SConscript'):
   env.SConscript('../../alljoyn_core/SConscript')

if 'java' in env['bindings'] and not env.has_key('_ALLJOYN_JAVA_') and os.path.exists('../../alljoyn_java/SConscript'):
   env.SConscript('../../alljoyn_java/SConscript')

cpsenv = env.Clone()

for b in cpsenv['bindings']:
    if os.path.exists('%s/SConscript' % b):
        cpsenv.VariantDir('$OBJDIR/%s' % b, b, duplicate = 0)

cpsenv.SConscript(['$OBJDIR/%s/SConscript' % b for b in env['bindings'] if os.path.exists('%s/SConscript' % b) ],
                  exports = ['cpsenv'])
