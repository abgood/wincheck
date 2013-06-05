#ifndef CHECK_INFO
#define CHECK_INFO

/* site相关信息 */
typedef struct info_list {
    char *telecom_ip;       /* 电信ip */
    char *unicom_ip;        /* 联通ip */
    char *domain;           /* 域名后半段 */
    int port;               /* 游戏端口 */
    int site_id;            /* 游戏id */
    int resource;           /* res本地资源域名, cdn域名 */
    int net_flag;           /* 玩家本地网络解析标志, 电信为0, 联通为1 */
} *site_info;

#endif
