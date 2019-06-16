#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum sys_node_id {
        SYS_VM_SHRINK_MEMORY,
        SYS_VM_COMPACT_MEMORY,
};

/*
 * Here,
 * @path is /proc/sys/vm/{shrink,compact}_memory
 * @value is always 1
 */
struct sys_node_table {
        enum sys_node_id sys_node_id;
        const char *path;
        int value;
};


static const struct sys_node_table sys_node_tables[] = {
        { SYS_VM_SHRINK_MEMORY, "/proc/sys/vm/shrink_memory", 1 },
        { SYS_VM_COMPACT_MEMORY, "/proc/sys/vm/compact_memory", 1 },
        { },
};

int proc_sys_node_trigger(enum sys_node_id sys_node_id)
{
        FILE *fp = NULL;

	if (sys_node_tables[sys_node_id].path == NULL) {
		printf("Path is Null...\n");
		return -1;
	}
        /* open and check if the path exists, else return fail */
        fp = fopen(sys_node_tables[sys_node_id].path, "w");
        if (fp == NULL) {
                printf("Failed to open: %s: %s\n",
                        sys_node_tables[sys_node_id].path, strerror(errno));
                return -1;
        }
        fputc(sys_node_tables[sys_node_id].value, fp);
        fclose(fp);
        return 0;
}


int main()
{
	int n=0;

	n = sizeof(sys_node_tables)/sizeof(sys_node_tables[0]);
	printf("Max size: %d\n", n);	

	proc_sys_node_trigger(3);

	return 0;
}
