/* ������Ϣ */
create table indepe_info (
    `Id` int(20) NOT NULL AUTO_INCREMENT primary key COMMENT '���',
    name varchar(100) not null default '',
    site varchar(20) not null default '',
    telecom_ip varchar(20) not null default '',
    unicom_ip varchar(20) not null default '',
    port integer not null default 0         -- 0�Ǵ�5000��ʼ,1�Ǵ�5004��ʼ
    resoure integer not null default 0      -- 0��res������Դ����,1��cdn����
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/* ��ͬ��Ϣ */
create table common_info (
    `Id` int(20) NOT NULL AUTO_INCREMENT primary key COMMENT '���',
    site_name varchar(15) not null default '',
    domain varchar(30) not null default '',
    bind boolean not null default 0         -- 0��Ϊ������,1�ǰ�����
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
