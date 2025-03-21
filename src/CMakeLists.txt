cmake_minimum_required(VERSION 3.27)

# Set the project name
project(circle)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include(CheckIncludeFiles)
include(CheckFunctionExists)

set(STDC_HEADERS 1)

# CIRCLE_MACINTOSH
# CIRCLE_ACORN
set(CIRCLE_UNIX 1)

set(TIME_WITH_SYS_TIME 1)
set(CIRCLE_CRYPT 1)
set(HAVE_STRUCT_IN_ADDR 1)
set(HAVE_INET_ADDR 1)

check_include_files("arpa/inet.h"  HAVE_ARPA_INET_H)
check_include_files("arpa/telnet.h"  HAVE_ARPA_TELNET_H)
check_include_files("assert.h"  HAVE_ASSERT_H)
check_include_files("crypt.h"  HAVE_CRYPT_H)
check_include_files("errno.h"  HAVE_ERRNO_H)
check_include_files("fcntl.h"  HAVE_FCNTL_H)
check_include_files("limits.h"  HAVE_LIMITS_H)
check_include_files("mcheck.h"  HAVE_MCHECK_H)
check_include_files("memory.h"  HAVE_MEMORY_H)
check_include_files("net/errno.h"  HAVE_NET_ERRNO_H)
check_include_files("netdb.h"  HAVE_NETDB_H)
check_include_files("netinet/in.h"  HAVE_NETINET_IN_H)
check_include_files("signal.h"  HAVE_SIGNAL_H)
check_include_files("string.h"  HAVE_STRING_H)
check_include_files("strings.h"  HAVE_STRINGS_H)
check_include_files("sys/fcntl.h"  HAVE_SYS_FCNTL_H)
check_include_files("sys/resource.h"  HAVE_SYS_RESOURCE_H)
check_include_files("sys/select.h"  HAVE_SYS_SELECT_H)
check_include_files("sys/socket.h"  HAVE_SYS_SOCKET_H)
check_include_files("sys/stat.h"  HAVE_SYS_STAT_H)
check_include_files("sys/time.h"  HAVE_SYS_TIME_H)
check_include_files("sys/types.h"  HAVE_SYS_TYPES_H)
check_include_files("sys/wait.h"  HAVE_SYS_WAIT_H)
check_include_files("sys/uio.h"  HAVE_SYS_UIO_H)
check_include_files("unistd.h"  HAVE_UNISTD_H)

check_function_exists(vprintf HAVE_VPRINTF)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)
check_function_exists(inet_addr HAVE_INET_ADDR)
check_function_exists(inet_aton HAVE_INET_ATON)
check_function_exists(select HAVE_SELECT)
check_function_exists(snprintf HAVE_SNPRINTF)
check_function_exists(strcasecmp HAVE_STRCASECMP)
check_function_exists(strdup HAVE_STRDUP)
check_function_exists(strerror HAVE_STRERROR)
check_function_exists(stricmp HAVE_STRICMP)
check_function_exists(strlcpy HAVE_STRLCPY)
check_function_exists(strncasecmp HAVE_STRNCASECMP)
check_function_exists(strnicmp HAVE_STRNICMP)
check_function_exists(strstr HAVE_STRSTR)
check_function_exists(vsnprintf HAVE_VSNPRINTF)

configure_file(conf.h.in.cmake conf.h)

# Global definitions
if(MSVC)
	# using Visual Studio C++
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
endif()

# circle itself
file(GLOB CIRCLE_SOURCES
	"*.h"
	"*.c"
)

add_executable(circle ${CIRCLE_SOURCES})

target_include_directories(circle PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(circle PUBLIC crypt)

if(MSVC)
	target_link_libraries(circle wsock32.lib)
	
	set_target_properties(circle PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/.."
	)
endif()