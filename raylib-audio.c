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
#include "raylib-audio.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Audio PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_audio_object_handlers;

void php_raylib_audio_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_audio_object *intern = php_raylib_audio_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_audio_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_audio_object *intern;
    intern = (php_raylib_audio_object*) ecalloc(1, sizeof(php_raylib_audio_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_audio_object_handlers;

    return &intern->std;
}



// PHP object handling

PHP_METHOD(Audio, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_audio_object *intern = Z_AUDIO_OBJ_P(getThis());
}

PHP_METHOD(Audio, initDevice)
{
    InitAudioDevice();
}

PHP_METHOD(Audio, closeDevice)
{
    CloseAudioDevice();
}

PHP_METHOD(Audio, isDeviceReady)
{
    RETURN_BOOL(IsAudioDeviceReady());
}

PHP_METHOD(Audio, setMasterVolume)
{
    double volume;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(volume)
    ZEND_PARSE_PARAMETERS_END();

    SetMasterVolume((float) volume);
}


const zend_function_entry php_raylib_audio_methods[] = {
        PHP_ME(Audio, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Audio, initDevice, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Audio, closeDevice, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Audio, isDeviceReady, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Audio, setMasterVolume, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_audio_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Audio", php_raylib_audio_methods);
    php_raylib_audio_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_audio_ce->create_object = php_raylib_audio_new;

    memcpy(&php_raylib_audio_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_audio_object_handlers.offset = XtOffsetOf(php_raylib_audio_object, std);
    php_raylib_audio_object_handlers.free_obj = &php_raylib_audio_free_storage;
    php_raylib_audio_object_handlers.clone_obj = NULL;
}