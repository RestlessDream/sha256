#include "sha256.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

uint64_t BUFFER_SIZE;
extern size_t byte_size;
extern sha_config sha_256;
extern sha_config * sha;

int parse_arguments(int argc, char ** argv, FILE ** input, size_t * file_size);

int main(int argc, char ** argv) {
    FILE * input;
    size_t file_size;
    
    if (parse_arguments(argc, argv, &input, &file_size) != 0) {
        return 1;
    }

    setup(&sha_256);
    BUFFER_SIZE = (file_size/sha->block_bsize + 1)*sha->block_bsize;
    byte * rbuffer = malloc(BUFFER_SIZE * sizeof(byte));
    byte * wbuffer = malloc(sha->message_diggest_bsize + 1);

    size_t reads;
    size_t read_blocks;

    if ((reads = fread(rbuffer, sizeof(byte), BUFFER_SIZE, input)) != 0) {
        read_blocks = reads / sha->block_bsize;

        if (reads % sha->block_bsize != 0) {
            pad_block((word *)(rbuffer + read_blocks * sha->block_bsize), reads * byte_size);
            read_blocks++;
        }

        hash((word *)rbuffer, read_blocks, (word *)wbuffer); 

        for (int i = 0; i < sha->message_diggest_bsize; i++) {
            if (fprintf(stdout, "%02x", wbuffer[i]) == 0) {
                fprintf(stderr, "Error occured while writting to the output.");
                return -1;
            }
        }
    } else {
        fprintf(stderr, "Error occured while reading the file.");
    }

    fprintf(stdout, "\n");

    free(rbuffer);
    free(wbuffer);
    fclose(input);

    return 0;
}

int parse_arguments(int argc, char ** argv, FILE ** input, size_t * file_size) {
    int option;
    if (argc >= 2) {
        *input = fopen(argv[1], "r");
        fseek(*input, 0L, SEEK_END);
        *file_size = ftell(*input);
        fseek(*input, 0L, SEEK_SET);
    }

    while ((option = getopt(argc, argv, "h")) != -1) {
        switch (option) {
            case 'h':
                printf("Usage:  sha256 file_path\n\n\
SHA-256 standart decryption\\encyption.\n\
Options:\n\
  -h    display this help.\n");

                return 1;
        }
    }

    return 0;
}
