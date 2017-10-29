
CC := $(CROSS_COMPILE)gcc

INCLUDEDIR := -I../../../../../drivers/staging/android/uapi/

CCFLAGS := $(INCLUDEDIR) -Wall -O2 -g

all: ionapp_export ionapp_import

ionapp_import : ionapp_import.c
	$(CC) -o ionapp_import ionapp_import.c ipcsocket.c ionutils.c $(CCFLAGS)

ionapp_export : ionapp_export
	$(CC) -o ionapp_export ionapp_export.c ipcsocket.c ionutils.c $(CCFLAGS)

clean:
	rm -rf *.o *~ ionapp_export ionapp_import
