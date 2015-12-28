#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define PCM_DEVICE "default"
#define RATE 44100

struct Buffer {
  uint32_t length;
  float *data;
};

int play(struct Buffer buffer) {
    unsigned int alsa_device;
    unsigned int err;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frame_size;

	  /* Open the PCM device in playback mode */
	  if (alsa_device =  (&pcm_handle, PCM_DEVICE,
                          					 SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        fprintf(stderr, "ERROR: Can't open \"%s\" PCM device: %s\n",
	              				PCM_DEVICE, snd_strerror(alsa_device));
        return 0;
    }

    if (err = snd_pcm_hw_params_malloc (&params)) {
        fprintf(stderr, "ERROR: Can't allocate hardware parameters PCM device: %s\n",
	              			 	 snd_strerror(err));
        return 0;
    }

    if (err = snd_pcm_hw_params_set_access(pcm_handle, params,
                                 					 SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
	   	  fprintf(stderr, "ERROR: Can't interleaved set mode. %s\n", snd_strerror(err));
        return 0;
    }

	  if (err = snd_pcm_hw_params_set_format(pcm_handle, params,
	                               					 SND_PCM_FORMAT_FLOAT) < 0) {
    		fprintf(stderr, "ERROR: Can't set float format. %s\n", snd_strerror(err));
    		return 0;
  	}

    if (err = snd_pcm_hw_params_set_channels(pcm_handle, params, 1) < 0) {
    		fprintf(stderr, "ERROR: Can't set mono format. %s\n", snd_strerror(err));
    		return 0;
    }


    int rate = RATE;

    if (err = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0) < 0) {
    		fprintf(stderr, "ERROR: Can't set rate. %s\n", snd_strerror(err));
    		return 0;
    }

  	if (err = snd_pcm_hw_params(pcm_handle, params) < 0) {
    		fprintf(stderr, "ERROR: Can't set hardware parameters. %s\n", snd_strerror(err));
        return 0;
  	}

    if (err = snd_pcm_hw_params_get_period_size(params, &frame_size, 0) < 0) {
        fprintf(stderr, "ERROR: Can't determine frame size for current parameters. %s\n", snd_strerror(err));
        return 0;
    }

    fprintf(stdout, "playback with frame size %ld", frame_size);


    return 1;
}
