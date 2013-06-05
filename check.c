#include "check.h"

int main (int argc, char **argv) {
    /* windows socket �������� */
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

    /* ����site */
    printf("�������½�쳣����Ϸsite(eg. 37wan_0001): ");
    scanf("%s", site);

    /* site�����Ϣ */
    if (!(site_info = collect_info(site))) {
        printf("site��Ϣ��ѯʧ��,����\n");
        exit(1);
    }

    /* �������� */
    if ((resolve_flag = check_resolve(site_info))) {
        printf("��Ϸ��½�����3���������в��ֽ���������,����\n");
    }

    /* pingֵ���� */
    check_ping(site_info);
    
    /* windows socket �رճ��� */
    WSACleanup();
    
    return 0;
}
