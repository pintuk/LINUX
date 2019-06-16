#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#define MAX_ORDER	11

struct free_area {
	unsigned long nr_free;
};

struct zone {
	struct free_area free_area[MAX_ORDER];	
};

static int measure_fragmentation_level(struct zone *zone, unsigned long totalfreepages, int order)
{
        unsigned long nr_freepages = 0;
        unsigned long highorderpages = 0;
        int level = 0;
        int o = 0;

        for(o=order; o<MAX_ORDER; o++) {
                nr_freepages = zone->free_area[o].nr_free;
                highorderpages += (1 << o)*nr_freepages;
        }
        level = ((totalfreepages - highorderpages)*100)/totalfreepages;

        return level;
}


int main()
{
	int order = 0;
	unsigned long totalfreepages = 0;
	unsigned long freepages = 0;
        unsigned long movablepages = 0;
        unsigned long reclaimablepages = 0;
        unsigned int fraglevel = 0;
	struct zone zone;
	char s = ' ';

	printf("Enter total free pages : ");
	scanf("%lu",&totalfreepages);
	totalfreepages = 0;
	printf("Enter the free pages in each order:\n");
	for(order=0; order<MAX_ORDER; order++) {
		scanf("%lu",&zone.free_area[order].nr_free);
		freepages = zone.free_area[order].nr_free;
		totalfreepages += (1 << order) * freepages;
	}
	printf("Total Free Pages = %lu\n",totalfreepages);
	//printf("Order%12c FreePages%12c MovablePages%12c ReclaimablePages%12c Fragmentation[%%]\n",s,s,s,s,s);
	printf("Order\t FreePages\t MovablePages\t ReclaimablePages\t Fragmentation[%%]\n");
	for(order=0; order<MAX_ORDER; order++) {
		freepages = zone.free_area[order].nr_free;
		fraglevel = measure_fragmentation_level(&zone,totalfreepages,order);
		//printf("%3d %18lu %25lu %25lu %25d\n",order,freepages,movablepages,reclaimablepages,fraglevel);
		printf("%3d %10lu %16lu %17lu %25d%%\n",order,freepages,movablepages,reclaimablepages,fraglevel);
	}

	return 0;
}

