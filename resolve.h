#ifndef CHECK_RESOLVE_h
#define CHECK_RESOLVE_h

/*
 * linux��socket��Ҫ���ļ� 
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
*/

#include "info.h"

/* ����������� */
int check_resolve(site_info);

/* ͨ�������õ�ip */
int get_ip(const char *, site_info);

#endif
