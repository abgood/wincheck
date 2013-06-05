#include "check.h"

/* ����ip */
int get_ip(const char *domain, site_info info) {
    struct hostent *host_name;
    char *host_ip;

    if ((host_name = gethostbyname(domain)) == NULL) {
        fprintf(stderr, "gethostbynameʧ��\n");
        exit(1);
    }

    host_ip = inet_ntoa(*((struct in_addr *)host_name->h_addr));

    /* �Ƚ�ip */
    if (strcmp(host_ip, info->telecom_ip) == 0) {
        printf("���ı�����������������ip\t");
        info->net_flag = 0;
        return 0;
    } else if (strcmp(host_ip, info->unicom_ip) == 0) {
        printf("���ı���������������ͨip\t");
        info->net_flag = 1;
        return 0;
    }

    return 1;
}

int check_resolve(site_info info) {
    char s_domain[LEN_32] = {0};
    char res_domain[LEN_32] = {0};
    char ass_domain[LEN_32] = {0};
    int ip_flag;
    int s_flag = 1;
    int res_flag = 1;
    int ass_flag = 1;

    /* ������� */
    sprintf(s_domain, "s%d%s", info->site_id, info->domain);
    sprintf(res_domain, "res%d%s", info->site_id, info->domain);
    sprintf(ass_domain, "assist%d%s", info->site_id, info->domain);

    /* s����������� */
    if (!(ip_flag = get_ip(s_domain, info))) {
        printf("s��������OK\n");
    } else {
        printf("s������������,����\n");
        s_flag = 0;
    }

    /* res����������� */
    if (!(ip_flag = get_ip(res_domain, info))) {
        printf("res��������OK\n");
    } else {
        printf("res������������,����\n");
        res_flag = 0;
    }

    /* ass����������� */
    if (!(ip_flag = get_ip(ass_domain, info))) {
        printf("ass��������OK\n");
    } else {
        printf("ass������������,����\n");
        ass_flag = 0;
    }

    if (s_flag && res_flag && ass_flag) {
        return 0;
    } else {
        return 1;
    }
}
