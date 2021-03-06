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
#include "raylib-camera3d.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Camera PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_camera3d_object_handlers;

void php_raylib_camera3d_free_storage(zend_object *object)
{
    php_raylib_camera3d_object *intern = php_raylib_camera3d_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_camera3d_new(zend_class_entry *ce)
{
    php_raylib_camera3d_object *intern;
    intern = (php_raylib_camera3d_object*) ecalloc(1, sizeof(php_raylib_camera3d_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_camera3d_object_handlers;

    return &intern->std;
}

//static void php_raylib_camera3d_register_prop_handler(HashTable *prop_handler, char *name, zip_read_int_t read_int_func, zip_read_const_char_t read_char_func, zip_read_const_char_from_ze_t read_char_from_obj_func, int rettype) /* {{{ */
//{
//    php_raylib_camera3d_object_handlers hnd;
//
//    hnd.read_const_char_func = read_char_func;
//    hnd.read_int_func = read_int_func;
//    hnd.read_const_char_from_obj_func = read_char_from_obj_func;
//    hnd.type = rettype;
//    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(php_raylib_camera3d_object_handlers));
//
//    /* Register for reflection */
//    zend_declare_property_null(zip_class_entry, name, strlen(name), ZEND_ACC_PUBLIC);
//}
///* }}} */

PHP_METHOD(Camera, __construct)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    intern->camera3d = (Camera) {
            .position = (Vector3) {.x = 0, .y = 0, .z = 0},
            .target = (Vector3) {.x = 0, .y = 0, .z = 0},
            .up = (Vector3) {.x = 0, .y = 0, .z = 0},
            .fovy = 0.4f,
            .type = CAMERA_PERSPECTIVE
    };
}

PHP_METHOD(Camera, getPosition)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    array_init(return_value);
    add_assoc_double(return_value, "x", (double) intern->camera3d.position.x);
    add_assoc_double(return_value, "y", (double) intern->camera3d.position.y);
    add_assoc_double(return_value, "z", (double) intern->camera3d.position.y);
}

PHP_METHOD(Camera, setPosition)
{
    php_raylib_camera3d_object *intern = Z_CAMERA3D_OBJ_P(ZEND_THIS);

    zval *positionArr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(positionArr)
    ZEND_PARSE_PARAMETERS_END();

    intern->camera3d.position = php_array_to_vector3(positionArr);

    UpdateCamera(&intern->camera3d);
}

const zend_function_entry php_raylib_camera3d_methods[] = {
        PHP_ME(Camera, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera, getPosition, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Camera, setPosition, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

void php_raylib_camera3d_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Camera3d", php_raylib_camera3d_methods);
    php_raylib_camera3d_ce = zend_register_internal_class(&ce);
    php_raylib_camera3d_ce->create_object = php_raylib_camera3d_new;

    memcpy(&php_raylib_camera3d_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_camera3d_object_handlers.offset = XtOffsetOf(php_raylib_camera3d_object, std);
    php_raylib_camera3d_object_handlers.free_obj = &php_raylib_camera3d_free_storage;
    php_raylib_camera3d_object_handlers.clone_obj = NULL;
}