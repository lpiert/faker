# 设置cmake版本范围
cmake_minimum_required(VERSION 3.10)
# 设置solution
project(Follow C CXX)
# 设置工程名
SET(PROJECT_OF OrderFollow)
SET(PROJECT_OF_UT OrderFollowUt)

SET(CMAKE_BUILD_TYPE debug)
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

#设置路径变量
SET(MYPRJ_DIR ${CMAKE_SOURCE_DIR}/../../../../)
SET(ROOT_DIR ${CMAKE_SOURCE_DIR}/../../)
set(COM_DIR D:/1-workspace/new/com)
set(API_DIR D:/1-workspace/new/lib)

# version
##########################################################################################
# com
set(VerBoost 1.65.1)
set(VerEco 2.1.0)
set(VerZlib 1.2.11)
set(VerMysql 6.1.11)
set(VerProtobuf 3.5.1)
SET(BoostDir ${COM_DIR}/boost_${VerBoost})
SET(ZlibDir ${COM_DIR}/zlib_${VerZlib})
SET(MysqlDir ${COM_DIR}/mysql_${VerMysql})
SET(ProtobufDir ${COM_DIR}/protobuf_${VerProtobuf})
# lib
SET(TmiDir ${API_DIR}/tmi_1.2.0)
SET(MarketDir ${API_DIR}/market_1.1.0)
SET(EcoDir ${API_DIR}/eco_${VerEco})


##########################################################################################
# add source files
AUX_SOURCE_DIRECTORY(${ROOT_DIR}/api CPP_FILES)
AUX_SOURCE_DIRECTORY(${ROOT_DIR}/api/protocol CPP_FILES)
AUX_SOURCE_DIRECTORY(${ROOT_DIR}/src/OrderFollow CPP_FILES)
AUX_SOURCE_DIRECTORY(${ROOT_DIR}/src/OrderFollow/meta CPP_FILES)
AUX_SOURCE_DIRECTORY(${EcoDir}/eco/proto CPP_FILES)
AUX_SOURCE_DIRECTORY(${TmiDir}/tmi/esunny CPP_FILES)
AUX_SOURCE_DIRECTORY(${TmiDir}/tmi/shzd CPP_FILES)
# AUX_SOURCE_DIRECTORY(${TmiDir}/tmi/src CPP_FILES)
SET(CPP_FILES 
${CPP_FILES} 
${TmiDir}/tmi/src/Trader.cpp
${TmiDir}/tmi/src/TraderEsunny3.cpp
${TmiDir}/tmi/src/TraderEsunny9.cpp
${TmiDir}/tmi/src/TraderShzd.cpp
${TmiDir}/tmi/src/TraderAccess.cpp
)


##########################################################################################
# add include path
INCLUDE_DIRECTORIES (${ROOT_DIR})
INCLUDE_DIRECTORIES (${ROOT_DIR}/api)
INCLUDE_DIRECTORIES (${ROOT_DIR}/api/protocol)
INCLUDE_DIRECTORIES (${ROOT_DIR}/src/OrderFollow)
INCLUDE_DIRECTORIES (${ROOT_DIR}/src/OrderFollow/meta)
# com dir
INCLUDE_DIRECTORIES (${COM_DIR})
INCLUDE_DIRECTORIES (${BoostDir})
INCLUDE_DIRECTORIES (${ZlibDir})
INCLUDE_DIRECTORIES (${MysqlDir})
INCLUDE_DIRECTORIES (${ProtobufDir})
# lib dir
INCLUDE_DIRECTORIES (${EcoDir})
INCLUDE_DIRECTORIES (${EcoDir}/eco/proto)
INCLUDE_DIRECTORIES (${TmiDir})
INCLUDE_DIRECTORIES (${TmiDir}/tmi)
INCLUDE_DIRECTORIES (${TmiDir}/tmi/src)
INCLUDE_DIRECTORIES (${MarketDir})


##########################################################################################
# add library path
# com dir
LINK_DIRECTORIES(${BoostDir}/boost/lib_vc141)
LINK_DIRECTORIES(${ZlibDir}/zlib/lib_vc141)
LINK_DIRECTORIES(${MysqlDir}/mysql/lib_win32/)
LINK_DIRECTORIES(${ProtobufDir}/google/protobuf/lib_vc141/${CMAKE_BUILD_TYPE})
LINK_DIRECTORIES(${COM_DIR}/counter/shzd/lib_win32)
LINK_DIRECTORIES(${COM_DIR}/counter/access/lib_win32)
LINK_DIRECTORIES(${COM_DIR}/counter/esunny/trade3/lib_win32)
LINK_DIRECTORIES(${COM_DIR}/counter/esunny/trade9/lib_win32)
LINK_DIRECTORIES(${EcoDir}/eco/lib_vc141)
LINK_DIRECTORIES(${TmiDir}/tmi/lib_vc141)
LINK_DIRECTORIES(${TmiDir}/type/lib_vc141)
LINK_DIRECTORIES(${MarketDir}/market/lib_vc141)


##########################################################################################
# SET(CPPFLAGS "${CPPFLAGS} /utf-8")
# SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} ${CPPFLAGS}")
if (MSVC)
    SET(CMAKE_CXX_FLAGS "/MP /EHsc /utf-8 ")
    add_compile_options(/W3 /wd4828 /wd4530 /wd4146 )
    add_definitions(-DWIN32 -DCTP_FOPT_6311 -D_CRT_SECURE_NO_WARNINGS)
else()
endif()


##########################################################################################
ADD_EXECUTABLE (${PROJECT_OF} ${CPP_FILES})

##########################################################################################
# add target depends
TARGET_LINK_LIBRARIES (${PROJECT_OF} libprotobuf libprotobuf-lite libprotoc libmysql
ShZdFutureTradeApi ForeignTradeApi iTapTradeAPI DAApi CtpTiEs3)







