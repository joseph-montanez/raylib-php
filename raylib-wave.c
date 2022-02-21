/* If defined, the following flags inhibit definition of the indicated items.*/
#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // SM_*
#define NOMENUS           // MF_*
#define NOICONS           // IDI_*
#define NOKEYSTATES       // MK_*
#define NOSYSCOMMANDS     // SC_*
#define NORASTEROPS       // Binary and Tertiary raster ops
#define NOSHOWWINDOW      // SW_*
#define OEMRESOURCE       // OEM Resource values
#define NOATOM            // Atom Manager routines
#define NOCLIPBOARD       // Clipboard routines
#define NOCOLOR           // Screen colors
#define NOCTLMGR          // Control and Dialog routines
#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
/*#define NONLS             // All NLS defines and routines*/
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include "php.h"

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"
#include "raylib-wave.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Wave PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_wave_object_handlers;

void php_raylib_wave_free_storage(zend_object *object)
{
    php_raylib_wave_object *intern = php_raylib_wave_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_wave_new(zend_class_entry *ce)
{
    php_raylib_wave_object *intern;
    intern = (php_raylib_wave_object*) ecalloc(1, sizeof(php_raylib_wave_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_wave_object_handlers;

    return &intern->std;
}



// PHP object handling

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, fileName)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    intern->wave = LoadWave(fileName->val);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_getSampleCount, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, getSampleCount)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->wave.frameCount);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_setSampleCount, 0, 0, 1)
    ZEND_ARG_INFO(0, sampleCount)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, setSampleCount)
{
    zend_long sampleCount;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(sampleCount)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    intern->wave.frameCount = (unsigned int) sampleCount;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_getSampleRate, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, getSampleRate)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->wave.sampleRate);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_setSampleRate, 0, 0, 1)
    ZEND_ARG_INFO(0, sampleRate)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, setSampleRate)
{
    zend_long sampleRate;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(sampleRate)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    intern->wave.sampleRate = (unsigned int) sampleRate;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_getSampleSize, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, getSampleSize)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->wave.sampleSize);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_setSampleSize, 0, 0, 1)
    ZEND_ARG_INFO(0, sampleSize)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, setSampleSize)
{
    zend_long sampleSize;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(sampleSize)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    intern->wave.sampleSize = (unsigned int) sampleSize;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_getChannels, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, getChannels)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);
    RETURN_LONG(intern->wave.channels);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_setChannels, 0, 0, 1)
    ZEND_ARG_INFO(0, channels)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, setChannels)
{
    zend_long channels;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(channels)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    intern->wave.channels = (unsigned int) channels;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_getData, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, getData)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    zend_string *str = zend_string_init(intern->wave.data, sizeof(intern->wave.data)-1, 0);

    RETURN_STR(str);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_export, 0, 0, 1)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, export)
{
    zend_string *data;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    ExportWave(intern->wave, data->val);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_exportAsCode, 0, 0, 1)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, exportAsCode)
{
    zend_string *data;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    ExportWaveAsCode(intern->wave, data->val);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_setData, 0, 0, 1)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, setData)
{
    zend_string *data;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    intern->wave.data = data->val;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_crop, 0, 0, 2)
    ZEND_ARG_INFO(0, initSample)
    ZEND_ARG_INFO(0, finalSample)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, crop)
{
    zend_long initSample;
    zend_long finalSample;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(initSample)
        Z_PARAM_LONG(finalSample)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    WaveCrop(&intern->wave, (unsigned int) initSample, (unsigned int) finalSample);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_format, 0, 0, 3)
    ZEND_ARG_INFO(0, sampleRate)
    ZEND_ARG_INFO(0, sampleSize)
    ZEND_ARG_INFO(0, channels)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, format)
{
    zend_long sampleRate;
    zend_long sampleSize;
    zend_long channels;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(sampleRate)
        Z_PARAM_LONG(sampleSize)
        Z_PARAM_LONG(channels)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    WaveFormat(&intern->wave, (unsigned int) sampleRate, (unsigned int) sampleSize, (unsigned int) channels);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_getDataArray, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, getDataArray)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    float *data = LoadWaveSamples(intern->wave);

//    int dataLength = 0;
//    float **dataP = data;
//    while (*dataP++ != NULL) {
//        dataLength++;
//    }
    int dataLength = intern->wave.frameCount * intern->wave.channels;


    array_init_size(return_value, dataLength);

    for (int i = 0; i < dataLength; i++) {
        add_index_double(return_value, i, data[i]);
    }

//    return return_value;
}
ZEND_BEGIN_ARG_INFO_EX(arginfo_wave_copy, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Wave, copy)
{
    php_raylib_wave_object *intern = Z_WAVE_OBJ_P(ZEND_THIS);

    object_init_ex(return_value, php_raylib_wave_ce);

    zend_object *object = php_raylib_wave_new(php_raylib_wave_ce);

    php_raylib_wave_object *internWave = php_raylib_wave_fetch_object(object);

    internWave->wave = WaveCopy(intern->wave);

    ZVAL_OBJ(return_value, object);
}


const zend_function_entry php_raylib_wave_methods[] = {
        PHP_ME(Wave, __construct   , arginfo_wave__construct, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, getSampleRate , arginfo_wave_getSampleRate, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, setSampleRate , arginfo_wave_setSampleRate, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, getSampleCount, arginfo_wave_getSampleCount, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, setSampleCount, arginfo_wave_setSampleCount, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, getSampleSize , arginfo_wave_getSampleSize, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, setSampleSize , arginfo_wave_setSampleSize, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, getChannels   , arginfo_wave_getChannels, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, setChannels   , arginfo_wave_setChannels, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, getData       , arginfo_wave_getData, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, setData       , arginfo_wave_setData, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, export        , arginfo_wave_export, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, exportAsCode  , arginfo_wave_exportAsCode, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, crop          , arginfo_wave_crop, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, format        , arginfo_wave_format, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, getDataArray  , arginfo_wave_getDataArray, ZEND_ACC_PUBLIC)
        PHP_ME(Wave, copy          , arginfo_wave_copy, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_wave_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Wave", php_raylib_wave_methods);
    php_raylib_wave_ce = zend_register_internal_class(&ce);
    php_raylib_wave_ce->create_object = php_raylib_wave_new;

    memcpy(&php_raylib_wave_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_wave_object_handlers.offset = XtOffsetOf(php_raylib_wave_object, std);
    php_raylib_wave_object_handlers.free_obj = &php_raylib_wave_free_storage;
    php_raylib_wave_object_handlers.clone_obj = NULL;
}