// Load model animations from file
// RLAPI Model LoadModelFromMesh(Mesh mesh);
ZEND_BEGIN_ARG_INFO_EX(arginfo_LoadModelAnimations, 0, 1, 2)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_INFO(1, animCount)
ZEND_END_ARG_INFO()
PHP_FUNCTION(LoadModelAnimations)
{
    zend_string *fileName;
    zval *zAnimsCount = NULL;
    unsigned int i;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STR(fileName)
    Z_PARAM_ZVAL(zAnimsCount)
    ZEND_PARSE_PARAMETERS_END();

    unsigned int animsCount = 0;
    ModelAnimation *anims = LoadModelAnimations(fileName->val, &animsCount);

    php_printf("animsCount: %d\n", animsCount);

    // Set output variable animsCount
    if (zAnimsCount) {
        ZEND_TRY_ASSIGN_REF_LONG(zAnimsCount, animsCount);
    }

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    // Create a PHP array with the default size of the animation count
    array_init_size(return_value, animsCount);

    for (i = 0; i < animsCount; i++) {
        zend_object *modelAnimation = php_raylib_modelanimation_new_ex(php_raylib_modelanimation_ce, NULL);
        php_raylib_modelanimation_object *phpModelAnimation = php_raylib_modelanimation_fetch_object(modelAnimation);
        // Assign model animation to PHP object
        *php_raylib_modelanimation_fetch_data(phpModelAnimation) = anims[i];

        // Push PHP object to array
        add_next_index_object(return_value,  &phpModelAnimation->std);
    }
}
