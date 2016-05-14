##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=graphAlgorithms
ConfigurationName      :=Release
WorkspacePath          :=C:/tcs
ProjectPath            :=C:/tcs/graphAlgorithms
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=MADAN KAPOOR
Date                   :=14/05/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW2/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW2/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="graphAlgorithms.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW2/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW2/bin/ar.exe rcu
CXX      := C:/MinGW2/bin/g++.exe
CC       := C:/MinGW2/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW2/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/GraphAlgorithms.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GraphAlgorithms.cpp$(ObjectSuffix): GraphAlgorithms.cpp $(IntermediateDirectory)/GraphAlgorithms.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/tcs/graphAlgorithms/GraphAlgorithms.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphAlgorithms.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphAlgorithms.cpp$(DependSuffix): GraphAlgorithms.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GraphAlgorithms.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphAlgorithms.cpp$(DependSuffix) -MM "GraphAlgorithms.cpp"

$(IntermediateDirectory)/GraphAlgorithms.cpp$(PreprocessSuffix): GraphAlgorithms.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphAlgorithms.cpp$(PreprocessSuffix) "GraphAlgorithms.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


