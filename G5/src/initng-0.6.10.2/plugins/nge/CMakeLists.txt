INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR} )

ADD_LIBRARY(nge MODULE initng_nge.c)
TARGET_LINK_LIBRARIES(nge initng)
INSTALL_TARGETS(${LIB_INSTALL_DIR}/initng nge)

ADD_LIBRARY(ngeclient SHARED libngeclient.c)
SET_TARGET_PROPERTIES(ngeclient PROPERTIES VERSION 0.0.0 SOVERSION 0)
INSTALL_TARGETS(${LIB_INSTALL_DIR} ngeclient)

ADD_EXECUTABLE(nge_bin nge.c)
TARGET_LINK_LIBRARIES(nge_bin ngeclient)
SET_TARGET_PROPERTIES(nge_bin PROPERTIES OUTPUT_NAME nge)
INSTALL_TARGETS(${SBIN_INSTALL_DIR} nge_bin)

ADD_EXECUTABLE(nge_raw nge_raw.c)
TARGET_LINK_LIBRARIES(nge_raw ngeclient)
INSTALL_TARGETS(${SBIN_INSTALL_DIR} nge_raw)

INSTALL_FILES(${INCLUDE_INSTALL_DIR}/initng FILES libngeclient.h initng_nge.h)

ADD_LIBRARY(ngeclient_static STATIC libngeclient.c)
