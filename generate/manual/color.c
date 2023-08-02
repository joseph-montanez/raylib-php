ZEND_BEGIN_ARG_INFO_EX(arginfo_color_[colorName], 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(Color, [colorName])
{
    zval *obj = malloc(sizeof(zval));
    object_init_ex(obj, php_raylib_color_ce);

    php_raylib_color_object *result = Z_COLOR_OBJ_P(obj);
    result->color->data = (Color){[r], [g], [b], [a]};

    RETURN_OBJ(&result->std);
}
