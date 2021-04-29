static unsigned int process_FILE(FILE *file, song_t playlist[], unsigned int max_size) {
    unsigned int i = 0u;
    while (!feof(file)) {
        if(i <= max_size){
            unsigned int readed=0;
            process_string(file, SEPARATOR, playlist[i].song_name, MAX_NAME_LENGTH + 1u);
            process_string(file, SEPARATOR, playlist[i].artist_name, MAX_ARTIST_LENGTH + 1u);
            readed = fscanf(file, " %u  %u  ", &playlist[i].year, &playlist[i].seconds);
            if(readed != 2){
                fprintf(stderr, "Invalid array.\n");
                exit(EXIT_FAILURE);
            }
            ++i;
        }
        else{
            fprintf(stderr, "Array is too long!\n");
            exit(EXIT_FAILURE);
        }
    }
    return (i);
}

static unsigned int process_FILE(FILE *file, song_t playlist[], unsigned int max_size) {
    unsigned int i = 0u;
    while (!feof(file)) {
        unsigned int readed=0;
        process_string(file, SEPARATOR, playlist[i].song_name, MAX_NAME_LENGTH + 1u);
        process_string(file, SEPARATOR, playlist[i].artist_name, MAX_ARTIST_LENGTH + 1u);
        readed = fscanf(file, " %u  %u  ", &playlist[i].year, &playlist[i].seconds);
        ++i;
    }
    return (i);
}