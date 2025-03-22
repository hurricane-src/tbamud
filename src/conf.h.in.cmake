/* src/conf.h.in.  Generated automatically from configure.in by autoheader.  */

#ifndef _CONF_H_
#define _CONF_H_

#include <limits.h>

// counter-productive for my current plan
#define DISPLAY_MOTD_PROMPT 0
#define DISPLAY_NEWS_PROMPT 0
#define DISPLAY_HAS_DIMENSIONS 0
#define LOOK_AT_ROOM_HAS_DESCRIPTOR 1

/* Define to empty if the keyword does not work.  */
//#cmakedefine const 1

/* Define if you don't have vprintf but do have _doprnt.  */
//#cmakedefine HAVE_DOPRNT 1

/* Define if you have <sys/wait.h> that is POSIX.1 compatible.  */
#cmakedefine HAVE_SYS_WAIT_H 1

/* Define if you have the vprintf function.  */
#cmakedefine HAVE_VPRINTF 1

/* Define to `int' if <sys/types.h> doesn't define.  */
#cmakedefine pid_t 1

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
//#cmakedefine size_t 1

/* Define if you have the ANSI C header files.  */
#cmakedefine STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#cmakedefine TIME_WITH_SYS_TIME 1

/* Define if we're compiling CircleMUD under any type of UNIX system.  */
#cmakedefine CIRCLE_UNIX 1

/* Define if the system is capable of using crypt() to encrypt.  */
#cmakedefine CIRCLE_CRYPT 1

/* Define if we don't have proper support for the system's crypt().  */
#cmakedefine HAVE_UNSAFE_CRYPT 1

/* Define is the system has struct in_addr.  */
#cmakedefine HAVE_STRUCT_IN_ADDR 1

/* Define to `int' if <sys/socket.h> doesn't define.  */
//#cmakedefine socklen_t 1

/* Define to `int' if <sys/types.h> doesn't define.  */
//#cmakedefine ssize_t 1

/* Define if you have the gettimeofday function.  */
#cmakedefine HAVE_GETTIMEOFDAY 1

/* Define if you have the inet_addr function.  */
#cmakedefine HAVE_INET_ADDR 1

/* Define if you have the inet_aton function.  */
#cmakedefine HAVE_INET_ATON 1

/* Define if you have the select function.  */
#cmakedefine HAVE_SELECT 1

/* Define if you have the snprintf function.  */
#cmakedefine HAVE_SNPRINTF 1

/* Define if you have the strcasecmp function.  */
#cmakedefine HAVE_STRCASECMP 1

/* Define if you have the strdup function.  */
#cmakedefine HAVE_STRDUP 1

/* Define if you have the strerror function.  */
#cmakedefine HAVE_STRERROR 1

/* Define if you have the stricmp function.  */
#cmakedefine HAVE_STRICMP 1

/* Define if you have the strlcpy function.  */
#cmakedefine HAVE_STRLCPY 1

/* Define if you have the strncasecmp function.  */
#cmakedefine HAVE_STRNCASECMP 1

/* Define if you have the strnicmp function.  */
#cmakedefine HAVE_STRNICMP 1

/* Define if you have the strstr function.  */
#cmakedefine HAVE_STRSTR 1

/* Define if you have the vsnprintf function.  */
#cmakedefine HAVE_VSNPRINTF 1

/* Define if you have the <arpa/inet.h> header file.  */
#cmakedefine HAVE_ARPA_INET_H 1

/* Define if you have the <arpa/telnet.h> header file.  */
#cmakedefine HAVE_ARPA_TELNET_H 1

/* Define if you have the <assert.h> header file.  */
#cmakedefine HAVE_ASSERT_H 1

/* Define if you have the <crypt.h> header file.  */
#cmakedefine HAVE_CRYPT_H 1

/* Define if you have the <errno.h> header file.  */
#cmakedefine HAVE_ERRNO_H 1

/* Define if you have the <fcntl.h> header file.  */
#cmakedefine HAVE_FCNTL_H 1

/* Define if you have the <limits.h> header file.  */
#cmakedefine HAVE_LIMITS_H 1

/* Define if you have the <mcheck.h> header file.  */
#cmakedefine HAVE_MCHECK_H 1

/* Define if you have the <memory.h> header file.  */
#cmakedefine HAVE_MEMORY_H 1

/* Define if you have the <net/errno.h> header file.  */
#cmakedefine HAVE_NET_ERRNO_H 1

/* Define if you have the <netdb.h> header file.  */
#cmakedefine HAVE_NETDB_H 1

/* Define if you have the <netinet/in.h> header file.  */
#cmakedefine HAVE_NETINET_IN_H 1

/* Define if you have the <signal.h> header file.  */
#cmakedefine HAVE_SIGNAL_H 1

/* Define if you have the <string.h> header file.  */
#cmakedefine HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
#cmakedefine HAVE_STRINGS_H 1

/* Define if you have the <sys/fcntl.h> header file.  */
#cmakedefine HAVE_SYS_FCNTL_H 1

/* Define if you have the <sys/resource.h> header file.  */
#cmakedefine HAVE_SYS_RESOURCE_H 1

/* Define if you have the <sys/select.h> header file.  */
#cmakedefine HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/socket.h> header file.  */
#cmakedefine HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/stat.h> header file.  */
#cmakedefine HAVE_SYS_STAT_H 1

/* Define if you have the <sys/time.h> header file.  */
#cmakedefine HAVE_SYS_TIME_H 1

/* Define if you have the <sys/types.h> header file.  */
#cmakedefine HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/uio.h> header file.  */
#cmakedefine HAVE_SYS_UIO_H 1

/* Define if you have the <unistd.h> header file.  */
#cmakedefine HAVE_UNISTD_H 1

/* Define if you have the malloc library (-lmalloc).  */
#cmakedefine HAVE_LIBMALLOC 1

/* Check for a prototype to accept. */
#cmakedefine NEED_ACCEPT_PROTO 1

/* Check for a prototype to atoi. */
#cmakedefine NEED_ATOI_PROTO 1

/* Check for a prototype to atol. */
#cmakedefine NEED_ATOL_PROTO 1

/* Check for a prototype to bind. */
#cmakedefine NEED_BIND_PROTO 1

/* Check for a prototype to bzero. */
#cmakedefine NEED_BZERO_PROTO 1

/* Check for a prototype to chdir. */
#cmakedefine NEED_CHDIR_PROTO 1

/* Check for a prototype to close. */
#cmakedefine NEED_CLOSE_PROTO 1

/* Check for a prototype to crypt. */
#cmakedefine NEED_CRYPT_PROTO 1

/* Check for a prototype to fclose. */
#cmakedefine NEED_FCLOSE_PROTO 1

/* Check for a prototype to fcntl. */
#cmakedefine NEED_FCNTL_PROTO 1

/* Check for a prototype to fflush. */
#cmakedefine NEED_FFLUSH_PROTO 1

/* Check for a prototype to fprintf. */
#cmakedefine NEED_FPRINTF_PROTO 1

/* Check for a prototype to fputc. */
#cmakedefine NEED_FPUTC_PROTO 1

/* Check for a prototype to fputs. */
#cmakedefine NEED_FPUTS_PROTO 1

/* Check for a prototype to fread. */
#cmakedefine NEED_FREAD_PROTO 1

/* Check for a prototype to fscanf. */
#cmakedefine NEED_FSCANF_PROTO 1

/* Check for a prototype to fseek. */
#cmakedefine NEED_FSEEK_PROTO 1

/* Check for a prototype to fwrite. */
#cmakedefine NEED_FWRITE_PROTO 1

/* Check for a prototype to getpeername. */
#cmakedefine NEED_GETPEERNAME_PROTO 1

/* Check for a prototype to getpid. */
#cmakedefine NEED_GETPID_PROTO 1

/* Check for a prototype to getrlimit. */
#cmakedefine NEED_GETRLIMIT_PROTO 1

/* Check for a prototype to getsockname. */
#cmakedefine NEED_GETSOCKNAME_PROTO 1

/* Check for a prototype to gettimeofday. */
#cmakedefine NEED_GETTIMEOFDAY_PROTO 1

/* Check for a prototype to htonl. */
#cmakedefine NEED_HTONL_PROTO 1

/* Check for a prototype to htons. */
#cmakedefine NEED_HTONS_PROTO 1

/* Check for a prototype to inet_addr. */
#cmakedefine NEED_INET_ADDR_PROTO 1

/* Check for a prototype to inet_aton. */
#cmakedefine NEED_INET_ATON_PROTO 1

/* Check for a prototype to inet_ntoa. */
#cmakedefine NEED_INET_NTOA_PROTO 1

/* Check for a prototype to listen. */
#cmakedefine NEED_LISTEN_PROTO 1

/* Check for a prototype to ntohl. */
#cmakedefine NEED_NTOHL_PROTO 1

/* Check for a prototype to perror. */
#cmakedefine NEED_PERROR_PROTO 1

/* Check for a prototype to printf. */
#cmakedefine NEED_PRINTF_PROTO 1

/* Check for a prototype to qsort. */
#cmakedefine NEED_QSORT_PROTO 1

/* Check for a prototype to read. */
#cmakedefine NEED_READ_PROTO 1

/* Check for a prototype to remove. */
#cmakedefine NEED_REMOVE_PROTO 1

/* Check for a prototype to rewind. */
#cmakedefine NEED_REWIND_PROTO 1

/* Check for a prototype to select. */
#cmakedefine NEED_SELECT_PROTO 1

/* Check for a prototype to setitimer. */
#cmakedefine NEED_SETITIMER_PROTO 1

/* Check for a prototype to setrlimit. */
#cmakedefine NEED_SETRLIMIT_PROTO 1

/* Check for a prototype to setsockopt. */
#cmakedefine NEED_SETSOCKOPT_PROTO 1

/* Check for a prototype to snprintf. */
#cmakedefine NEED_SNPRINTF_PROTO 1

/* Check for a prototype to socket. */
#cmakedefine NEED_SOCKET_PROTO 1

/* Check for a prototype to sprintf. */
#cmakedefine NEED_SPRINTF_PROTO 1

/* Check for a prototype to sscanf. */
#cmakedefine NEED_SSCANF_PROTO 1

/* Check for a prototype to strcasecmp. */
#cmakedefine NEED_STRCASECMP_PROTO 1

/* Check for a prototype to strdup. */
#cmakedefine NEED_STRDUP_PROTO 1

/* Check for a prototype to strerror. */
#cmakedefine NEED_STRERROR_PROTO 1

/* Check for a prototype to stricmp. */
#cmakedefine NEED_STRICMP_PROTO 1

/* Check for a prototype to strlcpy. */
#cmakedefine NEED_STRLCPY_PROTO 1

/* Check for a prototype to strncasecmp. */
#cmakedefine NEED_STRNCASECMP_PROTO 1

/* Check for a prototype to strnicmp. */
#cmakedefine NEED_STRNICMP_PROTO 1

/* Check for a prototype to system. */
#cmakedefine NEED_SYSTEM_PROTO 1

/* Check for a prototype to time. */
#cmakedefine NEED_TIME_PROTO 1

/* Check for a prototype to unlink. */
#cmakedefine NEED_UNLINK_PROTO 1

/* Check for a prototype to vsnprintf. */
#cmakedefine NEED_VSNPRINTF_PROTO 1

/* Check for a prototype to write. */
#cmakedefine NEED_WRITE_PROTO 1


#endif /* _CONF_H_ */
