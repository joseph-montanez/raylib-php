#include "php.h"
#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG
#define Rectangle RectangleWin
#define CloseWindow CloseWindowWin
#define ShowCursor ShowCursorWin
#define DrawTextA DrawTextAWin
#define DrawTextExA DrawTextExAWin
#define LoadImageA LoadImageAWin
#include "raylib.h"
#include "raylib-color.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Color PHP Custom Object
//------------------------------------------------------------------------------------------------------
/* {{{ ZE2 OO definitions */
zend_object_handlers php_raylib_color_object_handlers;

static HashTable php_raylib_color_prop_handlers;

typedef struct zval *(*raylib_color_read_color_from_ze_t)();

typedef struct _raylib_color_prop_handler {
    raylib_color_read_color_from_ze_t read_struct_color_func;
} raylib_color_prop_handler;
/* }}} */


static void php_raylib_color_register_prop_handler(HashTable *prop_handler, char *name, raylib_color_read_color_from_ze_t read_color_func) /* {{{ */
{
    raylib_color_prop_handler hnd;

    hnd.read_struct_color_func = read_color_func;
    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_color_prop_handler));

    /* Register for reflection */
    zend_declare_property_null(php_raylib_color_ce, name, strlen(name), ZEND_ACC_STATIC);
}
/* }}} */

static zval *php_raylib_color_property_reader(php_raylib_color_object *obj, raylib_color_prop_handler *hnd, zval *rv) /* {{{ */
{
    zval *retval;

    if (hnd->read_struct_color_func) {
        retval = hnd->read_struct_color_func();
//        if (retint == -1) {
//            php_error_docref(NULL, E_WARNING, "Internal raylib color error returned");
//            return NULL;
//        }
    }

    return retval;
}
/* }}} */

static zval *php_raylib_color_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_color_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_color_prop_handler *hnd = NULL;
    zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_COLOR_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd == NULL) {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static zval *php_raylib_color_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) /* {{{ */
{
    php_raylib_color_object *obj;
    zval tmp_member;
    zval *retval = NULL;
    raylib_color_prop_handler *hnd = NULL;
    zend_object_handlers *std_hnd;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_COLOR_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        retval = php_raylib_color_property_reader(obj, hnd, rv);
        if (retval == NULL) {
            retval = &EG(uninitialized_zval);
        }
    } else {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static int php_raylib_color_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    php_raylib_color_object *obj;
    zval tmp_member;
    raylib_color_prop_handler *hnd = NULL;
    zend_object_handlers *std_hnd;
    int retval = 0;

    if (Z_TYPE_P(member) != IS_STRING) {
        ZVAL_COPY(&tmp_member, member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
        cache_slot = NULL;
    }

    obj = Z_COLOR_OBJ_P(object);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
    }

    if (hnd != NULL) {
        zval tmp, *prop;

        if (type == 2) {
            retval = 1;
        } else if ((prop = php_raylib_color_property_reader(obj, hnd, &tmp)) != NULL) {
            if (type == 1) {
                retval = zend_is_true(&tmp);
            } else if (type == 0) {
                retval = (Z_TYPE(tmp) != IS_NULL);
            }
        }

        zval_ptr_dtor(&tmp);
    } else {
        std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->has_property(object, member, type, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}
/* }}} */

static HashTable *php_raylib_color_get_gc(zval *object, zval **gc_data, int *gc_data_count) /* {{{ */
{
    *gc_data = NULL;
    *gc_data_count = 0;
    return zend_std_get_properties(object);
}
/* }}} */

static HashTable *php_raylib_color_get_properties(zval *object)/* {{{ */
{
    php_raylib_color_object *obj;
    HashTable *props;
    raylib_color_prop_handler *hnd;
    zend_string *key;

    obj = Z_COLOR_OBJ_P(object);
    props = zend_std_get_properties(object);

    if (obj->prop_handler == NULL) {
        return NULL;
    }

    ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, key, hnd) {
                zval *ret, val;
                ret = php_raylib_color_property_reader(obj, hnd, &val);
                if (ret == NULL) {
                    ret = &EG(uninitialized_zval);
                }
                zend_hash_update(props, key, ret);
            } ZEND_HASH_FOREACH_END();

    return props;
}
/* }}} */

void php_raylib_color_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_color_object *intern = php_raylib_color_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_color_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_color_object *intern;
    intern = (php_raylib_color_object*) ecalloc(1, sizeof(php_raylib_color_object) + zend_object_properties_size(ce));
    intern->prop_handler = &php_raylib_color_prop_handlers;

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_color_object_handlers;

    return &intern->std;
}

zval *php_raylib_color_raywhite()
{
    zval *return_value;

    Color raywhite = RAYWHITE;

    array_init_size(return_value, 4);
    add_index_long(return_value, 0, raywhite.r);
    add_index_long(return_value, 1, raywhite.b);
    add_index_long(return_value, 2, raywhite.g);
    add_index_long(return_value, 3, raywhite.a);

    return return_value;
}

// PHP object handling

PHP_METHOD(Color, __construct)
{
    php_raylib_color_object *intern = Z_COLOR_OBJ_P(getThis());
}

const zend_function_entry php_raylib_color_methods[] = {
        PHP_ME(Color, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

static void php_raylib_color_free_prop_handler(zval *el) /* {{{ */ {
    pefree(Z_PTR_P(el), 1);
} /* }}} */

// Extension class startup

void php_raylib_color_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    //-- Object handlers
    memcpy(&php_raylib_color_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_color_object_handlers.offset = XtOffsetOf(php_raylib_color_object, std);
    php_raylib_color_object_handlers.free_obj = &php_raylib_color_free_storage;
    php_raylib_color_object_handlers.clone_obj = NULL;

    // Props
    php_raylib_color_object_handlers.get_property_ptr_ptr = php_raylib_color_get_property_ptr_ptr;
    php_raylib_color_object_handlers.get_gc         = php_raylib_color_get_gc;
    php_raylib_color_object_handlers.get_properties = php_raylib_color_get_properties;
    php_raylib_color_object_handlers.read_property	= php_raylib_color_read_property;
    php_raylib_color_object_handlers.has_property	= php_raylib_color_has_property;


    //-- Class Methods
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Image", php_raylib_color_methods);
    php_raylib_color_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_color_ce->create_object = php_raylib_color_new;

    zend_hash_init(&php_raylib_color_prop_handlers, 0, NULL, php_raylib_color_free_prop_handler, 1);
    php_raylib_color_register_prop_handler(&php_raylib_color_prop_handlers, "RAYWHITE", php_raylib_color_raywhite);

}

/**

    zend_hash_str_add_mem(prop_handler, name, strlen(name), &hnd, sizeof(raylib_color_prop_handler));

    /* Register for reflection */
//zend_declare_property_null(php_raylib_color_ce, name, strlen(name), ZEND_ACC_STATIC);