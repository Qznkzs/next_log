/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is the configure head file for this library.
 * Created on: 2015-07-30
 */

#ifndef _ELOG_CFG_H_
#define _ELOG_CFG_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*              *ELOG_BASIC_CONFIG*             */

/* enable log output. default open this macro */
#define ELOG_OUTPUT_ENABLE
/* enable terminal output. default open this macro */
#define ELOG_TERMINAL_ENABLE
/* enable log write file. default open this macro */
#define ELOG_FILE_ENABLE
/* enable flush file cache. default open this macro */
#define ELOG_FILE_FLUSH_CACHE_ENABLE

/* setting static output log level */
#define ELOG_OUTPUT_LVL                      ELOG_LVL_VERBOSE

/* enable assert check */
#define ELOG_ASSERT_ENABLE
/* buffer size for every line's log */
#define ELOG_LINE_BUF_SIZE                   512
/* output line number max length */
#define ELOG_LINE_NUM_MAX_LEN                5
/* output filter's tag max length */
#define ELOG_FILTER_TAG_MAX_LEN              16
/* output filter's keyword max length */
#define ELOG_FILTER_KW_MAX_LEN               16
/* output filter's tag level max num */
#define ELOG_FILTER_TAG_LVL_MAX_NUM          5
/* output newline sign */
#define ELOG_NEWLINE_SIGN                    "\n"
/* enable log color */
#define ELOG_COLOR_ENABLE
/* enable asynchronous output mode */
#define ELOG_ASYNC_OUTPUT_ENABLE

/* the highest output level for async mode, other level will sync output */
#define ELOG_ASYNC_OUTPUT_LVL                ELOG_LVL_DEBUG

/* buffer size for asynchronous output mode */
#define ELOG_ASYNC_OUTPUT_BUF_SIZE           (ELOG_LINE_BUF_SIZE * 50)
/* each asynchronous output's log which must end with newline sign */
//#define ELOG_ASYNC_LINE_OUTPUT
/* asynchronous output mode using POSIX pthread implementation */
#define ELOG_ASYNC_OUTPUT_USING_PTHREAD

/*              *ELOG_BASIC_CONFIG*             */


/*              +ELOG_COMMON_CONFIG+            */
/* output log's level */
#define ELOG_LVL_ASSERT                      0
#define ELOG_LVL_ERROR                       1
#define ELOG_LVL_WARN                        2
#define ELOG_LVL_INFO                        3
#define ELOG_LVL_DEBUG                       4
#define ELOG_LVL_VERBOSE                     5

/* the output silent level and all level for filter setting */
#define ELOG_FILTER_LVL_SILENT               ELOG_LVL_ASSERT
#define ELOG_FILTER_LVL_ALL                  ELOG_LVL_VERBOSE

/* output log's level total number */
#define ELOG_LVL_TOTAL_NUM                   6

/* EasyLogger software version number */
#define ELOG_SW_VERSION                      "2.2.99"

#ifdef ELOG_OUTPUT_ENABLE

    #ifdef ELOG_FMT_USING_FUNC
    #define ELOG_OUTPUT_FUNC __FUNCTION__
    #else
    #define ELOG_OUTPUT_FUNC NULL
    #endif

    #ifdef ELOG_FMT_USING_DIR
    #define ELOG_OUTPUT_DIR __FILE__
    #else
    #define ELOG_OUTPUT_DIR NULL
    #endif

    #ifdef ELOG_FMT_USING_LINE
    #define ELOG_OUTPUT_LINE __LINE__
    #else
    #define ELOG_OUTPUT_LINE 0
    #endif

#endif

/* all formats index */
typedef enum {
    ELOG_FMT_LVL    = 1 << 0, /**< level */
    ELOG_FMT_TAG    = 1 << 1, /**< tag */
    ELOG_FMT_TIME   = 1 << 2, /**< current time */
    ELOG_FMT_P_INFO = 1 << 3, /**< process info */
    ELOG_FMT_T_INFO = 1 << 4, /**< thread info */
    ELOG_FMT_DIR    = 1 << 5, /**< file directory and name */
    ELOG_FMT_FUNC   = 1 << 6, /**< function name */
    ELOG_FMT_LINE   = 1 << 7, /**< line number */
} ElogFmtIndex;

/* macro definition for all formats */
#define ELOG_FMT_ALL    (ELOG_FMT_LVL|ELOG_FMT_TAG|ELOG_FMT_TIME|ELOG_FMT_P_INFO|ELOG_FMT_T_INFO| \
    ELOG_FMT_DIR|ELOG_FMT_FUNC|ELOG_FMT_LINE)

/* output log's tag filter */
typedef struct {
    uint8_t level;
    char tag[ELOG_FILTER_TAG_MAX_LEN + 1];
    bool tag_use_flag; /**< false : tag is no used   true: tag is used */
} ElogTagLvlFilter, *ElogTagLvlFilter_t;

/* output log's filter */
typedef struct {
    uint8_t level;
    char tag[ELOG_FILTER_TAG_MAX_LEN + 1];
    char keyword[ELOG_FILTER_KW_MAX_LEN + 1];
    ElogTagLvlFilter tag_lvl[ELOG_FILTER_TAG_LVL_MAX_NUM];
} ElogFilter, *ElogFilter_t;

/* easy logger */
typedef struct {
    ElogFilter filter;
    size_t enabled_fmt_set[ELOG_LVL_TOTAL_NUM];
    bool init_ok;
    bool output_enabled;
    bool output_lock_enabled;
    bool output_is_locked_before_enable;
    bool output_is_locked_before_disable;

#ifdef ELOG_COLOR_ENABLE
    bool text_color_enabled;
#endif

}EasyLogger, *EasyLogger_t;

/* EasyLogger error code */
typedef enum {
    ELOG_NO_ERR,
} ElogErrCode;

/*              +ELOG_COMMON_CONFIG+            */

#endif /* _ELOG_CFG_H_ */
