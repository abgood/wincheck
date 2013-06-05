#include "check.h"

/* ��ѯ��� */
MYSQL_RES *mysql_result(MYSQL *conn, char *string) {
    MYSQL_RES *res;

    // ��ѯ���ݿ�
    if (mysql_query(conn,string))
    {
        fprintf(stderr, "��ѯʧ��\n");
        return NULL;
    }
    // ���ɽ����
    if (!(res=mysql_store_result(conn)))
    {
        fprintf(stderr, "���������ʧ��\n");
        return NULL;
    }

    return res;
}

/* site_id�Ƚ� */
int site_id_compare(char *id_token, int site_id) {
    char id_field_start_token[LEN_8] = {0};
    char *id_field_end_token;
    char *id_field;
    int id_start;
    int id_end;

    id_field = strstr(id_token, SITE_ID_FIELD);
    strncpy(id_field_start_token, id_token, id_field - id_token);
    id_field_end_token = id_field + 1;

    id_start = atoi(id_field_start_token);
    id_end = atoi(id_field_end_token);

    if ((site_id >= id_start) && (site_id <= id_end)) {
        return 1;
    } else {
        return 0;
    }
}

/* ��ѯsite_id��� */
int handle_site_id(site_info info, MYSQL_RES *site_name_result, int site_id) {
    char agent[LEN_64] = {0};
    MYSQL_ROW row;
    int info_cols;
    char *agent_start;
    char *agent_end;
    char id_field[LEN_32] = {0};
    char *id_token;
    int site_id_flag;
    char id_token_tmp[LEN_16];
    int master_id = 0;
    char *master_id_start;
    char *master_id_end;
    char master_id_tmp[LEN_16] = {0};

    info_cols = mysql_num_fields(site_name_result);
    while ((row = mysql_fetch_row(site_name_result))) {
        strncpy(agent, row[1], strlen(row[1]));

        // �ҳ�����id
        master_id_start = strstr(agent, "(");
        master_id_end = strstr(agent, "��");
        strncpy(master_id_tmp, master_id_start + 1, master_id_end - master_id_start - 1);
        master_id = atoi(master_id_tmp);

        // �ҳ�id��
        agent_start = strstr(agent, SITE_ID_START) + 1;
        agent_end = strstr(agent, "��");
        strncpy(id_field, agent_start, agent_end - agent_start);

        // id ������
        id_token = strtok(id_field, SITE_ID_DELIMITER);
        while (id_token) {
            memset(id_token_tmp, 0, LEN_16);
            strncpy(id_token_tmp, id_token, strlen(id_token));
            /* site_id�Ƚ� */
            site_id_flag = site_id_compare(id_token_tmp, site_id);

            /* site_id���� */
            if (site_id_flag == 1) {
                info->telecom_ip = (char *)calloc(LEN_16, sizeof(char));
                info->unicom_ip = (char *)calloc(LEN_16, sizeof(char));

                strncpy(info->telecom_ip, row[3], strlen(row[3]));
                strncpy(info->unicom_ip, row[4], strlen(row[3]));
                info->port = atoi(row[5]);
                info->resource = atoi(row[6]);
            }

            id_token = strtok(NULL, SITE_ID_DELIMITER);
        }
    }

    return master_id;
}

site_info collect_info(char *site) {
    MYSQL mysql, *conn;
    MYSQL_RES *site_name_result;
    MYSQL_RES *site_domain_result;
    MYSQL_ROW site_domain_row;
    char *site_name;
    char *site_id_tmp;
    char site_name_sql[LEN_1024] = {0};
    char site_domain_sql[LEN_1024] = {0};
    int site_id;
    int master_id;

    /* ��̬����site�����Ϣ�ڴ� */
    site_info info;
    if ((info = malloc(sizeof(struct info_list))) == NULL) {
        printf("info����̬�����ڴ����\n");
        exit(1);
    }

    /* ���ݿ���Ϣ */
    const char *ip = "192.168.56.101";
    const char *db_pawd = "123456";
    int port = 3306;

    /* ��ʱsite */
    char site_tmp[LEN_16] = {0};
    strncpy(site_tmp, site, strlen(site));

    /* ���site_name��site_id */
    site_name = strtok(site_tmp, SITE_DELIMITER);
    site_id_tmp = strtok(NULL, SITE_DELIMITER);
    site_id = atoi(site_id_tmp);

    /* ��ʼmysql����ṹ */
    mysql_init(&mysql);

    /* ����mysql */
    mysql_init(&mysql);
    if ((conn = mysql_real_connect(&mysql, ip, "root", db_pawd, "web_check", port, NULL, 0)) == NULL) {
        if (mysql_error(&mysql))
            fprintf(stderr, "connection error %d : %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        printf("Fail to connect mysql, ip:%s\tport:%d\n", ip, port);
        exit(1);
    }

    /* ��ѯsite_name��� */
    sprintf(site_name_sql, "select * from %s where site like \'%%%s%%\'", INDEPENDENT, site_name);
    site_name_result = mysql_result(conn, site_name_sql);

    /* ��ѯsite_id��� */
    master_id = handle_site_id(info, site_name_result, site_id);

    /* ��ѯdomain��� */
    sprintf(site_domain_sql, "select * from %s where site_name = \'%s\'", COMMON, site_name);
    site_domain_result = mysql_result(conn, site_domain_sql);
    while ((site_domain_row = mysql_fetch_row(site_domain_result))) {
        info->domain = (char *)calloc(LEN_16, sizeof(char));

        strncpy(info->domain, site_domain_row[2], strlen(site_domain_row[2]));

        /* �����Ƿ�� */
        if ((atoi(site_domain_row[4])) == 1) {
            info->site_id = site_id;
        } else {
            info->site_id = master_id;
        }
    }

    if ((info->telecom_ip == NULL) || (strlen(info->telecom_ip) == 0)) {
        printf("���������������,����!\n");
        exit(1);
    }

    return info;
}
