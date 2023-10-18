#pragma once

#include "picopass_listener.h"
#include <nfc/helpers/iso13239_crc.h>

#include <optimized_ikeys.h>
#include <optimized_cipher.h>

#define TAG "PicopassListener"

#define PICOPASS_LISTENER_BUFFER_SIZE_MAX (255)

typedef enum {
    PicopassListenerStateIdle,
    PicopassListenerStateHalt,
    PicopassListenerStateActive,
    PicopassListenerStateSelected,
} PicopassListenerState;

struct PicopassListener {
    Nfc* nfc;
    PicopassData* data;
    PicopassListenerState state;

    LoclassState_t cipher_state;
    PicopassListenerMode mode;

    BitBuffer* tx_buffer;
    BitBuffer* tmp_buffer;
    uint8_t key_block_num;

    PicopassListenerEvent event;
    PicopassListenerEventData event_data;
    PicopassListenerCallback callback;
    void* context;
};

void picopass_listener_init_cipher_state_key(PicopassListener* instance, const uint8_t* key);

void picopass_listener_init_cipher_state(PicopassListener* instance);

PicopassError picopass_listener_send_frame(PicopassListener* instance, BitBuffer* tx_buffer);

PicopassError picopass_listener_write_anticoll_csn(PicopassListener* instance, BitBuffer* buffer);
