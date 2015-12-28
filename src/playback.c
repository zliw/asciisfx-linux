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

uint32_t play_buffer_on_pcm_handle(struct Buffer buffer,
                                   snd_pcm_t *pcm_handle,
                                   snd_pcm_uframes_t frame_size);


uint32_t play(struct Buffer buffer) {
    uint32_t alsa_device;
    int err;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;

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


    snd_pcm_uframes_t frame_size;
    if (err = snd_pcm_hw_params_get_period_size(params, &frame_size, 0) < 0) {
        fprintf(stderr, "ERROR: Can't determine frame size for current parameters. %s\n", snd_strerror(err));
        return 0;
    }

    uint32_t result = play_buffer_on_pcm_handle(buffer, pcm_handle, frame_size);

  	snd_pcm_drain(pcm_handle);
  	snd_pcm_close(pcm_handle);

    return result;
}

uint32_t play_buffer_on_pcm_handle(struct Buffer buffer,
                                   snd_pcm_t *pcm_handle,
                                   snd_pcm_uframes_t frame_size) {
    uint32_t left = buffer.length;
    uint32_t position;
    int err;

    fprintf(stdout, "playback with frame size %ld\n", frame_size);

  	for (position = 0; position < buffer.length; position += frame_size, left -= buffer.length) {
  	    void *buffer_start = &buffer.data[position];
  	    uint32_t size = (left < frame_size) ? left : frame_size;

    		while (err = snd_pcm_writen(pcm_handle, &buffer_start, size) == -EPIPE) {
	  		    snd_pcm_prepare(pcm_handle);
	  	  }
	  	  if (err < 0) {
	    	  	fprintf(stderr, "ERROR. Can't write to PCM device. %s\n", snd_strerror(err));
	    	  	return 0;
	    	}
  	}
    return 1;
}
