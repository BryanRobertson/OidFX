# ProjectBuilder.py
#
# Generic project building functions and classes
#
# Bryan Robertson
# 09 June 2005

import os
import shutil
import string
import sys
import datetime
import os.path

#Variables used when building a project
p4 = "p4"
devenv = "devenv"

class VersionInfo:
    revision = 0
    major = 0
    minor = 0
    build = 0
    offset = 0
    buildType = ""
    versionString = ""

    def __init__(self):
        pass
    

#Class: LogWriter
#Class used to redirect output to a text file
#while still printing it to stdout
class LogWriter:

    log = 0

    def __init__(self):
        self.log = file ( "buildlog.txt", "w" )

    def __del__(self):
        self.log.close()
    
    def write ( self, textToWrite ):
        self.log.write ( textToWrite )
        sys.__stdout__.write ( textToWrite )
#end class LogWriter


#Function: Run
#Run an external program
def Run ( program ):
    resultFile = os.popen ( program, "r")
    result = 0
    resultLines = resultFile.readlines()

    for line in resultLines:
        print ( line )

    result = resultFile.close()

    if result != None:
        raise Exception ( program, " returned ", result )
#end Function: Run


def GetVersionNumber(fileName, version):

    versionFile = file ( fileName )

    #Skip lines until we find the part we're meant to be writing to
    while ( versionFile.readline().find("//Begin build script maintained code:") == -1):
        pass

    #Skip the first line of the version declaration
    versionFile.readline ( )

    version.offset = versionFile.tell()
    version.revision = int(string.split(versionFile.readline(),",")[0], 10)
    version.major = int(string.split(versionFile.readline(),",")[0], 10)
    version.minor = int(string.split(versionFile.readline(),",")[0], 10)
    version.build = int(string.split(versionFile.readline(),",")[0], 10)
    version.buildType = string.split(versionFile.readline(),",")[0]

    currdate = datetime.date.today()
    version.versionString = ("%d-%02d-%02d-Version-%d.%d.%d.%d%s") % ( currdate.year, currdate.month, currdate.day,\
                                                                version.revision, version.major, version.minor,\
                                                                version.build, version.buildType )

    versionFile.close()


#Class: UpdateVersionNumber
#Function used to update the version number of the project
def UpdateVersionNumber(fileName):

    try:
        print ( "Checking out Version.cpp\n" )
        Run ( "%s edit \"%s\"" % (p4, fileName) )
        
        version = VersionInfo

        GetVersionNumber(fileName, version)

        #Update version number
        if ( (version.build+1) > 65535 ):

            version.build = 0
            if ( (version.minor+1) > 65535 ):

                version.minor = 0
                if ((version.major+1) > 65535 ):
                    version.major = 0
                    version.revision = version.revision + 1

                else:
                    version.major = version.major + 1
                    
            else:
                version.minor = version.minor + 1

        else:
            version.build = version.build + 1


        currdate = datetime.date.today()
        version.versionString = ("%d-%02d-%02d-Version-%d.%d.%d.%d%s") % ( currdate.year, currdate.month, currdate.day,\
                                                                    version.revision, version.major, version.minor,\
                                                                    version.build, version.buildType )

        #Now write version number back into the file
        print ( "Updating version to %d.%d.%d.%d%s" % ( version.revision, version.major, version.minor, \
                                                        version.build, version.buildType ) )

        versionFile = file ( fileName, "a" )
        versionFile.truncate ( version.offset )
        versionFile.write ( "%d, //Revision\n" % (version.revision) )
        versionFile.write ( "%d, //Major\n" % (version.major) )
        versionFile.write ( "%d, //Minor\n" % (version.minor) )
        versionFile.write ( "%d, //Build\n" % (version.build) )
        versionFile.write ( "%s, //BuildType\n" % (version.buildType) )

        versionFile.write ( "\"%s\"\n" % (version.versionString) )
        versionFile.write ( ");\n//End\n" )

        versionFile.close()

    except Exception, exp:
        print ( "Build failed, %s" % ( str(exp) ) )
        Run ( "%s revert \"%s\"" % (p4, fileName) )
        raise
        
#End function: UpdateVersionNumber


#CommandLineArgsContains
def CommandLineArgsContain( searchString ):
    for str in sys.argv:
        if ( str == searchString ):
            return True

    return False


#Class: ProjectBuilder
#Class used to build a project
class ProjectBuilder:

    m_projectName = ""
    m_buildDir = ""
    m_sourceDir = ""
    m_solution = ""
    m_versionFileNames = ""
    m_depotLocation = ""
    m_deployDir = ""
    m_buildLabel = ""
    m_cleanConfigs = 0
    
    #Constructor
    def __init__( self, \
                  projectName,
                  solution, \
                  sourceDir, \
                  buildDir, \
                  versionFileNames, \
                  depotLocation, \
                  deployDir, \
                  cleanConfigs ):
        
        logWriter = LogWriter()
        sys.stdout = logWriter

        #Init variables
        self.m_projectName = projectName
        self.m_buildDir  = buildDir
        self.m_sourceDir = sourceDir
        self.m_solution = solution
        self.m_versionFileNames = versionFileNames
        self.m_depotLocation = depotLocation
        self.m_deployDir = deployDir
        self.m_cleanConfigs = cleanConfigs

        try:

            #Change to the source directory
            os.chdir( sourceDir )

            if not CommandLineArgsContain("--nobuild"):
                self.Clean()

                try:
                    self.GetLatest()
                except:
                    print ( "Error, couldn't get latest from source control!" )

                if not CommandLineArgsContain ( "--noversionupdate" ):
                    UpdateVersionNumber(versionFileNames)
                    
                self.Build()
            
            if not CommandLineArgsContain("--nocheckin"):
                try:
                    self.CheckIn()
                except:
                    print ( "Error, couldn't check files in!" )

            if not CommandLineArgsContain("--nolabelupdate"):
                self.UpdateLabel()

            if not CommandLineArgsContain("--nodeploy"):
                self.Deploy()

        except Exception, exp:
            print ( "Build failed, %s" % ( str(exp) ) )
            #Revert the version file
            Run ( "%s revert \"%s\"" % (p4, versionFileNames) )
            raise

    #Clean
    def Clean(self):
        print ( "Cleaning projects" )
        print ( "Deleting incremental linker files" )
        os.system ( "del " + self.m_buildDir + "\\*.ilk\"" )
        os.system ( "del " + self.m_buildDir + "\\*.pdb\"" )
        
        for config in self.m_cleanConfigs:
            print ( "Cleaning %s, configuration %s\n" % (self.m_solution, config))
            Run ( "%s /clean %s %s" % (devenv, config, self.m_solution) )

    #Clean
    def GetLatest(self):
        print ( "Getting latest from source control" )
        Run ( "%s sync" % (p4))
        pass

    #Build
    def Build(self):
        print ( "Building %s, configuration %s\n" % (self.m_solution, "Release"))
        print ( "%s /build %s %s\n" % (devenv, "Release", self.m_solution))
        Run ( "%s /build %s %s" % (devenv, "Release", self.m_solution) )
     
    #CheckIn
    def CheckIn(self):
         Run ( "%s submit %s" % (p4, self.m_depotLocation) )

    #UpdateLabel
    def UpdateLabel(self):

        #Generate a label from the version number
        version = VersionInfo
        GetVersionNumber(self.m_versionFileNames, version)

        currdate = datetime.date.today()
        m_buildLabel = version.versionString
        
        buildLabel = self.m_projectName + "-" + version.versionString
        Run ( "%s label %s" % (p4,buildLabel) )
        Run ( "%s labelsync -l %s %s" % (p4, buildLabel, self.m_depotLocation) )

    #Deploy
    def Deploy(self):

        version = VersionInfo
        GetVersionNumber(self.m_versionFileNames, version)

        print ( "del " + self.m_buildDir + "\\*.ilk\"" )
        os.system ( "del " + self.m_buildDir + "\\*.ilk\"" )
        print ( "del " + self.m_buildDir + "\\*.pdb\"" )
        os.system ( "del " + self.m_buildDir + "\\*.pdb\"" )
        
        print ( "Copying build output to " + self.m_deployDir + "\\" + version.versionString + "\n" )

        if os.path.exists ( self.m_deployDir ) != True :
            os.mkdirs( self.m_deployDir )
            
        shutil.copytree ( self.m_buildDir, self.m_deployDir + "\\" + version.versionString )


#End Class ProjectBuilder



