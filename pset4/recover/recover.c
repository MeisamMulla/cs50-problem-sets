#include <stdio.h>
#include <stdlib.h>

// look in 512 byte chunks
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
        printf("Unable to open file\n");
        return 2;
    }

    // counter for the number of images found
    int images = 0;

    // pointer for the image file
    FILE *img = NULL;

    // filename for the new file
    char filename[8];

    // repeat until the end of file is reached
    while (!feof(fp))
    {
        // the buffer to store the block
        unsigned char buffer[BLOCK_SIZE];

        // get current block an write it to buffer
        int read = fread(buffer, BLOCK_SIZE, 1, fp);

        // is it a jpeg?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&  buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // we already have a file open so lets close it
            if (images > 0)
            {
                fclose(img);
            }

            // open the file
            sprintf(filename, "%03i.jpg", images);
            img = fopen(filename, "w");
            images++;
        }

        // lets write to the file if we have more than one image && if there was something read during fread
        if (images > 0 && read > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    fclose(fp);
}
