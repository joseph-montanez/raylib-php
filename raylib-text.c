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
#include "raylib-utils.h"
#include "raylib-text.h"
#include "raylib-color.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Text PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_text_object_handlers;

void php_raylib_text_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_text_object *intern = php_raylib_text_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_text_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_text_object *intern;
    intern = (php_raylib_text_object*) ecalloc(1, sizeof(php_raylib_text_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_text_object_handlers;

    return &intern->std;
}

// PHP object handling

PHP_METHOD(Text, __construct)
{
    php_raylib_text_object *intern = Z_TEXT_OBJ_P(ZEND_THIS);
}


//void DrawFPS(int posX, int posY)
PHP_METHOD(Text, drawFps)
{
    zend_long posX;
    zend_long posY;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
    ZEND_PARSE_PARAMETERS_END();

    DrawFPS(zend_long_2int(posX), zend_long_2int(posY));
}

//void DrawText(const char *text, int posX, int posY, int fontSize, Color color)
PHP_METHOD(Text, draw)
{
    zend_string *text;
    zend_long posX;
    zend_long posY;
    zend_long fontSize;
    zval *color;

    ZEND_PARSE_PARAMETERS_START(5, 5)
            Z_PARAM_STR(text)
            Z_PARAM_LONG(posX)
            Z_PARAM_LONG(posY)
            Z_PARAM_LONG(fontSize)
            Z_PARAM_ZVAL(color)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_color_object *phpColor = Z_COLOR_OBJ_P(color);

    DrawText(text->val, zend_long_2int(posX), zend_long_2int(posY), zend_long_2int(fontSize), phpColor->color);
}

//int MeasureText(const char *text, int fontSize)
PHP_METHOD(Text, measure)
{
    zend_string *text;
    zend_long fontSize;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_STR(text)
            Z_PARAM_LONG(fontSize)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(MeasureText(text->val, zend_long_2int(fontSize)));
}


const zend_function_entry php_raylib_text_methods[] = {
        PHP_ME(Text, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Text, drawFps, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Text, draw, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Text, measure, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// Extension class startup

void php_raylib_text_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Text", php_raylib_text_methods);
    php_raylib_text_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_text_ce->create_object = php_raylib_text_new;

    memcpy(&php_raylib_text_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_text_object_handlers.offset = XtOffsetOf(php_raylib_text_object, std);
    php_raylib_text_object_handlers.free_obj = &php_raylib_text_free_storage;
    php_raylib_text_object_handlers.clone_obj = NULL;
}
