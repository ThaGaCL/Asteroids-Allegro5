#include "allegroAudio.h"

ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    sample_shot = al_load_sample("shot.flac");
    mustInit(sample_shot, "al_load_sample shot.flac");

    sample_explode[0] = al_load_sample("explode1.flac");
    mustInit(sample_explode[0], "al_load_sample explode1.flac");
    sample_explode[1] = al_load_sample("explode2.flac");
    mustInit(sample_explode[1], "al_load_sample explode2.flac");

}

void audio_deinit()
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}