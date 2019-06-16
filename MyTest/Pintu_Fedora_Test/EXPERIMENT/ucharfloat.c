#include<stdio.h>


main()
{
	unsigned char Zoom[] = {1, 1.2, 1.4, 1.6, 1.8, 2.0};
	unsigned char zoomvalue = 0;
	unsigned char zoomdriver = 0;

	printf("Enter the zoom value : ");
	scanf("%d",zoomvalue);

	zoomdriver = Zoom[zoomvalue - 1];
	printf("zoomdriver = %f\n",zoomdriver);
}


