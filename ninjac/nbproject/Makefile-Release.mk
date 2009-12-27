#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=g77.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/tokenizer.o \
	${OBJECTDIR}/loops.o \
	${OBJECTDIR}/variable.o \
	${OBJECTDIR}/conditional.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/parser.o \
	${OBJECTDIR}/ninjacexcept.o \
	${OBJECTDIR}/assignment.o \
	${OBJECTDIR}/block.o \
	${OBJECTDIR}/exprstmt.o \
	${OBJECTDIR}/operators.o \
	${OBJECTDIR}/functions.o \
	${OBJECTDIR}/globals.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/MinGW-Windows/ninjac.exe

dist/Release/MinGW-Windows/ninjac.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/MinGW-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ninjac ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/tokenizer.o: nbproject/Makefile-${CND_CONF}.mk tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/tokenizer.o tokenizer.cpp

${OBJECTDIR}/loops.o: nbproject/Makefile-${CND_CONF}.mk loops.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/loops.o loops.cpp

${OBJECTDIR}/variable.o: nbproject/Makefile-${CND_CONF}.mk variable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/variable.o variable.cpp

${OBJECTDIR}/conditional.o: nbproject/Makefile-${CND_CONF}.mk conditional.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/conditional.o conditional.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/parser.o: nbproject/Makefile-${CND_CONF}.mk parser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser.o parser.cpp

${OBJECTDIR}/ninjacexcept.o: nbproject/Makefile-${CND_CONF}.mk ninjacexcept.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ninjacexcept.o ninjacexcept.cpp

${OBJECTDIR}/assignment.o: nbproject/Makefile-${CND_CONF}.mk assignment.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/assignment.o assignment.cpp

${OBJECTDIR}/block.o: nbproject/Makefile-${CND_CONF}.mk block.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/block.o block.cpp

${OBJECTDIR}/exprstmt.o: nbproject/Makefile-${CND_CONF}.mk exprstmt.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/exprstmt.o exprstmt.cpp

${OBJECTDIR}/operators.o: nbproject/Makefile-${CND_CONF}.mk operators.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/operators.o operators.cpp

${OBJECTDIR}/functions.o: nbproject/Makefile-${CND_CONF}.mk functions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/functions.o functions.cpp

${OBJECTDIR}/globals.o: nbproject/Makefile-${CND_CONF}.mk globals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/globals.o globals.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/MinGW-Windows/ninjac.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
