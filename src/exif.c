

#include <stdio.h>
#include <string.h>
#include <libexif/exif-data.h>
#include <ctype.h>
#include <glib.h>
#include <glib/gprintf.h>


static void trim_spaces(char *buf)
{
#if 0
    char *s = buf-1;
    for (; *buf; ++buf) {
        if (*buf != ' ')
            s = buf;
    }
    *++s = '\0'; 
#endif
    
    int i;


    for ( i = strlen(buf) - 1; i > 0; i-- ) {
        if ( isspace((unsigned char)buf[i])) {
            continue;
        } else {
            break;
        }
    }
    buf[++i] = '\0';

}


char *
show_tag(ExifData *d, ExifIfd ifd, ExifTag tag)
{
        char buf[1024];

	
    ExifEntry *entry = exif_content_get_entry(d->ifd[ifd],tag);
    if (entry) {

        
        exif_entry_get_value(entry, buf, sizeof(buf));

        
        trim_spaces(buf);
        if (*buf) {
            printf("%s: %s\n", exif_tag_get_name_in_ifd(tag,ifd), buf);
        }
    }
    return g_strdup(buf);
}


void show_mnote_tag(ExifData *d, unsigned tag)
{
    ExifMnoteData *mn = exif_data_get_mnote_data(d);
    if (mn) {
        int num = exif_mnote_data_count(mn);
        int i;

        
        for (i=0; i < num; ++i) {
            char buf[1024];
            if (exif_mnote_data_get_id(mn, i) == tag) {
                if (exif_mnote_data_get_value(mn, i, buf, sizeof(buf))) {
                    
                    trim_spaces(buf);
                    if (*buf) {
                        printf("%s: %s\n", exif_mnote_data_get_title(mn, i),
                            buf);
                    }
                }
            }
        }
    }
}

int maina(int argc, char **argv)
{
    ExifData *ed;
    ExifEntry *entry;

    if (argc < 2) {
        printf("Usage: %s image.jpg\n", argv[0]);
        printf("Displays tags potentially relating to ownership "
                "of the image.\n");
        return 1;
    }

    
    ed = exif_data_new_from_file(argv[1]);
    if (!ed) {
        printf("File not readable or no EXIF data in file %s\n", argv[1]);
        return 2;
    }

    
    show_tag(ed, EXIF_IFD_0, EXIF_TAG_ARTIST);
    show_tag(ed, EXIF_IFD_0, EXIF_TAG_XP_AUTHOR);
    show_tag(ed, EXIF_IFD_0, EXIF_TAG_COPYRIGHT);

    
    show_tag(ed, EXIF_IFD_EXIF, EXIF_TAG_USER_COMMENT);
    show_tag(ed, EXIF_IFD_0, EXIF_TAG_IMAGE_DESCRIPTION);
    show_tag(ed, EXIF_IFD_1, EXIF_TAG_IMAGE_DESCRIPTION);

    
    entry = exif_content_get_entry(ed->ifd[EXIF_IFD_0], EXIF_TAG_MAKE);
    if (entry) {
        char buf[64];

        
        if (exif_entry_get_value(entry, buf, sizeof(buf))) {
            trim_spaces(buf);

            if (!strcmp(buf, "Canon")) {
                show_mnote_tag(ed, 9); 

            } else if (!strcmp(buf, "Asahi Optical Co.,Ltd.") || 
                       !strcmp(buf, "PENTAX Corporation")) {
                show_mnote_tag(ed, 0x23); 
            }
        }
    }

    
    exif_data_unref(ed);

    return 0;
}
