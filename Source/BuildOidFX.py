# BuildOidFX.py
#
# Terrain Demo build script
#
# Command line arguments:
#
# --nobuild : Don't clean, get latest update the version, or rebuild the project
#
# --noversionupdate: Don't update the version number
#
# --nocheckin: Don't do a check in after the build
#
# --nolabelupdate: Don't create a label
#
# --nodeploy: Don't copy the project to the deployment directory
#
# Bryan Robertson
# 09 June 2005

import os
import ProjectBuilder

projectName = "OidFX"
solution = "OidFX.sln"
baseDir = os.getcwd() 
sourceDir = baseDir
buildDir = "..\\bin"
versionFileName = baseDir + "\\OidFX\\Source\\Version.cpp"
depotLocation = "//depot/OidFX/..."
deployDir = "C:\\Documents and Settings\\All Users\\Documents\\Shared Builds\\OidFX"
cleanConfigs = "Debug","Release"

builder = ProjectBuilder.ProjectBuilder \
                ( projectName, solution, sourceDir, buildDir, versionFileName, \
                  depotLocation, deployDir, cleanConfigs )



                                          
