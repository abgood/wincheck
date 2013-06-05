#ifndef CHECK_COLLECT_H
#define CHECK_COLLECT_H

#include <mysql/mysql.h>
#include "info.h"

/* �ռ�site�����Ϣ */
site_info collect_info(char *);

/* ��ѯ��� */
MYSQL_RES *mysql_result(MYSQL *, char *);

/* site_id�Ƚ� */
int site_id_compare(char *, int);

/* ��ѯsite_id���,��ȡ��id */
int handle_site_id(site_info, MYSQL_RES *, int);

#endif
