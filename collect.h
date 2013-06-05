#ifndef CHECK_COLLECT_H
#define CHECK_COLLECT_H

#include <mysql/mysql.h>
#include "info.h"

/* 收集site相关信息 */
site_info collect_info(char *);

/* 查询结果 */
MYSQL_RES *mysql_result(MYSQL *, char *);

/* site_id比较 */
int site_id_compare(char *, int);

/* 查询site_id结果,获取主id */
int handle_site_id(site_info, MYSQL_RES *, int);

#endif
