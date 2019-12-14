#include "../log.h" 
#include "../util.h" 
#include <alsa/asoundlib.h>
#include <math.h>
#include <stdio.h>

static const int is_unmuted(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel) {
    int muted;
    if (snd_mixer_selem_get_playback_switch(elem, channel, &muted) < 0) {
        error("unable to retrieve mute switch state");
        return -1;
    }
    return muted;
}

static const int get_volume(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t channel) {
    long min, max, value;
    double normalized;

    snd_mixer_selem_get_playback_dB_range(elem, &min, &max);
    snd_mixer_selem_get_playback_dB(elem, 0, &value);

    normalized = pow(10, (value - max) / 6000.0);

    return round(normalized * 100);
}


const int volume(char *buffer, const char *fmt) {
    snd_mixer_t *handle;
    snd_mixer_elem_t *elem;
    snd_mixer_selem_id_t *sid;

    static const char mix_name[] = "Master";
    static const char card[] = "default";
    static int mix_index = 0;

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, mix_index);
    snd_mixer_selem_id_set_name(sid, mix_name);

    if (snd_mixer_open(&handle, 1) < 0)
        return -1;
    if (snd_mixer_attach(handle, card) < 0) {
        snd_mixer_close(handle);
        return -2;
    }
    if (snd_mixer_selem_register(handle, NULL, NULL) < 0) {
        snd_mixer_close(handle);
        return -3;
    }
    if (snd_mixer_load(handle) < 0) {
        snd_mixer_close(handle);
        return -4;
    }
    elem = snd_mixer_find_selem(handle, sid);
    if (!elem) {
        snd_mixer_close(handle);
        return -5;
    }

    int vol = get_volume(elem, 0);
    int unmuted = is_unmuted(elem, 0);

    snd_mixer_close(handle);

    int len = 0;
    if (unmuted && vol > 66)
        len = util_snprintf(buffer, BUFFER_LEN, "墳");
    else if (unmuted && vol > 33)
        len = util_snprintf(buffer, BUFFER_LEN, "奔");
    else if (unmuted)
        len = util_snprintf(buffer, BUFFER_LEN, "奄");
    else
        len = util_snprintf(buffer, BUFFER_LEN, "ﱝ");
    
    util_snprintf(buffer + len, BUFFER_LEN - len, " %d%%", vol);

    return 0;
}
