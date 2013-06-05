#include "check.h"

int main (int argc, char **argv) {
    /* windows socket 启动程序 */
    int status;
    WSADATA wsd;
    if((status=WSAStartup(MAKEWORD(2,2),&wsd))!=0)
    {
        perror( "wsastartup()   failed: ");
        exit(1);
    }
    
    char site[LEN_16] = {0};
    site_info site_info;
    int resolve_flag;

    /* 输入site */
    printf("请输入登陆异常的游戏site(eg. 37wan_0001): ");
    scanf("%s", site);

    /* site相关信息 */
    if (!(site_info = collect_info(site))) {
        printf("site信息查询失败,请检查\n");
        exit(1);
    }

    /* 域名解析 */
    if ((resolve_flag = check_resolve(site_info))) {
        printf("游戏登陆所需的3个域名中有部分解析有问题,请检查\n");
    }

    /* ping值计算 */
    check_ping(site_info);
    
    /* windows socket 关闭程序 */
    WSACleanup();
    
    return 0;
}
