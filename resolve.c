#include "check.h"

/* 解析ip */
int get_ip(const char *domain, site_info info) {
    struct hostent *host_name;
    char *host_ip;

    if ((host_name = gethostbyname(domain)) == NULL) {
        fprintf(stderr, "gethostbyname失败\n");
        exit(1);
    }

    host_ip = inet_ntoa(*((struct in_addr *)host_name->h_addr));

    /* 比较ip */
    if (strcmp(host_ip, info->telecom_ip) == 0) {
        printf("您的本地域名解析到电信ip\t");
        info->net_flag = 0;
        return 0;
    } else if (strcmp(host_ip, info->unicom_ip) == 0) {
        printf("您的本地域名解析到联通ip\t");
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

    /* 组合域名 */
    sprintf(s_domain, "s%d%s", info->site_id, info->domain);
    sprintf(res_domain, "res%d%s", info->site_id, info->domain);
    sprintf(ass_domain, "assist%d%s", info->site_id, info->domain);

    /* s域名解析检查 */
    if (!(ip_flag = get_ip(s_domain, info))) {
        printf("s域名解析OK\n");
    } else {
        printf("s域名解析错误,请检查\n");
        s_flag = 0;
    }

    /* res域名解析检查 */
    if (!(ip_flag = get_ip(res_domain, info))) {
        printf("res域名解析OK\n");
    } else {
        printf("res域名解析错误,请检查\n");
        res_flag = 0;
    }

    /* ass域名解析检查 */
    if (!(ip_flag = get_ip(ass_domain, info))) {
        printf("ass域名解析OK\n");
    } else {
        printf("ass域名解析错误,请检查\n");
        ass_flag = 0;
    }

    if (s_flag && res_flag && ass_flag) {
        return 0;
    } else {
        return 1;
    }
}
