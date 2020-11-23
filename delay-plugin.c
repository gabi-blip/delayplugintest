#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#define PLUGIN_URI "http://moddevices.com/plugins/mod-devel/delay-plugin"


typedef enum {
    INPUT       = 0,
    OUTPUT      = 1,
    DELAY_TIME  = 2,
    FEEDBACK    = 3
} PortIndex;

typedef struct {
    float* input;
    float* output;
    float* delay_time;
    float* feedback;
} Delay;


static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
        double                    rate,
        const char*               bundle_path,
        const LV2_Feature* const* features)
{
    Delay* self = (Delay*)malloc(sizeof(Delay));

    return (LV2_Handle)self;
}


static void
connect_port(LV2_Handle instance,
        uint32_t   port,
        void*      data)
{
    Delay* self = (Delay*)instance;

    switch ((PortIndex)port) {
        case INPUT:
            self->input = (float*)data;
            break;
        case OUTPUT:
            self->output = (float*)data;
            break;
        case DELAY_TIME:
            self->delay_time = (float*)data;
            break;
        case FEEDBACK:
            self->feedback = (float*)data;
            break;
    }
}


static void
activate(LV2_Handle instance)
{
}


static void
run(LV2_Handle instance, uint32_t n_samples)
{
    Delay* self = (Delay*) instance;

    for ( uint32_t i = 0; i < n_samples; i++)
    {
        self->output[i] = self->input[i];
    }
}


static void
deactivate(LV2_Handle instance)
{
}


static void
cleanup(LV2_Handle instance)
{
    free(instance);
}


static const void*
extension_data(const char* uri)
{
    return NULL;
}


static const LV2_Descriptor descriptor = {
    PLUGIN_URI,
    instantiate,
    connect_port,
    activate,
    run,
    deactivate,
    cleanup,
    extension_data
};


LV2_SYMBOL_EXPORT
    const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index) {
        case 0:  return &descriptor;
        default: return NULL;
    }
}
