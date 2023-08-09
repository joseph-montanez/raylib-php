// Load model animations from file
// RLAPI Model LoadModelFromMesh(Mesh mesh);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_LoadModelAnimations, 0, 2, IS_ARRAY, 0)
    ZEND_ARG_INFO(0, fileName)
    ZEND_ARG_TYPE_INFO(1, animCount, IS_LONG, 0)
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
        // Create the animation
        zend_object *modelAnimation = php_raylib_modelanimation_new_ex(php_raylib_modelanimation_ce, NULL);
        php_raylib_modelanimation_object *phpModelAnimation = php_raylib_modelanimation_fetch_object(modelAnimation);

        // Assign model animation to PHP object
        phpModelAnimation->modelanimation->type = RL_MODELANIMATION_IS_POINTER;
        phpModelAnimation->modelanimation->data.p = &anims[i];

        // Create sub-object BoneInfo
        for (int n = 0; n < anims[i].boneCount; n++) {
            zend_object *boneInfo = php_raylib_boneinfo_new_ex(php_raylib_boneinfo_ce, NULL);
            php_raylib_boneinfo_object *phpBoneInfo = php_raylib_boneinfo_fetch_object(boneInfo);
            phpBoneInfo->boneinfo->type = RL_BONEINFO_IS_POINTER;
            phpBoneInfo->boneinfo->data.p = &anims[i].bones[n];

            add_next_index_object(&phpModelAnimation->bones,  boneInfo);
        }

        // Create sub-object Transform
        for (int w = 0; w < anims[i].frameCount; w++) {
            zend_object *transform = php_raylib_transform_new_ex(php_raylib_transform_ce, NULL);
            php_raylib_transform_object *phpTransform = php_raylib_transform_fetch_object(transform);
            phpTransform->transform->type = RL_TRANSFORM_IS_POINTER;
            phpTransform->transform->data.p = anims[i].framePoses[w];

            add_next_index_object(&phpModelAnimation->frameposes,  transform);
        }

        // Push PHP object to array
        add_next_index_object(return_value,  &phpModelAnimation->std);
    }
}
