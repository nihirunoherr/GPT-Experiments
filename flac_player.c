#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FLAC/stream_decoder.h>
#include <ao/ao.h>

#define BUFFER_SIZE 4096

typedef struct {
    ao_device *device;
    ao_sample_format format;
} AudioData;

FLAC__StreamDecoderWriteStatus write_callback(
    const FLAC__StreamDecoder *decoder,
    const FLAC__Frame *frame,
    const FLAC__int32 *const buffer[],
    void *client_data) {
    AudioData *audio = (AudioData *)client_data;
    int samples = frame->header.blocksize;
    int channels = audio->format.channels;
    int sample_size = audio->format.bits / 8;
    int buffer_size = samples * channels * sample_size;
    unsigned char *output_buffer = (unsigned char *)malloc(buffer_size);

    for (int i = 0; i < samples; i++) {
        for (int j = 0; j < channels; j++) {
            int32_t sample = buffer[j][i];
            for (int k = 0; k < sample_size; k++) {
                output_buffer[i * channels * sample_size + j * sample_size + k] = (sample >> (8 * k)) & 0xff;
            }
        }
    }

    ao_play(audio->device, (char *)output_buffer, buffer_size);
    free(output_buffer);
    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data) {
    fprintf(stderr, "Error: %s\n", FLAC__StreamDecoderErrorStatusString[status]);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <flac file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
    AudioData audio;
    FLAC__StreamDecoderInitStatus init_status;

    ao_initialize();
    audio.format.bits = 16; // Default to 16 bits per sample
    audio.format.rate = 44100; // Default sample rate
    audio.format.channels = 2; // Default to stereo
    audio.format.byte_format = AO_FMT_NATIVE;
    audio.format.matrix = 0;
    audio.device = ao_open_live(ao_default_driver_id(), &audio.format, NULL);

    init_status = FLAC__stream_decoder_init_file(decoder, filename, write_callback, NULL, error_callback, &audio);
    if (init_status != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        fprintf(stderr, "Error initializing decoder: %s\n", FLAC__StreamDecoderInitStatusString[init_status]);
        FLAC__stream_decoder_delete(decoder);
        return 1;
    }

    if (!FLAC__stream_decoder_process_until_end_of_stream(decoder)) {
        fprintf(stderr, "Error decoding FLAC file\n");
    }

    FLAC__stream_decoder_finish(decoder);
    FLAC__stream_decoder_delete(decoder);
    ao_close(audio.device);
    ao_shutdown();

    return 0;
}
