# ����ѡ��
CC = gcc
CFLAGS = -g -O2 -Wall

# ��
# LIBDL = -ldl
# LIBSSL = -lssl
# ��̬�⶯̬����
# DYNAM = -rdynamic
LIBMYSQL = `mysql_config --libs`

# ������Ŀ¼
# DIRS = modules

# ִ���ļ�
TARGET = check

# ���е�c�ļ�����o�ļ�
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ��������.c��β���ļ��ŵ��б���
SOURCES = $(wildcard *.c)
# ƥ��sources�б�������.c�ļ��滻��.o�ļ��ŵ��б���
OBJS = $(patsubst %.c,%.o,$(SOURCES))

# ����ִ���ļ�
$(TARGET):$(OBJS)
#	make -C $(DIRS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBDL) $(DYNAM) $(LIBMYSQL) $(LIBSSL)
	chmod u+x $(TARGET)

# ɾ��.o�ļ���ִ���ļ�
clean:
	rm $(OBJS) $(TARGET) -f
#	cd $(DIRS); make clean; cd ..
